/*
 * TerminalControl.hh
 *
 *  Created on: Sep 8, 2012
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_TERMINALCONTROL_HH_
#define CXXUTILITIES_TERMINALCONTROL_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

class TerminalControl {
public:
	static void clearScreen() {
		printf("\033[2J");
	}

public:
	static void moveCursorToXY(uint32_t x, uint32_t y) {
		printf("\033[%d;%dH", y, x);
	}

public:
	static void displayInCyan(std::string str) {
		//cyan
		str = "\x1b[36m" + str + "\x1b[39m";
		printf("%s",str.c_str());
	}

public:
	static void displayInRed(std::string str) {
		//red color
		str = "\x1b[31m" + str + "\x1b[39m";
		printf("%s",str.c_str());
	}

public:
	static void displayInMagenta(std::string str) {
		//magenta color
		str = "\x1b[35m" + str + "\x1b[39m";
		printf("%s",str.c_str());
	}
};

}

#endif /* CXXUTILITIES_TERMINALCONTROL_HH_ */
