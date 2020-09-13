#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

#include "Utility.h"
#include "texFile.h"


class ImageExtractor
{
private:
	static const uint32_t headerSize = 728;
	static bool dxt1ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header);
	static bool dxt3ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header);
	static bool dxt5ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header);
public:
	static bool TextToPng(std::string &fileName);
};

