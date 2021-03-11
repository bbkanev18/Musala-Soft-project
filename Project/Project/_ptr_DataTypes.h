﻿#pragma once

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
EMAIL WstringToEmail(std::wstring email, std::wstring name = L"", std::wstring surname = L"");

EMAIL AutogenEmail(std::wstring name, std::wstring surname);

//Combines the elements of an email struct to a wstring
std::wstring EmailToWstring(EMAIL email);

//Student's role in a team
//There must 1 of each role per team (undefined doesn't count)
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
std::wstring StatusToWstring(STATUS status, int& activeColour);

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
//If no person is pushed to b, b will be the default value of PERSON
bool ArePeopleEqual(PERSON a, PERSON b = { L"Homo", L"Sapiens", L"Iamarealhuman" , L"mars.com" });

//A struct to store STUDENT info
struct STUDENT
{
	PERSON info;								//Student's Personal info
	wchar_t Class = '!';						//The class that the student is in
	enum class ROLE role = ROLE::Undefined;		//Student's role in the team
};

//Print a STUDENT in Box Style
void BoxPrintStudent(STUDENT* st, size_t indent = 0);

//Print a STUDENT in Inline Style
void InlinePrintStudent(STUDENT* st, size_t indent = 0, int id = -1);

//Return a STUDENT made by user input
STUDENT* EnterStudent();

//Return a STUDENT made by the computer
STUDENT* CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);

//Fills a vector with STUDENTs made by the computer
void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT*>& stvec, size_t amount = 5, bool empty = false);

//Adds a STUDENT to a vector of STUDENTs
//void AddObjectToVector(std::vector<STUDENT>& vec, STUDENT obj);
void AddPointerToVector(std::vector<STUDENT*>& vec, STUDENT* obj);

//Removes a STUDENT from a vector of STUDENTs
void RemovePointerFromVector(std::vector<STUDENT*>& vec, size_t posStart, size_t posEnd = 0);

//Prints a vector of STUDENTs
//Styles can be toggled by changing inlineStudents to true(for inline) or false(for box)
void PrintStudentVector(std::vector<STUDENT*>& vec, size_t indent = 0, bool inlineStudents = false, bool index = false);

void ClearPointerVector(std::vector<STUDENT*>& vec);

////A struct to store _ptr_TEACHER* info
//struct _ptr_TEACHER
//{
//	PERSON info;
//	std::vector<TEAM> teams;	//Array of teams the object is in
//};
//
////Print a _ptr_TEACHER* in Box Style
//void BoxPrintTeacher(_ptr_TEACHER* tch, size_t indent = 0);
//
////Print a _ptr_TEACHER* in Inline Style
//void InlinePrintTeacher(_ptr_TEACHER* tch, size_t indent = 0, int id = -1);
//
////Return a _ptr_TEACHER* made by user input
//_ptr_TEACHER* EnterTeacher(std::vector<TEAM>& tchlessTeams, std::vector<TEAM>& tchTemVec);
//
////Return a _ptr_TEACHER* made by the computer
//_ptr_TEACHER* CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& tchlessTeams, std::vector<TEAM>& tchTemVec);
//
////Fills a vector with _ptr_TEACHERs made by the computer
//void CreateSampleTeacherVector(std::vector<TEAM>& tchlessTeams, std::vector<TEAM>& tchTemVec, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEACHER*>& vec, size_t amount = 5, bool empty = false);
//
////Adds a _ptr_TEACHER* to a vector of _ptr_TEACHERs
//void AddObjectToVector(std::vector<_ptr_TEACHER*>& vec, _ptr_TEACHER* obj);
//
////Removes a _ptr_TEACHER* from a vector of _ptr_TEACHERs
//void RemovePointerFromVector(std::vector<_ptr_TEACHER*>& vec, size_t posStart, size_t posEnd = 0);
//
////Prints a vector of _ptr_TEACHERs
////Styles can be toggled by changing inlineStudents to true(for inline) or false(for box)
//void PrintTeacherVector(std::vector<_ptr_TEACHER*>& vec, size_t indent = 0, bool inlineTeacher = false, bool index = false);
//
////A struct to store School info
//struct SCHOOL
//{
//	std::wstring name = L"PGKPI";
//	std::wstring city = L"Burgas";
//	std::wstring address = L"Ортото 3";
//	std::vector<TEAM> teams = {};
//	std::vector<_ptr_TEACHER*> teachers = {};
//};
//
////Print a SCHOOL in Box Style
//void BoxPrintSchool(SCHOOL sch, size_t indent = 0, bool inlineTeachers = true, bool inlineTeams = true, bool inlineStudents = true);
//
////Print a SCHOOL in Inline Style
//void InlinePrintSchool(SCHOOL sch, size_t indent = 0, int id = -1);
//
////Return a SCHOOL made by user input
//SCHOOL EnterSchool(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);
//
////Return a SCHOOL made by the computer
//SCHOOL CreateSampleSchool(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);
//
////Fills a vector with SCHOOLs made by the computer
//void CreateSampleSchoolVector(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<SCHOOL>& vec, size_t amount = 5, bool empty = false);
//
////Adds a SCHOOL to a vector of SCHOOLs
//void AddObjectToVector(std::vector<SCHOOL>& vec, SCHOOL obj);
//
////Removes a SCHOOL from a vector of SCHOOLs
//void RemovePointerFromVector(std::vector<SCHOOL>& vec, size_t posStart, size_t posEnd = 0);
//
////Prints a vector of SCHOOLs
//void PrintSchoolVector(std::vector<SCHOOL> vec, size_t indent = 0, bool inlineSchool = false, bool index = false);

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//A struct to store _ptr_TEAM* info
struct _ptr_TEAM
{
	std::wstring name = L"‎Decameron";
	std::wstring description = L"Ora";				//Short summary of the team
	struct tm dateOfSetup = {};						//TimeStamp for when the team was added
	enum class STATUS status = STATUS::Undefined;	//Project's (Team's) current status
	std::vector<STUDENT*> _ptr_students = {};
	PERSON teacherInfo;
};

