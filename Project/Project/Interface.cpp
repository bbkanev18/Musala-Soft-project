#include <iostream>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <ctime>
#include <string>

#include "conio.h"
#include "windows.h"

#include "Interface.h"
#include "Log.h"
#include "DataTypes.h"

std::vector<std::wstring> GenerateWstringVector(std::string path)
{
	std::wifstream wif(path);
	std::wstringstream wss;
	std::vector<std::wstring> vec;
	std::wstring line = L"ENDOFFILE";

	//Do some research to figure out how the hell it works
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	wss << wif.rdbuf();
	wif.close();

	while (true)
	{
		getline(wss, line);
		if (line == L"ENDOFFILE")
			break;
		vec.push_back(line);
	}
	return vec;
}

void PrintBoxStyle(size_t hSize, std::wstring content, int baseColour, int specialColour, wchar_t wall, size_t indent)
{
	std::wstring overflow = L"empty";			//Is the wstring that overflows through the boundry
	int dif = (hSize - 3) - content.size();		//Is the difference between header's size and content's size
	wchar_t tempC = L'-';						//Is a temporary wchar_t
	
	SetColour(baseColour);
	NewLine();
	PrintIndent(indent);
	std::wcout << wall << L' ';
	
	//Overflow protection
	if (content.size() >= (hSize - 5))	//If the size of the content is bigger than the header's size - 5
	{
		//Overflow becomes a substring of content from hSize and is long (content's size - (header's size - 5))
		overflow = content.substr(hSize - 5, content.size() - (hSize - 5));

		if (content[hSize - 6] == L' ')
			tempC = ' ';

		content = content.substr(0, hSize - 5) +  tempC;
	}
	
	SetColour(baseColour);
	PrintIndent(dif / 2);
	SetColour(specialColour);
	std::wcout << content;
	
	SetColour(baseColour);
	if (hSize % 2 == 1 and content.size() % 2 == 1)
		std::wcout << ' ';
	else if (hSize % 2 == 0 and content.size() % 2 == 0)
		std::wcout << ' ';

	PrintIndent(dif / 2);
	std::wcout << wall;

	if (overflow != L"empty")			//If there is any content in the overflow wstring recurse through PrintBoxStyle
		PrintBoxStyle(hSize, overflow, baseColour, specialColour, wall, indent);
}

void PrintInlineStyle(std::vector<std::wstring>& content, size_t indent, int id, wchar_t seperator)
{
	PrintIndent(indent);

	if (id != -1)
	{
		SetColour(WALL_COLOUR);
		std::wcout << seperator;
		SetColour(INLINEPRINT_COLOUR);
		std::wcout << L' ' << std::to_wstring(id + 1) << L' ';
	}


	SetColour(WALL_COLOUR);
	std::wcout << seperator << L' ';

	for (size_t i = 0; i < content.size(); i++)
	{
		SetColour(INLINEPRINT_COLOUR);
		std::wcout << content[i];
		SetColour(WALL_COLOUR);
		std::wcout << L' ' << seperator;

		if (i != content.size() - 1)
			std::wcout << L' ';
	}
	SetColour(BASE_COLOUR);
}

std::wstring AddLeadingZeroes(int num)
{
	std::wstring st = L"";

	if (num < 10 and num >= 0)
		st += L'0';

	st += std::to_wstring(num);

	return st;
}

std::wstring TmToDateWstring(tm tm, bool addWeekday, wchar_t delimiter)
{
	std::wstring out = L"";

	if (addWeekday)
	{
		switch (tm.tm_wday)
		{
		case 0:
			out = L"Monday ";
			break;
		case 1:
			out = L"Tuesday ";
			break;
		case 2:
			out = L"Wednesday ";
			break;
		case 3:
			out = L"Thursday ";
			break;
		case 4:
			out = L"Friday ";
			break;
		case 5:
			out = L"Saturday ";
			break;
		case 6:
			out = L"Sunday ";
			break;
		default:
			out = L"";
			break;
		}
	}
	out += AddLeadingZeroes(tm.tm_year + 1900) + delimiter;
	out += AddLeadingZeroes(tm.tm_mon + 1) + delimiter;
	out += AddLeadingZeroes(tm.tm_mday);

	return out;
}

std::wstring TmToTimeWstring(tm tm, wchar_t delimiter)
{
	std::wstring out = L"";

	out += AddLeadingZeroes(tm.tm_hour) + delimiter;
	out += AddLeadingZeroes(tm.tm_min) + delimiter;
	out += AddLeadingZeroes(tm.tm_sec);
	
	return out;
}

void PrintIndent(size_t indent)
{
	for (size_t i = 0; i < indent; i++)
		std::wcout << ' ';
}

void NewLine(size_t lines)
{
	for (size_t i = 0; i < lines; i++)
		std::wcout << L'\n';
}

