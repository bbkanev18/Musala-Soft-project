#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "windows.h"

#include "DataTypes.h"
#include "Interface.h"

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

		if (writeInUsername)
			out.username += email[i];
		else
			out.domain += email[i];
	}
	if (out.username.empty())
		out.username = L"Wrong_Input";
	if (out.domain.empty())
		out.domain = L"badinput.io";
	return out;
}

std::wstring EmailToWstring(EMAIL email)
{
	return (email.username + L'@' + email.domain);
}

std::wstring RoleToWstring(ROLE role, bool shortVersion)
{
	switch (role)
	{
	case ROLE::ScrumTrainer:
		if (shortVersion)
			return L"Scrum";
		return L"Scrum Trainer";
	case ROLE::QAEngineer:
		if (shortVersion)
			return L"QA Engi";
		return L"Q&A Engineer";
	case ROLE::BackendDev:
		if (shortVersion)
			return L"Backend";
		return L"Backend Developer";
	case ROLE::FrontendDev:
		if (shortVersion)
			return L"Frontend";
		return L"Frontend Developer";
	default:
		if (shortVersion)
			return L"Undef";
		return L"Undefined";
	}
	return L"ERROR!";
}

std::wstring StatusToWstring(STATUS status, int& activeColor)
{
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

void BoxPrintStudent(STUDENT st, HANDLE hConsole, size_t indent)
{
	//┌─┤├─┐└┘├┤─│
	std::wstring header = L"┌──────────────┤ STUDENT ├──────────────┐";
	std::wstring footer = L"└───────────────────────────────────────┘";
	std::wstring temp = L"";
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;
	PrintBoxStyle(header, hConsole,(st.name + L' ' + st.surname), BASE_COLOUR, NAME_COLOUR, L'│', indent);
	temp = st.Class;
	PrintBoxStyle(header, hConsole, (L"Class " + temp), BASE_COLOUR, CLASS_COLOUR, L'│', indent);
	PrintBoxStyle(header, hConsole, RoleToWstring(st.role), BASE_COLOUR, ROLE_COLOUR, L'│', indent);
	PrintBoxStyle(header, hConsole, EmailToWstring(st.email), BASE_COLOUR, EMAIL_COLOUR, L'│', indent);
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << footer;
	std::wcout << L'\n';
}

void InlinePrintStudent(STUDENT st, HANDLE hConsole, size_t indent)
{
	std::vector<std::wstring> content;
	std::wstring temp = L"Class ";
	content.push_back((st.name + L" " + st.surname));
	temp += st.Class;
	content.push_back(temp);
	content.push_back(RoleToWstring(st.role));
	content.push_back(EmailToWstring(st.email));
	PrintInlineStyle(content, hConsole, indent);
	content.clear();
	std::wcout << L'\n';
}

//Job for q&a
//Pls test enterStudent with all kinds of values!

STUDENT EnterStudent()
{
	STUDENT st;
	std::wstring email = L"";
	wchar_t temp = ' ';
	std::wcout << L"Name: ";
	std::wcin >> st.name;
	std::wcout << L"Surname: ";
	std::wcin >> st.surname;
	std::wcout << L"Class (A,B,C...): ";
	std::wcin >> st.Class;
	//seperate into a function!
	if (st.Class >= 'a' and st.Class <= 'z')
		st.Class -= ('a' - 'A');
	if (!(st.Class >= 'A' and st.Class <= 'Z'))
		st.Class = '?';
	std::wcout << L"Role (1.BackendDev, 2.FrontendDev, 3.Q&AEngineer, 4.ScrumTrainer): ";
	std::wcin >> temp;
	st.role = ROLE(int(temp) - 48);
	std::wcout << L"Email: ";
	std::wcin >> email;
	st.email = WstringToEmail(email);
	return st;
}

STUDENT CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	STUDENT st;
	std::wstring email = L"";
	st.name = names[rand() % names.size()];
	email += st.name + L'_';
	st.surname = surnames[rand() % surnames.size()];
	email += st.surname + L'.';
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);
	st.Class = char(rand() % 4 + 65);
	switch (rand() % 4)
	{
	case 0:
		st.role = ROLE::BackendDev;
		email += L"BD";
		break;
	case 1:
		st.role = ROLE::FrontendDev;
		email += L"FD";
		break;
	case 2:
		st.role = ROLE::QAEngineer;
		email += L"QA";
		break;
	case 3:
		st.role = ROLE::ScrumTrainer;
		email += L"ST";
		break;
	default:
		st.role = ROLE::Undefined;
		email += L"UF!!!";
		break;
	}
	st.email = WstringToEmail((email + L"@sample.io"));
	return st;
}

