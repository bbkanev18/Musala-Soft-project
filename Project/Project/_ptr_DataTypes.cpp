#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "windows.h"

#include "_ptr_DataTypes.h"
#include "Interface.h"
#include "Log.h"

//Email

EMAIL WstringToEmail(std::wstring email, std::wstring name, std::wstring surname)
{
	EMAIL out = {};
	bool writeInUsername = true;

	if ((email == L"autogen" or email == L"ag") and name != L"" and surname != L"")
		return AutogenEmail(name, surname);

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

EMAIL AutogenEmail(std::wstring name, std::wstring surname)
{
	EMAIL out = {};
	std::wstring email = L"";												//The name and surname are used as the email's username

	email += name + L'.';
	email += surname;
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);	//Sets all characters to lower case
	out = WstringToEmail(email + L"@sample.io");							//Adds the sample domain

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

std::wstring StatusToWstring(STATUS status, int& activeColour)
{
	//Word this in a better way
	//StatusToWstring is meant to be used in a printTeam function, it gets passed a refference to activeColour that would be the colour that the status is printed in
	switch (status)
	{
	case STATUS::InUse:
		activeColour = INUSE_COLOUR;
		return L"In Use";
	case STATUS::NotActive:
		activeColour = NOTACTIVE_COLOUR;
		return L"Not Active";
	case STATUS::Archived:
		activeColour = ARCHIVED_COLOUR;
		return L"Archived";
	default:
		activeColour = UNDEFINED_COLOUR;
		return L"Undefined";
	}
}

//Person

PERSON EnterPerson()
{
	PERSON info;
	std::wstring temp = L"";

	std::wcout << L"Name: ";
	std::wcin >> info.name;
	info.name = NameInputCheck(info.name);
	std::wcout << L"Surname: ";
	std::wcin >> info.surname;
	info.surname = NameInputCheck(info.surname);
	std::wcout << L"Email (write: \"autogen\" or \"ag\" to skip): ";
	std::wcin >> temp;
	info.email = WstringToEmail(temp, info.name, info.surname);

	return info;
}

PERSON CreateSamplePerson(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	PERSON info;

	info.name = names[rand() % names.size()];
	info.surname = surnames[rand() % surnames.size()];
	info.email = AutogenEmail(info.name, info.surname);

	return info;
}

bool ArePeopleEqual(PERSON a, PERSON b)
{
	if (EmailToWstring(a.email) == EmailToWstring(b.email) and a.name == b.name and a.surname == b.surname)
		return true;

	return false;
}

//Student

void BoxPrintStudent(STUDENT* st, size_t indent)
{
	//Symbols used for the box
	//┌─┤├─┐└┘├┤─│
	std::wstring header = L"┌──────────────┤ STUDENT ├──────────────┐";
	std::wstring footer = L"└───────────────────────────────────────┘";
	std::wstring temp = L"Class ";	//Used to store st->Class
	temp += st->Class;

	SetColour(BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), (st->info.name + L' ' + st->info.surname), BASE_COLOUR, NAME_COLOUR, L'│', indent);
	PrintBoxStyle(header.size(), temp, BASE_COLOUR, CLASS_COLOUR, L'│', indent);
	PrintBoxStyle(header.size(), RoleToWstring(st->role), BASE_COLOUR, ROLE_COLOUR, L'│', indent);

	//TESTING PURPOUSES ONLY
	if (st->info.email.domain == L"badinput.io")
		std::wcout << L"\n\n\n\nDIE\n\n\n\n";
	
	PrintBoxStyle(header.size(), EmailToWstring(st->info.email), BASE_COLOUR, EMAIL_COLOUR, L'│', indent);

	SetColour(BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintStudent(STUDENT* st, size_t indent, int id)
{
	std::vector<std::wstring> content;
	std::wstring temp = L"Class ";
	temp += st->Class;

	content.push_back((st->info.name + L" " + st->info.surname));
	content.push_back(temp);
	content.push_back(RoleToWstring(st->role));
	content.push_back(EmailToWstring(st->info.email));
	PrintInlineStyle(content, indent, id);
	content.clear();
	NewLine();
}

STUDENT* EnterStudent()
{
	STUDENT* st = new STUDENT();
	size_t temp = 0;

	st->info = EnterPerson();

	std::wcout << L"Class (A,B,C...): ";
	st->Class = ReadWcharInput();
	if (st->Class >= 'a' and st->Class <= 'z')
		st->Class -= ('a' - 'A');
	if (!(st->Class >= 'A' and st->Class <= 'Z'))
		st->Class = char(rand() % 26 + 65);

	//Add special restrictions for roles, so that there is only one role in a team
	//Maybe optionall parameter

	std::wcout << L"Role (1.BackendDev, 2.FrontendDev, 3.Q&A Engineer, 4.ScrumTrainer): ";
	temp = ReadSizeInput();
	st->role = ROLE(temp);

	/*
	std::wcout << L"Role (";

	if(availableRoles % 2 == 1)				//---1
		std::wcout << L"1.BackendDev ";
	if((availableRoles / 10) % 2 == 1)		//--1-
		std::wcout << L"2.FrontendDev ";
	if((availableRoles / 100) % 2 == 1)		//-1--
		std::wcout << L"3.Q&A Engineer ";
	if((availableRoles / 1000) % 2 == 1)	//1---
		std::wcout << L"4.ScrumTrainer ";

	std::wcout << L"): ";
	std::wcin >> temp;

	//think of a smarter solution
	if (temp == 1 and (availableRoles % 2 == 1))					//---1
		st->role = ROLE(int(temp) - 48);
	else if (temp == 2 and ((availableRoles / 10) % 2 == 1))		//--1-
		st->role = ROLE(int(temp) - 48);
	else if (temp == 3 and ((availableRoles / 100) % 2 == 1))		//-1--
		st->role = ROLE(int(temp) - 48);
	else if (temp == 4 and ((availableRoles / 1000) % 2 == 1))		//1---
		st->role = ROLE(int(temp) - 48);
	else
	{

	}
	*/

	NewLine();
	return st;
}

STUDENT* CreateSampleStudent(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	STUDENT* st = new STUDENT();

	st->Class = char(rand() % 4 + 65);
	st->role = ROLE(rand() % 4);
	st->info = CreateSamplePerson(names, surnames);
	
	return st;
}

void RemovePointerFromVector(std::vector<STUDENT*>& vec, size_t posStart, size_t posEnd)
{
	if (posEnd != 0)
		vec.erase(vec.begin() + posStart, vec.begin() + posEnd);
	vec.erase(vec.begin() + posStart);
}

void PrintStudentVector(std::vector<STUDENT*>& vec, size_t indent, bool inlineStudents, bool index)
{
	NewLine(inlineStudents);

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineStudents)
			BoxPrintStudent(vec[i], indent);
		else
			InlinePrintStudent(vec[i], indent, ((i * index) + (-1 * !index)));

		SetColour(BASE_COLOUR);
		NewLine(!inlineStudents);
	}
}

