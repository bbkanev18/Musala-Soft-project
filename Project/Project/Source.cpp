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

#include <sstream>
#include <fstream>
#include <codecvt>

//_log is global in order to save time and effort of passing it to every function
LOG _log;

int main()
{	
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
		//BoxPrintTeacher(tch, hConsole);
		//NewLine(3);
		//InlinePrintTeacher(tch, hConsole);
		//NewLine(3);
		//UpdateTeacherlessTeamVector(tvec, tchlessVec);
		//PrintTeamVector(tchlessVec, hConsole, 0, true, false);
		//NewLine(3);
		//TEACHER tch2;
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
		
		//SCHOOL sch = CreateSampleSchool(schoolnamesList, teamnamesList, namesList, surnamesList);
		//BoxPrintSchool(sch, hConsole);
		//InlinePrintSchool(sch, hConsole);
		SCHOOL sch = EnterSchool(teamnamesList, namesList, surnamesList, hConsole);
		BoxPrintSchool(sch, hConsole);
		//std::wcout << L'\n';
		//BoxPrintSchool(sch, hConsole, false, false, false);
		//std::wcout << L'\n';

		//===========================================
		//SCHOOL vector testing site



		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//QA testing site

		//PERSON p;
		//p = EnterPerson(hConsole);
		//std::wcout << L'\n' << p.name;
		//std::wcout << L'\n' << p.surname;
		//std::wcout << L'\n' << EmailToWstring(p.email);






		//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

		/*
		Main menu bs...
		
		# 1

		main menu

		1. load
		2. save

		3. school
		4. teacher
		5. team
		6. student

		9. info
		0. quit

		## 3,4,5 and 6 will have submenues



		*/






		//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

		_log.Close();
	}
}

// SCHOOL IS OVERALL BROKEN RN
// THE TEAMS IN THE TEACHERS DONT GET SYNCHRONIZED WITH THE TEAMS THEMSELVES
// 
// POSSIBLE SOLUTION!
// MAYBE REMOVE THE TEAM VECTOR AND LEAVE THE TEAM VECTOR BE ONLY IN THE TEACHERS
// 
// SOLUTION WORKED!
// HOWEVER, A FEW TEAMS GET LOST IN THE PROCCESS
// 
// MANUAL MODE ISNT FINISHED!!!
// 
// 
// 
