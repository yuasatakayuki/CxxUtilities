/*
 * Interfaces.hh
 *
 *  Created on: Jun 16, 2012
 *      Author: yuasa
 */

#ifndef INTERFACES_HH_
#define INTERFACES_HH_

#include "CommonHeader.hh"

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

template<typename T>
class TerminateInterface_ {
private:
	static std::vector<TerminateInterface_<int>*> db;
	static Mutex mutex;
public:
	TerminateInterface_() {
		db.push_back(this);
	}
	virtual ~TerminateInterface_() {
		mutex.lock();
		std::vector<TerminateInterface_<int>*>::iterator it=db.begin();
		for(;it!=db.begin();it++){
			if((*it)==this){
				db.erase(it);
				break;
			}
		}
		mutex.unlock();
	}

public:
	static void terminateAll(){
		for(size_t i=0;i<db.size();i++){
			db[i]->terminate();
		}
	}

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
