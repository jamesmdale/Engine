#pragma once
#include <string>
#include <vector>

bool CreateFolder(const char* filePath);
LPCWSTR ConvertToLPCWSTR(const char* string);
void ReadSubFolderNamesForPath(const std::string& path, std::vector<std::string>& outFolders);
bool GetFileNameFromPath(const std::string & path, std::string & outFileName);
bool GetFileNameFromPathNoExtension(const std::string& path, std::string& outFileName);
void ReadContainedFilePathsForPath(const std::string& path, std::vector<std::string>& outFiles);
bool DoesFileExist(const std::string& path);