char PrintMainMenu()
{
	system("CLS");


	std::wcout << L"                        ╔═══════════════╗\n"					;
	std::wcout << L"                        ║   MAIN MENU   ║\n"					;
	std::wcout << L"                        ╚═══════════════╝\n"					;
	std::wcout << L"    ╔═══════════════╗   ╔═══════════════╗   ╔═══════════════╗\n";
	std::wcout << L"    ║   Save&Load   ║   ║    _TOKEN_    ║   ║    Others     ║\n";
	std::wcout << L"    ╚═══════════════╝   ╚═══════════════╝   ╚═══════════════╝\n";
	std::wcout << L"    ╔═══════════════╗   ╔═══════════════╗   ╔═══════════════╗\n";
	std::wcout << L"    ║   1. Save     ║   ║   q. school   ║   ║   Tab. info   ║\n";
	std::wcout << L"    ║   2. Load     ║   ║   w. teacher  ║   ║   Esc. quit   ║\n";
	std::wcout << L"    ╚═══════════════╝   ║   e. team     ║   ╚═══════════════╝\n";
	std::wcout << L"                        ║   r. student  ║\n"					;
	std::wcout << L"                        ╚═══════════════╝\n"					;
	return _getch();


	/*
		╔ ╗ ╝ ╚ ║ ═
		
		
							╔═══════════════╗
							║	MAIN MENU	║
							╚═══════════════╝
					
		╔═══════════════╗	╔═══════════════╗	╔═══════════════╗
		║	Save&Load	║	║	 _TOKEN_ 	║	║	 Others		║
		╚═══════════════╝	╚═══════════════╝	╚═══════════════╝
		╔═══════════════╗	╔═══════════════╗	╔═══════════════╗
		║	1. Save		║	║	q. school	║	║	Tab. info	║
		║	2. Load		║	║	w. teacher	║	║	Esc. quit	║
		╚═══════════════╝	║	e. team		║	╚═══════════════╝
							║	r. student	║
							╚═══════════════╝

	
	
	
	
	*/





}

char StructSubMenu(std::wstring type, bool empty)
{
	system("CLS");

	/*
							╔═══════════════╗
							║	SUB MENU	║
							╚═══════════════╝
				   ╔═══════════════╗	╔═══════════════╗
				   ║  Enter&Create ║	║	 Go Bac		║
				   ╚═══════════════╝	╚═══════════════╝
				   ╔═══════════════╗	╔═══════════════╗
				   ║   a. Enter    ║	║ Esc. Go back  ║
				   ║   s. Create   ║	╚═══════════════╝
				   ║      └Sample  ║
				   ╚═══════════════╝
							
	
	
	*/

	if (!empty)
	{
		//std::wcout << L"f. Print by criteria\n\n";

		//std::wcout << L"z. Delete?\n";
		//std::wcout << L"x. Edit?\n\n";


		/*
							 ╔═══════════════╗
							 ║	 SUB MENU	 ║
							 ╚═══════════════╝
					╔═══════════════╗	╔═══════════════╗
					║  Enter&Create ║	║	 Display 	║
					╚═══════════════╝	╚═══════════════╝
					╔═══════════════╗	╔═══════════════╗
					║	a. Enter	║	║	d. Print	║
					║	s. Create	║	║	f. Print	║
					║	   └Sample	║	║	 criteria	║
					╚═══════════════╝	╚═══════════════╝
							 ╔══════════════╗
							 ║ Esc. Go back ║
							 ╚══════════════╝
		
		
		*/
		std::wcout << L"                       ╔══════════════╗\n"			;
		std::wcout << L"                       ║   SUB MENU   ║\n"			;
		std::wcout << L"                       ╚══════════════╝\n"			;
		std::wcout << L"            ╔═══════════════╗   ╔═══════════════╗\n";
		std::wcout << L"            ║  Enter&Create ║   ║    Display    ║\n";
		std::wcout << L"            ╚═══════════════╝   ╚═══════════════╝\n";
		std::wcout << L"            ╔═══════════════╗   ╔═══════════════╗\n";
		std::wcout << L"            ║   a. Enter    ║   ║   d. Print    ║\n";
		std::wcout << L"            ║   s. Create   ║   ║   f. Print    ║\n";
		std::wcout << L"            ║      └Sample  ║   ║    criteria   ║\n";
		std::wcout << L"            ╚═══════════════╝   ╚═══════════════╝\n";
		std::wcout << L"                       ╔══════════════╗\n"			;
		std::wcout << L"                       ║ Esc. Go back ║\n"			;
		std::wcout << L"                       ╚══════════════╝\n\n"			;
	}
	else
	{
		std::wcout << L"                         ╔═══════════════╗\n";
		std::wcout << L"                         ║   SUB MENU    ║\n";
		std::wcout << L"                         ╚═══════════════╝\n";
		std::wcout << L"                         ╔═══════════════╗\n";
		std::wcout << L"                         ║  Enter&Create ║\n";
		std::wcout << L"                         ╚═══════════════╝\n";
		std::wcout << L"                         ╔═══════════════╗\n";
		std::wcout << L"                         ║   a. Enter    ║\n";
		std::wcout << L"                         ║   s. Create   ║\n";
		std::wcout << L"                         ║      └Sample  ║\n";
		std::wcout << L"                         ╚═══════════════╝\n";
		std::wcout << L"                         ╔═══════════════╗\n";
		std::wcout << L"                         ║ Esc. Go back  ║\n";
		std::wcout << L"                         ╚═══════════════╝\n\n";
	}

	

	char out = _getch();

	switch (out)
	{
	case 'd':
	//case 'f':
	//case 'z':
	//case 'x':
		if (empty)
			return 'p';
	default:
		return out;
	}

}

size_t ReadSizeInput()
{
	size_t input = -1;
	bool valid = false;
	do
	{
		std::wcin >> input;
		if (std::wcin.good())
			return input;
		else
		{
			std::wcin.clear();
			std::wcin.ignore(SIZE_MAX, '\n');
			std::wcout << L"Invalid input; please re-enter.\n";
		}
	} while (true);
}

void SetColour(const int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}