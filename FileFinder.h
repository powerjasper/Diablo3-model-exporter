#pragma once
#include <CascLib.h>

#include <string>
#include <iostream>

//casclib wrapper
class FileFinder
{
private:
	std::string &path;

public:
	FileFinder(std::string &path);
	int extractFile(std::string &filename);
	int extractFile(uint32_t &fileId);

	~FileFinder();
};
