#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "windows.h"

#include "DataTypes.h"
#include "Interface.h"
#include "Log.h"

//Email

EMAIL WstringToEmail(std::wstring email)
{
	EMAIL out;
	bool writeInUsername = true;
	
	for (size_t i = 0; i < email.length(); i++)
	{
		if (email[i] == L'@')
		{
			writeInUsername = false;
			continue;
		}

		if (writeInUsername)	//Adds the current char from the email to the username
			out.username += email[i];
		else					//Adds the current char from the email to the domain
			out.domain += email[i];
	}
	
	if (out.username.empty())	//Sets a default username if none was found
		out.username = L"Wrong_Input";
	if (out.domain.empty())		//Sets a default domain if none was found
		out.domain = L"badinput.io";
	
	return out;
}

std::wstring EmailToWstring(EMAIL email)
{
	return (email.username + L'@' + email.domain);
}

//Role

std::wstring RoleToWstring(ROLE role, bool shortVersion)
{
	switch (role)
	{
	case ROLE::ScrumTrainer:
		if (shortVersion)
			return L"ST";
		return L"Scrum Trainer";
	case ROLE::QAEngineer:
		if (shortVersion)
			return L"QA";
		return L"Q&A Engineer";
	case ROLE::BackendDev:
		if (shortVersion)
			return L"BD";
		return L"Backend Developer";
	case ROLE::FrontendDev:
		if (shortVersion)
			return L"FD";
		return L"Frontend Developer";
	default:
		if (shortVersion)
			return L"UF";
		return L"Undefined";
	}

	return L"ERROR!";
}

//Status

std::wstring StatusToWstring(STATUS status, int& activeColor)
{
	//Word this in a better way
	//StatusToWstring is meant to be used in a printTeam function, it gets passed a refference to activeColour that would be the colour that the status is printed in
	switch (status)
	{
	case STATUS::InUse:
		activeColor = INUSE_COLOUR;
		return L"In Use";
	case STATUS::NotActive:
		activeColor = NOTACTIVE_COLOUR;
		return L"Not Active";
	case STATUS::Archived:
		activeColor = ARCHIVED_COLOUR;
		return L"Archived";
	default:
		activeColor = UNDEFINED_COLOUR;
		return L"Undefined";
	}
}

//Person

PERSON EnterPerson()
{
	PERSON info;
	std::wstring email = L"";

	std::wcout << L"Name: ";
	std::wcin >> info.name;
	std::wcout << L"Surname: ";
	std::wcin >> info.surname;
	std::wcout << L"Email: ";
	std::wcin >> email;
	info.email = WstringToEmail(email);

	return info;
}

PERSON CreateSamplePerson(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	PERSON info;
	std::wstring email = L"";												//The name and surname are used as the email's username

	info.name = names[rand() % names.size()];
	email += info.name + L'.';
	info.surname = surnames[rand() % surnames.size()];
	email += info.surname;
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);	//Sets all characters to lower case
	info.email = WstringToEmail(email + L"@sample.io");						//Adds the sample domain

	return info;
}

bool ArePeopleEqual(PERSON a, PERSON b)
{
	if (EmailToWstring(a.email) == EmailToWstring(b.email) and a.name == b.name and a.surname == b.surname)
		return true;

	return false;
}

//Student

void BoxPrintStudent(STUDENT st, HANDLE hConsole, size_t indent)
{
	//Symbols used for the box
	//┌─┤├─┐└┘├┤─│
	std::wstring header = L"┌──────────────┤ STUDENT ├──────────────┐";
	std::wstring footer = L"└───────────────────────────────────────┘";
	std::wstring temp = L"Class ";	//Used to store st.Class
	temp += st.Class;

	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), hConsole,(st.info.name + L' ' + st.info.surname), BASE_COLOUR, NAME_COLOUR, L'│', indent);
	PrintBoxStyle(header.size(), hConsole, temp, BASE_COLOUR, CLASS_COLOUR, L'│', indent);
	PrintBoxStyle(header.size(), hConsole, RoleToWstring(st.role), BASE_COLOUR, ROLE_COLOUR, L'│', indent);
	PrintBoxStyle(header.size(), hConsole, EmailToWstring(st.info.email), BASE_COLOUR, EMAIL_COLOUR, L'│', indent);

	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintStudent(STUDENT st, HANDLE hConsole, size_t indent)
{
	std::vector<std::wstring> content;
	std::wstring temp = L"Class ";
	temp += st.Class;

	content.push_back((st.info.name + L" " + st.info.surname));
	content.push_back(temp);
	content.push_back(RoleToWstring(st.role));
	content.push_back(EmailToWstring(st.info.email));
	PrintInlineStyle(content, hConsole, indent);
	content.clear();
	NewLine();
}

