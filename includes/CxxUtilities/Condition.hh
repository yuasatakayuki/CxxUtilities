/*
 * Condition.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef CONDITION_HH_
#define CONDITION_HH_

#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/Mutex.hh"

namespace CxxUtilities {

class Condition {
private:
	Mutex mutex;
	pthread_cond_t condition;
public:
	Condition(){
		pthread_cond_init(&condition,NULL);
	}

	~Condition(){

	}

	void wait(){
		mutex.lock();
		pthread_cond_wait(&condition,mutex.getPthread_Mutex_T());
		mutex.unlock();
	}

	void wait(int millis){
		if ( millis <= 0 ) return;
		wait((unsigned int)millis);
	}

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

	void signal(){
		mutex.lock();
		pthread_cond_signal(&condition);
		mutex.unlock();
	}

	void broadcast(){
		mutex.lock();
		pthread_cond_broadcast(&condition);
		mutex.unlock();
	}

	Mutex* getConditionMutex(){
		return &mutex;
	}
};

}
#endif /* CONDITION_HH_ */
