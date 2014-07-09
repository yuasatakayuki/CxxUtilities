/*
 * Logger.hh
 *
 *  Created on: Jun 15, 2012
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_LOGGER_HH_
#define CXXUTILITIES_LOGGER_HH_

#include "CommonHeader.hh"
#include "Time.hh"

namespace CxxUtilities {

class Log {
public:
	std::vector<std::string> logText;
	std::vector<std::string> logDateTime;
	std::string id;

public:
	Log(std::string& id) {
		this->id = id;
	}

public:
	void add(std::string line) {
		logText.push_back(line);
		logDateTime.push_back(Time::getCurrentTimeAsString());
	}

public:
	size_t getNLines() {
		return logText.size();
	}

public:
	void clear() {
		logText.clear();
	}

public:
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

public:
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
	static bool dumpToFile;
	static std::ofstream outputFileStream;
	static bool recordAll;

	static std::string color;
	static std::string colorDefault;

public:
	Logger_() {
	}

public:
	~Logger_() {

	}

public:
	static void enableDumpToFile(std::string filename) {
		if (outputFileStream.is_open()) {
			outputFileStream.close();
		}
		outputFileStream.open(filename.c_str());
		dumpToFile = true;
	}

public:
	static void disableDumpToFile() {
		dumpToFile = false;
		if (outputFileStream.is_open()) {
			outputFileStream.close();
		}
	}

public:
	static void enableDumpAll() {
		dumpAll = true;
	}

public:
	static void disableDumpAll() {
		dumpAll = false;
	}

public:
	static void enableRecordAll() {
		recordAll = true;
	}

public:
	static void disableRecordAll() {
		recordAll = false;
	}

public:
	enum Color {
		DefaultColor, Red, Cyan, Magenta
	};

public:
	static void add(std::string logBookID, std::string line, Color color=DefaultColor) {
		using namespace std;
		mutex.lock();

		//record
		if (recordAll) {
			std::map<std::string, Log*>::iterator it = logs.find(logBookID);
			if (it != logs.end()) {
				it->second->add(line);
			} else {
				logs[logBookID] = new Log(logBookID);
			}
			allLogDateTime.push_back(Time::getCurrentTimeAsString());
			allLogText.push_back(line);
			allLogLogBookID.push_back(logBookID);
		}

		//dump to screen
		if (dumpAll) {
			std::string colorString;
			switch(color){
			case Cyan:
				colorString = "\x1b[36m";//cyan
				break;
			case Red:
				colorString= "\x1b[31m";//red color
				break;
			case Magenta:
				colorString = "\x1b[35m";//magenta color
				break;
			default:
				colorString= colorDefault;
				break;
			}
			cout << Time::getCurrentTimeAsString() << " " << logBookID << ": " << colorString << line << colorDefault << endl;
		}

		if (dumpToFile) {
			outputFileStream << Time::getCurrentTimeAsString() << " " << logBookID << ": " << line << endl;
		}

		mutex.unlock();
	}

public:
	static void addWarning(std::string logBookID, std::string line) {
		line = "Warning: " + line;
		add(logBookID, line, Cyan);
	}

public:
	static void addError(std::string logBookID, std::string line) {
		line = "Error: " + line;
		add(logBookID, line, Red);
	}

public:
	static void addMagenta(std::string logBookID, std::string line) {
		add(logBookID, line, Magenta);
	}

public:
	static Log* getLogBook(std::string logBookID) {
		std::map<std::string, Log*>::iterator it = logs.find(logBookID);
		if (it != logs.end()) {
			return it->second;
		} else {
			logs[logBookID] = new Log(logBookID);
			return logs[logBookID];
		}
	}

public:
	static bool saveToFolder(std::string folderName) {
		try {
			Directory::create("", folderName);
			std::map<std::string, Log*>::iterator it = logs.begin();
			for (; it != logs.end(); it++) {
				try {
					it->second->saveToFile(folderName + "/" + it->first + ".log");
				} catch (...) {
					return false;
				}
			}
			saveAllLogToFile(folderName + "/" + "AllLog.text");
			return true;
		} catch (...) {
			return false;
		}
		//should not reach here
		return false;
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
template<typename T> bool Logger_<T>::dumpAll = true;
template<typename T> bool Logger_<T>::dumpToFile = false;
template<typename T> std::ofstream Logger_<T>::outputFileStream;
template<typename T> bool Logger_<T>::recordAll = false;

template<typename T> std::string Logger_<T>::color;
template<typename T> std::string Logger_<T>::colorDefault("\x1b[39m");

typedef Logger_<int> Logger;

}

#endif /* CXXUTILITIES_LOGGER_HH_ */
