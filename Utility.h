#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace Utility {
	uint32_t istreamToUint32(std::array<uint8_t, 4> & arr);
	uint32_t convertEndian(uint32_t input);



	std::stringstream toStream(std::vector<unsigned char> const& v);


	/* templating FML*/

	template <class T>
	std::vector<T> vectorResize(std::vector<T> inputV, size_t start, size_t end) {
		std::vector<T> newV;
		for (size_t i = start; i < end; i++)
		{
			newV.push_back(inputV[i]);
		}

		return newV;
	}


	
}