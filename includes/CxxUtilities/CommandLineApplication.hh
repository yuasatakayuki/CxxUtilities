/*
 * CommandLineApplication.hh
 *
 *  Created on: Nov 28, 2012
 *      Author: yuasa
 */

#ifndef COMMANDLINEAPPLICATION_HH_
#define COMMANDLINEAPPLICATION_HH_

#include "CommonHeader.hh"

namespace CxxUtilities {
class CommandLineApplication {
protected:
	std::vector<std::string> arguments;

public:
	CommandLineApplication(int nArguments, char* arguments[]) {
		storeArguments(nArguments, arguments);
	}

public:
	virtual ~CommandLineApplication() {
	}

protected:
	void storeArguments(int nArguments, char* arguments[]) {
		this->arguments = convertArgumentsToVector(nArguments, arguments);
	}

protected:
	std::vector<std::string> convertArgumentsToVector(int nArguments, char* arguments[]) {
		std::vector<std::string> argumentsVector;
		for (size_t i = 0; i < nArguments; i++) {
			argumentsVector.push_back(arguments[i]);
		}
		return argumentsVector;
	}

public:
	virtual void checkArguments(std::vector<std::string> arguments) =0;

public:
	virtual void initializeInstanceVariables() =0;

public:
	virtual void finalizeInstanceVariables() =0;

public:
	virtual void showUsage() =0;

public:
	virtual void showWelcomeMessage() =0;

public:
	virtual void showHelpMessage() =0;

public:
	virtual void showClosingMessage() =0;

public:
	void startInteractiveSession() {
		interactiveSessionWillStart();
		interactiveSession();
		interactiveSessionWillComplete();
	}

public:
	virtual void interactiveSessionWillStart() {
	}

public:
	virtual void interactiveSession() {
	}

public:
	virtual void interactiveSessionWillComplete() {
	}

public:
	virtual void terminate() =0;

};
}

#endif /* COMMANDLINEAPPLICATION_HH_ */
