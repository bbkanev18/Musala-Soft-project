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

STUDENT CreateSampleStudent(std::vector<std::wstring> names, std::vector<std::wstring> surnames)
{
	STUDENT st;
	std::wstring email = L"";
	st.name = names[rand() % names.size()];
	email += st.name + L'_';
	st.surName = surnames[rand() % surnames.size()];
	email += st.surName + L'.';
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

void PrintStudent(STUDENT st, HANDLE hConsole, size_t indent)
{
	//┌─┤├─┐└┘├┤─│
	std::wstring header = L"┌──────────────┤ STUDENT ├──────────────┐";
	std::wstring footer = L"└───────────────────────────────────────┘";
	std::wstring temp = L"";
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << header;
	PrintInBoxStyle(header, hConsole,(st.name + L' ' + st.surName), BASE_COLOUR, NAME_COLOUR, L'│', indent);
	temp = st.Class;
	PrintInBoxStyle(header, hConsole, (L"Class " + temp), BASE_COLOUR, CLASS_COLOUR, L'│', indent);
	temp = L"Undefined";
	switch (st.role)
	{
	case ROLE::ScrumTrainer:
		temp = L"Scrum Trainer";
		break;
	case ROLE::QAEngineer:
		temp = L"Q&A Engineer";
		break;
	case ROLE::BackendDev:
		temp = L"Backend Developer";
		break;
	case ROLE::FrontendDev:
		temp = L"Frontend Developer";
		break;
	default:
		break;
	}
	PrintInBoxStyle(header, hConsole, temp, BASE_COLOUR, ROLE_COLOUR, L'│', indent);
	PrintInBoxStyle(header, hConsole, EmailToWstring(st.email), BASE_COLOUR, EMAIL_COLOUR, L'│', indent);
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	PrintIndent(indent);
	std::wcout << footer;
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
	std::wcin >> st.surName;
	std::wcout << L"Class (A,B,C...): ";
	std::wcin >> st.Class;
	//seperate into a function!
	if (st.Class >= 'a' and st.Class <= 'z')
		st.Class -= ('a' - 'A');
	if (!(st.Class >= 'A' and st.Class <= 'Z'))
		st.Class = '?';
	std::wcout << L"Role (1.BackendDev, 2.FrontendDev, 3.Q&AEngineer, 4.ScrumTrainer): ";
	std::wcin >> temp;
	switch (temp)
	{
	case '1':
		st.role = ROLE::BackendDev;
		break;
	case '2':
		st.role = ROLE::FrontendDev;
		break;
	case '3':
		st.role = ROLE::QAEngineer;
		break;
	case '4':
		st.role = ROLE::ScrumTrainer;
		break;
	default:
		st.role = ROLE::Undefined;
		break;
	}
	std::wcout << L"Email: ";
	std::wcin >> email;
	st.email = WstringToEmail(email);
	return st;
}

void CreateSampleStudentVector(std::vector<std::wstring> names, std::vector<std::wstring> surnames, std::vector<STUDENT>& vec, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		AddStudentToVector(vec, CreateSampleStudent(names, surnames));
}

void PrintStudentVector(std::vector<STUDENT> vec, HANDLE hConsole)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		PrintStudent(vec[i], hConsole);
		SetConsoleTextAttribute(hConsole, BASE_COLOUR);
		std::wcout << L'\n';
	}
}

void AddStudentToVector(std::vector<STUDENT>& vec, STUDENT st)
{
	vec.push_back(st);
}

TEAM CreateSampleTeam(std::vector<std::wstring> teamNames, std::vector<std::wstring> names, std::vector<std::wstring> surnames, bool empty)
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

void PrintTeam(TEAM team, HANDLE hConsole, size_t indent)
{
	//┃━┏┓┗┛┫┣
	std::wstring header =   L"┏━━━━━━━━━━━━━━━━━━┫ TEAM ┣━━━━━━━━━━━━━━━━━━┓";
	std::wstring splitstr = L"┗┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┛";
	std::wstring splitend = L"┏┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┓";
	std::wstring footer =   L"┗━━━━━━━━━━━━━━━━━━┫ END. ┣━━━━━━━━━━━━━━━━━━┛";
	std::wstring temp = L"";
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	std::wcout << header;
	PrintInBoxStyle(header, hConsole, team.name, BASE_COLOUR, NAME_COLOUR, L'┃'); //TAKE CARE OF COLOURS!!
	PrintInBoxStyle(header, hConsole, team.description, BASE_COLOUR, DESCRIPTION_COLOUR, L'┃');
	PrintInBoxStyle(header, hConsole, (TmToWstring(team.dateOfSetup ,7) + L" " + TmToWstring(team.dateOfSetup, 4) + L"-" + TmToWstring(team.dateOfSetup, 5) + L"-" + TmToWstring(team.dateOfSetup, 6)), BASE_COLOUR, DATEOFSETUP_COLOUR, L'┃');
	std::wcout << L'\n';
	std::wcout << splitstr;
	PrintStudent(team.students[0], hConsole, indent + 2);
	PrintStudent(team.students[1], hConsole, indent + 2);
	PrintStudent(team.students[2], hConsole, indent + 2);
	PrintStudent(team.students[3], hConsole, indent + 2);
	std::wcout << L'\n';
	std::wcout << splitend;
	int activeColor = UNDEFINED_COLOUR;
	temp = L"Undefined";
	switch (team.status)
	{
	case STATUS::InUse:
		temp = L"In Use";
		activeColor = INUSE_COLOUR;
		break;
	case STATUS::NotActive:
		temp = L"Not Active";
		activeColor = NOTACTIVE_COLOUR;
		break;
	case STATUS::Archived:
		temp = L"Archived";
		activeColor = ARCHIVED_COLOUR;
		break;
	default:
		break;
	}
	PrintInBoxStyle(header, hConsole, temp, BASE_COLOUR, activeColor, L'┃');
	//Add smt to show the teacher responsible for this team!
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << L'\n';
	std::wcout << footer;
}
