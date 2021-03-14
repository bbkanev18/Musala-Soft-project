#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "io.h"
#include "fcntl.h"
#include "windows.h"
#include "conio.h"

#include "DataTypes.h"
#include "Interface.h"
#include "Log.h"
#include "FileHandler.h"

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

		//Update to pesho's standart;
		SetColour(BASE_COLOUR);

		int a = _setmode(_fileno(stdout), _O_U16TEXT);
		a = _setmode(_fileno(stdin), _O_U16TEXT);

		std::vector<std::wstring> namesList =    GenerateWstringVector("Database\\firstnames.txt" );
		std::vector<std::wstring> surnamesList =  GenerateWstringVector("Database\\surnames.txt"   );
		std::vector<std::wstring> teamnamesList =  GenerateWstringVector("Database\\teamnames.txt"  );
		std::vector<std::wstring> schoolnamesList = GenerateWstringVector("Database\\schoolnames.txt");

		//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
		/*
		Main menu bs...
		
		# IDEA 1

		main menu

		1. load
		2. save

		3. school
		4. teacher
		5. team
		6. student

		9. info
		0. quit

		## 3, 4, 5 and 6 will have submenues
		<x> submenu

		1. Enter
		2. Create Sample -> amount?

		3. Print all
		4. Print by criteria

		5. Delete?
		6. Edit?

		0. quit


		*/


		/*

		//Connect students to teams, teachers and schools
		//Update the students vec with data from all other structs
		//Do the same for the other structs
		std::vector<SCHOOL>			 schVec;
		std::vector<TEACHER>		 tchVec;
		std::vector<TEAM>			teamVec;
		std::vector<TEAM>	tchlessTeamsVec;
		std::vector<STUDENT>		 stdVec;
		size_t amount = 0;

		char _getchErrorRemover = ' ';
		bool inLoop = true;
		while (inLoop)
		{
			amount = 0;
			switch(PrintMainMenu())
			{
			case '1':
				//load
				break;
			case '2':
				//save
				break;
			case 'q':	//School
				switch (StructSubMenu(L"School", schVec.empty()))
				{
				case 'a':	//Enter
					AddObjectToVector(schVec, EnterSchool(teamnamesList, namesList, surnamesList));
					break;
				case 's':	//Sample
					std::wcout << L"Amount of sample schools: ";
					amount = ReadSizeInput();
					CreateSampleSchoolVector(schoolnamesList, teamnamesList, namesList, surnamesList, schVec, amount);
					break;
				case 'd':	//Print all
					//Ask if it should be inline, or box
					PrintSchoolVector(schVec);
					_getchErrorRemover = _getch();
					break;
				//case 'f':	//Print by criteria

				//	//Ask for criteria!
				//	//return and print a vec
				//	break;
				//case 'z':	//Delete?

				//	break;
				//case 'x':	//Edit?

				//	break;
				default:
					break;
				}
				break;
			case 'w':	//Teacher
				switch (StructSubMenu(L"Teacher", tchVec.empty()))
				{
				case 'a':	//Enter
					AddObjectToVector(tchVec, EnterTeacher(tchlessTeamsVec, teamVec));
					break;
				case 's':	//Sample
					std::wcout << L"Amount of sample teachers: ";
					amount = ReadSizeInput();
					CreateSampleTeacherVector(tchlessTeamsVec, teamVec, namesList, surnamesList, tchVec, amount);
					break;
				case 'd':	//Print all
					PrintTeacherVector(tchVec);
					_getchErrorRemover = _getch();
					break;
				//case 'f':	//Print by criteria
				//	//Ask for criteria!
				//	//return and print a vec
				//	break;
				//case 'z':	//Delete?

				//	break;
				//case 'x':	//Edit?

				//	break;
				default:
					break;
				}
				UpdateTeacherlessTeamVector(teamVec, tchlessTeamsVec);
				break;
			case 'e':	//Team
				switch (StructSubMenu(L"Team", teamVec.empty()))
				{
				case 'a':	//Enter
					AddObjectToVector(teamVec, EnterTeam());
					break;
				case 's':	//Sample
					std::wcout << L"Amount of sample teams: ";
					amount = ReadSizeInput();
					CreateSampleTeamVector(teamnamesList, namesList, surnamesList, teamVec, amount);
					break;
				case 'd':	//Print all
					PrintTeamVector(teamVec);
					_getchErrorRemover = _getch();
					break;
				//case 'f':	//Print by criteria
				//	//Ask for criteria!
				//	//return and print a vec
				//	break;
				//case 'z':	//Delete?

				//	break;
				//case 'x':	//Edit?

				//	break;
				default:
					break;
				}
				UpdateTeacherlessTeamVector(teamVec, tchlessTeamsVec);
				break;
			case 'r':	//Student
				switch (StructSubMenu(L"Student", stdVec.empty()))
				{
				case 'a':	//Enter
					AddObjectToVector(stdVec, EnterStudent());
					break;
				case 's':	//Sample
					std::wcout << L"Amount of sample students: ";
					amount = ReadSizeInput();
					CreateSampleStudentVector(namesList, surnamesList, stdVec, amount);
					break;
				case 'd':	//Print all
					PrintStudentVector(stdVec);
					_getchErrorRemover = _getch();
					break;
				//case 'f':	//Print by criteria
				//	//Ask for criteria!
				//	//return and print a vec
				//	break;
				//case 'z':	//Delete?

				//	break;
				//case 'x':	//Edit?

				//	break;
				default:
					break;
				}
				break;
			case 9:		//tab
				//info
				break;
			case 27:	//esc
				inLoop = false;
				break;
			default:

				break;
			}
		}


		*/


		//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

		/*
		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//TEAM testing site

		//TEAM team = EnterTeam();
		//TEAM team = CreateSampleTeam(teamnamesList, namesList, surnamesList);
		//BoxPrintTeam(team);
	
		//===========================================
		//TEAM vector testing site

		//std::vector<TEAM> tvec;
		//std::vector<TEAM> tchlessVec;
		//CreateSampleTeamVector(teamnamesList, namesList, surnamesList, tvec, 50);
		//UpdateTeacherlessTeamVector(tvec, tchlessVec);
		//PrintTeamVector(tvec, true);
		//NewLine(3);
		//PrintTeamVector(tvec, false);
		//NewLine(3);


		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//STUDENT testing site

		//STUDENT st = EnterStudent();
		//BoxPrintStudent(st);
		//NewLine(3);
		//InlinePrintStudent(st);
		//NewLine(3);

		//===========================================
		//STUDENT vector testing site

		//std::vector<STUDENT> stvec;
		//CreateSampleStudentVector(namesList, surnamesList, stvec, 50);
		//PrintStudentVector(stvec, false);
		//NewLine(3);
		//PrintStudentVector(stvec, true);
		//NewLine(3);


		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//TEACHER testing site

		//TEACHER tch = CreateSampleTeacher(namesList, surnamesList, tvec);
		//BoxPrintTeacher(tch);
		//NewLine(3);
		//InlinePrintTeacher(tch);
		//NewLine(3);
		//UpdateTeacherlessTeamVector(tvec, tchlessVec);
		//PrintTeamVector(tchlessVec, 0, true, false);
		//NewLine(3);
		//TEACHER tch2;
		//tch2 = EnterTeacher(tchlessVec, tvec);
		//BoxPrintTeacher(tch2);


		//===========================================
		//TEACHER vector testing site

		//std::vector<TEACHER> tcvec;
		//CreateSampleTeacherVector(tvec, namesList, surnamesList, tcvec);
		//PrintTeacherVector(tcvec, 0, true);
		//NewLine(3);
		//PrintTeacherVector(tcvec, 0, false);
		//NewLine(3);

		
		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//SCHOOL testing site
		
		//SCHOOL sch = CreateSampleSchool(schoolnamesList, teamnamesList, namesList, surnamesList);
		//BoxPrintSchool(sch);
		//InlinePrintSchool(sch);
		//SCHOOL sch = EnterSchool(teamnamesList, namesList, surnamesList);
		//BoxPrintSchool(sch);
		//std::wcout << L'\n';
		//BoxPrintSchool(sch, false, false, false);
		//std::wcout << L'\n';

		//===========================================
		//SCHOOL vector testing site



		/////////////////////////////////////////////////////////////////////////////////////
		//===========================================
		//QA testing site

		//PERSON p;
		//p = EnterPerson();
		//std::wcout << L'\n' << p.name;
		//std::wcout << L'\n' << p.surname;
		//std::wcout << L'\n' << EmailToWstring(p.email);
		*/

		/////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////

		if (false)
		{

			std::vector<STUDENT*> stdVec;

			CreateSampleStudentVector(namesList, surnamesList, stdVec);
			//AddPointerToVector(stdVec, EnterStudent());
			//SaveStudents(stdVec, "c:\\ProjectSaveFiles\\Musala_Soft_Project\\Saves\\studentsTest.txt");
			PrintStudentVector(stdVec, 0, false);
			NewLine();
			PrintStudentVector(stdVec, 0, true, false);
			NewLine();
			PrintStudentVector(stdVec, 0, true, true);
			ClearPointerVector(stdVec);
		}

		if (false)
		{

			std::vector<TEAM*> temVec;

			CreateSampleTeamVector(teamnamesList, namesList, surnamesList, temVec);
			PrintTeamVector(temVec);
			NewLine();
			PrintTeamVector(temVec, 0, false, true, true);
			NewLine();
			PrintTeamVector(temVec, 0, true);
		}

		if (false)
		{
			std::vector<TEAM*> tchlessVec;
			CreateSampleTeamVector(teamnamesList, namesList, surnamesList, tchlessVec, 20);
			std::vector<TEAM*> tchTemVec;
			std::vector<TEAM*> temVec;

			std::vector<TEACHER*> tchVec;

			CreateSampleTeacherVector(tchlessVec, tchTemVec, namesList, surnamesList, tchVec);
			//AddPointerToVector(tchVec, EnterTeacher(tchlessVec, tchTemVec));
			PrintTeacherVector(tchVec);
			NewLine(2);
			temVec = CombineTeamVectors(tchTemVec, tchlessVec);
			PrintTeamVector(temVec);
		}
		

		if (false)
		{
		std::vector<SCHOOL*> schVec;

		CreateSampleSchoolVector(schoolnamesList, teamnamesList, namesList, surnamesList, schVec);
		//AddPointerToVector(schVec, EnterSchool(teamnamesList, namesList, surnamesList));
		PrintSchoolVector(schVec);
		}


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
// 
