#include "FileFinder.h"



FileFinder::FileFinder(std::string &path):
	path(path)
{
	
}

int FileFinder::extractFile(std::string & filename)
{
	HANDLE hStorage = NULL;
	HANDLE hFile = NULL;
	HANDLE handle = NULL;
	HANDLE findHandle = NULL;
	CASC_FIND_DATA findData;
	DWORD dwErrCode = ERROR_SUCCESS;

	// open the storage
	if (dwErrCode == ERROR_SUCCESS)
	{
		if (!CascOpenStorage(path.c_str(), 0, &hStorage))
			dwErrCode = GetLastError();
	}
	// find the file
	if(dwErrCode == ERROR_SUCCESS)
	{
		findHandle = CascFindFirstFile(hStorage, filename.c_str(), &findData, 0);

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
	// create new file
	if (dwErrCode == ERROR_SUCCESS)
	{
		
		handle = CreateFile(findData.szPlainName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
		if (handle == INVALID_HANDLE_VALUE)
			dwErrCode = GetLastError();
	}

	// write to file
	if (dwErrCode == ERROR_SUCCESS)
	{
		char  szBuffer[0x10000];
		DWORD dwBytes = 1;

		while (dwBytes != 0)
		{
			CascReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes);
			if (dwBytes == 0)
				break;

			WriteFile(handle, szBuffer, dwBytes, &dwBytes, NULL);
			if (dwBytes == 0)
				break;
		}
	}
	if (handle != NULL)
		CloseHandle(handle);
	if (hFile != NULL)
		CascCloseFile(hFile);
	if (hStorage != NULL)
		CascCloseStorage(hStorage);
	return dwErrCode;
}


FileFinder::~FileFinder()
{
}
