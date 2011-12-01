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

/** A class which provides a wrapper for a condition object used for inter-thread communication.
 * By using this class, a code block can be made atomic (or only one thread can execute the block at a time).
 */
class Mutex {
private:
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;

public:
	/** Constructs an instance.
	 */
	Mutex() {
		pthread_mutexattr_init(&mutex_attr);
		pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &mutex_attr);
	}

	/** Destructor.
	 */
	~Mutex() {
		pthread_mutex_destroy(&mutex);
	}

	/** Locks this mutex. If successfully locked, the following code block
	 * will be locked from other threads. The other threads try to lock
	 * this mutex will be forced to wait until the present thread unlocks the
	 * mutex.
	 */
	void lock() throw (MutexException) {
		if (pthread_mutex_lock(&mutex) != 0) {
			throw MutexException(MutexException::LockFailed);
		}
	}

	/** Unlocks this mutex.
	 */
	void unlock() throw (MutexException) {
		if (pthread_mutex_unlock(&mutex) != 0) {
			throw MutexException(MutexException::UnlockFailed);
		}
	}

	/** Returns pthread_mutex_t object which is internally used by this class.
	 * @return pthread_mutex_t instance.
	 */
	pthread_mutex_t* getPthread_Mutex_T() {
		return &mutex;
	}
};

}
#endif /* MUTEX_HH_ */
