/*
 * Time.hh
 *
 *  Created on: Jun 19, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_TIME_HH_
#define CXXUTILITIES_TIME_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {
class TimeValues {
public:
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t msec;
	uint16_t yday;
};

class Time {
public:
	/** Returns the current date/time formatted accordingly.
	 */
	static std::string getCurrentTimeAsString(std::string format ="%Y-%m-%d %H:%M:%S") {
		time_t timer = time(NULL);
		struct tm *date;
		char str[1024];
		date = localtime(&timer);
		strftime(str, 1023, format.c_str(), date);
		return std::string(str);
	}

	/** Returns the current date/time formatted accordingly.
	 */
	static std::string getCurrentTimeYYYYMMDD_HHMM() {
		return getCurrentTimeAsString("%Y%m%d_%H%M");
	}

	static time_t getUNIXTime(){
		return time(0);
	}

	static TimeValues getCurrentTimeAsNumbers(){
		time_t timer = time(NULL);
		struct tm *date;
		date = localtime(&timer);
		TimeValues timeValues;
		timeValues.year=date->tm_year+1900;
		timeValues.month=date->tm_mon;
		timeValues.day=date->tm_mday;
		timeValues.hour=date->tm_hour;
		timeValues.min=date->tm_min;
		timeValues.sec=date->tm_sec;
		timeValues.msec=0;
		timeValues.yday=date->tm_yday;
		return timeValues;
	}
};
}
#endif /* CXXUTILITIES_TIME_HH_ */
