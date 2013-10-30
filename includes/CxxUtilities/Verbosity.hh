/*
 * Verbosity.hh
 *
 *  Created on: Oct 30, 2013
 *      Author: yuasa
 */

#ifndef VERBOSITY_HH_
#define VERBOSITY_HH_

#include "CommonHeader.hh"

class Verbosity {

public:
	enum VerbosityLevel {
		Quiet = 0, //
		Low = 100, //
		Middle = 200, //
		High = 300, //
		Debug = 999 //
	};

public:
	static VerbosityLevel level = Quiet;

public:
	static void setVerbosity(VerbosityLevel level_) {
		level = level_;
	}

public:
	static VerbosityLevel getVerbosity() {
		return level;
	}

public:
	std::string toString() {
		std::string result;
		switch (level) {
		Quiet: //
		result = "Quiet";
		break;
		Low: //
		result = "Low";
		break;
		Middle: //
		result = "Middle";
		break;
		High: //
		result = "High";
		break;
		Debug: //
		result = "Debug";
		break;
		}
		return result;
	}

};

#endif /* VERBOSITY_HH_ */
