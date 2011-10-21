/*
 * Mutex.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef MUTEX_HH_
#define MUTEX_HH_

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/Exception.hh"

namespace CxxUtilities {

class MutexException: public CxxUtilities::Exception {
public:
	enum type {
		LockFailed, UnlockFailed
	};

public:
	MutexException(unsigned int status) : Exception(status){
	}
};

class Mutex {
private:
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;

public:
	Mutex() {
		pthread_mutexattr_init(&mutex_attr);
		pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &mutex_attr);
	}

	~Mutex() {
		pthread_mutex_destroy(&mutex);
	}

	void lock() throw (MutexException) {
		if (pthread_mutex_lock(&mutex) != 0) {
			throw MutexException(MutexException::LockFailed);
		}
	}

	void unlock() throw (MutexException) {
		if (pthread_mutex_unlock(&mutex) != 0) {
			throw MutexException(MutexException::UnlockFailed);
		}
	}

	pthread_mutex_t* getPthread_Mutex_T() {
		return &mutex;
	}
};

}
#endif /* MUTEX_HH_ */
