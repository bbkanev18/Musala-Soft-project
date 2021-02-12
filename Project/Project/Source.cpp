#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "io.h"
#include "fcntl.h"
#include "windows.h"

#include "DataTypes.h"
#include "Interface.h"

int main()
{
	srand(time(NULL));
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);

	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	a = _setmode(_fileno(stdin), _O_U16TEXT);

	std::vector<std::wstring> namesList = GenerateNameVector("Database\\firstnames.txt");
	std::vector<std::wstring> surNamesList = GenerateNameVector("Database\\surnames.txt");

	std::vector<STUDENT> vec;

	//Active work!
	CreateSampleStudentVector(namesList, surNamesList, vec);
	PrintStudentVector(vec, hConsole);

	//for q&a testing!
	//AddStudentToVector(vec, EnterStudent());
	//PrintStudentVector(vec, hConsole);
}