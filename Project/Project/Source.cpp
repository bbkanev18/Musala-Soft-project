#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "io.h"
#include "fcntl.h"
#include "windows.h"

#include "DataTypes.h"
#include "Interface.h"
#include "Log.h"

//_log is global in order to save time and effort of passing it to every function
LOG _log;

int main()
{
	_log.severityFilter = SEVERITY::Debug;
	CreateSaveDir();
	if (_log.Open(L"c:\\ProjectSaveFiles\\Musala_Soft_Project\\Logs\\logs.log"))
	{
		_log.MakeLog(SEVERITY::Debug, L"Program has started successfully");

		srand(time(NULL));

		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);

		int a = _setmode(_fileno(stdout), _O_U16TEXT);
		a = _setmode(_fileno(stdin), _O_U16TEXT);

		std::vector<std::wstring> namesList =   GenerateNameVector("Database\\firstnames.txt");
		std::vector<std::wstring> surnamesList = GenerateNameVector("Database\\surnames.txt");
		std::vector<std::wstring> teamNamesList = GenerateNameVector("Database\\teamnames.txt");

		/////////////////////////////////////////////////////////////////////////////////////
		//TEAM testing site

		//TEAM team = EnterTeam();
		//BoxPrintTeam(team, hConsole);
	
		//TEAM vector testing site

		std::vector<TEAM> tvec;
		CreateSampleTeamVector(teamNamesList, namesList, surnamesList, tvec, 5);
		BoxPrintTeamVector(tvec, hConsole, true);
		//std::wcout << L"\n\n\n";
		//BoxPrintTeamVector(tvec, hConsole, false);
		//std::wcout << L"\n\n\n";

	
		/////////////////////////////////////////////////////////////////////////////////////
		//STUDENT testing site

		//STUDENT st = EnterStudent();
		//BoxPrintStudent(st, hConsole);
		//std::wcout << L"\n\n\n";
		//InlinePrintStudent(st, hConsole);

		//STUDENT vector testing site

		//std::vector<STUDENT> stvec;
		//CreateSampleStudentVector(namesList, surnamesList, stvec, 50);
		//PrintStudentVector(stvec, hConsole, false);
		//PrintStudentVector(stvec, hConsole, true);

	
		/////////////////////////////////////////////////////////////////////////////////////
		//TEACHER testing site

		//TEACHER tch = CreateSampleTeacher(namesList, surnamesList, tvec);
		//tch = CreateSampleTeacher(namesList, surnamesList, tvec);
		//BoxPrintTeacher(tch, hConsole);
		//std::wcout << L"\n\n\n";
		//InlinePrintTeacher(tch, hConsole);

		//TEACHER vector testing site

		//std::vector<TEACHER> tcvec;
		//CreateSampleTeacherVector(tvec, namesList, surnamesList, tcvec);
		//BoxPrintTeacherVector(tcvec, hConsole, 0, true);
		//std::wcout << L"\n\n\n";
		//BoxPrintTeacherVector(tcvec, hConsole, 0, false);

	
		/////////////////////////////////////////////////////////////////////////////////////
		//QA testing site

		_log.Close();
	}
}