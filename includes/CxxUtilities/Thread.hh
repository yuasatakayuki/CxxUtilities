/*
 * Thread.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef THREAD_HH_
#define THREAD_HH_

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/Condition.hh"

namespace CxxUtilities {

class Thread {
private:
	static void* start_routine(void* arg) {
		if (arg == 0) {
			std::cout << "Thread start_routine() returning zero" << std::hex << (uintptr_t) (arg) << std::endl;
			std::cout.flush();
			return 0;
		}
		Thread* newthread = reinterpret_cast<Thread*> (arg);
		newthread->run();
		pthread_exit(arg);
		return arg;
	}

public:
	Thread() {
		threadid = 0;
	}

	~Thread() {
	}

	int start() {
		int result = pthread_create(&threadid, NULL, Thread::start_routine, (void*) this);
		return result;
	}

	void yield() {
		sched_yield();
	}

	void sleep(double millis) {
		condition.wait(millis);
	}

	void wait() {
		condition.wait();
	}

	void interrupt() {
		condition.signal();
	}

	void notify() {
		condition.signal();
		yield();
	}

	int join() {
		return pthread_join(threadid, 0);
	}

	void exit() {
		pthread_exit((void**) 0);
	}

	int detach() {
		return pthread_detach(threadid);
	}

	int cancel() {
		return pthread_cancel(threadid);
	}

	int kill(int signo) {
		return pthread_kill(threadid, signo);
	}

protected:
	virtual void run() =0;

protected:
	pthread_t threadid;
	Condition condition;
};

class StoppableThread : public CxxUtilities::Thread {
private:
	bool stopped;
public:
	StoppableThread(){
		stopped=true;
	}

	void stop(){
		stopped=true;
	}

	bool isStopped(){
		return stopped;
	}
};

}
#endif /* THREAD_HH_ */
