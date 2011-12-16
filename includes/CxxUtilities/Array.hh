/*
 * Array.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_ARRAY_HH_
#define CXXUTILITIES_ARRAY_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

/**
 * A class which provides utility functions related to array and vector.
 */

template<class T>
class Array: public std::vector<T> {
public:
	/** Joins number elements of an array (vector) into a string.
	 *  @param data array (vector) to be joined.
	 *  @param dec (for decimal; e.g. 123) or hex (for hexagonal; e.g. 0xAB).
	 *  @param maxBytesToBeDumped the maximum number of elements to be actually joined (for long array).
	 *  @return joined string.
	 */
	static std::string toString(std::vector<T>& data, std::string mode = "dec", int maxBytesToBeDumped = 8) {
		return toString(&data, mode, maxBytesToBeDumped);
	}

	/** Joins number elements of an array (vector) into a string.
	 *  @param data array (vector) to be joined.
	 *  @param dec (for decimal; e.g. 123) or hex (for hexagonal; e.g. 0xAB).
	 *  @param maxBytesToBeDumped the maximum number of elements to be actually joined (for long array).
	 *  @return joined string.
	 */
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
				ss << hex << "0x" << setw(2) << setfill('0') << right << (uint32_t)data->at(i);
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
	/** Splits a string into an array.
	 * @param str a string to be split.
	 * @param delimitter a character or a word used as a delimitter.
	 * @return a newly create array instance.
	 */
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

	/** Splits a string into an array.
	 * @param str a string to be split.
	 * @param delimitter a character or a word used as a delimitter.
	 * @return pointer to a newly created Array instance.
	 */
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

	/** Splits a string into an array.
	 * @param str a string to be split.
	 * @param delimitter a character or a word used as a delimitter.
	 * @return pointer to a newly created Array instance.
	 */
	static Array<std::string>* arrayBySplittingString(std::string str, std::string delimitter) {
		return newBySplittingString(str, delimitter);
	}
};

}
#endif /* CXXUTILITIES_ARRAY_HH_ */
