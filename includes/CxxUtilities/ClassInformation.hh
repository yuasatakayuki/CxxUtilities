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

namespace CxxUtilities {
/** A class which provides a demangling function for class name operations.
 */
class ClassInformation {
public:
	/** Demangles a mangled identifier name.
	 * @param mangledName a mangled name.
	 * @return a demanged name.
	 */
	static std::string demangle(std::string mangledName){
		int status;
		return abi::__cxa_demangle(mangledName.c_str(),0,0,&status);
	}
};
}
#endif /* CLASSINFORMATION_HH_ */
