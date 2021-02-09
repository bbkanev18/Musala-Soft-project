#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "io.h"
#include "fcntl.h"

#include "DataTypes.h"
#include "Interface.h"

int main()
{
	srand(time(NULL));

	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	a = _setmode(_fileno(stdin), _O_U16TEXT);

	std::vector<std::wstring> NamesList = GenerateNameVector("Database\\firstnames.txt");
	std::vector<std::wstring> SurNamesList = GenerateNameVector("Database\\surnames.txt");

	STUDENT st = CreateSampleStudent(NamesList, SurNamesList);

}