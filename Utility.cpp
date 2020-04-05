#include "Utility.h"

namespace Utility{

	uint32_t istreamToUint32(std::array<uint8_t, 4> & arr) {
		uint32_t returnVal = arr[3];
		returnVal = (returnVal << 8) + arr[2];
		returnVal = (returnVal << 8) + arr[1];
		returnVal = (returnVal << 8) + arr[0];
		return returnVal;
	}

	uint32_t convertEndian(uint32_t input) {
		uint32_t returnVal = (input << 24) >> 24;
		returnVal = (returnVal << 8) + ((input << 16) >> 24);
		returnVal = (returnVal << 8) + ((input << 8) >> 24);
		returnVal = (returnVal << 8) + (input >> 24);
		return returnVal;
	}

	std::stringstream toStream(std::vector<unsigned char> const& v) {
		std::stringstream ss;
		ss.write((char const*)v.data(), std::streamsize(v.size()));
		return ss;
	}
	
}