void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT>& vec, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		AddStudentToVector(vec, CreateSampleStudent(names, surnames));
}

void AddStudentToVector(std::vector<STUDENT>& vec, STUDENT st)
{
	vec.push_back(st);
}

void PrintStudentVector(std::vector<STUDENT>& vec, HANDLE hConsole, bool inlineStudents)
{
	if (inlineStudents)
		std::wcout << L'\n';
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineStudents)
			BoxPrintStudent(vec[i], hConsole);
		else
			InlinePrintStudent(vec[i], hConsole);
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		if(!inlineStudents)
			std::wcout << L'\n';
	}
}

void PrintTeam(TEAM team, HANDLE hConsole, size_t indent, bool inlineStudents)
{
	//┃━┏┓┗┛┫┣
	std::wstring header =   L"┏━━━━━━━━━━━━━━━━━━┫ TEAM ┣━━━━━━━━━━━━━━━━━━┓";
	std::wstring splitstr = L"┗┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┛";
	std::wstring splitend = L"┏┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┓";
	std::wstring footer =   L"┗━━━━━━━━━━━━━━━━━━┫ END. ┣━━━━━━━━━━━━━━━━━━┛";
	std::wstring temp = L"";
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << header;
	PrintBoxStyle(header, hConsole, team.name, BASE_COLOUR, NAME_COLOUR, L'┃', indent); //TAKE CARE OF COLOURS!!
	PrintBoxStyle(header, hConsole, team.description, BASE_COLOUR, DESCRIPTION_COLOUR, L'┃', indent);
	PrintBoxStyle(header, hConsole, (TmToWstring(team.dateOfSetup ,7) + L" " + TmToWstring(team.dateOfSetup, 4) + L"-" + TmToWstring(team.dateOfSetup, 5) + L"-" + TmToWstring(team.dateOfSetup, 6)), BASE_COLOUR, DATEOFSETUP_COLOUR, L'┃', indent);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << splitstr;
	//FIGURE OUT A SMARTER SOLUTION!!!
	std::wcout << L'\n';
	if (inlineStudents)
	{
		InlinePrintStudent(team.students[0], hConsole, indent + 2);
		InlinePrintStudent(team.students[1], hConsole, indent + 2);
		InlinePrintStudent(team.students[2], hConsole, indent + 2);
		InlinePrintStudent(team.students[3], hConsole, indent + 2);
	}
	else
	{
		BoxPrintStudent(team.students[0], hConsole, indent + 2);
		std::wcout << L'\n';
		BoxPrintStudent(team.students[1], hConsole, indent + 2);
		std::wcout << L'\n';
		BoxPrintStudent(team.students[2], hConsole, indent + 2);
		std::wcout << L'\n';
		BoxPrintStudent(team.students[3], hConsole, indent + 2);
	}
	PrintIndent(indent);
	std::wcout << splitend;
	int activeColor = UNDEFINED_COLOUR;
	temp = StatusToWstring(team.status, activeColor);
	PrintBoxStyle(header, hConsole, temp, BASE_COLOUR, activeColor, L'┃', indent);
	//Add smt to show the teacher responsible for this team!
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << footer;
	std::wcout << L'\n';
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
	wchar_t temp = ' ';
	TEAM team;
	std::wcout << L"Team Name: ";
	//std::wcin >> team.name;
	getline(std::wcin, team.name);
	std::wcout << L"Description: ";
	//std::wcin >> team.description;
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
	std::wcout << L"\nStudent 1\n";
	team.students[0] = EnterStudent();
	std::wcout << L"\nStudent 2\n";
	team.students[1] = EnterStudent();
	std::wcout << L"\nStudent 3\n";
	team.students[2] = EnterStudent();
	std::wcout << L"\nStudent 4\n";
	team.students[3] = EnterStudent();
	return team;
}

void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<TEAM>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount; i++)
		AddTeamToVector(vec, CreateSampleTeam(teamNames, names, surnames));
}

void AddTeamToVector(std::vector<TEAM>& vec, TEAM team)
{
	vec.push_back(team);
}

void PrintTeamVector(std::vector<TEAM>& vec, HANDLE hConsole, bool inlineStudents)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		PrintTeam(vec[i], hConsole, 0, inlineStudents);
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		std::wcout << L"\n\n";
	}
}
