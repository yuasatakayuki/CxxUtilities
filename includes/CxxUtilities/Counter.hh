/*
 * Counter.hh
 *
 *  Created on: Jun 13, 2012
 *      Author: yuasa
 */

#ifndef COUNTER_HH_
#define COUNTER_HH_

#include "CommonHeader.hh"
#include "Mutex.hh"

namespace CxxUtilities {

/** Counters class provides an application-wide counter system.
 * Use Counters::createCounterInstance(std::string id) or
 * Counters::getCounterInstance(std::string id) to instantiate of the Counter class.
 */
class Counter {
private:
	std::string id;
	size_t counter;

public:
	Counter(std::string id){
		this->id=id;
		counter=0;
	}

public:
	inline void increment(size_t byN = 1) {
		counter = counter + byN;
	}

	inline void decreent(size_t byN = 1) {
		counter = counter - byN;
	}

	inline size_t getValue() {
		return counter;
	}

	inline size_t getCounterValue() {
		return counter;
	}

	inline void clear() {
		counter = 0;
	}

	inline void setValue(size_t counter) {
		this->counter = counter;
	}

	inline void setCounterValue(size_t counter) {
		this->counter = counter;
	}

public:
	std::string getID(){
		return id;
	}

public:
	std::string toString(size_t widthOfIDLabel = 10) {
		std::stringstream ss;
		ss << std::setw(widthOfIDLabel) << id << " : " << std::dec << counter;
		return ss.str();
	}

public:
	size_t getIDLength() {
		return id.size();
	}
};

/** A class that collects counter instances.
 * Note: Typenamed version of this called "Counters" is available instead of "Counters_".
 * This class definition with template is for defining class variable in the header file.
 */
template<typename T>
class Counters_ {
private:
	static std::map<std::string,Counter*> counters;


public:
	static bool isDefined(std::string id){
		std::map<std::string,Counter*>::iterator it=counters.find(id);
		if(it!=counters.end()){
			return true;
		}else{
			return false;
		}
	}

	static void deleteInstance(std::string id){
		std::map<std::string,Counter*>::iterator it=counters.find(id);
		if(it!=counters.end()){
			delete it->second;
			counters.erase(it);
		}
	}

public:
	static Counter* getCounterInstance(std::string id){
		std::map<std::string,Counter*>::iterator it=counters.find(id);
		if(it!=counters.end()){
			return it->second;
		}else{
			Counter* instance=new Counter(id);
			counters[id]=instance;
			return instance;
		}
	}

	static Counter* createCounterInstance(std::string id){
		std::map<std::string,Counter*>::iterator it=counters.find(id);
		if(it!=counters.end()){
			return it->second;
		}else{
			Counter* instance=new Counter(id);
			counters[id]=instance;
			return instance;
		}
	}


public:
	static void deleteAllCounters(){
		std::map<std::string,Counter*>::iterator it;//=counters.begin();
		for(;it!=counters.end();it++){
			delete it->second;
		}
		counters.clear();
	}

public:
	/** Increments counter value. If the specified counter does not exist,
	 * a new counter instance will be created and then incremented.
	 * @param[in] id counter id
	 * @param[in] byN increment value (default = 1)
	 */
	static void increment(std::string id, size_t byN = 1) {
		getCounterInstance(id)->increment(byN);
	}

public:
	std::string toString(){
		using namespace std;
		size_t width=getMaximumIDLabelWidth();
		std::stringstream ss;
		std::map<std::string, Counter*>::iterator it = counters.begin();
		for (; it != counters.end(); it++) {
			ss << it->second->toString(width) << endl;
		}
		return ss.str();
	}

public:
	size_t getMaximumIDLabelWidth() {
		size_t max = 0;
		std::map<std::string, Counter*>::iterator it = counters.begin();
		for (; it != counters.end(); it++) {
			if (max < it->first.size()) {
				max  = it->first.size();
			}
		}
		return max;
	}
};

template<typename T> std::map<std::string,Counter*> Counters_<T>::counters;

typedef Counters_<int> Counters;
}



#endif /* COUNTER_HH_ */
