/*
 * Action.hh
 *
 *  Created on: Dec 16, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_ACTION_HH_
#define CXXUTILITIES_ACTION_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

template<typename T>
class Action {
public:
	virtual void doAction(T* parentObject) =0;

public:
	Action(){}

public:
	virtual ~Action(){}
};

template<typename T>
class Actions : public std::vector<Action<T>*> {
public:
	virtual void addAction(Action<T>* action){
		this->push_back(action);
	}

public:
	virtual ~Actions(){}

public:
	virtual void removeAction(Action<T>* action){
		std::vector<Action<T>*> newActions;
		for(size_t i=0;i<this->size();i++){
			if(this->at(i)!=action){
				newActions.push_back(this->at(i));
			}
		}
		this->clear();
		for(size_t i=0;i<newActions.size();i++){
			this->push_back(newActions[i]);
		}
	}

public:
	virtual void doEachAction(T* parentObject){
		for(size_t i=0;i<this->size();i++){
			this->at(i)->doAction(parentObject);
		}
	}
};
}

#endif /* CXXUTILITIES_ACTION_HH_ */
