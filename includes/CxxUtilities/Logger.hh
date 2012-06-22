/*
 * Logger.hh
 *
 *  Created on: Jun 15, 2012
 *      Author: yuasa
 */

#ifndef LOGGER_HH_
#define LOGGER_HH_

#include "CommonHeader.hh"
#include "Time.hh"

namespace CxxUtilities {

class Log {
public:
	std::vector<std::string> logText;
	std::vector<std::string> logDateTime;
	std::string id;

public:
	Log(std::string id) {
		this->id = id;
	}

public:
	void add(std::string line) {
		logText.push_back(line);
		logDateTime.push_back(Time::getCurrentTimeAsString());
	}

	size_t getNLines() {
		return logText.size();
	}

	void clear() {
		logText.clear();
	}

	void saveToFile(std::string filename) {
		using namespace std;
		ofstream ofs(filename.c_str());
		if (!ofs.is_open()) {
			return;
		}
		for (size_t i = 0; i < logText.size(); i++) {
			ofs << logDateTime[i] << " " << logText[i] << endl;
		}
		ofs.close();
	}

	void saveToFile() {
		saveToFile(id);
	}
};

template<typename T>
class Logger_ {
private:
	static std::map<std::string, Log*> logs;
	static std::vector<std::string> allLogText;
	static std::vector<std::string> allLogLogBookID;
	static std::vector<std::string> allLogDateTime;
	static Mutex mutex;
	static bool dumpAll;

public:
	Logger_() {
	}

	~Logger_() {

	}

public:
	static void enableDumpAll(){
		dumpAll=true;
	}

	static void disableDumpAll(){
		dumpAll=false;
	}



public:
	static void add(std::string logBookID, std::string line) {
		mutex.lock();
		std::map<std::string, Log*>::iterator it = logs.find(logBookID);
		if (it != logs.end()) {
			it->second->add(line);
		} else {
			logs[logBookID] = new Log(logBookID);
		}
		allLogDateTime.push_back(Time::getCurrentTimeAsString());
		allLogText.push_back(line);
		allLogLogBookID.push_back(logBookID);

		if(dumpAll){
			using namespace std;
			cout << Time::getCurrentTimeAsString() << " " << logBookID << ": " << line << endl;
		}

		mutex.unlock();
	}

	static Log* getLogBook(std::string logBookID) {
		std::map<std::string, Log*>::iterator it = logs.find(logBookID);
		if (it != logs.end()) {
			return it->second;
		} else {
			logs[logBookID] = new Log(logBookID);
			return logs[logBookID];
		}
	}

	static bool saveToFolder(std::string folderName) {
		try {
			Directory::create("", folderName);
			std::map<std::string, Log*>::iterator it = logs.begin();
			for (; it != logs.end(); it++) {
				try {
					it->second->saveToFile(folderName + "/" + it->first+".log");
				} catch (...) {
					return false;
				}
			}
			saveAllLogToFile(folderName+"/"+"AllLog.text");
			return true;
		} catch (...) {
			return false;
		}

	}

private:
	static void saveAllLogToFile(std::string filename) {
		using namespace std;
		ofstream ofs(filename.c_str());
		if (!ofs.is_open()) {
			return;
		}
		for (size_t i = 0; i < allLogText.size(); i++) {
			ofs << allLogDateTime[i] << " " << allLogLogBookID[i] << ": " << allLogText[i] << endl;
		}
		ofs.close();
	}

};

template<typename T> std::map<std::string, Log*> Logger_<T>::logs;
template<typename T> std::vector<std::string> Logger_<T>::allLogText;
template<typename T> std::vector<std::string> Logger_<T>::allLogLogBookID;
template<typename T> std::vector<std::string> Logger_<T>::allLogDateTime;
template<typename T> Mutex Logger_<T>::mutex;
template<typename T> bool Logger_<T>::dumpAll=false;

typedef Logger_<int> Logger;

}

#endif /* LOGGER_HH_ */