STUDENT EnterStudent()
{
	STUDENT st;
	wchar_t temp = ' ';

	st.info = EnterPerson();
	
	std::wcout << L"Class (A,B,C...): ";
	std::wcin >> st.Class;
	if (st.Class >= 'a' and st.Class <= 'z')
		st.Class -= ('a' - 'A');
	if (!(st.Class >= 'A' and st.Class <= 'Z'))
		st.Class = '?';
	
	std::wcout << L"Role (1.BackendDev, 2.FrontendDev, 3.Q&AEngineer, 4.ScrumTrainer): ";
	std::wcin >> temp;
	st.role = ROLE(int(temp) - 48);

	NewLine();
	return st;
}

STUDENT CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	STUDENT st;

	st.Class = char(rand() % 4 + 65);
	st.role = ROLE(rand() % 4);
	st.info = CreateSamplePerson(names, surnames);

	return st;
}

void AddObjectToVector(std::vector<STUDENT>& vec, STUDENT obj)
{
	vec.push_back(obj);
}

void PrintStudentVector(std::vector<STUDENT>& vec, HANDLE hConsole, bool inlineStudents)
{
	if (inlineStudents)
		NewLine();

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineStudents) 
			BoxPrintStudent(vec[i], hConsole);
		else
			InlinePrintStudent(vec[i], hConsole);
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		if(!inlineStudents)
			NewLine();
	}
}

void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT>& stvec, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		AddObjectToVector(stvec, CreateSampleStudent(names, surnames));
}

//Team

void BoxPrintTeam(TEAM team, HANDLE hConsole, size_t indent, bool inlineStudents)
{
	//Symbols used for box
	//┃━┏┓┗┛┫┣┅┄┎─┖┨┠┒┚
	std::wstring header =   L"┏━━━━━━━━━━━━━━━━━━┫ TEAM ┣━━━━━━━━━━━━━━━━━━┓";
	std::wstring splitstr = L"┗┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┛";
	std::wstring splitend = L"┏┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┓";
	std::wstring footer =   L"┗━━━━━━━━━━━━━━━━━━┫ END. ┣━━━━━━━━━━━━━━━━━━┛";
	std::wstring tchHeader    = L"┎────────────┨ TEACHER ┠────────────┒";
	std::wstring tchFooter    = L"┖───────────────────────────────────┚";
	std::wstring temp = L"";
	int activeColor = UNDEFINED_COLOUR;

	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), hConsole, team.name, BASE_COLOUR, NAME_COLOUR, L'┃', indent); //TAKE CARE OF COLOURS!!
	PrintBoxStyle(header.size(), hConsole, team.description, BASE_COLOUR, DESCRIPTION_COLOUR, L'┃', indent);
	PrintBoxStyle(header.size(), hConsole, (TmToDateWstring(team.dateOfSetup, true)), BASE_COLOUR, DATEOFSETUP_COLOUR, L'┃', indent);
	NewLine();

	PrintIndent(indent);
	std::wcout << splitstr;
	NewLine(2);
	PrintIndent(indent + 4);
	std::wcout << tchHeader;

	PrintBoxStyle(tchHeader.size(), hConsole, (team.teacherInfo.name + L" " + team.teacherInfo.surname), BASE_COLOUR, NAME_COLOUR, L'┃', indent + 4);
	PrintBoxStyle(tchHeader.size(), hConsole, EmailToWstring(team.teacherInfo.email), BASE_COLOUR, EMAIL_COLOUR, L'┃', indent + 4);

	NewLine();
	PrintIndent(indent + 4);
	std::wcout << tchFooter;
	NewLine(2);

	//FIGURE OUT A SMARTER SOLUTION!!!
	//A FOR LOOP ISN'T GOOD ENOUGH!
	for (size_t i = 0; i < 4; i++)
	{
		if(inlineStudents)
			InlinePrintStudent(team.students[i], hConsole, indent + 2);
		else
		{
			BoxPrintStudent(team.students[i], hConsole, indent + 2);
			NewLine();
		}
	}

	NewLine();
	std::wcout << splitend;

	temp = StatusToWstring(team.status, activeColor);
	PrintBoxStyle(header.size(), hConsole, temp, BASE_COLOUR, activeColor, L'┃', indent);

	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintTeam(TEAM team, HANDLE hConsole, size_t indent, bool inlineStudents)
{
	std::vector<std::wstring> content;
	int n = 0;
	
	content.push_back((team.name));
	content.push_back(StatusToWstring(team.status, n));
	PrintInlineStyle(content, hConsole, indent);
	content.clear();
	NewLine();
}

TEAM CreateSampleTeam(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, bool empty)
{
	TEAM team;
	team.name = teamNames[rand() % teamNames.size()];
	team.description = L"Medesimi novellare fa divina niuno sé";
	
	time_t _t;
	time(&_t);
	localtime_s(&team.dateOfSetup, &_t);
	
	if (!empty)
	{
		for (size_t i = 0; i < 4; i++)
			team.students[i] = CreateSampleStudent(names, surnames);
	}
	
	switch (rand() % 3)
	{
	case 0:
		team.status = STATUS::InUse;
		break;
	case 1:
		team.status = STATUS::Archived;
		break;
	case 2:
		team.status = STATUS::NotActive;
		break;
	default:
		team.status = STATUS::Undefined;
		break;
	}
	
	return team;
}

