/*
 * Histogram.hh
 *
 *  Created on: Apr 6, 2014
 *      Author: yuasa
 */

#ifndef HISTOGRAM_HH_
#define HISTOGRAM_HH_

#include "CommonHeader.hh"
#include "Interfaces.hh"
#include <iostream>

namespace CxxUtilities {

template<typename T>
class Histogram : public CxxUtilities::InstanceNameInterface {
private:
	T* buffer;
	size_t nBins;

public:
	Histogram(size_t nBins) : CxxUtilities::InstanceNameInterface(""){
		buffer = new T[nBins];
		this->nBins = nBins;
	}

public:
	Histogram(std::string histogramName, size_t nBins) : CxxUtilities::InstanceNameInterface(histogramName){
		buffer = new T[nBins];
		this->nBins = nBins;
	}

public:
	~Histogram() {
		delete buffer;
	}

public:
	void fill(size_t binIndex, size_t byN = 1) {
		buffer[binIndex] += byN;
	}

public:
	void increment(size_t binIndex, size_t byN = 1) {
		buffer[binIndex] += byN;
	}

public:
	T getValue(size_t binIndex) {
		return buffer[binIndex];
	}

public:
	void setValue(size_t binIndex, T value) {
		buffer[binIndex] = value;
	}

public:
	std::string toString(std::string options = "") {
		using namespace std;
		std::stringstream ss;

		//---------------------------------------------
		//parse options
		//---------------------------------------------

		// bin index in hex
		bool hexBinIndex = false;
		if (CxxUtilities::String::includes(options, "h")) {
			hexBinIndex = true;
		}

		// display non-zero bins only
		bool nonZeroBinsOnly=false;
		if (CxxUtilities::String::includes(options, "nz")) {
			nonZeroBinsOnly=true;
		}

		//dump name if not empty
		ss << this->getInstanceName() << endl;

		//dump as string
		ss << std::dec;
		for (size_t i = 0; i < this->nBins; i++) {
			if(nonZeroBinsOnly && buffer[i]==0){
				continue;
			}
			if (hexBinIndex) {
				ss << hex << i << dec << " " << buffer[i] << endl;
			} else {
				ss << i << " " << buffer[i] << endl;
			}
		}
		return ss.str();
	}

public:

};

}

#endif /* HISTOGRAM_HH_ */
