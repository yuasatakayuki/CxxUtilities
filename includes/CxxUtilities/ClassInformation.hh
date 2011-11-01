/*
 * ClassInformation.hh
 *
 *  Created on: Oct 27, 2011
 *      Author: yuasa
 */

#ifndef CLASSINFORMATION_HH_
#define CLASSINFORMATION_HH_

#include <typeinfo>
#include <cxxabi.h>
#include <string>

class ClassInformation {
public:
	static std::string demangle(std::string mangledName){
		int status;
		return abi::__cxa_demangle(mangledName.c_str(),0,0,&status);
	}
};

#endif /* CLASSINFORMATION_HH_ */
