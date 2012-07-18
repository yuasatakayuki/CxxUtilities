/*
 * Thread.hh
 *
 *  Created on: Jul 15, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_THREAD_HH_
#define CXXUTILITIES_THREAD_HH_

#ifndef _PTHREAD_H
#include <pthread.h>
#endif

#ifndef _USER_SIGNAL_H
#include <signal.h>
#endif

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

	virtual ~Thread() {
	}

	virtual int start() {
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
protected:
	bool stopped;
	bool inRunMethod;

public:
	StoppableThread(){
		stopped=true;
		inRunMethod=false;
	}

	/** Stops thread. This method executes notify() to interrupt
	 * sleep() used in the running thread.
	 */
	void stop(){
		stopped=true;
		notify();
	}

	virtual int start() {
		int result = pthread_create(&threadid, NULL, StoppableThread::start_routine_stoppable, (void*) this);
		return result;
	}

private:
	static void* start_routine_stoppable(void* arg) {
		if (arg == 0) {
			std::cout << "Thread start_routine() returning zero" << std::hex << (uintptr_t) (arg) << std::endl;
			std::cout.flush();
			return 0;
		}
		StoppableThread* newthread = reinterpret_cast<StoppableThread*> (arg);
		newthread->run_();
		pthread_exit(arg);
		return arg;
	}

	void run_(){
		stopped=false;
		inRunMethod=true;
		run();
		inRunMethod=false;
		stopped=true;
	}

public:
	bool isStopped(){
		return stopped;
	}

	bool isInRunMethod(){
		return inRunMethod;
	}
};

}
#endif /* CXXUTILITIES_THREAD_HH_ */
