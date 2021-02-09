﻿#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
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

void PrintInBoxStyle(std::wstring header, std::wstring content) 
{
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
	std::wcout << padding << content << padding << L'┃';
	if (overflow != L"empty")
	{
		PrintInBoxStyle(header, overflow);
	}
	//It would be easy to make the padding left or right too!
	//| hello          |
	//|           help |
	//| break the nigh |
	//| t initial d    |
}
//Create overflow preventions!!!!

/*
string line;
int random = 0;
int numOfLines = 0;
ifstream File("file.txt");

	srand(time(0));
	random = rand() % 50;

while(getline(File, line))
{
	++numOfLines;

	if(numOfLines == random)
	{
		cout << line;
	}

}
*/