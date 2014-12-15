/*
 * Time.hh
 *
 *  Created on: Jun 19, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_CXXUTILITIES_TIME_HH_
#define CXXUTILITIES_CXXUTILITIES_TIME_HH_

#include "CxxUtilities/CommonHeader.hh"
#include <time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

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
	static std::string getCurrentTimeAsString(std::string format = "%Y-%m-%d %H:%M:%S") {
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

	static std::string getCurrentTimeYYYYMMDD_HHMMSS() {
		return getCurrentTimeAsString("%Y%m%d_%H%M%S");
	}

	static time_t getUNIXTime() {
		return time(0);
	}

	static time_t getUNIXTimeAsUInt32() {
		return (uint32_t)(time(0));
	}

	static TimeValues getCurrentTimeAsNumbers() {
		time_t timer = time(NULL);
		struct tm *date;
		date = localtime(&timer);
		TimeValues timeValues;
		timeValues.year = date->tm_year + 1900;
		timeValues.month = date->tm_mon;
		timeValues.day = date->tm_mday;
		timeValues.hour = date->tm_hour;
		timeValues.min = date->tm_min;
		timeValues.sec = date->tm_sec;
		timeValues.msec = 0;
		timeValues.yday = date->tm_yday;
		return timeValues;
	}

public:
	static double getClockValueInMilliSec() {
		struct timespec tp;
		struct timespec ts;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
		clock_serv_t clockServ;
		mach_timespec_t machTimespec;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clockServ);
		clock_get_time(clockServ, &machTimespec);
		mach_port_deallocate(mach_task_self(), clockServ);
		ts.tv_sec = machTimespec.tv_sec;
		ts.tv_nsec = machTimespec.tv_nsec;
#else
		clock_gettime(CLOCK_REALTIME, &ts);
#endif

		return (double) ((ts.tv_sec + ts.tv_nsec *1e-9 )*1000);
	}

public:
	static time_t getUNIXTime(std::string yyyymmdd_hhmmss){
	   time_t timer;
	   struct tm tm;
	   const char* datetime = "2013-06-15 12:00:00";
	   if( strptime(yyyymmdd_hhmmss.c_str(), "%Y%m%d_%H%M%S", &tm ) != NULL ) {
	      return mktime(&tm);
	   }else{
	  	 return 0;
	   }
	}
};

}
#endif /* CXXUTILITIES_TIME_HH_ */
