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
bool GetFileNameFromPath(const std::string& path, std::string& outFileName)
{
	std::experimental::filesystem::path fileSystemPath = path.c_str();

	if (!fileSystemPath.has_extension())
		return false; //not a file

	outFileName = fileSystemPath.filename().string();
	return true;
}

//  =========================================================================================
bool GetFileNameFromPathNoExtension(const std::string& path, std::string& outFileName)
{
	std::experimental::filesystem::path fileSystemPath = path.c_str();

	if (!fileSystemPath.has_extension())
		return false; //not a file

	fileSystemPath.replace_extension("");
	outFileName = fileSystemPath.filename().string();
	return true;
}

//  =========================================================================================
void ReadContainedFilePathsForPath(const std::string& path, std::vector<std::string>& outFiles)
{
	for (std::experimental::filesystem::directory_entry entry : std::experimental::filesystem::directory_iterator(path.c_str()))
	{
		//directories won't have extensions
		if(entry.path().has_extension())
			outFiles.push_back(entry.path().string());
	}
}

