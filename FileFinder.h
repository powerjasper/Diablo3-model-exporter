#pragma once
#include <string>
#include <CascLib.h>
#include <iostream>

//casclib wrapper
class FileFinder
{
private:
	std::string &path;

public:
	FileFinder(std::string &path);
	int extractFile(std::string &filename);

	~FileFinder();
};
