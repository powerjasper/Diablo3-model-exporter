#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

#include "Utility.h"

namespace TexFile {
	enum pixelFormat
	{
		A8R8G8B8 = 0,
		A1R5G5B5 = 4,
		L8 = 7,
		DXT1_ = 9,
		DXT1 = 10,
		DXT3 = 11,
		DXT5 = 12,
	};

	struct header {
		uint32_t deadbeef;
		uint32_t version;
		uint32_t unkown1[2];
		uint32_t sno;
		uint32_t unkown2[3];
		uint32_t pixelformat;
		uint32_t width;
		uint32_t height;
		uint32_t faceCount;
		uint32_t unkown3[170]; // rly don't care for now

		friend std::istream& operator>>(std::istream& is, header& rhs);

		friend std::ostream& operator<<(std::ostream& os, header& rhs);
	};
	struct body
	{
		std::vector<uint32_t> color;
		std::vector<uint32_t> unkown; // unkown however neccesery
	};
}