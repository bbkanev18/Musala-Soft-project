#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "windows.h"

#include "Interface.h"

std::vector<std::wstring> GenerateNameVector(std::string path)
{
	std::vector<std::wstring> vec;

	std::wstring line;
	std::wifstream File(path);

	while (true)
	{
		getline(File, line);
		if (line == L"")
			break;
		vec.push_back(line);
	}
	File.close();
	return vec;
}

void PrintInBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content, int baseColour, int specialColour)
{
	SetConsoleTextAttribute(hConsole, baseColour);
	std::wcout << L"\n┃";
	std::wstring overflow = L"empty";
	if (content.size() >= (header.size() - 5))
	{
		overflow = content.substr(header.size() - 5, content.size() - (header.size() - 5));
		wchar_t tempC = L'-';
		if (content[header.size() - 6] == L' ')
			tempC = ' ';
		content = content.substr(0, header.size() - 5) +  tempC;
	}
	int dif = (header.size() - 3) - content.size();
	if (dif % 2 == 1)
		std::wcout << ' ';
	std::wstring padding = L"";
	for (size_t i = 0; i < dif / 2; i++)
		padding += ' ';
	SetConsoleTextAttribute(hConsole, baseColour);
	std::wcout << padding;
	SetConsoleTextAttribute(hConsole, specialColour);
	std::wcout << content;
	SetConsoleTextAttribute(hConsole, baseColour);
	std::wcout << padding << L'┃';
	if (overflow != L"empty")
		PrintInBoxStyle(header, hConsole, overflow, baseColour, specialColour);
	//It would be easy to make the padding left or right too!
	//| hello          |
	//|           help |
	//| break the nigh |
	//| t initial d    |
}

