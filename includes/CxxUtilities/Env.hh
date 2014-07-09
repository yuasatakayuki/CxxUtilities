/*
 * Env.hh
 *
 *  Created on: Sep 26, 2013
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_ENV_HH_
#define CXXUTILITIES_ENV_HH_

#include "CommonHeader.hh"

namespace CxxUtilities {
class Env {
public:
	/** Sets an environment variable.
	 * @param[in] key environment variable name
	 * @param[in] value value to be set to the environment variable
	 */
	static void set(std::string key,std::string value){
		using namespace std;
		string putenv_arg = key + "=" + value;
		::putenv((char*) putenv_arg.c_str());
	}

public:
	/** Returns environment variable value.
	 * @param[in] key environment variable name
	 * @return environment variable value
	 */
	static std::string get(std::string key){
		std::string  value(getenv(key.c_str()));
		return value;
	}
};
}


#endif /* CXXUTILITIES_ENV_HH_ */
