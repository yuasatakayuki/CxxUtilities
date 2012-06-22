/*
 * String.hh
 *
 *  Created on: Jun 7, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_STRING_HH_
#define CXXUTILITIES_STRING_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

namespace CCTYPE {
#include <ctype.h>
}

class String {
public:
	static int toInteger(char* str) {
		return toInteger(std::string(str));
	}

	static int toInteger(const char* str) {
		return toInteger(std::string(str));
	}

	static int toInteger(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		int avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static uint8_t toUInt8(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint32_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return (uint8_t) avalue;
	}

	static uint32_t toUInt32(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint32_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static uint64_t toUInt64(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint64_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static std::vector<int> toIntegerArray(std::string str) {
		using namespace std;
		vector<int> result;
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			result.push_back(String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned int> toUnsignedIntegerArray(std::string str) {
		using namespace std;
		vector<unsigned int> result;
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			result.push_back((unsigned int) String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned char> toUnsignedCharArray(std::string str) {
		using namespace std;
		vector<unsigned char> result;
		str = String::replace(str, "\n", "");
		str = String::replace(str, "\r", "");
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			if (stringArray[i].size() > 2 && stringArray[i][0] == '0' && (stringArray[i][1] == 'x' || stringArray[i][1]
					== 'X')) {
				string element = String::replace(String::toLowerCase(stringArray[i]), "0x", "");
				size_t elementLength = element.size();
				uint32_t avalue = 0;
				size_t o = 0;
				bool firstByte = true;

				while (o < element.size()) {
					std::stringstream ss;
					if (firstByte) {
						if (elementLength % 2 == 0) {//even number
							ss << "0x" << element.substr(o, 2);
							o += 2;
						} else {//odd number
							ss << "0x" << element.substr(o, 1);
							o++;
						}
						firstByte = false;
					} else {
						//read two characters
						ss << "0x" << element.substr(o, 2);
						o += 2;
					}
					ss >> hex >> avalue;
					result.push_back((uint8_t) avalue);
				}
			} else {
				unsigned char avalue = (unsigned char) String::toUInt32(stringArray[i]);
				result.push_back(avalue);
			}
		}
		return result;
	}

	static std::vector<uint8_t> toUInt8Array(std::string str) {
		using namespace std;
		vector<unsigned char> result;
		str = String::replace(str, "\n", "");
		str = String::replace(str, "\r", "");
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			if (stringArray[i].size() > 2 && stringArray[i][0] == '0' && (stringArray[i][1] == 'x' || stringArray[i][1]
					== 'X')) {
				string element = String::replace(String::toLowerCase(stringArray[i]), "0x", "");
				size_t elementLength = element.size();
				uint32_t avalue = 0;
				size_t o = 0;
				bool firstByte = true;

				while (o < element.size()) {
					std::stringstream ss;
					if (firstByte) {
						if (elementLength % 2 == 0) {//even number
							ss << "0x" << element.substr(o, 2);
							o += 2;
						} else {//odd number
							ss << "0x" << element.substr(o, 1);
							o++;
						}
						firstByte = false;
					} else {
						//read two characters
						ss << "0x" << element.substr(o, 2);
						o += 2;
					}
					ss >> hex >> avalue;
					result.push_back((uint8_t) avalue);
				}
			} else {
				uint8_t uint8_value = (uint8_t) String::toUInt32(stringArray[i]);
				result.push_back(uint8_value);
			}
		}
		return result;
	}

	static double toDouble(char* str) {
		return toDouble(std::string(str));
	}

	static double toDouble(const char* str) {
		return toDouble(std::string(str));
	}

	static double toDouble(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		double avalue = 0;
		ss >> avalue;
		return avalue;
	}

	static std::vector<std::string> split(std::string str, std::string delimitter) {
		std::vector<std::string> result;
		size_t n = 0;
		for (size_t i = 0; i <= str.length(); i = n + 1) {
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

	static std::vector<std::string> splitIntoLines(std::string str) {
		using namespace std;
		stringstream ss;
		std::vector<std::string> result;
		ss << str;
		while (!ss.eof()) {
			string line;
			getline(ss, line);
			result.push_back(line);
		}
		return result;
	}

	static std::string replace(std::string str, std::string find_what, std::string replace_with) {
		std::string::size_type pos = 0;
		while ((pos = str.find(find_what, pos)) != std::string::npos) {
			str.erase(pos, find_what.length());
			str.insert(pos, replace_with);
			pos += replace_with.length();
		}
		return str;
	}

	static std::string join(std::vector<std::string> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << list[i];
			} else {
				ss << list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::vector<std::string> getRangeOf(std::vector<std::string>& list, int from, int to) {
		std::vector<std::string> newlist;
		size_t size = list.size();
		if (from < 0) {
			from = size + from;
		}
		if (to < 0) {
			to = size + to;
		}
		if (from < 0 || to < 0) {
			return newlist;
		}
		if (size <= (unsigned int)from || size <= (unsigned int)to) {
			return newlist;
		}
		if (from <= to) {
			for (size_t i = (unsigned int)from; i <= (unsigned int)to; i++) {
				newlist.push_back(list[i]);
			}
		} else {
			for (size_t i = (unsigned int)to; i <= (unsigned int)from; i++) {
				newlist.push_back(list[i]);
			}
		}
		return newlist;
	}

	static std::string dumpAddress(void* address, unsigned int width = 4) {
		std::stringstream ss;
		ss << "0x" << std::setw(width) << std::setfill('0') << std::hex << (long long) address;
		return ss.str();
	}

	static bool contains(std::string str1, std::string str2) {
		std::string::size_type index = str1.find(str2.c_str(), 0);
		if (index != std::string::npos) {
			return true;
		} else {
			return false;
		}
	}

	static std::string toLowerCase(std::string str) {
		using namespace std;
		for (size_t i = 0; i < str.size(); i++) {
			if ('A' <= str[i] && str[i] <= 'Z') {
				str[i] = str[i] - 'A' + 'a';
			}
		}
		return str;
	}

	static std::string toUpperCase(std::string str) {
		using namespace std;
		for (size_t i = 0; i < str.size(); i++) {
			if ('a' <= str[i] && str[i] <= 'z') {
				str[i] = str[i] - 'a' + 'A';
			}
		}
		return str;
	}

	static std::string toStringFromInteger(int avalue) {
		std::stringstream ss;
		ss << avalue;
		return ss.str();
	}

	static std::string toStringFromDouble(double avalue, unsigned int precision = 3) {
		std::stringstream ss;
		ss << std::setprecision(precision) << avalue;
		return ss.str();
	}

	static std::string toHexString(unsigned int avalue, unsigned int width = 2, std::string prefix = "0x") {
		using namespace std;
		stringstream ss;
		ss << prefix << setw(width) << setfill('0') << right << hex << avalue << dec;
		return ss.str();
	}

	static bool includes(std::string str, std::string searched_str) {
		if (str.find(searched_str) == std::string::npos) {
			return false;
		} else {
			return true;
		}
	}

	static size_t indexOf(std::string str, std::string searched_str) {
		size_t result = str.find(searched_str);
		if (result == std::string::npos) {
			return std::string::npos;
		} else {
			return result;
		}
	}

public:
	static std::string put0xForAllElements(std::string str) {
		using namespace std;
		vector<string> array = String::split(str, " ");
		for (size_t i = 0; i < array.size(); i++) {
			string element = array[i];
			if (element[0] != '0' || !(element[1] == 'x' || element[1] == 'X')) {
				element = String::replace(element, " ", "");
				array[i] = "0x" + element;
			}
		}
		return String::join(array, " ");
	}
};
}

#endif /* CXXUTILITIES_STRING_HH_ */
