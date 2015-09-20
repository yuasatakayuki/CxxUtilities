/*
 * Date.hh
 *
 *  Created on: Dec 15, 2014
 *      Author: yuasa
 */

#ifndef DATE_HH_
#define DATE_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {
class Date {
public:
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;

public:
	static CxxUtilities::Date parseYYYYMMDD_HHMMSS(std::string yyyymmdd_hhmmss) {
		CxxUtilities::Date result;
		if (yyyymmdd_hhmmss.size() == 15) {
			result.year = atoi(yyyymmdd_hhmmss.substr(0, 4).c_str());
			result.month = atoi(yyyymmdd_hhmmss.substr(4, 2).c_str());
			result.day = atoi(yyyymmdd_hhmmss.substr(6, 2).c_str());
			result.hour = atoi(yyyymmdd_hhmmss.substr(9, 2).c_str());
			result.min = atoi(yyyymmdd_hhmmss.substr(11, 2).c_str());
			result.sec = atoi(yyyymmdd_hhmmss.substr(13, 2).c_str());
			return result;
		} else {
			using namespace std;
			cerr << "CxxUtilities::Date::parseYYYYMMDD_HHMMSS(yyyymmdd_hhmmss): invailid yyyymmdd_hhmmss " << yyyymmdd_hhmmss
					<< endl;
			return result;
		}
	}

public:
	std::string toString() {
		using namespace std;
		std::stringstream ss;
		ss << setfill('0') << setw(4) << (uint32_t)this->year << setw(2) << (uint32_t)this->month << setw(2) << (uint32_t)this->day << "_" << setw(2)
				<< (uint32_t)this->hour << setw(2) << (uint32_t)this->min << setw(2) << (uint32_t)this->sec;
		return ss.str();
	}

};
}

#endif /* DATE_HH_ */
