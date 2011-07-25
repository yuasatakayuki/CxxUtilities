/*
 * Bitset.hh
 *
 *  Created on: Jul 12, 2011
 *      Author: yuasa
 */

#ifndef BITSET_HH_
#define BITSET_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

class Bitset {
public:
	template<int inputBitsetWidth, int index, int size>
	static std::bitset<size> getSubset(std::bitset<inputBitsetWidth>& bits) {
		std::bitset < size > result;
		for (int i = 0; i < size; i++) {
			result[i] = bits[index + i];
		}
		return result;
	}

	template<int bitset1Width, int bitset2Width>
	static std::bitset<bitset1Width + bitset2Width> join(std::bitset<bitset1Width>& bits1,
			std::bitset<bitset2Width>& bits2) {
		std::bitset < bitset1Width + bitset2Width > result;
		for (int i = 0; i < bitset1Width; i++) {
			result[i] = bits1[i];
		}
		for (int i = 0; i < bitset2Width; i++) {
			result[i + bitset1Width] = bits2[i];
		}
		return result;
	}

	template<int inputBitsetWidth, int index, int replaceWidth>
	static std::bitset<inputBitsetWidth> replace(std::bitset<inputBitsetWidth>& target,
			std::bitset<replaceWidth>& subset) {
		std::bitset < inputBitsetWidth > result = target;
		for (int i = 0; i < replaceWidth; i++) {
			result[index + i] = subset[i];
		}
		return result;
	}
};
}

#endif /* BITSET_HH_ */
