#pragma once
#include <string>
#include <vector>

constexpr int MAX_SIMULATION_DATA_CSV_SIZE = 10'000'000;

class CSVEditor
{
public:
	CSVEditor();
	~CSVEditor();

	virtual void AddCell(const std::string& cellContent, bool doesWriteNewline = false);
	virtual void AddNewLine();
	virtual void AppendNewLine();

	bool WriteToFile(const std::string& filePath);
	bool ReadFromFile(const std::string& filePath);
	void ClearContent();

public:
	std::vector<std::string> m_content;
};