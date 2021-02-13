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

enum class STATUS
{
	Undefined,
	InUse,
	NotActive,
	Archived
};

struct STUDENT
{
	std::wstring name = L"Boris";
	std::wstring surName = L"Johnson";
	char Class = 'G';
	enum class ROLE role = ROLE::Undefined;
	struct EMAIL email = WstringToEmail(L"boris.johnson@gov.uk");
};

void PrintStudent(STUDENT st, HANDLE hConsole, size_t indent = 0);

STUDENT EnterStudent();

STUDENT CreateSampleStudent(std::vector<std::wstring> names, std::vector<std::wstring> surnames);

void CreateSampleStudentVector(std::vector<std::wstring> names, std::vector<std::wstring> surnames, std::vector<STUDENT>& vec, size_t amount = 5);

void AddStudentToVector(std::vector<STUDENT>& vec, STUDENT st);

void PrintStudentVector(std::vector<STUDENT> vec, HANDLE hConsole);

struct TEAM
{
	std::wstring name;
	std::wstring description;
	struct tm dateOfSetup;
	enum class STATUS status = STATUS::Undefined;
	struct STUDENT students[4];
};

TEAM CreateSampleTeam(std::vector<std::wstring> teamNames, std::vector<std::wstring> names, std::vector<std::wstring> surnames, bool empty = false);

void PrintTeam(TEAM team, HANDLE hConsole, size_t indent = 0);

struct TEACHER
{
	std::wstring name;
	std::wstring surName;
	//Array of teams the object is in
	struct EMAIL email;
};

struct SCHOOL
{
	std::wstring name;
	std::wstring City;
	std::wstring Address;
	//array of Students
	//array of Teams
	//array of Teachers
};