//Print a _ptr_TEAM* in Box Style
void BoxPrintTeam(_ptr_TEAM* team, size_t indent = 0, bool inlineStudents = false);

//Print a _ptr_TEAM* in Inline Style
void InlinePrintTeam(_ptr_TEAM* team, size_t indent = 0, int id = -1);

//Return a _ptr_TEAM* made by the computer
_ptr_TEAM* CreateSampleTeam(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, bool empty = false);

//Return a _ptr_TEAM* made by user input
_ptr_TEAM* EnterTeam();

//Fills a vector with _ptr_TEAMs made by the computer
void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEAM*>& vec, size_t amount = 5, bool empty = false);

//Adds a _ptr_TEAM* to a vector of _ptr_TEAMs

//Removes a _ptr_TEAM* from a vector of _ptr_TEAMs
void RemovePointerFromVector(std::vector<_ptr_TEAM*>& vec, size_t posStart, size_t posEnd = 0);

//Prints a vector of _ptr_TEAMs
//Styles for the students in the teams can be toggled by changing inlineStudents to true(for inline) or false(for box)
//Styles for the teams can be toggled by changing inlineTeamss to true(for inline) or false(for box)
void PrintTeamVector(std::vector<_ptr_TEAM*>& vec, size_t indent = 0, bool inlineTeams = false, bool inlineStudents = false, bool index = false);

void AddPointerToVector(std::vector<_ptr_TEAM*>& vec, _ptr_TEAM* obj);

void ClearPointerVector(std::vector<_ptr_TEAM*>& vec);

std::vector<_ptr_TEAM*> CombineTeamVectors(std::vector<_ptr_TEAM*>& tchTemVec, std::vector<_ptr_TEAM*>& tchlessTeams);

//Make the team interact with the teachers!!!!

//A struct to store _ptr_TEACHER* info
struct _ptr_TEACHER
{
	PERSON info;
	std::vector<_ptr_TEAM*> teams;	//Array of teams the object is in
};

//Print a _ptr_TEACHER* in Box Style
void BoxPrintTeacher(_ptr_TEACHER* tch, size_t indent = 0);

//Print a _ptr_TEACHER* in Inline Style
void InlinePrintTeacher(_ptr_TEACHER* tch, size_t indent = 0, int id = -1);

//Return a _ptr_TEACHER* made by user input
_ptr_TEACHER* EnterTeacher(std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec);

//Return a _ptr_TEACHER* made by the computer
_ptr_TEACHER* CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec);

//Fills a vector with _ptr_TEACHERs made by the computer
void CreateSampleTeacherVector(std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEACHER*>& vec, size_t amount = 5, bool empty = false);

//Adds a _ptr_TEACHER* to a vector of _ptr_TEACHERs
void AddPointerToVector(std::vector<_ptr_TEACHER*>& vec, _ptr_TEACHER* obj);

//Removes a _ptr_TEACHER* from a vector of _ptr_TEACHERs
void RemovePointerFromVector(std::vector<_ptr_TEACHER*>& vec, size_t posStart, size_t posEnd = 0);

//Prints a vector of _ptr_TEACHERs
//Styles can be toggled by changing inlineStudents to true(for inline) or false(for box)
void PrintTeacherVector(std::vector<_ptr_TEACHER*>& vec, size_t indent = 0, bool inlineTeacher = false, bool index = false);