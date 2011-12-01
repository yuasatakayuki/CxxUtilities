/*
 * File.hh
 *
 *  Created on: Jun 13, 2011
 *      Author: yuasa
 */

#ifndef FILE_HH_
#define FILE_HH_

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/String.hh"

namespace CxxUtilities {

/** A class which provides file-related utility functions.
 * Reading all lines in a text file, checking if a file exists,
 * getting a full path to the current directory, and so on are
 * possible with this class.
 */
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
	/** Checks existence of a file.
	 * @param filename file name.
	 */
	static bool exists(std::string filename) {
		using namespace std;
		vector<string> lines;
		ifstream ifs(filename.c_str());
		if (!ifs.is_open()) {
			ifs.close();
			return false;
		} else {
			return true;
		}
	}

public:
	/** Returns a vector which contains all lines in a specified text file.
	 * @param filename file to be loaded.
	 * @return a vector which contains all lines in the specified text file.
	 */
	static std::vector<std::string> getAllLines(std::string filename) throw (FileException) {
		using namespace std;
		vector<string> lines;
		std::ifstream ifs(filename.c_str());
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
	/** Returns a string which contains all lines in a specified text file.
	 * @param filename file to be loaded.
	 * @return a string which contains all lines in the specified text file.
	 */
	static std::string getAllLinesAsString(std::string filename) throw (FileException) {
		using namespace std;
		stringstream ss;
		std::ifstream ifs(filename.c_str());
		if (!ifs.is_open()) {
			throw FileException(FileException::FileNotFound);
		}
		while (!ifs.eof()) {
			string line;
			getline(ifs, line);
			ss << line;
		}
		return ss.str();
	}

public:
	/** Reads a white-space-separated text file into a map.
	 * This method assumes a file containing e.g.:<br/>
	 * Keyword1 Value1<br/>
	 * Keyword2 Value2<br/>
	 * Keyword3 Value3
	 * @param filename file name.
	 * @return map containing the key-value pairs in the file.
	 */
	static std::map<std::string, std::string> readLinesAsMap(std::string filnemae) throw (FileException) {
		using namespace std;
		map<string, string> result;
		vector<string> lines = getAllLines(filnemae);
		for (unsigned int i = 0; i < lines.size(); i++) {
			vector<string> array = String::split(lines[i], " ");
			if (array.size() >= 2) {
				result[array[0]] = array[1];
			}
		}
		return result;
	}

public:
	/** Returns the current working directory as a string.
	 */
	static std::string getCurrentWorkingDirectory() {
		const unsigned int MaximumFilenameLength = 10 * 1024;
		char* buffer = new char[MaximumFilenameLength];
		getcwd(buffer, MaximumFilenameLength);
		std::string path(buffer);
		delete buffer;
		return path;
	}

public:
	/** Converts a relative path to an absolute path.
	 * @param relativePath a relative path to be converted.
	 * @return an absolute path.
	 */
	static std::string toFullPath(std::string relativePath) throw (FileException) {
		if (File::exists(relativePath) == false) {
			throw FileException(FileException::FileNotFound);
		}
		std::string path = File::getCurrentWorkingDirectory() + "/" + relativePath;
		return path;
	}

	/** Converts a relative path to an absolute path.
	 * @param relativePath a relative path to be converted.
	 * @return an absolute path.
	 */
	static std::string toAbsolutePath(std::string relativePath) throw (FileException) {
		return toFullPath(relativePath);
	}

	/** Converts a relative path to an absolute path.
	 * @param relativePath a relative path to be converted.
	 * @return an absolute path.
	 */
	static std::string getFullPath(std::string relativePath) throw (FileException) {
		return toFullPath(relativePath);
	}

	/** Converts a relative path to an absolute path.
	 * @param relativePath a relative path to be converted.
	 * @return an absolute path.
	 */
	static std::string getAbsolutePath(std::string relativePath) throw (FileException) {
		return toFullPath(relativePath);
	}
};

}
#endif /* FILE_HH_ */
