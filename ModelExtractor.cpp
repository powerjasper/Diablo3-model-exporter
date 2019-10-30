#include "ModelExtractor.h"



ModelExtractor::ModelExtractor()
{
}


ModelExtractor::~ModelExtractor()
{

}


void ModelExtractor::convertFile(std::string &filename) {
	std::fstream infile;
	infile.open(filename, std::ios::binary);
	appFile::header head;
	infile >> head;
	std::cout << head;


	infile.close();

	std::cout << std::ifstream(filename, std::ios::binary).rdbuf();

};