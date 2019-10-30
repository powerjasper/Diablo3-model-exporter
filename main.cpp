#include <iostream>
#include <sstream>
#include <string>

#include "FileFinder.h"
#include "ModelExtractor.h"
#include <Casclib.h>

int main(int argc, char** argv) {
	//std::string gamePath;
	//std::string filename;
	//std::cout << "Input full folder path:\n";
	//std::getline(std::cin, gamePath);
	//std::cout << std::endl << "GamePath set as \"" << gamePath  << "\"" << std::endl;
	//std::cout << "Input text to search filename for: " << std::endl;
	//std::getline(std::cin, filename);
	//std::cout << std::endl << "Filename set as \"" << filename << "\"" << std::endl;
	//// file magic
	//FileFinder lib(gamePath);
	//if (lib.extractFile(filename) == ERROR_SUCCESS) {
	//	std::cout << std::endl << "succes" << std::endl;
	//}
	//else {
	//	std::cout << std::endl << "no succes" << std::endl;
	//}

	ModelExtractor me;
	std::string converFilename = "Cain.app";
	me.convertFile(converFilename);
	return 0;
}

