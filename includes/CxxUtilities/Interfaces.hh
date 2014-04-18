/*
 * Interfaces.hh
 *
 *  Created on: Jun 16, 2012
 *      Author: yuasa
 */

#ifndef INTERFACES_HH_
#define INTERFACES_HH_

#include "CommonHeader.hh"
#include "CxxUtilities/Condition.hh"
#include "CxxUtilities/Thread.hh"

namespace CxxUtilities {

class ClassnameInterface {
protected:
	std::string classname;

public:
	ClassnameInterface(std::string classname) {
		setClassname(classname);
	}

public:
	std::string getClassname() {
		return classname;
	}

	std::string getClassName() {
		return classname;
	}

	void setClassname(std::string classname) {
		this->classname = classname;
	}

	void setClassName(std::string classname) {
		this->classname = classname;
	}
};

class InstanceNameInterface {
private:
	std::string instanceName;

public:
	InstanceNameInterface(std::string instanceName){
		this->instanceName=instanceName;
	}

public:
	std::string getInstanceName(){
		return instanceName;
	}

public:
	void setInstanceName(std::string instanceName){
		this->instanceName=instanceName;
	}

};

template<typename T>
class TerminateInterface_ {
private:
	static std::vector<TerminateInterface_<int>*> db;
	static Mutex mutex;

public:
	class TerminateThread: public CxxUtilities::Thread {
	private:
		TerminateInterface_<int>* instance;
	public:
		TerminateThread(TerminateInterface_<int>* instance) {
			this->instance = instance;
		}
	public:
		void run() {
			instance->terminate();
		}
	};

public:
	TerminateInterface_() {
		db.push_back(this);
	}
	virtual ~TerminateInterface_() {
		mutex.lock();
		std::vector<TerminateInterface_<int>*>::iterator it = db.begin();
		for (; it != db.begin(); it++) {
			if ((*it) == this) {
				db.erase(it);
				break;
			}
		}
		mutex.unlock();
	}

public:
	static void terminateAll() {
		for (size_t i = 0; i < db.size(); i++) {
			TerminateThread* thread = new TerminateThread(db[i]);
			thread->start();
		}
		CxxUtilities::Condition c;
		c.wait(DefaultWaitDurationForTerminateAllInMs);
	}

public:
	constexpr static const double DefaultWaitDurationForTerminateAllInMs = 1000; //ms

public:
	virtual void terminate() = 0;

};

template<typename T>
std::vector<TerminateInterface_<int>*> TerminateInterface_<T>::db;

template<typename T>
Mutex TerminateInterface_<T>::mutex;

typedef TerminateInterface_<int> TerminateInterface;

}

#endif /* INTERFACES_HH_ */