TEAM EnterTeam()
{
	TEAM team;
	wchar_t temp = ' ';
	
	std::wcout << L"Team Name: ";
	getline(std::wcin, team.name);
	std::wcout << L"Description: ";
	getline(std::wcin, team.description);
	
	//TEMPORARY SOLUTION!!!
	
	time_t _t;
	time(&_t);
	localtime_s(&team.dateOfSetup, &_t);

	//LET THE USER CHOOSE!!!
	
	std::wcout << L"Status (1.InUse, 2.Not Active, 3.Archived): ";
	std::wcin >> temp;
	team.status = STATUS(int(temp) - 48);

	//Seperate into a function?!
	for (size_t i = 0; i < 4; i++)
	{
		NewLine();
		std::wcout << L"Student " + std::to_wstring(i + 1);
		NewLine();
		team.students[i] = EnterStudent();
	}
	
	return team;
}

void AddObjectToVector(std::vector<TEAM>& vec, TEAM obj)
{
	vec.push_back(obj);
}

void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount; i++)
		AddObjectToVector(vec, CreateSampleTeam(teamNames, names, surnames));
}

void PrintTeamVector(std::vector<TEAM>& vec, HANDLE hConsole, size_t indent, bool inlineStudents, bool inlineTeams)
{
	if (inlineTeams)
		NewLine();

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineTeams)
			BoxPrintTeam(vec[i], hConsole);
		else
			InlinePrintTeam(vec[i], hConsole, indent, inlineStudents);
		
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		if (!inlineTeams)
			NewLine();
	}
}

//Teacher

TEACHER CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& teams)
{
	TEACHER tch;
	std::wstring email = L"";
	
	tch.info.name = names[rand() % names.size()];
	email += tch.info.name + L'_';
	tch.info.surname = surnames[rand() % surnames.size()];
	email += tch.info.surname + L'.';
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);
	tch.info.email = WstringToEmail(email + L"@sample.io");

	if (teams.size() > 0)
	{
		for (size_t i = 0; i < teams.size(); i++)
		{
			//There is an 80% chance for a team to be assigned to a teacher
			if (rand() % 100 + 1 >= 80 and ArePeopleEqual(teams[i].teacherInfo, { L"Homo", L"Sapiens", WstringToEmail(L"Iamarealhuman@mars.com") }))
			{
				teams[i].teacherInfo = tch.info;
				AddObjectToVector(tch.teams, teams[i]);
			}
		}
	}

	return tch;
}

void BoxPrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent)
{
	//Symbols used for box
	//─┤├──┠┨┎┒┃┖┚┄
	std::wstring header =   L"┎────────────────┨ TEACHER ┠────────────────┒";
	std::wstring splitstr = L"┖┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┚";
	std::wstring splitend = L"┎┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┒";
	std::wstring footer =   L"┖───────────────────────────────────────────┚";
	std::wstring temp = L"";
	
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;
	
	PrintBoxStyle(header.size(), hConsole, (tch.info.name + L' ' + tch.info.surname), BASE_COLOUR, NAME_COLOUR, L'┃', indent);
	PrintBoxStyle(header.size(), hConsole, EmailToWstring(tch.info.email), BASE_COLOUR, EMAIL_COLOUR, L'┃', indent);
	
	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;
	
	PrintTeamVector(tch.teams, hConsole, 3, true, true);
	
	PrintIndent(indent);
	std::wcout << splitend;
	
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintTeacher(TEACHER tch, HANDLE hConsole, size_t indent)
{
	std::vector<std::wstring> content;

	content.push_back(tch.info.name + L" " + tch.info.surname);
	content.push_back(EmailToWstring(tch.info.email));
	PrintInlineStyle(content, hConsole, indent);
	content.clear();
	NewLine();
}

TEACHER EnterTeacher()
{
	TEACHER tch;

	tch.info = EnterPerson();

	//Create this!

	return tch;
}

void AddObjectToVector(std::vector<TEACHER>& vec, TEACHER obj)
{
	vec.push_back(obj);
}

void PrintTeacherVector(std::vector<TEACHER> vec, HANDLE hConsole, size_t indent, bool inlineTeacher)
{
	if (inlineTeacher)
		NewLine();

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineTeacher)
			BoxPrintTeacher(vec[i], hConsole, indent);
		else
			InlinePrintTeacher(vec[i], hConsole, indent);
		
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		if (!inlineTeacher)
			NewLine();
	}
}

void CreateSampleTeacherVector(std::vector<TEAM>& teams, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEACHER>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount; i++)
		AddObjectToVector(vec, CreateSampleTeacher(names, surnames, teams));
}

//School