/*
 * Exception.hh
 *
 *  Created on: Jun 13, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_EXCEPTION_HH_
#define CXXUTILITIES_EXCEPTION_HH_

#include "ClassInformation.hh"

namespace CxxUtilities {

/** A base class for exception classes with exception status.
 * enum can be used to specify user defined exception status for a (user-defined) child class.
 */
class Exception {
public:
	int status;

public:
	virtual ~Exception(){}

public:
	/** Returns status.
	 * @return status.
	 */
	unsigned int getStatus() const {
		return status;
	}

	/** Sets status.
	 * @param status status value to be set.
	 */
	void setStatus(int status) {
		this->status = status;
	}

public:
	/** Constructs an instance which holds a specified status value.
	 * @param status a status value.
	 */
	Exception(int status) {
		this->status = status;
	}

public:
	/** Generates a string which explains this exception.
	 * Practically, this method should be implemented in user-defined child classes.
	 * @return string value which represents this exception instance.
	 */
	virtual std::string toString(){
		return ClassInformation::demangle(typeid(*this).name());
	}

};
}
#endif /* CXXUTILITIES_EXCEPTION_HH_ */
