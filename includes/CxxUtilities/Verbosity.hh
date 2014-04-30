/*
 * Verbosity.hh
 *
 *  Created on: Oct 30, 2013
 *      Author: yuasa
 */

#ifndef VERBOSITY_HH_
#define VERBOSITY_HH_

#include "CommonHeader.hh"

namespace CxxUtilities {
template<typename T>
class _Verbosity {
public:
	enum VerbosityLevel {
		Quiet = 0, //
		Low = 100, //
		Middle = 200, //
		High = 300, //
		Debug = 999 //
	};

public:
	static int DefaultVerbosityLevel;
	static int level;

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

template<typename T> int _Verbosity<T>::DefaultVerbosityLevel = _Verbosity<T>::Middle;
template<typename T> int _Verbosity<T>::level = _Verbosity<T>::DefaultVerbosityLevel;

typedef _Verbosity<int> Verbosity;
}
#endif /* VERBOSITY_HH_ */
