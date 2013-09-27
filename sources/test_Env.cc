/*
 * test_Env.cc
 *
 *  Created on: Sep 27, 2013
 *      Author: yuasa
 */

#include "CxxUtilities/CxxUtilities.hh"

int main(int argc, char* argv[]){
	using namespace std;
	using namespace CxxUtilities;
	cout << Env::get("PATH") << endl;
	Env::set("TLMPATH","abc");
	cout << Env::get("TLMPATH") << endl;

}
