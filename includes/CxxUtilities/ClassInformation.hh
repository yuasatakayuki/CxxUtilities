/*
 * ClassInformation.hh
 *
 *  Created on: Oct 27, 2011
 *      Author: yuasa
 */

#ifndef CLASSINFORMATION_HH_
#define CLASSINFORMATION_HH_

#include "CommonHeader.hh"

class ClassInformation {
public:
	template<clas T>
	static std::string getClassNameAsString(T& instance){
		int status;
		const type_info & id_p = typeid(instance);
	    return std::string(abi::__cxa_demangle(id_p.name(), 0, 0, &status));
	}
};

#endif /* CLASSINFORMATION_HH_ */
