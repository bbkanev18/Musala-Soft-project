#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "DataTypes.h"


EMAIL GenerateEmail(std::wstring email)
{
	EMAIL out;
	bool writeInUsername = true;
	for (size_t i = 0; i < email.length(); i++)
	{
		if (email[i] == L'@')
			writeInUsername = false;

		if (writeInUsername)
			out.username += email[i];
		else
			out.domain += email[i];
	}
	return out;
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
	st.Email = GenerateEmail((email + L"@sample.io"));
	return st;
}

void PrintStudent(STUDENT st)
{

}

template <typename T>
void AddToVector(std::vector<T>& vec, T obj)
{
	vec.push_back(obj);
}
//IDK if this works... test!!!

STUDENT EnterStudent()
{
	return STUDENT();
}

void PrintStVector(std::vector<STUDENT> vec)
{

}