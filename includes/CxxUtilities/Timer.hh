/*
 * Timer.hh
 *
 *  Created on: Nov 29, 2012
 *      Author: yuasa
 */

#ifndef TIMER_HH_
#define TIMER_HH_

#include "Condition.hh"
#include "Thread.hh"

namespace CxxUtilities {
/** Timer which measures a specified time duration, and signals (bells) a given
 * CxxUtilities::Condition instance to tell its caller that the timer has expired.
 * The method hasExpired() could be used to poll timer status from the caller side as well.
 * @par Example1: with a CxxUtilities::Condition instance being not provided
 * Timer* timer=new Timer(1000);
 * timer->start();//expires after 1s
 * ...do something...
 * if(timer->hasExpired()){
 *  ...do something...
 * }
 *
 * @par Example2: with a CxxUtilities::Condition instance being provided
 * CxxUtilities::Condition c;
 * Timer* timer=new Timer(1000,&c);
 * timer->start();//expires after 1s
 * ...do something...
 * c.wait(); //this wait will be signaled (interrupted) when the timer expires
 */
class Timer: public CxxUtilities::StoppableThread {
private:
	double waitDuration;
	CxxUtilities::Condition* conditionInstanceToBeSignalled;
	bool startedAtLeastOnce;

public:
	Timer(double waitDuration, CxxUtilities::Condition* conditionInstanceToBeSignalled = NULL) {
		this->waitDuration = waitDuration;
		this->conditionInstanceToBeSignalled = conditionInstanceToBeSignalled;
		startedAtLeastOnce=false;
	}

public:
	void run() {
		startedAtLeastOnce=true;
		this->sleep(waitDuration);
		if (conditionInstanceToBeSignalled != NULL) {
			conditionInstanceToBeSignalled->signal();
		}
	}

public:
	bool hasStartedAtLeastOnce(){
		return startedAtLeastOnce;
	}

public:
	bool hasExpired(){
		if(isStopped() && hasStartedAtLeastOnce()){
			return true;
		}else{
			return false;
		}
	}

public:
	bool isWaitingForExpiration(){
		if(isStopped()){
			return false;
		}else{
			return true;
		}
	}
};
}

#endif /* TIMER_HH_ */
