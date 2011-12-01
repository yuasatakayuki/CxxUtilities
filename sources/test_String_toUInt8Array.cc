/*
 * test_String_toUInt8Array.cc
 *
 *  Created on: Nov 29, 2011
 *      Author: yuasa
 */

#include "CxxUtilities/String.hh"
#include "CxxUtilities/Array.hh"
using namespace std;
using namespace CxxUtilities;

int main(){
	string str="  0xabcdefgh";
	vector<uint8_t> array=String::toUInt8Array(str);
	cout << Array<uint8_t>::toString(array,"hex") << endl;
}
