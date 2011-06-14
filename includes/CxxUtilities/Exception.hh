/*
 * Exception.hh
 *
 *  Created on: Jun 13, 2011
 *      Author: yuasa
 */

#ifndef EXCEPTION_HH_
#define EXCEPTION_HH_

namespace CxxUtilities {

class Exception {
public:
	unsigned int status;

public:
	unsigned int getStatus() const {
		return status;
	}

	void setStatus(unsigned int status) {
		this->status = status;
	}

public:
	Exception(unsigned int status) {
		this->status = status;
	}

};
}
#endif /* EXCEPTION_HH_ */