void CreateSampleStudentVector(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<STUDENT*>& stvec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount * !empty; i++)
		AddPointerToVector(stvec, CreateSampleStudent(names, surnames));
}

void AddPointerToVector(std::vector<STUDENT*>& vec, STUDENT* obj)
{
	vec.push_back(obj);
}

void ClearPointerVector(std::vector<STUDENT*>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		delete vec[i];
	vec.clear();
}

////School
//
//void BoxPrintSchool(SCHOOL* sch, size_t indent, bool inlineTeachers, bool inlineTeams, bool inlineStudents)
//{
//	//Symbols used for box
//	//─┤├──┠┨┎┒┃┖┚┄
//	//║╔╗╚╝╠═╍╌╣
//	std::wstring header = L"╔════════════════════════════╣ SCHOOL* ╠════════════════════════════╗";
//	std::wstring splitstr = L"╚╍╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╍╝";
//	std::wstring splitend = L"╔╍╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╍╗";
//	std::wstring footer = L"╚══════════════════════════════════════════════════════════════════╝";
//	std::wstring temp = L"";
//
//	SetColour(BASE_COLOUR);
//	PrintIndent(indent);
//	std::wcout << header;
//
//	PrintBoxStyle(header.size(), sch.name, BASE_COLOUR, NAME_COLOUR, L'║', indent);
//	PrintBoxStyle(header.size(), sch.city, BASE_COLOUR, EMAIL_COLOUR, L'║', indent);
//	PrintBoxStyle(header.size(), sch.address, BASE_COLOUR, DESCRIPTION_COLOUR, L'║', indent);
//
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitstr;
//
//	NewLine(2);
//	PrintIndent(indent);
//	std::wcout << splitend;
//	PrintBoxStyle(header.size(), L"TEACHERS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitstr;
//
//	if (!inlineTeachers)
//		NewLine();
//	PrintTeacherVector(sch.teachers, indent + 1, inlineTeachers);
//
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitend;
//	PrintBoxStyle(header.size(), L"TEAMS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitstr;
//
//	if (!inlineTeams)
//		NewLine();
//	PrintTeamVector(sch.teams, indent + 2, inlineTeams, inlineStudents);
//
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitend;
//	PrintBoxStyle(header.size(), L"STUDENTS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitstr;
//	NewLine();
//
//	if (!inlineStudents)
//		NewLine();
//	for (size_t i = 0; i < sch.teams.size(); i++)
//		PrintStudentsFromTeam(sch.teams[i], indent + 3, inlineStudents);
//
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << splitend;
//
//	SetColour(BASE_COLOUR);
//	NewLine();
//	PrintIndent(indent);
//	std::wcout << footer;
//	NewLine();
//}
//
//void InlinePrintSchool(SCHOOL* sch, size_t indent, int id)
//{
//	std::vector<std::wstring> content;
//
//	content.push_back((sch.name));
//	content.push_back(sch.city);
//	content.push_back(sch.address);
//	PrintInlineStyle(content, indent, id);
//	content.clear();
//	NewLine();
//}
//
//SCHOOL* EnterSchool(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
//{
//	SCHOOL* sch;
//	std::vector<_ptr_TEAM*> tchlessVec;
//	std::vector<_ptr_TEAM*> tempTeam;
//	size_t temp = 0;
//	std::wstring wstemp = L"";
//	bool automatic = true;
//
//	NewLine();
//	std::wcout << L"════════════════════════╣ MAKING SCHOOL* ╠════════════════════════";
//	NewLine();
//
//	//wsrtring name
//	std::wcout << L"Name: ";
//	std::wcin >> sch.name;
//	sch.name = NameInputCheck(sch.name);
//	//wsrtring city
//	std::wcout << L"City: ";
//	std::wcin >> sch.city;
//	sch.city = NameInputCheck(sch.city);
//
//	//wsrtring address
//	std::wcout << L"Address (seperate with a comma ','): ";
//	std::wcin >> wstemp;
//	getline(std::wcin, sch.address);
//	wstemp += sch.address;
//	temp = wstemp.length();
//	sch.address = L"";
//	for (size_t i = 0; i < temp; i++)
//	{
//		if (i == temp - 1 and wstemp[i] == L',')
//			sch.address += L'.';
//		else
//			sch.address += wstemp[i];
//		if ((i + 1 < temp) and (wstemp[i] == L',' and wstemp[i + 1] != L' '))
//			sch.address += L' ';
//	}
//	temp = 0;
//
//	//Make Teams
//	//Ask how many
//	std::wcout << L"How many Teams (0 for none): ";
//	temp = ReadSizeInput();
//
//	if (temp > 0)
//	{
//		//Ask if user wants to make the teams manually or automatically
//		std::wcout << L"Create Teams manually or automatically (0 - for manual; 1 - for automatic): ";
//		automatic = ReadSizeInput();
//		if (automatic == 0)
//			for (size_t i = 0; i < temp; i++)
//			{
//				NewLine();
//				std::wcout << L"Team ";
//				if (temp > 1)
//					std::wcout << i + 1;
//				NewLine();
//				AddObjectToVector(tchlessVec, EnterTeam());
//			}
//		else
//			CreateSampleTeamVector(teamNames, names, surnames, tchlessVec, temp);
//	}
//
//	//Make Teachers
//	//Ask how many
//	temp = 0;
//	std::wcout << L"How many Teachers (0 for none): ";
//	temp = ReadSizeInput();
//	if (temp > 0)
//	{
//		//Ask if user wants to make the teachers manually or automatically
//		std::wcout << L"Create Teachers manually or automatically(0 - for manual; 1 - for automatic): ";
//		automatic = ReadSizeInput();
//		if (automatic == 0)
//			for (size_t i = 0; i < temp; i++)
//				AddObjectToVector(sch.teachers, EnterTeacher(tchlessVec, tempTeam));
//		else
//			CreateSampleTeacherVector(tchlessVec, tempTeam, names, surnames, sch.teachers, temp);
//
//		size_t size = tchlessVec.size();
//		for (size_t i = 0; i < size; i++)
//			AddObjectToVector(sch.teams, tchlessVec[i]);
//
//		for (size_t i = 0; i < temp; i++)
//			for (size_t j = 0; j < sch.teachers[i].teams.size(); j++)
//				AddObjectToVector(sch.teams, sch.teachers[i].teams[j]);
//	}
//	else
//		sch.teams = tempTeam;
//
//	return sch;
//}
//
//SCHOOL* CreateSampleSchool(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
//{
//	SCHOOL* sch;
//	std::vector<_ptr_TEAM*> tchlessVec;
//
//	sch.name = schoolNames[rand() % schoolNames.size()];
//	sch.city = L"Manberg";
//	sch.address = L"I have no idea where? NULL island?";
//
//	CreateSampleTeamVector(teamNames, names, surnames, tchlessVec, 40);
//	CreateSampleTeacherVector(tchlessVec, sch.teams, names, surnames, sch.teachers, 8);
//
//	size_t size = tchlessVec.size();
//	for (size_t i = 0; i < size; i++)
//		AddObjectToVector(sch.teams, tchlessVec[i]);
//
//	for (size_t i = 0; i < sch.teachers.size(); i++)
//		for (size_t j = 0; j < sch.teachers[i].teams.size(); j++)
//			AddObjectToVector(sch.teams, sch.teachers[i].teams[j]);
//
//	return sch;
//}
//
//void CreateSampleSchoolVector(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<SCHOOL*>& vec, size_t amount, bool empty)
//{
//	for (size_t i = 0; i < amount; i++)
//		AddObjectToVector(vec, CreateSampleSchool(schoolNames, teamNames, names, surnames));
//}
//
//void AddObjectToVector(std::vector<SCHOOL*>& vec, SCHOOL* obj)
//{
//	vec.push_back(obj);
//}
//
//void RemovePointerFromVector(std::vector<SCHOOL*>& vec, size_t posStart, size_t posEnd)
//{
//	if (posEnd != 0)
//		vec.erase(vec.begin() + posStart, vec.begin() + posEnd);
//	vec.erase(vec.begin() + posStart);
//}
//
//void PrintSchoolVector(std::vector<SCHOOL*> vec, size_t indent, bool inlineSchool, bool index)
//{
//	if (inlineSchool)
//		NewLine();
//
//	for (size_t i = 0; i < vec.size(); i++)
//	{
//		if (!inlineSchool)
//			BoxPrintSchool(vec[i], indent);
//		else
//			if (index)
//				InlinePrintSchool(vec[i], indent, i);
//			else
//				InlinePrintSchool(vec[i], indent);
//
//		SetColour(BASE_COLOUR);
//		if (!inlineSchool)
//			NewLine();
//	}
//}

