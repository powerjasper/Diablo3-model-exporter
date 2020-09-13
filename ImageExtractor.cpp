#include "ImageExtractor.h"

bool ImageExtractor::dxt1ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header) {
	std::cout << "In dxt1ToPng" << std::endl;
	//filename
	std::vector<std::string> filenameVect;
	std::istringstream ss(fileName);
	std::string tmpString;
	while (ss.good())
	{
		std::getline(ss, tmpString, '.');
		filenameVect.push_back(tmpString);
	}
	std::string imageFileName = filenameVect[0] + ".png";
	
	// loading
	uint32_t infoCount = (header.height * header.width) / 4; // 4 = compression ratio of dxt1
	std::stringstream colorStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, headerSize, (infoCount + headerSize)));
	std::stringstream otherStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, (headerSize + infoCount), ((infoCount*2) + headerSize)));
	
	std::vector<uint32_t> colorVect, OtherVect;
	uint32_t tmpColor, tmpOther;
	for (size_t i = 0; i < infoCount; i++)
	{
		colorStream.read(reinterpret_cast<char *>(&tmpColor), sizeof(tmpColor));
		otherStream.read(reinterpret_cast<char *>(&tmpOther), sizeof(tmpOther));
		colorVect.push_back(tmpColor);
		OtherVect.push_back(tmpOther);
	}
	
	//saving to file
	//dds
	uint32_t dwMagic = 542327876; // standard
	uint32_t dwSize = 124; // standard
	uint32_t dwFlags = 4103;
	uint32_t dwHeight = header.height;
	uint32_t dwWidth = header.width;
	uint32_t dwPitchOrLinearSize = 0;
	uint32_t dwDepth = 0;
	uint32_t dwMipMapCount = 0;
	uint32_t dwReserved1[11] = { 0 };
	uint32_t pf_dwSize = 32; // 32 bit
	uint32_t pf_dwFlags = 4; // DDPF_FOURCC	Texture contains compressed RGB data; dwFourCC contains valid data.	0x4
	uint32_t pf_dwFourCC = 827611204; // spells DXT1
	uint32_t pf_dwRGBBitCount = 0;
	uint32_t pf_dwRBitMask = 0;
	uint32_t pf_dwGBitMask = 0;
	uint32_t pf_dwBBitMask = 0;
	uint32_t pf_dwABitMask = 0;
	uint32_t dwCaps = 0;
	uint32_t dwCaps2 = 0;
	uint32_t dwCaps3 = 0;
	uint32_t dwCaps4 = 0;
	uint32_t dwReserved2 = 0;

	// create file
	
	std::fstream file;
	file.open(imageFileName, std::ios::out | std::ios::binary);
	// oneline all the bs
	//file <<  dwMagic << dwSize << dwFlags << dwHeight << dwWidth << dwPitchOrLinearSize << dwDepth << dwMipMapCount << dwReserved1[11] << pf_dwSize << pf_dwFlags << pf_dwFourCC << pf_dwRGBBitCount << pf_dwRBitMask << pf_dwGBitMask << pf_dwBBitMask << pf_dwABitMask << dwCaps << dwCaps2 << dwCaps3 << dwCaps4 << dwReserved2;
	file.write((char*)&dwMagic, sizeof(dwMagic));
	file.write((char*)&dwSize, sizeof(dwSize));
	file.write((char*)&dwFlags, sizeof(dwFlags));
	file.write((char*)&dwHeight, sizeof(dwHeight));
	file.write((char*)&dwWidth, sizeof(dwWidth));
	file.write((char*)&dwPitchOrLinearSize, sizeof(dwPitchOrLinearSize));
	file.write((char*)&dwDepth, sizeof(dwDepth));
	file.write((char*)&dwMipMapCount, sizeof(dwMipMapCount));
	file.write((char*)&dwReserved1, sizeof(dwReserved1));
	file.write((char*)&pf_dwSize, sizeof(pf_dwSize));
	file.write((char*)&pf_dwFlags, sizeof(pf_dwFlags));
	file.write((char*)&pf_dwFourCC, sizeof(pf_dwFourCC));
	file.write((char*)&pf_dwRGBBitCount, sizeof(pf_dwRGBBitCount));
	file.write((char*)&pf_dwRBitMask, sizeof(pf_dwRBitMask));
	file.write((char*)&pf_dwGBitMask, sizeof(pf_dwGBitMask));
	file.write((char*)&pf_dwBBitMask, sizeof(pf_dwBBitMask));
	file.write((char*)&pf_dwABitMask, sizeof(pf_dwABitMask));
	file.write((char*)&dwCaps, sizeof(dwCaps));
	file.write((char*)&dwCaps2, sizeof(dwCaps2));
	file.write((char*)&dwCaps3, sizeof(dwCaps3));
	file.write((char*)&dwCaps4, sizeof(dwCaps4));
	file.write((char*)&dwReserved2, sizeof(dwReserved2));
	//fill file with color & other
	std::cout << "info count :" << infoCount << std::endl;
	for (size_t i = 0; i < (infoCount / 4); i++)
	{
		file.write((char*)&colorVect[i], sizeof(colorVect[i]));
		file.write((char*)&OtherVect[i], sizeof(OtherVect[i]));
	}
	
	
	file.close();


	return true;
}
bool ImageExtractor::dxt3ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header) {
	std::cout << "In dxt3ToPng" << std::endl;
	//filename
	std::vector<std::string> filenameVect;
	std::istringstream ss(fileName);
	std::string tmpString;
	while (ss.good())
	{
		std::getline(ss, tmpString, '.');
		filenameVect.push_back(tmpString);
	}
	std::string imageFileName = filenameVect[0] + ".png";

	// loading
	uint32_t infoCount = (header.height * header.width) / 4;
	std::cout << "InfoCount: " << infoCount << std::endl;
	// 2d8 eerste 8 bytes
	std::stringstream colorStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, headerSize, (infoCount*2 + headerSize)));
	std::stringstream otherStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, (headerSize + infoCount*2), ((infoCount * 3) + headerSize)));
	std::stringstream alphaStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, (headerSize + infoCount * 3), ((infoCount * 4) + headerSize)));
	std::vector<uint64_t> colorVect;
	std::vector<uint32_t> otherVect, alphaVect;
	uint64_t tmpColor;
	uint32_t tmpOther, tmpAlpha;
	for (size_t i = 0; i < infoCount; i++)
	{
		colorStream.read(reinterpret_cast<char *>(&tmpColor), sizeof(tmpColor));
		otherStream.read(reinterpret_cast<char *>(&tmpOther), sizeof(tmpOther));
		alphaStream.read(reinterpret_cast<char *>(&tmpAlpha), sizeof(tmpAlpha));
		colorVect.push_back(tmpColor);
		otherVect.push_back(tmpOther);
		alphaVect.push_back(tmpAlpha);
	}

	//saving to file
	//dds
	uint32_t dwMagic = 542327876; // standard
	uint32_t dwSize = 124; // standard
	uint32_t dwFlags = 4103;
	uint32_t dwHeight = header.height;
	uint32_t dwWidth = header.width;
	uint32_t dwPitchOrLinearSize = 0;
	uint32_t dwDepth = 0;
	uint32_t dwMipMapCount = 0;
	uint32_t dwReserved1[11] = { 0 };
	uint32_t pf_dwSize = 32; // 32 bit
	uint32_t pf_dwFlags = 4; // DDPF_FOURCC	Texture contains compressed RGB data; dwFourCC contains valid data.	0x4
	uint32_t pf_dwFourCC = 861165636; // spells DXT3
	uint32_t pf_dwRGBBitCount = 0;
	uint32_t pf_dwRBitMask = 0;
	uint32_t pf_dwGBitMask = 0;
	uint32_t pf_dwBBitMask = 0;
	uint32_t pf_dwABitMask = 0;
	uint32_t dwCaps = 0;
	uint32_t dwCaps2 = 0;
	uint32_t dwCaps3 = 0;
	uint32_t dwCaps4 = 0;
	uint32_t dwReserved2 = 0;

	// create file

	std::fstream file;
	file.open(imageFileName, std::ios::out | std::ios::binary);
	// oneline all the bs
	//file <<  dwMagic << dwSize << dwFlags << dwHeight << dwWidth << dwPitchOrLinearSize << dwDepth << dwMipMapCount << dwReserved1[11] << pf_dwSize << pf_dwFlags << pf_dwFourCC << pf_dwRGBBitCount << pf_dwRBitMask << pf_dwGBitMask << pf_dwBBitMask << pf_dwABitMask << dwCaps << dwCaps2 << dwCaps3 << dwCaps4 << dwReserved2;
	file.write((char*)&dwMagic, sizeof(dwMagic));
	file.write((char*)&dwSize, sizeof(dwSize));
	file.write((char*)&dwFlags, sizeof(dwFlags));
	file.write((char*)&dwHeight, sizeof(dwHeight));
	file.write((char*)&dwWidth, sizeof(dwWidth));
	file.write((char*)&dwPitchOrLinearSize, sizeof(dwPitchOrLinearSize));
	file.write((char*)&dwDepth, sizeof(dwDepth));
	file.write((char*)&dwMipMapCount, sizeof(dwMipMapCount));
	file.write((char*)&dwReserved1, sizeof(dwReserved1));
	file.write((char*)&pf_dwSize, sizeof(pf_dwSize));
	file.write((char*)&pf_dwFlags, sizeof(pf_dwFlags));
	file.write((char*)&pf_dwFourCC, sizeof(pf_dwFourCC));
	file.write((char*)&pf_dwRGBBitCount, sizeof(pf_dwRGBBitCount));
	file.write((char*)&pf_dwRBitMask, sizeof(pf_dwRBitMask));
	file.write((char*)&pf_dwGBitMask, sizeof(pf_dwGBitMask));
	file.write((char*)&pf_dwBBitMask, sizeof(pf_dwBBitMask));
	file.write((char*)&pf_dwABitMask, sizeof(pf_dwABitMask));
	file.write((char*)&dwCaps, sizeof(dwCaps));
	file.write((char*)&dwCaps2, sizeof(dwCaps2));
	file.write((char*)&dwCaps3, sizeof(dwCaps3));
	file.write((char*)&dwCaps4, sizeof(dwCaps4));
	file.write((char*)&dwReserved2, sizeof(dwReserved2));
	//fill file with color & other

	for (size_t i = 0; i < (infoCount/4); i++)
	{
		file.write((char*)&colorVect[i], sizeof(colorVect[i]));
		file.write((char*)&otherVect[i], sizeof(otherVect[i]));
		file.write((char*)&alphaVect[i], sizeof(alphaVect[i]));
	}


	file.close();


	return true;
}

