#pragma once
#include <string>
#include <vector>

bool CreateFolder(const char* filePath);
LPCWSTR ConvertToLPCWSTR(const char* string);
void ReadSubFolderNamesForPath(const std::string& path, std::vector<std::string>& outFolders);
void ReadContainedFileNamesForPath(const std::string& path, std::vector<std::string>& outFiles);