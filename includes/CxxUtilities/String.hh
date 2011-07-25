/*
 * String.hh
 *
 *  Created on: Jun 7, 2011
 *      Author: yuasa
 */

#ifndef STRING_HH_
#define STRING_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities{

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
		int avalue;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static std::vector<int> toIntegerArray(std::string str){
		using namespace std;
		vector<int> result;
		vector<string> stringArray=String::split(str," ");
		for(unsigned int i=0;i<stringArray.size();i++){
			result.push_back(String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned int> toUnsignedIntegerArray(std::string str){
		using namespace std;
		vector<unsigned int> result;
		vector<string> stringArray=String::split(str," ");
		for(unsigned int i=0;i<stringArray.size();i++){
			result.push_back((unsigned int)String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned char> toUnsignedCharArray(std::string str){
		using namespace std;
		vector<unsigned char> result;
		vector<string> stringArray=String::split(str," ");
		for(unsigned int i=0;i<stringArray.size();i++){
			result.push_back((unsigned char)String::toInteger(stringArray[i]));
		}
		return result;
	}

	static double toDouble(char* str) {
		toDouble(std::string(str));
	}

	static double toDouble(const char* str) {
		toDouble(std::string(str));
	}

	static double toDouble(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		double avalue;
		ss >> avalue;
		return avalue;
	}

	static std::vector<std::string> split(std::string str, std::string delimitter) {
		std::vector < std::string > result;
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
		int size = list.size();
		for (int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << list[i];
			} else {
				ss << list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::vector<std::string> getRangeOf(std::vector<std::string>& list, int from, int to) {
		std::vector < std::string > newlist;
		int size = list.size();
		if (from < 0) {
			from = size + from;
		}
		if (to < 0) {
			to = size + to;
		}
		if (from < 0 || to < 0) {
			return newlist;
		}
		if (size <= from || size <= to) {
			return newlist;
		}
		if (from <= to) {
			for (int i = from; i <= to; i++) {
				newlist.push_back(list[i]);
			}
		} else {
			for (int i = to; i <= from; i++) {
				newlist.push_back(list[i]);
			}
		}
		return newlist;
	}

	static std::string dumpAddress(void* address,unsigned int width=4) {
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
		for(unsigned int i=0;i<str.size();i++){
			if('A'<=str[i] && str[i]<='Z'){
				str[i]=str[i]-'A'+'a';
			}
		}
		return str;
	}

	static std::string toUpperCase(std::string str) {
		using namespace std;
		for(unsigned int i=0;i<str.size();i++){
			if('a'<=str[i] && str[i]<='z'){
				str[i]=str[i]-'a'+'A';
			}
		}
		return str;
	}

	static std::string toStringFromInteger(int avalue){
		std::stringstream ss;
		ss << avalue;
		return ss.str();
	}

	static std::string toStringFromDouble(double avalue,unsigned int precision=3){
		std::stringstream ss;
		ss << std::setprecision(precision) << avalue;
		return ss.str();
	}

	static std::string toHexString(unsigned int avalue,unsigned int width=2,std::string prefix="0x"){
		using namespace std;
		stringstream ss;
		ss << prefix << setw(width) << setfill('0') << right << hex << avalue << dec;
		return ss.str();
	}

	static bool includes(std::string str,std::string searched_str){
		if(str.find(searched_str)==std::string::npos){
			return false;
		}else{
			return true;
		}
	}

	static size_t indexOf(std::string str,std::string searched_str){
		size_t result=str.find(searched_str);
		if(result==std::string::npos){
			return std::string::npos;
		}else{
			return result;
		}
	}

};
}

#endif /* STRING_HH_ */
