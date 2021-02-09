#pragma once
#include <iostream>
#include <ctime>

struct EMAIL
{
	std::wstring username;
	std::wstring domain;
};

enum class ROLE
{
	Undefined,
	ScrumTrainer,
	QAEngineer,
	BackendDev,
	FrontendDev
};

struct STUDENT
{
	std::wstring Name;
	std::wstring SurName;
	char Class;
	enum class ROLE role = ROLE::Undefined;
	struct EMAIL email;
};


enum class STATUS
{
	Undefined,
	InUse,
	NotActive,
	Archived
};

struct TEAM
{
	std::wstring Name;
	std::wstring Description;
	struct tm DateOfSetup;
	struct STUDENT students[4];
	enum class STATUS status = STATUS::Undefined;
};

struct TEACHER
{
	std::wstring Name;
	std::wstring SurName;
	//Array of teams the object is in
	struct EMAIL email;
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