//Team

void BoxPrintTeam(_ptr_TEAM* team, size_t indent, bool inlineStudents)
{
	//Symbols used for box
	//┃━┏┓┗┛┫┣┅┄┎─┖┨┠┒┚
	std::wstring header    = L"┏━━━━━━━━━━━━━━━━━━┫ TEAM ┣━━━━━━━━━━━━━━━━━━┓";
	std::wstring splitstr  = L"┗┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┛";
	std::wstring splitend  = L"┏┅┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┅┓";
	std::wstring footer    = L"┗━━━━━━━━━━━━━━━━━━┫ END. ┣━━━━━━━━━━━━━━━━━━┛";
	std::wstring tchHeader = L"┎────────────┨ TEACHER ┠────────────┒";
	std::wstring tchFooter = L"┖───────────────────────────────────┚";
	std::wstring temp = L"";
	int activeColour = UNDEFINED_COLOUR;

	SetColour(BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), team->name, BASE_COLOUR, NAME_COLOUR, L'┃', indent); //TAKE CARE OF COLOURS!!
	PrintBoxStyle(header.size(), team->description, BASE_COLOUR, DESCRIPTION_COLOUR, L'┃', indent);
	PrintBoxStyle(header.size(), (TmToDateWstring(team->dateOfSetup, true)), BASE_COLOUR, DATEOFSETUP_COLOUR, L'┃', indent);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;
	NewLine(2);
	PrintIndent(indent + 4);
	std::wcout << tchHeader;

	if (!(ArePeopleEqual(team->teacherInfo)))
	{
		PrintBoxStyle(tchHeader.size(), (team->teacherInfo.name + L" " + team->teacherInfo.surname), BASE_COLOUR, NAME_COLOUR, L'┃', indent + 4);
		PrintBoxStyle(tchHeader.size(), EmailToWstring(team->teacherInfo.email), BASE_COLOUR, EMAIL_COLOUR, L'┃', indent + 4);
	}
	else
		PrintBoxStyle(tchHeader.size(), L"No teacher has been assigned", BASE_COLOUR, EMAIL_COLOUR, L'┃', indent + 4);

	NewLine();
	PrintIndent(indent + 4);
	std::wcout << tchFooter;
	NewLine(!inlineStudents * 2 + 1 * inlineStudents);

	PrintStudentVector(team->_ptr_students, indent + 2, inlineStudents, inlineStudents);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitend;

	temp = StatusToWstring(team->status, activeColour);
	PrintBoxStyle(header.size(), temp, BASE_COLOUR, activeColour, L'┃', indent);

	SetColour(BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintTeam(_ptr_TEAM* team, size_t indent, int id)
{
	std::vector<std::wstring> content;
	int n = 0;

	content.push_back(team->name);
	content.push_back(StatusToWstring(team->status, n));
	PrintInlineStyle(content, indent, id);
	content.clear();
	NewLine();
}

_ptr_TEAM* CreateSampleTeam(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, bool empty)
{
	_ptr_TEAM* team = new _ptr_TEAM();
	team->name = teamNames[rand() % teamNames.size()];
	team->description = L"Medesimi novellare fa divina niuno sé";

	time_t _t;
	time(&_t);
	localtime_s(&team->dateOfSetup, &_t);

	CreateSampleStudentVector(names, surnames, team->_ptr_students, 4 * !empty + 0);

	switch (rand() % 3)
	{
	case 0:
		team->status = STATUS::InUse;
		break;
	case 1:
		team->status = STATUS::Archived;
		break;
	case 2:
		team->status = STATUS::NotActive;
		break;
	default:
		team->status = STATUS::Undefined;
		break;
	}

	return team;
}

_ptr_TEAM* EnterTeam()
{
	_ptr_TEAM* team = new _ptr_TEAM();
	size_t temp = 0;

	std::wcin.clear();
	std::wcin.ignore();
	std::wcout << L"Name: ";
	getline(std::wcin, team->name);
	//team->name = NameInputCheck(team->name);
	std::wcout << L"Description: ";
	getline(std::wcin, team->description);
	//team->description = NameInputCheck(team->description);

	//TEMPORARY SOLUTION???

	time_t _t;
	time(&_t);
	localtime_s(&team->dateOfSetup, &_t);

	//LET THE USER CHOOSE???

	std::wcout << L"Status (1.InUse, 2.Not Active, 3.Archived): ";
	temp = ReadSizeInput();

	if (temp >= 1 and temp <= 3)
		team->status = STATUS(int(temp) - 48);
	else
		team->status = STATUS::Undefined;

	//Seperate into a function?!
	for (size_t i = 0; i < 4; i++)
	{
		NewLine();
		std::wcout << L"Student " + std::to_wstring(i + 1);
		NewLine();
		team->_ptr_students.push_back(EnterStudent());
	}

	return team;
}

void RemovePointerFromVector(std::vector<_ptr_TEAM*>& vec, size_t posStart, size_t posEnd)
{
	if (posEnd != 0)
		vec.erase(vec.begin() + posStart, vec.begin() + posEnd);
	vec.erase(vec.begin() + posStart);
}

void CreateSampleTeamVector(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEAM*>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount * !empty; i++)
		AddPointerToVector(vec, CreateSampleTeam(teamNames, names, surnames));
}

