#include "Engine\Core\WindowsCommon.hpp"
#include "Engine\File\FileHelpers.hpp"
#include <experimental\filesystem>
#include <stdio.h>

//  =============================================================================
bool CreateFolder(const char* filePath)
{
	LPCWSTR convertedPath = ConvertToLPCWSTR(filePath);
	return CreateDirectory(convertedPath, NULL) ? true : false;
}

//  =============================================================================
LPCWSTR ConvertToLPCWSTR(const char* string)
{
	wchar_t wString[4096];
	MultiByteToWideChar(CP_ACP, 0, string, -1, wString, 4096);
	return wString;
}

//  =========================================================================================
void ReadSubFolderNamesForPath(const std::string& path, std::vector<std::string>& outFolders)
{
	std::experimental::filesystem::directory_iterator iterator(path.c_str());
	std::experimental::filesystem::directory_iterator end; //default constructor is end

	while (iterator != end)
	{
		outFolders.push_back(iterator->path().string());
		iterator++;
	}
}

//  =========================================================================================
void ReadContainedFileNamesForPath(const std::string& path, std::vector<std::string>& outFiles)
{
	//for (std::experimental::filesystem::directory_entry entry : std::experimental::filesystem::directory_iterator(path.c_str()))
	//{
	//	outFolders.push_back(entry.path().string());
	//}
}
