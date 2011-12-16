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
class Action {
public:
	virtual void doAction(void* parentObject) =0;
};

class Actions : public std::vector<Action*> {
public:
	virtual void addAction(Action* action){
		this->push_back(action);
	}

public:
	virtual void removeAction(Action* action){
		std::vector<Action*> newActions;
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
	virtual void doEachAction(void* parentObject){
		for(size_t i=0;i<this->size();i++){
			this->at(i)->doAction(parentObject);
		}
	}
};
}
#endif /* CXXUTILITIES_ACTION_HH_ */
