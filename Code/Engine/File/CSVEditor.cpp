#include "Engine\File\CSVEditor.hpp"
#include "Engine\Core\StringUtils.hpp"
#include "Engine\File\File.hpp"

//  =============================================================================
CSVEditor::CSVEditor()
{
}

//  =============================================================================
CSVEditor::~CSVEditor()
{
}

//  =============================================================================
void CSVEditor::AddCell(const std::string& cellContent, bool doesWriteNewline)
{
	if (IsStringNullOrEmpty(cellContent))
	{
		m_content.push_back("");
		return;
	}

	if (DoesStringContainCharacter(cellContent, ','))
	{
		m_content.push_back(Stringf("\"%s\"", cellContent.c_str()));
		return;
	}

	m_content.push_back(cellContent);

	if (doesWriteNewline)
	{
		AppendNewLine();
	}
}

//  =============================================================================
void CSVEditor::AddNewLine()
{
	m_content.push_back("\n");
}

//  =============================================================================
void CSVEditor::AppendNewLine()
{
	m_content[m_content.size() - 1].append("\n");
}

//  =============================================================================
bool CSVEditor::WriteToFile(const std::string& filePath)
{
	//create a final newline to end writing
	std::ofstream writer(filePath.c_str());

	for (int contentIndex = 0; contentIndex < (int)m_content.size(); ++contentIndex)
	{
		if (!writer.is_open())
			return false;

		writer << Stringf("%s", m_content[contentIndex].c_str());

		//check the next cell to see if we need a comma separator or not
		if (contentIndex + 1 < (int)m_content.size() && contentIndex - 1 >= 0)
		{
			if(StringCompareExact(m_content[contentIndex + 1], "\n") || StringCompareExact(m_content[contentIndex - 1], "\n"))
				writer << ",";
		}
	}

	writer.close();

	return true;
}

//  =========================================================================================
bool CSVEditor::ReadFromFile(const std::string& filePath)
{
	//create a final newline to end writing
	std::ifstream reader(filePath.c_str());
	std::string line;

	if (!reader.is_open())
		return false;

	while (getline(reader, line))
	{
		m_content.push_back(line);
	}

	reader.close();

	return true;
}

//  =============================================================================
void CSVEditor::ClearContent()
{
	m_content.clear();
}
