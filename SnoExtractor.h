#pragma once
#include <CascLib.h>
#include "Utility.h"

#include <string>
#include <iostream>
#include <array>
#include <fstream>

class SnoExtractor
{
private:
	std::vector<std::pair<uint32_t, std::string>> snoVect;

public:
	int SnoToCsv(std::string &path);
	// int SnoToVect(std::string &path); // prob make generic sno retreive function if implementing this
	void CsvToVect(std::string &filename);
	uint32_t getSno(std::string &path);
	std::string getSno(uint32_t& id);
};

