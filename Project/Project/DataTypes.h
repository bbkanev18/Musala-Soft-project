#pragma once

#include <iostream>
#include <ctime>
#include <vector>

#include "windows.h"

//A struct to store the elements of an email
//username@domain
struct EMAIL
{
	std::wstring username = L"";	//First part of an email
	std::wstring domain = L"";		//Second part of an email
};

//Separate a wstring into an email struct
EMAIL WstringToEmail(std::wstring email);

//Combines the elements of an email struct to a wstring
std::wstring EmailToWstring(EMAIL email);

//Student's role in a team
enum class ROLE
{
	Undefined,		//The role is not defined
	ScrumTrainer,	//Scrum Trainer
	QAEngineer,		//Q&A Engineer
	BackendDev,		//Backend developer
	FrontendDev		//Frontend developer
};

//Returns the wstring form of role
std::wstring RoleToWstring(ROLE role, bool shortVersion = false);

//Project's (Team's) status
enum class STATUS
{
	Undefined,		//The status is not defined
	InUse,			//The project/team is "in use"? - My guess is that they mean active instead of "in use"
	NotActive,		//The project/team is inactive
	Archived		//The project/team has been archived/finished
};

//Returns the wstring form of status
std::wstring StatusToWstring(STATUS status, int& activeColor);

//A struct to store personal information
struct PERSON
{
	std::wstring name = L"Homo";
	std::wstring surname = L"Sapiens";
	struct EMAIL email = WstringToEmail(L"Iamarealhuman@mars.com");
	//maybe add more fields?
	//eg: age?
};

//Return a PERSON made by user input
PERSON EnterPerson();

//Return a PERSON made by the computer
PERSON CreateSamplePerson(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);

//Checks if 2 People (2 PERSONs) are the same
bool ArePeopleEqual(PERSON a, PERSON b);

//A struct to store STUDENT info
struct STUDENT
{
	PERSON info;								//Student's Personal info
	wchar_t Class = '!';						//The class that the student is in
	enum class ROLE role = ROLE::Undefined;		//Student's role in the team
};

//Print a STUDENT in Box Style
void BoxPrintStudent(STUDENT st, HANDLE hConsole, size_t indent = 0);

//Print a STUDENT in Inline Style
void InlinePrintStudent(STUDENT st, HANDLE hConsole, size_t indent = 0);

//Return a STUDENT made by user input
STUDENT EnterStudent();

//Return a STUDENT made by the computer
STUDENT CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);

//Fills a vector with STUDENTs made by the computer
void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT>& stvec, size_t amount = 5);

//Adds a STUDENT to a vector of STUDENTs
void AddObjectToVector(std::vector<STUDENT>& vec, STUDENT obj);

//Prints a vector of STUDENTs
//Styles can be toggled by changing inlineStudents to true(for inline) or false(for box)
void PrintStudentVector(std::vector<STUDENT>& vec, HANDLE hConsole, bool inlineStudents = false);

//A struct to store TEAM info
struct TEAM
{
	std::wstring name = L"‎Decameron";
	std::wstring description = L"Ora";				//Short summary of the team
	struct tm dateOfSetup;							//TimeStamp for when the team was added
	enum class STATUS status = STATUS::Undefined;	//Project's (Team's) current status
	struct STUDENT students[4] = {};				//An array of students that are a part of the team
	PERSON teacherInfo;								//Personal info for the teacher that is the team's mentor
};

//Print a TEAM in Box Style
void BoxPrintTeam(TEAM team, HANDLE hConsole, size_t indent = 0, bool inlineStudents = false);

//Print a TEAM in Inline Style
void InlinePrintTeam(TEAM team, HANDLE hConsole, size_t indent = 0, bool inlineStudents = false);

//Return a TEAM made by the computer
TEAM CreateSampleTeam(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, bool empty = false);

//Return a TEAM made by user input
TEAM EnterTeam();

//Fills a vector with TEAMs made by the computer
void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& vec, size_t amount = 5, bool empty = false);

//Adds a TEAM to a vector of TEAMs
void AddObjectToVector(std::vector<TEAM>& vec, TEAM obj);

//Prints a vector of TEAMs
//Styles for the students in the teams can be toggled by changing inlineStudents to true(for inline) or false(for box)
//Styles for the teams can be toggled by changing inlineTeamss to true(for inline) or false(for box)
void PrintTeamVector(std::vector<TEAM>& vec, HANDLE hConsole, size_t indent, bool inlineStudents = false, bool inlineTeams = false);

//A struct to store TEACHER info
struct TEACHER
{
	PERSON info;
	//Array of teams the object is in
	std::vector<TEAM> teams;
};

//Print a TEACHER in Box Style
void BoxPrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent = 0);

//Print a TEACHER in Inline Style
void InlinePrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent = 0);

//Return a TEACHER made by user input
TEACHER EnterTeacher();

//Return a TEACHER made by the computer
TEACHER CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& teams);

//Fills a vector with TEACHERs made by the computer
void CreateSampleTeacherVector(std::vector<TEAM>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEACHER>& vec, size_t amount = 5, bool empty = false);

//Adds a TEACHER to a vector of TEACHERs
void AddObjectToVector(std::vector<TEACHER>& vec, TEACHER obj);

//Prints a vector of TEACHERs
//Styles can be toggled by changing inlineStudents to true(for inline) or false(for box)
void PrintTeacherVector(std::vector<TEACHER> vec, HANDLE hConsole, size_t indent = 0, bool inlineTeacher = false);

//A struct to store School info
struct SCHOOL
{
	std::wstring name;
	std::wstring city;
	std::wstring address;
	//array of Teams
	//array of Teachers
};
