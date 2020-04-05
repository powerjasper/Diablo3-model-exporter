#include <iostream>
#include <sstream>
#include <string>
// diablo export
#include "FileFinder.h"
#include "AppFile.h"
#include "ModelExtractor.h"
#include <CascLib.h>
#include "Utility.h"
#include "SnoExtractor.h"

uint32_t istreamToUint32(std::array<uint8_t, 4> & arr) {
	uint32_t returnVal = arr[3];
	returnVal = (returnVal << 8) + arr[2];
	returnVal = (returnVal << 8) + arr[1];
	returnVal = (returnVal << 8) + arr[0];
	return returnVal;
}

int main(int argc, char** argv) {

	std::string gamePath = "C:\\Program Files (x86)\\Diablo III\\";
	std::string filename;
	//std::cout << "Input full folder path:\n";
	//std::getline(std::cin, gamePath);

	std::cout << std::endl << "GamePath set as \"" << gamePath  << "\"" << std::endl;
	std::cout << "Input text to search filename for: " << std::endl;
	std::getline(std::cin, filename);
	std::cout << std::endl << "Filename set as \"" << filename << "\"" << std::endl;

	//// file magic
	FileFinder lib(gamePath);
	std::string fullFilename = "Base\\Appearance\\" + filename + ".app";
	if (lib.extractFile(fullFilename) == ERROR_SUCCESS) {
		std::cout << std::endl << fullFilename << " succes" << std::endl;
		ModelExtractor me(lib);
		std::string convertFilename = filename + ".app";
		AppFile::data model = me.convertFromFile(convertFilename);
		me.dataToOBJ(model, filename);


		/*
		// extracts sno from files
		SnoExtractor snoEx;
		snoEx.SnoToCsv(gamePath);*/
	}
	else {
		std::cout << std::endl << fullFilename << " no succes" << std::endl;
	}

	

	return 0;
}

