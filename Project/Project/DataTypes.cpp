#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	return out;
}

std::wstring EmailToWstring(EMAIL email)
{
	return (email.username + L'@' + email.domain);
}

STUDENT CreateSampleStudent(std::vector<std::wstring> names, std::vector<std::wstring> surnames, int index)
{
	STUDENT st;
	std::wstring email = L"";
	st.Name = names[rand() % names.size()];
	email += st.Name + L'.';
	st.SurName = surnames[rand() % surnames.size()];
	email += st.SurName + L'.';
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);
	st.Class = char(rand() % 4 + 65);
	switch (rand() % 4)
	{
	case 0:
		st.Role = ROLE::BackendDev;
		email += L"BD";
		break;
	case 1:
		st.Role = ROLE::FrontendDev;
		email += L"FD";
		break;
	case 2:
		st.Role = ROLE::QAEngineer;
		email += L"QA";
		break;
	case 3:
		st.Role = ROLE::ScrumTrainer;
		email += L"ST";
		break;
	default:
		st.Role = ROLE::Undefined;
		email += L"UF!!!";
		break;
	}
	st.Email = WstringToEmail((email + L"@sample.io"));
	return st;
}

void PrintStudent(STUDENT st)
{
	//┃━┏┓┗┛┫┣
	std::wstring header = L"\n┏━━━━━━━━━━━━━━┫STUDENT┣━━━━━━━━━━━━━━┓";
	std::wstring footer = L"\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	std::wstring temp = L"";
	std::wcout << header;
	PrintInBoxStyle(header, (st.Name + L' ' + st.SurName));
	temp = st.Class;
	PrintInBoxStyle(header, (L"Class " + temp));
	switch (st.Role)
	{
	case ROLE::Undefined:
		PrintInBoxStyle(header, (L"Undefined"));
		break;
	case ROLE::ScrumTrainer:
		PrintInBoxStyle(header, (L"Scrum Trainer"));
		break;
	case ROLE::QAEngineer:
		PrintInBoxStyle(header, (L"Q&A Engineer"));
		break;
	case ROLE::BackendDev:
		PrintInBoxStyle(header, (L"Backend Developer"));
		break;
	case ROLE::FrontendDev:
		PrintInBoxStyle(header, (L"Frontend Developer"));
		break;
	default:
		break;
	}
	PrintInBoxStyle(header, EmailToWstring(st.Email));
	std::wcout << footer;
}

void AddToVector(std::vector<STUDENT>& vec, STUDENT st)
{
	vec.push_back(st);
}
//IDK if this works... test!!!

STUDENT EnterStudent()
{
	return STUDENT();
}

void PrintStVector(std::vector<STUDENT> vec)
{

}