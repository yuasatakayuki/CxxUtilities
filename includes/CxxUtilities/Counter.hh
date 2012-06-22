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
	uint64_t counter;

public:
	Counter(std::string id){
		this->id=id;
		counter=0;
	}

public:
	inline void increment(uint64_t byN=1){
		counter=counter+byN;
	}

	inline void decreent(uint64_t byN=1){
		counter=counter-byN;
	}

	inline uint64_t getValue(){
		return counter;
	}

	inline uint64_t getCounterValue(){
		return counter;
	}

	inline void clear(){
		counter=0;
	}

	inline void setValue(uint64_t counter){
		this->counter=counter;
	}

	inline void setCounterValue(uint64_t counter){
		this->counter=counter;
	}

public:
	std::string getID(){
		return id;
	}
};

template<typename T>
class Counters_ : public Counter {
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
};

template<typename T> std::map<std::string,Counter*> Counters_<T>::counters;

typedef Counters_<int> Counters;
}



#endif /* COUNTER_HH_ */
