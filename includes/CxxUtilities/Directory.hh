/*
 * Directory.hh
 *
 *  Created on: Jun 15, 2012
 *      Author: yuasa
 */

#ifndef DIRECTORY_HH_
#define DIRECTORY_HH_

#include "CommonHeader.hh"

#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

namespace CxxUtilities {

class DirectoryException: public CxxUtilities::Exception {
public:
	enum {
		PermissionDenied,
		TooManyDescriptors,
		TooManyFilesAreOpened,
		DoesNotExist,
		NotEnoughMemory,
		NotADirectory,
		UndefinedError
	};

public:
	DirectoryException(int status) :
			CxxUtilities::Exception(status) {
	}

	virtual ~DirectoryException() {
	}

	std::string toString() {
		switch (status) {
		case PermissionDenied:
			return "PermissionDenied";
			break;
		case TooManyDescriptors:
			return "TooManyDescriptors";
			break;
		case TooManyFilesAreOpened:
			return "TooManyFilesAreOpened";
			break;
		case DoesNotExist:
			return "DoesNotExist";
			break;
		case NotEnoughMemory:
			return "NotEnoughMemory";
			break;
		case NotADirectory:
			return "NotADirectory";
			break;
		case UndefinedError:
			return "UndefinedError";
			break;
		}
		return "";
	}
};

class Directory {
public:
	static bool exists(std::string directory) throw (DirectoryException) {
		try {
			return accessible(directory);
		} catch (DirectoryException& e) {
			if (e.getStatus() == DirectoryException::PermissionDenied) {
				return true;
			} else {
				return false;
			}
		}
	}

	static bool accessible(std::string directory) throw (DirectoryException) {
		DIR *dir;
		if ((dir = opendir(directory.c_str())) == NULL) {
			switch(errno) {
				case EACCES :
				throw DirectoryException(DirectoryException::PermissionDenied);
				break;

				case EMFILE :
				throw DirectoryException(DirectoryException::TooManyDescriptors);
				break;

				case ENFILE :
				throw DirectoryException(DirectoryException::TooManyFilesAreOpened);
				break;

				case ENOENT :
				throw DirectoryException(DirectoryException::DoesNotExist);
				break;

				case ENOMEM :
				throw DirectoryException(DirectoryException::NotEnoughMemory);
				break;

				case ENOTDIR :
				throw DirectoryException(DirectoryException::NotADirectory);
				break;

				default :
				throw DirectoryException(DirectoryException::UndefinedError);
				break;
			}
			return false;
		} else {
			::close((uint64_t)dir);
			return true;
		}
	}

	static void create(std::string baseDirectory, std::string createdDirectoryName) {

		if(baseDirectory==""){
			baseDirectory="./";
		}
		DIR* dir = opendir(baseDirectory.c_str());
		if (dir == NULL) {
			mkdir(baseDirectory.c_str(), 0777);
		} else {
			closedir(dir);
		}

		std::vector<std::string> folders=String::split(createdDirectoryName,"/");

		for (size_t i = 0; i<folders.size(); i++) {
			baseDirectory = baseDirectory + "/" + folders[i];
			DIR* dir = opendir(baseDirectory.c_str());
			if (dir == NULL) {
				mkdir(baseDirectory.c_str(), 0777);
				return;
			}
			closedir(dir);
		}
	}
};

}

#endif /* DIRECTORY_HH_ */
