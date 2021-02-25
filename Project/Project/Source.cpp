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
	_log.severityFilter = SEVERITY::Info;
	
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

		std::vector<std::wstring> namesList =    GenerateWstringVector("Database\\firstnames.txt" );
		std::vector<std::wstring> surnamesList =  GenerateWstringVector("Database\\surnames.txt"   );
		std::vector<std::wstring> teamnamesList =  GenerateWstringVector("Database\\teamnames.txt"  );
		std::vector<std::wstring> schoolnamesList = GenerateWstringVector("Database\\schoolnames.txt");

		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//TEAM testing site

		//TEAM team = EnterTeam();
		//TEAM team = CreateSampleTeam(teamnamesList, namesList, surnamesList);
		//BoxPrintTeam(team, hConsole);
	
		//===========================================
		//TEAM vector testing site

		//std::vector<TEAM> tvec;
		//std::vector<TEAM> tchlessVec;
		//CreateSampleTeamVector(teamnamesList, namesList, surnamesList, tvec, 50);
		//UpdateTeacherlessTeamVector(tvec, tchlessVec);
		//PrintTeamVector(tvec, hConsole, true);
		//NewLine(3);
		//PrintTeamVector(tvec, hConsole, false);
		//NewLine(3);


		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//STUDENT testing site

		//STUDENT st = EnterStudent();
		//BoxPrintStudent(st, hConsole);
		//NewLine(3);
		//InlinePrintStudent(st, hConsole);
		//NewLine(3);

		//===========================================
		//STUDENT vector testing site

		//std::vector<STUDENT> stvec;
		//CreateSampleStudentVector(namesList, surnamesList, stvec, 50);
		//PrintStudentVector(stvec, hConsole, false);
		//NewLine(3);
		//PrintStudentVector(stvec, hConsole, true);
		//NewLine(3);


		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//TEACHER testing site

		//TEACHER tch = CreateSampleTeacher(namesList, surnamesList, tvec);
		//TEACHER tch2;
		//BoxPrintTeacher(tch, hConsole);
		//NewLine(3);
		//InlinePrintTeacher(tch, hConsole);
		//NewLine(3);
		//UpdateTeacherlessTeamVector(tvec, tchlessVec);
		//PrintTeamVector(tchlessVec, hConsole, 0, true, false);
		//NewLine(3);
		//tch2 = EnterTeacher(tchlessVec, tvec, hConsole);
		//BoxPrintTeacher(tch2, hConsole);


		//===========================================
		//TEACHER vector testing site

		//std::vector<TEACHER> tcvec;
		//CreateSampleTeacherVector(tvec, namesList, surnamesList, tcvec);
		//PrintTeacherVector(tcvec, hConsole, 0, true);
		//NewLine(3);
		//PrintTeacherVector(tcvec, hConsole, 0, false);
		//NewLine(3);

		
		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//SCHOOL testing site



		//===========================================
		//SCHOOL vector testing site
		
		SCHOOL sch = CreateSampleSchool(schoolnamesList, teamnamesList, namesList, surnamesList);
		BoxPrintSchool(sch, hConsole);
		InlinePrintSchool(sch, hConsole);


		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//QA testing site

		_log.Close();
	}
}