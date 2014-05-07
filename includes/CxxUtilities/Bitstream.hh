/*
 * Bitstream.hh
 *
 *  Created on: 2012/01/02
 *      Author: Soki Sakurai
 */

#ifndef BITSTREAM_HH_
#define BITSTREAM_HH_

#include <iostream>
#include <vector>
#include <iomanip>
#include <CxxUtilities/Exception.hh>

namespace CxxUtilities {
class BitstreamException: public CxxUtilities::Exception {
public:
	BitstreamException(int status) :
			CxxUtilities::Exception(status) {

	}

public:
	enum {
		InvalidEndian, InvalidByteWidth,
	};

public:
	std::string toString() {
		std::string result;
		switch(status)
		{
			case InvalidByteWidth:
			result = "InvalidByteWidth";
			break;
			case InvalidEndian:
			result = "InvalidEndian";
			break;
			default:
			result = "UndefinedExceptionState";
			break;
		}
		return result;
	}

};

/** A class that handles bitstream stored as an array of bytes (uint8_t).
 * This class can be used to decode bitstream data from instruments,
 * a data transfer protocol, and so on.
 * An Bitstream instance holds an internal bit position that
 * points a certain bit in the bit stream. When a bit which
 * the bit position pointer points is processed via e.g. pop(),
 * the bit position is moved to the consequent bit.
 */
class Bitstream {
public:
	/** Constructs an empty instance.
	 */
	Bitstream() {
		initialize();
	}

public:
	/** Constructs an instance from a uint8_t array.
	 * @param[in] byteArray a reference to a uint8_t array
	 */
	Bitstream(const std::vector<uint8_t>& byteArray, bool fromMSB = true) {
		initialize();
		byteStream = byteArray;
		size = byteStream.size();
		popFromMSB = fromMSB;
	}

public:
	/** Constructs an instance from a uint8_t array.
	 * @param[in] byteArray a uint8_t array (pointer to a C array)
	 * @param[in] length length of data in the array
	 */
	Bitstream(const uint8_t* byteArray, uint32_t length, bool fromMSB = false) {
		initialize();
		copyStream(byteArray, length);
		popFromMSB = fromMSB;
	}

public:
	/** Destructs an instance.
	 */
	virtual ~Bitstream() {
	}

public:
	struct Endian {
		enum {
			Little = 1, Big = 2
		};
	};

private:
	uint32_t bitpointer;
	uint32_t size;
	bool popFromMSB;
	std::vector<uint8_t> byteStream;

private:
	void initialize() {
		byteStream.clear();
		size = 0;
		bitpointer = 0;
	}

public:
	/** Sets uint8_t array to this bitstream instance.
	 * @param[in] byteArray a reference to uint8_t array
	 */
	void setStream(const std::vector<uint8_t>& byteArray, bool fromMSB = true) {
		initialize();
		byteStream.clear();
		popFromMSB = fromMSB;
		size = byteArray.size();
		byteStream = byteArray;
	}

public:
	/** Sets uint8_t array to this bitstream instance.
	 * @param[in] byteArray a uint8_t array (C array)
	 * @param[in] length length of data in the array
	 */
	void setStream(const uint8_t* byteArray, size_t length, uint16_t wordWidth = 1, int endian = Endian::Big,
			bool fromMSB = false) {
		initialize();
		byteStream.clear();
		this->size = length;
		bitpointer = 0;
		popFromMSB = fromMSB;
		temporary_buf_p tempbuf(byteArray, this->size);
		if (wordWidth == 1) {
			for (size_t i = 0; i < this->size; i++) {
				byteStream.push_back(tempbuf[i]);
			}
		} else if (wordWidth == 2) {
			for (size_t i = 0; i < this->size; i += 2) {
				if (endian == Endian::Big) {
					byteStream.push_back(tempbuf[i + 1]);
					byteStream.push_back(tempbuf[i]);
				} else if (endian == Endian::Little) {
					byteStream.push_back(tempbuf[i]);
					byteStream.push_back(tempbuf[i + 1]);
				} else {
					throw BitstreamException(BitstreamException::InvalidEndian);
				}
			}
		} else if (wordWidth == 4) {
			for (size_t i = 0; i < this->size; i += 4) {
				if (endian == Endian::Big) {
					byteStream.push_back(tempbuf[i + 3]);
					byteStream.push_back(tempbuf[i + 2]);
					byteStream.push_back(tempbuf[i + 1]);
					byteStream.push_back(tempbuf[i]);
				} else if (endian == Endian::Little) {
					byteStream.push_back(tempbuf[i]);
					byteStream.push_back(tempbuf[i + 1]);
					byteStream.push_back(tempbuf[i + 2]);
					byteStream.push_back(tempbuf[i + 3]);
				} else {
					throw BitstreamException(BitstreamException::InvalidEndian);
				}
			}
		}
	}

public:
	/** Returns current bit position.
	 * An Bitstream instance holds an internal bit position that
	 * points a certain bit in the bit stream. When a bit which
	 * the bit position pointer points is processed via e.g. pop(),
	 * the bit position is moved to the consequent bit.
	 * @return bit position
	 */
	size_t getPointer() const {
		return bitpointer;
	}

public:
	/** Dumps a result of toString() to output stream.
	 * e.g. dump(std::cout);
	 * @param[in] output stream instance (e.g. std::cout, std::cerr, instance of std::ofstream)
	 */
	void dump(std::ostream& ost) {
		using namespace std;
		ost << toString() << endl;
	}

public:
	/** Returns a string that contains the bistream in the shape of hex binary.
	 * @return stringified value of this bitstream instance
	 */
	std::string toString() {
		return toString(0, this->size);
	}

public:
	/** Returns a string that contains the bistream in the shape of hex binary.
	 * @param[in] bytePositionFrom dump start byte position
	 * @param[in] bytePositionTo dump end byte position
	 * @return stringified value of this bitstream instance
	 */
	std::string toString(size_t bytePositionFrom, size_t bytePositionTo) {
		using namespace std;
		std::stringstream ss;
		for (size_t i = bytePositionFrom; i < bytePositionTo; i++) {
			ss << hex << right << setw(2) << setfill('0') << (uint32_t) byteStream[i];
		}
		return ss.str();
	}

public:
	/** Copies byte array from the specified C array.
	 * @param[in] byteArray a uint8_t array (pointer to a C array)
	 * @param[in] length length of data in the array
	 */
	void copyStream(const uint8_t* byteArray, uint32_t length) {
		initialize();
		for (size_t i = 0; i < length; i++) {
			byteStream.push_back(byteArray[i]);
		}
		this->size = length;
	}

public:
	/**
	 *
	 */
	void push4Bytes(uint32_t value, int endian = Endian::Little) {
		if (endian == Endian::Little) {
			byteStream.push_back(value & 0xff);
			byteStream.push_back((value >> 8) & 0xff);
			byteStream.push_back((value >> 16) & 0xff);
			byteStream.push_back((value >> 24) & 0xff);
		} else if (endian == Endian::Big) {
			byteStream.push_back((value >> 24) & 0xff);
			byteStream.push_back((value >> 16) & 0xff);
			byteStream.push_back((value >> 8) & 0xff);
			byteStream.push_back(value & 0xff);
		}
	}

private:
	void putPointerBack(uint32_t nbits) {
		bitpointer -= nbits;
	}

public:
	bool isEmpty() const {
		return (bitpointer >= 8 * size);
	}

public:
	uint8_t pop1Bit() {
		uint8_t value = byteStream[bitpointer / 8];
		uint32_t rest = bitpointer % 8;
		if (bitpointer >= 8 * size) {
			return 0;
		}
		if (popFromMSB) {
			value = (value >> (7 - rest)) & 0x01;
			bitpointer += 1;
			return value;
		} else {
			value = (value >> rest) & 0x01;
			bitpointer += 1;
			return value;
		}
	}

public:
	uint8_t show1Bit() const {
		uint8_t value = byteStream[bitpointer / 8];
		uint32_t rest = bitpointer % 8;
		if (popFromMSB) {
			value = (value >> (7 - rest)) & 0x01;
			return value;
		} else {
			value = (value >> rest) & 0x01;
			return value;
		}
	}

public:
	/** Returns an integer value constructed by decoding
	 * the nBits-bit-wide data as a binary value (i.e.
	 * an unsigned integer). The bit position pointer moves
	 * when this method processes the specified bits.
	 * @param[in] nBits bit width (0 < nBits <= 32)
	 * @return unsigned integer value of nBits-bit data
	 */
	uint32_t pop(uint32_t nBits, bool reverse = false) {
		if (nBits == 0 || nBits > 32) {
			return 0;
		}
		uint32_t ret = 0;
		if (popFromMSB) {
			for (size_t i = 0; i < nBits; i++) {
				ret += ((uint32_t) this->pop1Bit() << (nBits - i - 1));
			}
		} else {
			for (size_t i = 0; i < nBits; i++) {
				ret += ((uint32_t) this->pop1Bit() << i);
			}
		}
		if (reverse) {
			ret = reverseBits((ret << (32 - nBits)));
		}
		return ret;
	}

public:
	/** Moves the bit position pointer by nBits.
	 * @param[in] nBits cursor is moved by nBits bits
	 */
	void skip(uint32_t nBits) {
		uint32_t rest = nBits;
		while (rest > 0) {
			if (rest > 32) {
				this->pop(32);
				rest -= 32;
			} else {
				this->pop(rest);
				rest = 0;
			}
		}
	}

public:
	uint32_t show(uint32_t nBits, bool reverse = false) {
		if (nBits == 0 || nBits > 32) {
			return 0;
		}
		uint32_t ret = this->pop(nBits, reverse);
		this->putPointerBack(nBits);
		return ret;
	}

public:
	/** Returns unsigned 8-bit integer value constructed
	 * from 8 bits in the bit position pointer position.
	 * The bit position pointer is shifted by 8 bits.
	 * @return uint8_t value of the 8-bit data
	 */
	uint8_t pop1Byte() {
		return this->pop(8);
	}

public:
	/** Returns unsigned 16-bit integer value constructed
	 * from 16 bits in the bit position pointer position.
	 * The bit position pointer is shifted by 16 bits.
	 * @param[in] endian Bitstream::Endian::Big or Bitstream::Endian::Little
	 * @return uint16_t value of the 16-bit data
	 */
	uint16_t pop2Bytes(int endian) {
		uint16_t lower = this->pop(8);
		uint16_t upper = this->pop(8);
		uint16_t value = 0;
		if (endian == Endian::Big) {
			value = (lower << 8) + upper;
		} else if (endian == Endian::Little) {
			value = (upper << 8) + lower;
		} else {
			throw BitstreamException(BitstreamException::InvalidEndian);
		}
		return value;
	}

public:
	/** Returns unsigned 32-bit integer value constructed
	 * from 32 bits in the bit position pointer position.
	 * The bit position pointer is shifted by 32 bits.
	 * @param[in] endian Bitstream::Endian::Big or Bitstream::Endian::Little
	 * @return uint32_t value of the 32-bit data
	 */
	uint32_t pop4Bytes(int endian) {
		uint32_t lower = this->pop2Bytes(endian);
		uint32_t upper = this->pop2Bytes(endian);
		uint32_t value = 0;
		if (endian == Endian::Big) {
			value = (lower << 16) + upper;
		} else if (endian == Endian::Little) {
			value = (upper << 16) + lower;
		} else {
			throw BitstreamException(BitstreamException::InvalidEndian);
		}
		return value;
	}

public:
	/** Returns unsigned 64-bit integer value constructed
	 * from 64 bits in the bit position pointer position.
	 * The bit position pointer is shifted by 64 bits.
	 * @param[in] endian Bitstream::Endian::Big or Bitstream::Endian::Little
	 * @return uint64_t value of the 64-bit data
	 */
	uint64_t pop8Bytes(int endian) {
		uint64_t lower = this->pop4Bytes(endian);
		uint64_t upper = this->pop4Bytes(endian);
		uint64_t value = 0;
		if (endian == Endian::Big) {
			value = (lower << 32) + upper;
		} else if (endian == Endian::Little) {
			value = (upper << 32) + lower;
		} else {
			throw BitstreamException(BitstreamException::InvalidEndian);
		}
		return value;
	}

public:
	/** Returns unsigned N*8-bit integer value constructed
	 * from N*8 bits in the bit position pointer position.
	 * The bit position pointer is shifted by N*8 bits.
	 * @param[in] nBytes byte width to be popped (should be < 8 bytes)
	 * @param[in] endian Bitstream::Endian::Big or Bitstream::Endian::Little
	 * @return uintN*8_t value of the N*8-bit data (as uint64_t)
	 */
	uint64_t popNBytes(int nBytes, int endian) {
		if (nBytes > 8) {
			throw BitstreamException(BitstreamException::InvalidByteWidth);
		}
		uint64_t ret = 0;
		if (endian == Endian::Big) {
			std::vector<uint8_t> buf;
			for (size_t i = 0; i < nBytes; i++) {
				buf.push_back(this->pop1Byte());
			}
			for (size_t i = 0; i < nBytes; i++) {
				int index = (int) buf.size() - 1 - i;
				ret += ((uint64_t) buf[index] << (i * 8));
			}
		} else if (endian == Endian::Little) {
			for (size_t i = 0; i < nBytes; i++) {
				ret += ((uint64_t) this->pop1Byte() << (i * 8));
			}
		} else {
			throw BitstreamException(BitstreamException::InvalidEndian);
		}
		return ret;
	}

public:
	uint32_t reverseBits(uint32_t val) const {
		uint32_t ret = 0;
		for (size_t i = 0; i < 32; i++) {
			ret += (((val & (1 << i)) >> i) << (31 - i));
		}
		return ret;
	}

private:
	/** Internal class used by Bitstream.
	 */
	class temporary_buf {
	private:
		const std::vector<uint8_t>& buffer;
	public:
		temporary_buf(const std::vector<uint8_t>& byteArray) :
				buffer(byteArray) {
		}
		uint8_t operator [](uint32_t index) {
			if (index < buffer.size()) {
				return buffer[index];
			} else {
				return 0;
			}
		}
	};

private:
	/** Internal class used by Bitstream.
	 */
	class temporary_buf_p {
	private:
		const uint8_t* buffer;
		uint32_t size;
	public:
		temporary_buf_p(const uint8_t* byteArray, uint32_t bytes) :
				buffer(byteArray), size(bytes) {
		}
		uint8_t operator [](uint32_t index) {
			if (index < size) {
				return buffer[index];
			} else {
				return 0;
			}
		}
	};
};

}
#endif /* BITSTREAM_HH_ */
