/*
 * Condition.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_CONDITION_HH_
#define CXXUTILITIES_CONDITION_HH_

#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/Mutex.hh"
#include <sys/time.h>

namespace CxxUtilities {

/** A class which provides a wrapper for a condition object used for inter-thread communication.
 * By using this class, a thread can wait until another thread completes a task or proceeds to a certain stage.
 */
class Condition {
private:
	Mutex mutex;
	pthread_cond_t condition;
public:
	/** Constructs an instance.
	 */
	Condition(){
		pthread_cond_init(&condition,NULL);
	}

	/** Deconstructor.
	 */
	~Condition(){

	}

	/** Waits until signaled. If there is no signal from another thread,
	 * this method waits forever without timing out.
	 */
	void wait(){
		mutex.lock();
		pthread_cond_wait(&condition,mutex.getPthread_Mutex_T());
		mutex.unlock();
	}

	/** Waits until signaled. If there is no signal from another thread,
	 * this method times out after the specified time.
	 * @param millis timeout duration in millisecond.
	 */
	void wait(int millis){
		if ( millis <= 0 ) return;
		wait((unsigned int)millis);
	}

	/** Waits until signaled. If there is no signal from another thread,
	 * this method times out after the specified time.
	 * @param millis timeout duration in millisecond.
	 */
	void wait(unsigned int millis){
		struct timespec timeout;
		struct timeval tp;
		gettimeofday(&tp, NULL);

		timeout.tv_sec = (millis / 1000) + tp.tv_sec;
		timeout.tv_nsec = ((millis % 1000) * 1000000) + (tp.tv_usec * 1000);

		while (timeout.tv_nsec >= 1000000000) {
			timeout.tv_nsec -= 1000000000;
			timeout.tv_sec++;
		}

		mutex.lock();
		pthread_cond_timedwait(&condition,mutex.getPthread_Mutex_T(),&timeout);
		mutex.unlock();
	}

	/** Waits until signaled. If there is no signal from another thread,
	 * this method times out after the specified time.
	 * @param millis timeout duration in millisecond.
	 */
	void wait(double millis){
		struct timespec timeout;
		struct timeval tp;
		unsigned int sc, ns;

		if ( millis <= 0.0 ) return;

		sc = (unsigned int)(millis/1000);
		ns = (unsigned int)(1e9*(millis/1000 - sc));
		gettimeofday(&tp, NULL);
		timeout.tv_sec = sc + tp.tv_sec;
		timeout.tv_nsec = ns + (tp.tv_usec * 1000);

		while (timeout.tv_nsec >= 1000000000) {
			timeout.tv_nsec -= 1000000000;
			timeout.tv_sec++;
		}

		mutex.lock();
		pthread_cond_timedwait(&condition,mutex.getPthread_Mutex_T(),&timeout);
		mutex.unlock();
	}

	/** Signals a waiting thread. A thread which was sleeping by calling
	 * wait() or wait(timeout duration) awakes, and restarts its processing.
	 * Signal only wakes the first thread in the wait list.
	 */
	void signal(){
		mutex.lock();
		pthread_cond_signal(&condition);
		mutex.unlock();
	}

	/** Signals a waiting thread. A thread which was sleeping by calling
	 * wait() or wait(timeout duration) awakes, and restarts its processing.
	 * This method broadcasts a signal, and therefore, all the threads in the
	 * wait list will be awoken.
	 */
	void broadcast(){
		mutex.lock();
		pthread_cond_broadcast(&condition);
		mutex.unlock();
	}

	/** Returns a pointer to an internal mutex object.
	 * @return a pointer to an internal mutex object.
	 */
	Mutex* getConditionMutex(){
		return &mutex;
	}
};

}
#endif /* CXXUTILITIES_CONDITION_HH_ */
