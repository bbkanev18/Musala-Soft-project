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