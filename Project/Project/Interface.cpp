#include <iostream>
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
	int dif = (header.size() - 3) - content.size();
	if (dif % 2 == 1)
		std::wcout << ' ';
	std::wstring padding = L"";
	for (size_t i = 0; i < dif / 2; i++)
		padding += ' ';
	std::wcout << padding << content << padding << L'┃';
	//It would be easy to make the padding left or right too!
	//| hello          |
	//|           help |
}

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