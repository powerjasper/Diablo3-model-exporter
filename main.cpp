#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
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
	if (argc > 2) {
		std::cout << argc;
		std::string gamePath = argv[1]; // argv 1
		std::string filename = argv[2]; // argv 2
		std::cout << gamePath << filename;
		//std::getline(std::cin, filename);

		//// file magic
		FileFinder lib(gamePath);
		std::string fullFilename = "Base\\Appearance\\" + filename + ".app";
		auto state = lib.extractFile(fullFilename);
		if (state == ERROR_SUCCESS) {
			// maybe do this check in the constructor of SnoExtractor
			SnoExtractor snoEx;
			std::string snoCSVName = "sno.csv";
			if (!std::filesystem::exists(snoCSVName))
			{

				snoEx.SnoToCsv(gamePath);

			}
			snoEx.CsvToVect(snoCSVName);

			std::cout << std::endl << fullFilename << " succes" << std::endl;
			ModelExtractor me(lib);
			std::string convertFilename = filename + ".app";
			AppFile::data model = me.convertFromFile(convertFilename, snoEx);
			me.dataToOBJ(model, filename, snoEx);

			

			return 1;
		}
		else {
			std::cout << std::endl << fullFilename << " no succes" << std::endl;
			std::cout << state;
			return 0;
		}
	}
	else {
		std::string gamePath = "F:/blizzard/Diablo III/"; // argv 1
		std::string filename = "a2dun_Zolt_black_soulstone"; // argv 2

		FileFinder lib(gamePath);
		std::string fullFilename = "Base\\Appearance\\" + filename + ".app";
		auto state = lib.extractFile(fullFilename);
		if (state == ERROR_SUCCESS) {
			// maybe do this check in the constructor of SnoExtractor
			SnoExtractor snoEx;
			std::string snoCSVName = "sno.csv";
			if (!std::filesystem::exists(snoCSVName))
			{

				snoEx.SnoToCsv(gamePath);

			}
			
			snoEx.CsvToVect(snoCSVName);

			std::cout << std::endl << fullFilename << " succes" << std::endl;
			ModelExtractor me(lib);
			std::string convertFilename = filename + ".app";
			AppFile::data model = me.convertFromFile(convertFilename, snoEx);
			me.dataToOBJ(model, filename, snoEx);



			return 1;
		}
		else {
			std::cout << std::endl << fullFilename << " no succes" << std::endl;
			std::cout << state;
			return 0;
		}
	}

	return 0;
}

