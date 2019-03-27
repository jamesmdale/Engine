#pragma once
#include <string>
#include <vector>

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

protected:
	void ClearContent();

private:
	std::vector<std::string> m_content;
};