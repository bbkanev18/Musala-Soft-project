#pragma once
#include <iostream>
#include <ctime>
#include <vector>

#include "windows.h"

struct EMAIL
{
	std::wstring username = L"";
	std::wstring domain = L"";
};

EMAIL WstringToEmail(std::wstring email);

std::wstring EmailToWstring(EMAIL email);

enum class ROLE
{
	Undefined,
	ScrumTrainer,
	QAEngineer,
	BackendDev,
	FrontendDev
};

std::wstring RoleToWstring(ROLE role, bool shortVersion = false);

enum class STATUS
{
	Undefined,
	InUse,
	NotActive,
	Archived
};

std::wstring StatusToWstring(STATUS status, int& activeColor);

struct STUDENT
{
	std::wstring name = L"Boris";
	std::wstring surname = L"Johnson";
	wchar_t Class = '!';
	enum class ROLE role = ROLE::Undefined;
	struct EMAIL email = WstringToEmail(L"boris.johnson@gov.uk");
};

void BoxPrintStudent(STUDENT st, HANDLE hConsole, size_t indent = 0);

void InlinePrintStudent(STUDENT st, HANDLE hConsole, size_t indent = 0);

STUDENT EnterStudent();

STUDENT CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);

void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT>& vec, size_t amount = 5);

void AddStudentToVector(std::vector<STUDENT>& vec, STUDENT st);

void PrintStudentVector(std::vector<STUDENT>& vec, HANDLE hConsole, bool inlineStudents = false);

struct TEAM
{
	std::wstring name = L"‎Conservative";
	std::wstring description = L"I have no idea. I took the Boris Johnson meme too far.";
	struct tm dateOfSetup;
	enum class STATUS status = STATUS::Undefined;
	struct STUDENT students[4] = {};
};

void PrintTeam(TEAM team, HANDLE hConsole, size_t indent = 0, bool inlineStudents = false);

TEAM CreateSampleTeam(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, bool empty = false);

TEAM EnterTeam();

void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& vec, size_t amount = 5, bool empty = false);

void AddTeamToVector(std::vector<TEAM>& vec, TEAM team);

void PrintTeamVector(std::vector<TEAM>& vec, HANDLE hConsole, bool inlineStudents = false);

struct TEACHER
{
	std::wstring name;
	std::wstring surname;
	//Array of teams the object is in
	struct EMAIL email;
};

TEACHER CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames);

void BoxPrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent = 0);

void InlinePrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent = 0);

struct SCHOOL
{
	std::wstring name;
	std::wstring City;
	std::wstring Address;
	//array of Students
	//array of Teams
	//array of Teachers
};

//print school -> school - team(teacher,students)

//Maybe Seperate a function to create (name,surname,email) from Teacher/Student functions