void PrintTeamVector(std::vector<_ptr_TEAM*>& vec, size_t indent, bool inlineTeams, bool inlineStudents, bool index)
{
	NewLine(inlineTeams);

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineTeams)
			BoxPrintTeam(vec[i], indent, inlineStudents);
		else
			InlinePrintTeam(vec[i], indent, ((i * index) + (-1 * !index)));

		SetColour(BASE_COLOUR);
		NewLine(!inlineTeams);
	}
}


void AddPointerToVector(std::vector<_ptr_TEAM*>& vec, _ptr_TEAM* obj)
{
	vec.push_back(obj);
}

void ClearPointerVector(std::vector<_ptr_TEAM*>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		delete vec[i];
	vec.clear();
}

std::vector<_ptr_TEAM*> CombineTeamVectors(std::vector<_ptr_TEAM*>& tchTemVec, std::vector<_ptr_TEAM*>& tchlessTeams)
{
	std::vector<_ptr_TEAM*> temVec;
	for (size_t i = 0; i < tchlessTeams.size(); i++)
		AddPointerToVector(temVec, tchlessTeams[i]);
	for (size_t i = 0; i < tchTemVec.size(); i++)
		AddPointerToVector(temVec, tchTemVec[i]);
	return temVec;
}

//Teacher

