/*
 * MessageTemplate.hh
 *
 *  Created on: Jul 16, 2014
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_MESSAGETEMPLATE_HH_
#define CXXUTILITIES_MESSAGETEMPLATE_HH_

namespace CxxUtilities {

class MessageTemplate {
private:
	std::stringstream ss;

public:
	/** Returns string containing a progress status like "Processed 2000/128000 (15.6%)"
	 * @return progress status string
	 */
	static std::string progressState(size_t total, size_t current) {
		std::stringstream ss;
		double percent = ((double) current) / total * 100;
		ss << "Processed " << current << " / " << total << " (" << std::setprecision(3) << percent << "%)";
		return ss.str();
	}

public:
	/** Returns string containing a progress status like "Processed 2000/128000 (15.6%) filtered events 567"
	 * @return progress status string
	 */
	static std::string progressState(size_t total, size_t current, std::string additionalString,
			size_t additionalNumber) {
		std::stringstream ss;
		double percent = ((double) current) / total * 100;
		ss << "Processed " << current << " / " << total << " (" << std::setprecision(3) << percent << "%) "
				<< additionalString << " " << additionalNumber;
		return ss.str();
	}

public:
	static std::string nEvents(size_t nEvents) {
		std::stringstream ss;
		ss << std::dec << nEvents << " events";
		return ss.str();
	}

};

}

#endif /* CXXUTILITIES_MESSAGETEMPLATE_HH_ */
