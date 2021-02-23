#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "windows.h"

#include "Interface.h"
#include "Log.h"
#include "DataTypes.h"

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

//Its possible to send online a size_t of header Size rather than the wstring itselv 
// |
// V

void PrintBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content, int baseColour, int specialColour, wchar_t wall, size_t indent)
{
	size_t hSize = header.size();
	SetConsoleTextAttribute(hConsole, baseColour);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << wall << L' ';
	std::wstring overflow = L"empty";
	if (content.size() >= (hSize - 5))
	{
		overflow = content.substr(hSize - 5, content.size() - (hSize - 5));
		wchar_t tempC = L'-';
		if (content[hSize - 6] == L' ')
			tempC = ' ';
		content = content.substr(0, hSize - 5) +  tempC;
	}
	int dif = (hSize - 3) - content.size();
	std::wstring padding = L"";
	for (size_t i = 0; i < dif / 2; i++)
		padding += ' ';
	SetConsoleTextAttribute(hConsole, baseColour);
	std::wcout << padding;
	SetConsoleTextAttribute(hConsole, specialColour);
	std::wcout << content;
	SetConsoleTextAttribute(hConsole, baseColour);
	if (hSize % 2 == 1 and content.size() % 2 == 1)
		std::wcout << ' ';
	else if (hSize % 2 == 0 and content.size() % 2 == 0)
		std::wcout << ' ';
	std::wcout << padding << wall;
	if (overflow != L"empty")
		PrintBoxStyle(header, hConsole, overflow, baseColour, specialColour, wall, indent);
	//It would be easy to make the padding left or right too!
	//| hello          |
	//|           help |
	//| break the nigh |
	//| t initial d    |
}

std::wstring AddLeadingZeroes(int num)
{
	std::wstring st = L"";
	if (num < 10 and num >= 0)
		st += L'0';
	st += std::to_wstring(num);
	return st;
}

std::wstring TmToDateOfSetupWstring(tm tm)
{
	std::wstring out = L"";
	switch (tm.tm_wday)
	{
	case 0:
		out = L"Monday ";
		break;
	case 1:
		out = L"Tuesday ";
		break;
	case 2:
		out = L"Wednesday ";
		break;
	case 3:
		out = L"Thursday ";
		break;
	case 4:
		out = L"Friday ";
		break;
	case 5:
		out = L"Saturday ";
		break;
	case 6:
		out = L"Sunday ";
		break;
	default:
		out = L"";
		break;
	}
	out += AddLeadingZeroes(tm.tm_mday) + L'-';
	out += AddLeadingZeroes(tm.tm_mon + 1) + L'-';
	out += AddLeadingZeroes(tm.tm_year + 1900);
	return out;
}

std::wstring TmToDateWstring(tm tm, wchar_t delimiter)
{
	std::wstring out = L"";
	out += AddLeadingZeroes(tm.tm_year + 1900) + delimiter;
	out += AddLeadingZeroes(tm.tm_mon + 1) + delimiter;
	out += AddLeadingZeroes(tm.tm_mday);
	return out;
}

std::wstring TmToTimeWstring(tm tm, wchar_t delimiter)
{
	std::wstring out = L"";
	out += AddLeadingZeroes(tm.tm_hour) + delimiter;
	out += AddLeadingZeroes(tm.tm_min) + delimiter;
	out += AddLeadingZeroes(tm.tm_sec);
	return out;
}

void PrintIndent(size_t indent)
{
	for (size_t i = 0; i < indent; i++)
		std::wcout << ' ';
}

void PrintInlineStyle(std::vector<std::wstring>& content, HANDLE hConsole, size_t indent, wchar_t seperator)
{

	PrintIndent(indent);
	SetConsoleTextAttribute(hConsole, WALL_COLOUR);
	std::wcout << seperator << L' ';
	for (size_t i = 0; i < content.size(); i++)
	{
		SetConsoleTextAttribute(hConsole, INLINEPRINT_COLOUR);
		std::wcout << content[i];
		SetConsoleTextAttribute(hConsole, WALL_COLOUR);
		std::wcout << L' ' << seperator;
		if (i != content.size() - 1)
			std::wcout << L' ';
	}
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
}
//Find a way to print a content field up to said amounts of chars