bool ImageExtractor::dxt5ToPng(std::string &fileName, const std::vector<unsigned char> &filebuffer, TexFile::header &header) {
	std::cout << "In dxt5ToPng" << std::endl;
	//filename
	std::vector<std::string> filenameVect;
	std::istringstream ss(fileName);
	std::string tmpString;
	while (ss.good())
	{
		std::getline(ss, tmpString, '.');
		filenameVect.push_back(tmpString);
	}
	std::string imageFileName = filenameVect[0] + ".png";

	// loading
	uint32_t infoCount = (header.height * header.width) / 4;
	uint32_t curPos;
	std::cout << "InfoCount: " << infoCount << std::endl;
	
	curPos = infoCount / 2;
	std::stringstream streamOne = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, headerSize, (curPos + headerSize))); // 16
	curPos = curPos + headerSize;
	std::stringstream streamTwo = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, curPos, (int(infoCount * 1.5) + curPos))); // 48
	curPos = int(infoCount * 1.5) + curPos;
	std::stringstream streamThree = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, curPos, (curPos + infoCount)));
	curPos = curPos + infoCount;
	std::stringstream streamFour = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, curPos, (curPos + infoCount)));

	std::vector<uint16_t> vectOne, vectTwoP1;
	std::vector<uint32_t> vectTwoP2, vectThree, vectFour;
	uint16_t tmpOne, tmpTwoP1;
	uint32_t tmpTwoP2, tmpThree, tmpFour;
	for (size_t i = 0; i < infoCount; i++)
	{
		streamOne.read(reinterpret_cast<char *>(&tmpOne), sizeof(tmpOne));
		streamTwo.read(reinterpret_cast<char *>(&tmpTwoP1), sizeof(tmpTwoP1));
		streamTwo.read(reinterpret_cast<char *>(&tmpTwoP2), sizeof(tmpTwoP2));
		streamThree.read(reinterpret_cast<char *>(&tmpThree), sizeof(tmpThree));
		streamFour.read(reinterpret_cast<char *>(&tmpFour), sizeof(tmpFour));
		vectOne.push_back(tmpOne);
		vectTwoP1.push_back(tmpTwoP1);
		vectTwoP2.push_back(tmpTwoP2);
		vectThree.push_back(tmpThree);
		vectFour.push_back(tmpFour);
	}

	//saving to file
	//dds
	uint32_t dwMagic = 542327876; // standard
	uint32_t dwSize = 124; // standard
	uint32_t dwFlags = 4103;
	uint32_t dwHeight = header.height;
	uint32_t dwWidth = header.width;
	uint32_t dwPitchOrLinearSize = 0;
	uint32_t dwDepth = 0;
	uint32_t dwMipMapCount = 0;
	uint32_t dwReserved1[11] = { 0 };
	uint32_t pf_dwSize = 32; // 32 bit
	uint32_t pf_dwFlags = 4; // DDPF_FOURCC	Texture contains compressed RGB data; dwFourCC contains valid data.	0x4
	uint32_t pf_dwFourCC = 894720068; // spells DXT5
	uint32_t pf_dwRGBBitCount = 0;
	uint32_t pf_dwRBitMask = 0;
	uint32_t pf_dwGBitMask = 0;
	uint32_t pf_dwBBitMask = 0;
	uint32_t pf_dwABitMask = 0;
	uint32_t dwCaps = 0;
	uint32_t dwCaps2 = 0;
	uint32_t dwCaps3 = 0;
	uint32_t dwCaps4 = 0;
	uint32_t dwReserved2 = 0;

	// create file

	std::fstream file;
	file.open(imageFileName, std::ios::out | std::ios::binary);
	// oneline all the bs
	//file <<  dwMagic << dwSize << dwFlags << dwHeight << dwWidth << dwPitchOrLinearSize << dwDepth << dwMipMapCount << dwReserved1[11] << pf_dwSize << pf_dwFlags << pf_dwFourCC << pf_dwRGBBitCount << pf_dwRBitMask << pf_dwGBitMask << pf_dwBBitMask << pf_dwABitMask << dwCaps << dwCaps2 << dwCaps3 << dwCaps4 << dwReserved2;
	file.write((char*)&dwMagic, sizeof(dwMagic));
	file.write((char*)&dwSize, sizeof(dwSize));
	file.write((char*)&dwFlags, sizeof(dwFlags));
	file.write((char*)&dwHeight, sizeof(dwHeight));
	file.write((char*)&dwWidth, sizeof(dwWidth));
	file.write((char*)&dwPitchOrLinearSize, sizeof(dwPitchOrLinearSize));
	file.write((char*)&dwDepth, sizeof(dwDepth));
	file.write((char*)&dwMipMapCount, sizeof(dwMipMapCount));
	file.write((char*)&dwReserved1, sizeof(dwReserved1));
	file.write((char*)&pf_dwSize, sizeof(pf_dwSize));
	file.write((char*)&pf_dwFlags, sizeof(pf_dwFlags));
	file.write((char*)&pf_dwFourCC, sizeof(pf_dwFourCC));
	file.write((char*)&pf_dwRGBBitCount, sizeof(pf_dwRGBBitCount));
	file.write((char*)&pf_dwRBitMask, sizeof(pf_dwRBitMask));
	file.write((char*)&pf_dwGBitMask, sizeof(pf_dwGBitMask));
	file.write((char*)&pf_dwBBitMask, sizeof(pf_dwBBitMask));
	file.write((char*)&pf_dwABitMask, sizeof(pf_dwABitMask));
	file.write((char*)&dwCaps, sizeof(dwCaps));
	file.write((char*)&dwCaps2, sizeof(dwCaps2));
	file.write((char*)&dwCaps3, sizeof(dwCaps3));
	file.write((char*)&dwCaps4, sizeof(dwCaps4));
	file.write((char*)&dwReserved2, sizeof(dwReserved2));
	//fill file with color & other

	for (size_t i = 0; i < (infoCount / 4); i++)
	{
		file.write((char*)&vectOne[i], sizeof(vectOne[i]));
		file.write((char*)&vectTwoP1[i], sizeof(vectTwoP1[i]));
		file.write((char*)&vectTwoP2[i], sizeof(vectTwoP2[i]));
		file.write((char*)&vectThree[i], sizeof(vectThree[i]));
		file.write((char*)&vectFour[i], sizeof(vectFour[i]));
	}


	file.close();


	return true;
}


bool ImageExtractor::TextToPng(std::string &fileName) {
	std::ifstream infile;
	std::vector<unsigned char> filebuffer;
	infile.open(fileName, std::ios::binary);
	unsigned char bufferChar;
	while (infile >> std::noskipws >> bufferChar) {
		filebuffer.push_back(bufferChar);
	}
	infile.close();

	TexFile::header header;

	//header
	std::stringstream headerStream = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, 0, headerSize));
	headerStream >> header;
	std::cout << header;
	//call the correct image converter
	bool result = false;
	switch (header.pixelformat)
	{
	case TexFile::pixelFormat::DXT1_:
		result = dxt1ToPng(fileName, filebuffer, header);
		break;
	case TexFile::pixelFormat::DXT3:
		result = dxt3ToPng(fileName, filebuffer, header);
		break;
	case TexFile::pixelFormat::DXT5:
		result = dxt5ToPng(fileName, filebuffer, header);
		break;
	default:
		std::cout << "pixelFormat switch on: " << header.pixelformat << std::endl;
		break;
	}
	return result;
}