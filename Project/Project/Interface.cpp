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

//Its possible to send online a size_t of header Size rather than the wstring itselv 
// |
// V

void PrintInBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content, int baseColour, int specialColour, wchar_t wall, size_t indent)
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
		PrintInBoxStyle(header, hConsole, overflow, baseColour, specialColour, wall, indent);
	//It would be easy to make the padding left or right too!
	//| hello          |
	//|           help |
	//| break the nigh |
	//| t initial d    |
}

std::wstring Add0BeforeIntSmallerThan10(int num)
{
	std::wstring st = L"";
	if (num < 10 and num >= 0)
		st += L'0';
	st += std::to_wstring(num);
	return st;
}

std::wstring TmToWstring(tm tm, BYTE args)
{
/*
Args:
	1. second
	2. minute
	3. hour
	4. day of month
	5. month
	6. year
	7. day of week
	8. day of year
*/
	switch (args)
	{
	case 1: //second
		return Add0BeforeIntSmallerThan10(tm.tm_sec);
	case 2: //minute
		return Add0BeforeIntSmallerThan10(tm.tm_min);
	case 3: //hour
		return Add0BeforeIntSmallerThan10(tm.tm_hour);
	case 4: //day of month
		return Add0BeforeIntSmallerThan10(tm.tm_mday);
	case 5: //month
		return Add0BeforeIntSmallerThan10(tm.tm_mon + 1);
	case 6: //year
		return Add0BeforeIntSmallerThan10(tm.tm_year + 1900);
	case 7: //day of week
		switch (tm.tm_wday)
		{
		case 0:
			return L"Monday";
		case 1:
			return L"Tuesday";
		case 2:
			return L"Wednesday";
		case 3:
			return L"Thursday";
		case 4:
			return L"Friday";
		case 5:
			return L"Saturday";
		case 6:
			return L"Sunday";
		default:
			return L"";
		}
	case 8: //day of year
		return Add0BeforeIntSmallerThan10(tm.tm_yday);
	default:
		return L"";
	}
}

void PrintIndent(size_t indent)
{
	for (size_t i = 0; i < indent; i++)
		std::wcout << ' ';
}
