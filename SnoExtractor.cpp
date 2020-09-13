#include "SnoExtractor.h"


int SnoExtractor::SnoToCsv(std::string &path) {
	
	// read sno of each file at 0x10 writes it to csv. id, filename
	std::string filename = "Base\\";
	// so far Textures are the only neccesary id's more can be added here.
	std::vector<std::string> subDirectories = {"Textures", "Actor", "Particle"};
	HANDLE hStorage = NULL;
	HANDLE hFile = NULL;
	HANDLE handle = NULL;
	HANDLE findHandle = NULL;
	CASC_FIND_DATA findData;
	DWORD dwErrCode = ERROR_SUCCESS;
	// filestream
	
	std::fstream file;
	file.open("sno.csv", std::fstream::out);
	// open the storage
	for (std::string &subd : subDirectories)
	{
		std::string search = filename + subd;
		if (dwErrCode == ERROR_SUCCESS)
		{
			if (!CascOpenStorage(path.c_str(), 0, &hStorage))
				dwErrCode = GetLastError();
		}
		// find the file
		if (dwErrCode == ERROR_SUCCESS)
		{
			findHandle = CascFindFirstFile(hStorage, search.c_str(), &findData, 0);

			if (findHandle == INVALID_HANDLE_VALUE)
			{
				dwErrCode = GetLastError();
			}

		}
		// open the file
		if (dwErrCode == ERROR_SUCCESS)
		{
			if (!CascOpenFile(hStorage, findData.szFileName, 0, 0, &hFile))
				dwErrCode = GetLastError();

		}

		// write to file
		if (dwErrCode == ERROR_SUCCESS)
		{
			uint8_t  szBuffer[0x14];
			DWORD dwBytes = 1;
			CascReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes);

			// read 10 to 14 for id
			//name findData.szFileName
			std::array<uint8_t, 4>id_arr = { szBuffer[16], szBuffer[17], szBuffer[18], szBuffer[19] };
			uint32_t id = Utility::istreamToUint32(id_arr);
			std::cout << id << "," << findData.szFileName << std::endl;
			file << id << "," << findData.szFileName << std::endl;

		}
		while (GetLastError() == ERROR_SUCCESS)
		{
			if (CascFindNextFile(findHandle, &findData)) {
				// open the file
				if (dwErrCode == ERROR_SUCCESS)
				{
					if (!CascOpenFile(hStorage, findData.szFileName, 0, 0, &hFile))
						dwErrCode = GetLastError();

				}

				// write to file
				if (dwErrCode == ERROR_SUCCESS)
				{
					uint8_t  szBuffer[0x14];
					DWORD dwBytes = 1;
					CascReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes);

					// read 10 to 14 for id
					//name findData.szFileName
					std::array<uint8_t, 4>id_arr = { szBuffer[16], szBuffer[17], szBuffer[18], szBuffer[19] };
					uint32_t id = Utility::istreamToUint32(id_arr);
					std::cout << id << "," << findData.szFileName << std::endl;
					file << id << "," << findData.szFileName << std::endl;
				}
			}
			else {
				break;
			}


		}
	}
	
	file.close();
	if (handle != NULL)
		CloseHandle(handle);
	if (hFile != NULL)
		CascCloseFile(hFile);
	if (hStorage != NULL)
		CascCloseStorage(hStorage);
	return dwErrCode;
}

void SnoExtractor::CsvToVect(std::string& filename)
{
	
	std::fstream file;
	file.open(filename, std::ios::in);
	
	while (file.good()) {
		std::string id, path;
		if(std::getline(file,id,',')){
			std::getline(file,path);
			std::pair<uint32_t, std::string> idPathPair = std::make_pair(static_cast<uint32_t>(std::stoul(id)), path);
			snoVect.push_back(idPathPair);
		}
	}
	
	
	file.close();
}

uint32_t SnoExtractor::getSno(std::string& path)
{
	return (*std::find_if(snoVect.begin(), snoVect.end(), [&path](const std::pair<uint32_t, std::string>& element) {return element.second == path; })).first;
}

std::string SnoExtractor::getSno(uint32_t& id){
	return (*std::find_if(snoVect.begin(), snoVect.end(), [&id](const std::pair<uint32_t, std::string>& element) {return element.first == id; })).second;
}