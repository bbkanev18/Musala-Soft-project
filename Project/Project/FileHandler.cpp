#include <iostream>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <string>

#include "conio.h"
#include "windows.h"

#include "Interface.h"
#include "Log.h"
#include "DataTypes.h"
#include "FileHandler.h"

std::vector<std::wstring> GenerateWstringVector(std::string path)
{
	std::wifstream wif(path);
	std::wstringstream wss;
	std::vector<std::wstring> vec;
	std::wstring line = L"ENDOFFILE";

	//Do some research to figure out how the hell it works
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	wss << wif.rdbuf();
	wif.close();

	while (true)
	{
		getline(wss, line);
		if (line == L"ENDOFFILE")
			break;
		vec.push_back(line);
	}
	return vec;
}
//
//void SaveStudents(std::vector<STUDENT*>& stdVec, std::string path)
//{
//	std::wofstream wof(path);
//	std::wstring line = L"ENDOFFILE";
//	std::wstring delimiter = L"┃";
//
//
//	for (size_t i = 0; i < stdVec.size(); i++)
//	{
//		line.clear();
//		line += stdVec[i]->info.name + delimiter;
//		line += stdVec[i]->info.surname + delimiter;
//		line += EmailToWstring(stdVec[i]->info.email) + delimiter;
//		line += stdVec[i]->Class + delimiter;
//		line += std::to_wstring(size_t(stdVec[i]->role)) + delimiter;
//		line += std::to_wstring(int(stdVec[i]->id)) + L'\n';
//		std::wcout << line;
//	}
//
//	wof.close();
//}
//
//void LoadStudents(std::vector<STUDENT*>& stdVec, std::string path)
//{
//	std::wstring delimiter = L"┃";
//
//}