void BoxPrintTeacher(_ptr_TEACHER* tch, size_t indent)
{
	//Symbols used for box
	//─┤├──┠┨┎┒┃┖┚┄
	std::wstring header = L"┎────────────────┨ TEACHER ┠────────────────┒";
	std::wstring splitstr = L"┖┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┚";
	std::wstring splitend = L"┎┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┒";
	std::wstring footer = L"┖───────────────────────────────────────────┚";
	std::wstring temp = L"";

	SetColour(BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), (tch->info.name + L' ' + tch->info.surname), BASE_COLOUR, NAME_COLOUR, L'┃', indent);
	PrintBoxStyle(header.size(), EmailToWstring(tch->info.email), BASE_COLOUR, EMAIL_COLOUR, L'┃', indent);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;

	PrintTeamVector(tch->teams, 3, true, true);

	PrintIndent(indent);
	std::wcout << splitend;

	SetColour(BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintTeacher(_ptr_TEACHER* tch, size_t indent, int id)
{
	std::vector<std::wstring> content;

	content.push_back(tch->info.name + L" " + tch->info.surname);
	content.push_back(EmailToWstring(tch->info.email));
	PrintInlineStyle(content, indent, id);
	content.clear();
	NewLine();
}

_ptr_TEACHER* EnterTeacher(std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec)
{
	_ptr_TEACHER* tch = new _ptr_TEACHER();

	

	NewLine();
	std::wcout << L"━━━━━━━━━━━━┫ MAKING TEACHER ┣━━━━━━━━━━━━";
	NewLine();
	tch->info = EnterPerson();

	//Create this!
	//Print all teams that have the default value of teacherInfo
	//Maybe have a function return a vector of all teacherless teams
	//Maybe store them in a second vector
	//Let the user choose teams from this list
	int choice = 0;
	do
	{
		//Could use some cleanup, but it works!!!

		//Maybe add an option to display a max of 30 teams and have the rest in seperate pages?

		choice = 0;
		NewLine();
		std::wcout << L"━━━━━━━━━━━━━━━━━━┫ AVAILABLE TEAM ┣━━━━━━━━━━━━━━━━━━";
		NewLine();
		PrintTeamVector(tchlessTeams, 4, true, true, true);
		NewLine();
		std::wcout << L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
		NewLine(2);
		if (!tch->teams.empty())
		{
			std::wcout << L"━━━━━━━━━━━━━━━━━━┫ ASSIGNED TEAM ┣━━━━━━━━━━━━━━━━━━";
			NewLine();
			PrintTeamVector(tch->teams, 0, true, true, true);
			NewLine();
			std::wcout << L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
			NewLine();
		}
		std::wcout << L"Choose a team from the available teams to assign the teacher to \n(0 to stop assigning) \n(negative number to remove a team from the assigned teams)\n: ";
		choice = ReadSizeInput();
		std::wcin.clear();
		//BREAKS THE PROGRAM WHEN THE USER INPUTS -1 AND THE TCH._ptr_TEAM*S IS EMPTY
		if (choice < 0 and (choice * -1) - 1 <= tch->teams.size())
		{
			AddPointerToVector(tchlessTeams, tch->teams[(choice * -1) - 1]);
			tchlessTeams[tchlessTeams.size() - 1]->teacherInfo = tch->info;
			RemovePointerFromVector(tch->teams, (choice * -1) - 1);
			RemovePointerFromVector(tchTemVec, (choice * -1) - 1);
		}
		if (choice - 1 < tchlessTeams.size())
		{
			tchlessTeams[choice - 1]->teacherInfo = tch->info;
			AddPointerToVector(tch->teams, tchlessTeams[choice - 1]);
			AddPointerToVector(tchTemVec, tchlessTeams[choice - 1]);
			RemovePointerFromVector(tchlessTeams, size_t(choice - 1));
		}
	} while (choice != 0);
	NewLine(3);

	return tch;
}

_ptr_TEACHER* CreateSampleTeacher(std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec)
{
	_ptr_TEACHER* tch = new _ptr_TEACHER();
	std::wstring email = L"";

	tch->info = CreateSamplePerson(names, surnames);

	if (tchlessTeams.size() > 0)
	{
		for (size_t i = 0; i < tchlessTeams.size(); i++)
		{
			//There is an 80% chance for a team to be assigned to a teacher
			if (rand() % 100 + 1 >= 80 and ArePeopleEqual(tchlessTeams[i]->teacherInfo))
			{
				tchlessTeams[i]->teacherInfo = tch->info;
				AddPointerToVector(tch->teams, tchlessTeams[i]);
				AddPointerToVector(tchTemVec, tchlessTeams[i]);
				RemovePointerFromVector(tchlessTeams, i);
			}
		}
	}

	return tch;
}

void AddPointerToVector(std::vector<_ptr_TEACHER*>& vec, _ptr_TEACHER* obj)
{
	vec.push_back(obj);
}

void RemovePointerFromVector(std::vector<_ptr_TEACHER*>& vec, size_t posStart, size_t posEnd)
{
	if (posEnd != 0)
		vec.erase(vec.begin() + posStart, vec.begin() + posEnd);
	vec.erase(vec.begin() + posStart);
}

void PrintTeacherVector(std::vector<_ptr_TEACHER*>& vec, size_t indent, bool inlineTeacher, bool index)
{
	NewLine(inlineTeacher);

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineTeacher)
			BoxPrintTeacher(vec[i], indent);
		else
			InlinePrintTeacher(vec[i], indent, ((i * index) + (-1 * !index)));

		SetColour(BASE_COLOUR);
		NewLine(!inlineTeacher);
	}
}

