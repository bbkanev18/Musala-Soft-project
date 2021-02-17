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

	std::vector<std::wstring> namesList =   GenerateNameVector("Database\\firstnames.txt");
	std::vector<std::wstring> surnamesList = GenerateNameVector("Database\\surnames.txt");
	std::vector<std::wstring> teamNamesList = GenerateNameVector("Database\\teamnames.txt");

	//TEAM testing site

	//std::vector<TEAM> tvec;
	//CreateSampleTeamVector(teamNamesList, namesList, surnamesList, tvec);
	//PrintTeamVector(tvec, hConsole, true);


	//STUDENT testing site

	//std::vector<STUDENT> stvec;
	//CreateSampleStudentVector(namesList, surnamesList, stvec, 50);
	//PrintStudentVector(stvec, hConsole, false);
	//PrintStudentVector(stvec, hConsole, true);

	
}