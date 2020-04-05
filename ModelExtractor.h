#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>

#include "Utility.h"
#include "AppFile.h"
#include <CascLib.h>
#include "FileFinder.h"

class ModelExtractor
{
private:
	std::vector<unsigned char> filebuffer;
	FileFinder& lib;

public:
	ModelExtractor(FileFinder& lib);
	~ModelExtractor();

	AppFile::data convertFromFile(std::string & fileName);
	int dataToOBJ(AppFile::data& data, std::string name);
};


