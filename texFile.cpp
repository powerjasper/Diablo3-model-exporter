#include "texFile.h"

namespace TexFile {
	std::istream& operator>>(std::istream& is, header& rhs) {

		is.read(reinterpret_cast<char *>(&rhs.deadbeef), sizeof(rhs.deadbeef));
		is.read(reinterpret_cast<char *>(&rhs.version), sizeof(rhs.version));
		is.read(reinterpret_cast<char *>(&rhs.unkown1), sizeof(rhs.unkown1));
		is.read(reinterpret_cast<char *>(&rhs.sno), sizeof(rhs.sno));
		is.read(reinterpret_cast<char *>(&rhs.unkown2), sizeof(rhs.unkown2));
		is.read(reinterpret_cast<char *>(&rhs.pixelformat), sizeof(rhs.pixelformat));
		is.read(reinterpret_cast<char *>(&rhs.width), sizeof(rhs.width));
		is.read(reinterpret_cast<char *>(&rhs.height), sizeof(rhs.height));
		is.read(reinterpret_cast<char *>(&rhs.faceCount), sizeof(rhs.faceCount));
		is.read(reinterpret_cast<char *>(&rhs.unkown3), sizeof(rhs.unkown3));


		// Just so we know our stream is intended endian
		bool goodEndian = false;
		if (rhs.deadbeef == 3735928559)
		{
			goodEndian = true;
		}

		if (!goodEndian)
		{
			rhs.deadbeef = Utility::convertEndian(rhs.deadbeef);
			rhs.version = Utility::convertEndian(rhs.version);
			rhs.sno = Utility::convertEndian(rhs.sno);
			rhs.pixelformat = Utility::convertEndian(rhs.pixelformat);
			rhs.width = Utility::convertEndian(rhs.width);
			rhs.height = Utility::convertEndian(rhs.height);
			rhs.faceCount = Utility::convertEndian(rhs.faceCount);

		}



		return is;
	}

	std::ostream& operator<<(std::ostream& os, header& rhs) {
		os << "---------HEADER Chunk---------" << std::endl;
		os << "Deadbeef: " << ((rhs.deadbeef == 3735928559) ? "true" : "false") << std::endl;
		os << "Version: " << rhs.version << std::endl;
		os << "SNO: " << rhs.sno << std::endl;
		os << "Pixelformat: " << rhs.pixelformat << std::endl;
		os << "width: " << rhs.width << std::endl;
		os << "height: " << rhs.height << std::endl;
		os << "faceCount: " << rhs.faceCount << std::endl;
		os << "------------------------------" << std::endl;
		return os;
	}
}