void CreateSampleTeacherVector(std::vector<_ptr_TEAM*>& tchlessTeams, std::vector<_ptr_TEAM*>& tchTemVec, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<_ptr_TEACHER*>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount * !empty and !tchlessTeams.empty(); i++)
	{
		AddPointerToVector(vec, CreateSampleTeacher(names, surnames, tchlessTeams, tchTemVec));

		//if (tchlessTeams.empty())
		//	return;
	}
}

//School

void BoxPrintSchool(SCHOOL* sch, size_t indent, bool inlineTeachers, bool inlineTeams, bool inlineStudents)
{
	//Symbols used for box
	//─┤├──┠┨┎┒┃┖┚┄
	//║╔╗╚╝╠═╍╌╣
	std::wstring header = L"╔════════════════════════════╣ SCHOOL ╠════════════════════════════╗";
	std::wstring splitstr = L"╚╍╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╍╝";
	std::wstring splitend = L"╔╍╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╍╗";
	std::wstring footer = L"╚══════════════════════════════════════════════════════════════════╝";
	std::wstring temp = L"";

	SetColour(BASE_COLOUR);
	PrintIndent(indent);
	std::wcout << header;

	PrintBoxStyle(header.size(), sch->name, BASE_COLOUR, NAME_COLOUR, L'║', indent);
	PrintBoxStyle(header.size(), sch->city, BASE_COLOUR, EMAIL_COLOUR, L'║', indent);
	PrintBoxStyle(header.size(), sch->address, BASE_COLOUR, DESCRIPTION_COLOUR, L'║', indent);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;

	NewLine(2);
	PrintIndent(indent);
	std::wcout << splitend;
	PrintBoxStyle(header.size(), L"TEACHERS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;

	if (!inlineTeachers)
		NewLine();
	PrintTeacherVector(sch->teachers, indent + 1, inlineTeachers);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitend;
	PrintBoxStyle(header.size(), L"TEAMS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;

	if (!inlineTeams)
		NewLine();
	PrintTeamVector(sch->teams, indent + 2, inlineTeams, inlineStudents);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitend;
	PrintBoxStyle(header.size(), L"STUDENTS", BASE_COLOUR, ROLE_COLOUR, L'║', indent);
	NewLine();
	PrintIndent(indent);
	std::wcout << splitstr;
	NewLine();

	if (!inlineStudents)
		NewLine();
	PrintStudentVector(sch->students, indent + 3, inlineStudents);

	NewLine();
	PrintIndent(indent);
	std::wcout << splitend;

	SetColour(BASE_COLOUR);
	NewLine();
	PrintIndent(indent);
	std::wcout << footer;
	NewLine();
}

void InlinePrintSchool(SCHOOL* sch, size_t indent, int id)
{
	std::vector<std::wstring> content;

	content.push_back((sch->name));
	content.push_back(sch->city);
	content.push_back(sch->address);
	PrintInlineStyle(content, indent, id);
	content.clear();
	NewLine();
}

SCHOOL* EnterSchool(std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	SCHOOL* sch = new SCHOOL();
	std::vector<_ptr_TEAM*> tchlessVec;
	std::vector<_ptr_TEAM*> tempTeam;
	size_t temp = 0;
	std::wstring wstemp = L"";
	bool automatic = true;

	NewLine();
	std::wcout << L"════════════════════════╣ MAKING SCHOOL ╠════════════════════════";
	NewLine();

	//wsrtring name
	std::wcout << L"Name: ";
	std::wcin >> sch->name;
	sch->name = NameInputCheck(sch->name);
	//wsrtring city
	std::wcout << L"City: ";
	std::wcin >> sch->city;
	sch->city = NameInputCheck(sch->city);

	//wsrtring address
	std::wcout << L"Address (seperate with a comma ','): ";
	std::wcin >> wstemp;
	getline(std::wcin, sch->address);
	wstemp += sch->address;
	temp = wstemp.length();
	sch->address = L"";
	for (size_t i = 0; i < temp; i++)
	{
		if (i == temp - 1 and wstemp[i] == L',')
			sch->address += L'.';
		else
			sch->address += wstemp[i];
		if ((i + 1 < temp) and (wstemp[i] == L',' and wstemp[i + 1] != L' '))
			sch->address += L' ';
	}
	temp = 0;

	//Make Teams
	//Ask how many
	std::wcout << L"How many Teams (0 for none): ";
	temp = ReadSizeInput();

	if (temp > 0)
	{
		//Ask if user wants to make the teams manually or automatically
		std::wcout << L"Create Teams manually or automatically (0 - for manual; 1 - for automatic): ";
		automatic = ReadSizeInput();
		if (automatic == 0)
			for (size_t i = 0; i < temp; i++)
			{
				NewLine();
				std::wcout << L"Team ";
				if (temp > 1)
					std::wcout << i + 1;
				NewLine();
				AddPointerToVector(tchlessVec, EnterTeam());
			}
		else
			CreateSampleTeamVector(teamNames, names, surnames, tchlessVec, temp);
	}

	//Make Teachers
	//Ask how many
	temp = 0;
	std::wcout << L"How many Teachers (0 for none): ";
	temp = ReadSizeInput();
	if (temp > 0)
	{
		//Ask if user wants to make the teachers manually or automatically
		std::wcout << L"Create Teachers manually or automatically(0 - for manual; 1 - for automatic): ";
		automatic = ReadSizeInput();
		if (automatic == 0)
			for (size_t i = 0; i < temp; i++)
				AddPointerToVector(sch->teachers, EnterTeacher(tchlessVec, tempTeam));
		else
			CreateSampleTeacherVector(tchlessVec, tempTeam, names, surnames, sch->teachers, temp);

		size_t size = tchlessVec.size();
		for (size_t i = 0; i < size; i++)
			AddPointerToVector(sch->teams, tchlessVec[i]);

		for (size_t i = 0; i < temp; i++)
			for (size_t j = 0; j < sch->teachers[i]->teams.size(); j++)
				AddPointerToVector(sch->teams, sch->teachers[i]->teams[j]);
	}
	else
		sch->teams = tempTeam;

	for (size_t i = 0; i < sch->teams.size(); i++)
		for (size_t j = 0; j < sch->teams[i]->_ptr_students.size(); j++)
			AddPointerToVector(sch->students, sch->teams[i]->_ptr_students[j]);

	return sch;
}

SCHOOL* CreateSampleSchool(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames)
{
	SCHOOL* sch = new SCHOOL();
	std::vector<_ptr_TEAM*> tchlessVec;

	sch->name = schoolNames[rand() % schoolNames.size()];
	sch->city = L"Manberg";
	sch->address = L"I have no idea where? NULL island?";

	CreateSampleTeamVector(teamNames, names, surnames, tchlessVec, 40);
	CreateSampleTeacherVector(tchlessVec, sch->teams, names, surnames, sch->teachers, 8);

	size_t size = tchlessVec.size();
	for (size_t i = 0; i < size; i++)
		AddPointerToVector(sch->teams, tchlessVec[i]);

	for (size_t i = 0; i < sch->teachers.size(); i++)
		for (size_t j = 0; j < sch->teachers[i]->teams.size(); j++)
			AddPointerToVector(sch->teams, sch->teachers[i]->teams[j]);

	for (size_t i = 0; i < sch->teams.size(); i++)
		for (size_t j = 0; j < sch->teams[i]->_ptr_students.size(); j++)
			AddPointerToVector(sch->students, sch->teams[i]->_ptr_students[j]);

	return sch;
}

void CreateSampleSchoolVector(std::vector<std::wstring>& schoolNames, std::vector<std::wstring>& teamNames, std::vector<std::wstring>& names, std::vector<std::wstring>& surnames, std::vector<SCHOOL*>& vec, size_t amount, bool empty)
{
	for (size_t i = 0; i < amount; i++)
		AddPointerToVector(vec, CreateSampleSchool(schoolNames, teamNames, names, surnames));
}

void AddPointerToVector(std::vector<SCHOOL*>& vec, SCHOOL* obj)
{
	vec.push_back(obj);
}

void RemovePointerFromVector(std::vector<SCHOOL*>& vec, size_t posStart, size_t posEnd)
{
	if (posEnd != 0)
		vec.erase(vec.begin() + posStart, vec.begin() + posEnd);
	vec.erase(vec.begin() + posStart);
}

void PrintSchoolVector(std::vector<SCHOOL*> vec, size_t indent, bool inlineSchool, bool index)
{
	if (inlineSchool)
		NewLine();

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (!inlineSchool)
			BoxPrintSchool(vec[i], indent);
		else
			if (index)
				InlinePrintSchool(vec[i], indent, i);
			else
				InlinePrintSchool(vec[i], indent);

		SetColour(BASE_COLOUR);
		if (!inlineSchool)
			NewLine();
	}
}
