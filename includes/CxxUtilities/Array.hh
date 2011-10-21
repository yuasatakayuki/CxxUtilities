/*
 * Array.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef ARRAY_HH_
#define ARRAY_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

template<class T>
class Array: public std::vector<T> {
public:
	static std::string toString(std::vector<T>& data, std::string mode = "dec", int maxBytesToBeDumped = 8) {
		return toString(&data, mode, maxBytesToBeDumped);
	}

	static std::string toString(std::vector<T>* data, std::string mode = "dec", int maxBytesToBeDumped = 8) {
		using namespace std;
		stringstream ss;
		int maxSize;
		if (data->size() < maxBytesToBeDumped) {
			maxSize = data->size();
		} else {
			maxSize = maxBytesToBeDumped;
		}
		for (int i = 0; i < maxSize; i++) {
			if (mode == "dec") {
				ss << dec << left << data->at(i);
			} else if (mode == "hex") {
				ss << hex << "0x" << setw(2) << setfill('0') << right << data->at(i);
			} else {
				ss << data->at(i);
			}
			if (i != maxSize - 1) {
				ss << " ";
			}
		}
		ss << dec;
		if (maxSize < data->size()) {
			ss << " ... (total size = " << dec << data->size();
			if (data->size() == 1) {
				ss << " entry)";
			} else {
				ss << " entries)";
			}
		}
		return ss.str();
	}

public:
	static Array<std::string> splitString(std::string str, std::string delimitter) {
		Array<std::string> result;
		int n;
		for (int i = 0; i <= str.length(); i = n + 1) {
			n = str.find_first_of(delimitter, i);
			if (n == std::string::npos) {
				n = str.length();
			}
			std::string element = str.substr(i, n - i);
			if (element != "") {
				result.push_back(element);
			}
		}
		return result;
	}

	static Array<std::string>* newBySplittingString(std::string str, std::string delimitter) {
		Array<std::string>* result=new Array<std::string>;
		int n;
		for (int i = 0; i <= str.length(); i = n + 1) {
			n = str.find_first_of(delimitter, i);
			if (n == std::string::npos) {
				n = str.length();
			}
			std::string element = str.substr(i, n - i);
			if (element != "") {
				result->push_back(element);
			}
		}
		return result;
	}

	static Array<std::string>* arrayBySplittingString(std::string str, std::string delimitter) {
		return newBySplittingString(str, delimitter);
	}
};

}
#endif /* ARRAY_HH_ */
