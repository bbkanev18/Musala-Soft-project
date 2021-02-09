#pragma once
#include <iostream>
#include <ctime>
#include <vector>

struct EMAIL
{
	std::wstring username = L"";
	std::wstring domain = L"";
};

EMAIL GenerateEmail(std::wstring email);

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
	std::wstring Name;
	std::wstring SurName;
	char Class;
	enum class ROLE Role = ROLE::Undefined;
	struct EMAIL Email;
};

STUDENT CreateSampleStudent(std::vector<std::wstring> names, std::vector<std::wstring> surnames, int index = -1);

void PrintStudent(STUDENT st);

template <typename T>
void AddToVector(std::vector<T>& vec, T obj);
//IDK if this works... test!!!

STUDENT EnterStudent();

void PrintStVector(std::vector<STUDENT> vec);

struct TEAM
{
	std::wstring Name;
	std::wstring Description;
	struct tm DateOfSetup;
	struct STUDENT Students[4];
	enum class STATUS Status = STATUS::Undefined;
};

struct TEACHER
{
	std::wstring Name;
	std::wstring SurName;
	//Array of teams the object is in
	struct EMAIL Email;
};

struct SCHOOL
{
	std::wstring Name;
	std::wstring City;
	std::wstring Address;
	//array of Students
	//array of Teams
	//array of Teachers
};