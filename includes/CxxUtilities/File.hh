/*
 * File.hh
 *
 *  Created on: Jun 13, 2011
 *      Author: yuasa
 */

#ifndef FILE_HH_
#define FILE_HH_

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>

#include <unistd.h>
#include <sys/param.h>

#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/String.hh"

namespace CxxUtilities {

class File {
public:
	class FileException: public Exception {
	public:
		enum {
			FileNotFound
		};
	public:
		FileException(unsigned int status) :
			Exception(status) {
		}
	};

public:
	static bool exists(std::string filename) {
		using namespace std;
		vector < string > lines;
		ifstream ifs(filename.c_str());
		if (!ifs.is_open()) {
			ifs.close();
			return false;
		} else {
			return true;
		}
	}

public:
	static std::vector<std::string> getAllLines(std::string filename) throw (FileException) {
		using namespace std;
		vector < string > lines;
		ifstream ifs(filename.c_str());
		if (!ifs.is_open()) {
			throw FileException(FileException::FileNotFound);
		}
		while (!ifs.eof()) {
			string line;
			getline(ifs, line);
			lines.push_back(line);
		}
		return lines;
	}

public:
	static std::map<std::string, std::string> readLinesAsMap(std::string filnemae) throw (FileException) {
		using namespace std;
		map < string, string > result;
		vector < string > lines = getAllLines(filnemae);
		for (unsigned int i = 0; i < lines.size(); i++) {
			vector < string > array = String::split(lines[i], " ");
			result[array[0]] = array[1];
		}
		return result;
	}

public:
	static std::string getCurrentWorkingDirectory() {
		const unsigned int MaximumFilenameLength=10*1024;
		char* buffer=new char[MaximumFilenameLength];
		getcwd(buffer,MaximumFilenameLength);
		std::string path(buffer);
		delete buffer;
		return path;
	}

public:
	static std::string toFullPath(std::string relativePath) throw (FileException){
		if(File::exists(relativePath)==false){
			throw FileException(FileException::FileNotFound);
		}
		std::string path=File::getCurrentWorkingDirectory()+relativePath;
		return path;
	}

	static std::string toAbsolutePath(std::string relativePath) throw (FileException){
		return toFullPath(relativePath);
	}

	static std::string getFullPath(std::string relativePath) throw (FileException){
		return toFullPath(relativePath);
	}

	static std::string getAbsolutePath(std::string relativePath) throw (FileException){
		return toFullPath(relativePath);
	}
};

}
#endif /* FILE_HH_ */
