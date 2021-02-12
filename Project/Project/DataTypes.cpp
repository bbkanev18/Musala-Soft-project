#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	if (out.domain.empty())
		out.domain = L"@badinput.io";
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

void PrintStudent(STUDENT st, HANDLE hConsole)
{
	//┃━┏┓┗┛┫┣
	std::wstring header = L"\n┏━━━━━━━━━━━━━━┫STUDENT┣━━━━━━━━━━━━━━┓";
	std::wstring footer = L"\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	std::wstring temp = L"";
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << header;
	PrintInBoxStyle(header, hConsole,(st.name + L' ' + st.surName), BASE_COLOUR, NAME_COLOUR);
	temp = st.Class;
	PrintInBoxStyle(header, hConsole, (L"Class " + temp), BASE_COLOUR, CLASS_COLOUR);
	temp = L"Undefined";
	switch (st.role)
	{
	case ROLE::Undefined:
		temp = L"Undefined";
		break;
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
	PrintInBoxStyle(header, hConsole, temp, BASE_COLOUR, ROLE_COLOUR);
	PrintInBoxStyle(header, hConsole, EmailToWstring(st.email), BASE_COLOUR, EMAIL_COLOUR);
	SetConsoleTextAttribute(hConsole, BASE_COLOUR);
	std::wcout << footer;
}

//Job for q&a
//Pls test enterStudent with all kinds of values!

STUDENT EnterStudent()
{
	STUDENT st;
	std::wstring email = L"";
	char temp = ' ';
	std::wcout << L"Name and Surname: ";
	std::wcin >> st.name >> st.surName;
	std::wcout << L"Class (A,B,C...): ";
	std::cin >> st.Class;
	//seperate into a function!
	if (st.Class >= 'a' and st.Class <= 'z')
		st.Class -= 32;
	if (!(st.Class >= 'A' and st.Class <= 'Z'))
		st.Class = 'U';
	std::wcout << L"Role (1.BackendDev, 2.FrontendDev, 3.QAEngineer, 4.ScrumTrainer): ";
	std::cin >> temp;
	switch (rand() % 4)
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

TEAM CreateSampleTeam(std::vector<std::wstring> teamNames, std::vector<std::wstring> names, std::vector<std::wstring> surnames)
{
	TEAM tm;
	tm.name = teamNames[rand() % teamNames.size()];
	tm.description = L"Medesimi novellare fa divina niuno sé";
	//Think about tm...
	for (size_t i = 0; i < 4; i++)
		tm.students[i] = CreateSampleStudent(names, surnames);
	switch (rand() % 3)
	{
	case 0:
		tm.status = STATUS::InUse;
		break;
	case 1:
		tm.status = STATUS::Archived;
		break;
	case 2:
		tm.status = STATUS::NotActive;
		break;
	default:
		tm.status = STATUS::Undefined;
		break;
	}
	return tm;
}
