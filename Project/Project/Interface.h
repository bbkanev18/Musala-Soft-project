#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "windows.h"

#define BACKGROUND_COLOUR 0
#define BASE_COLOUR        (7  + BACKGROUND_COLOUR * 16)
#define ERROR_COLOUR       (2  + BACKGROUND_COLOUR * 16)
#define WALL_COLOUR        (4  + BACKGROUND_COLOUR * 16)
#define NAME_COLOUR        (14 + BACKGROUND_COLOUR * 16)
#define CLASS_COLOUR       (9  + BACKGROUND_COLOUR * 16)
#define ROLE_COLOUR        (11 + BACKGROUND_COLOUR * 16)
#define EMAIL_COLOUR       (6  + BACKGROUND_COLOUR * 16)
#define DESCRIPTION_COLOUR (3  + BACKGROUND_COLOUR * 16)
#define DATEOFSETUP_COLOUR (12 + BACKGROUND_COLOUR * 16)
#define INLINEPRINT_COLOUR (10 + BACKGROUND_COLOUR * 16)
#define INUSE_COLOUR       (9  + 6  * 16)
#define NOTACTIVE_COLOUR   (7  + 8  * 16)
#define ARCHIVED_COLOUR    (14 + 4  * 16)
#define UNDEFINED_COLOUR   (0  + 13 * 16)

//Prints the content in Box Style
//Eg:
//| Esse esse allo occulta noi |
void PrintBoxStyle(size_t hSize, std::wstring content = L"", int baseColour = 7, int specialColour = 7, wchar_t wall = L'|', size_t indent = 0);

//Prints the content in Inline Style
//Eg:
//| Incominciare fragilita | Intendo ingannati volta cosa | Nostra |
void PrintInlineStyle(std::vector<std::wstring>& content, size_t indent = 0, int id = -1, wchar_t seperator = L'|');

//Adds leading zeroes to num and returns it as a wstring
//Eg: 5 -> 05
//Credit for the name goes to pkgeorgiev
std::wstring AddLeadingZeroes(int num);

//Returns Day of the month, the Month and the Year as a wstring
std::wstring TmToDateWstring(tm tm, bool addWeekday = false, wchar_t delimiter = L'-');

//Returns Hours, Minutes and Seconds as a wstring
std::wstring TmToTimeWstring(tm tm, wchar_t delimiter = L':');

//Print empty spaces
void PrintIndent(size_t indent = 3);

//Print new lines
void NewLine(size_t lines = 1);

size_t ReadSizeInput();

wchar_t ReadWcharInput();

std::wstring NameInputCheck(std::wstring name);

void SetColour(const int colour);

struct MENU_ITEM
{
	size_t indent = 0;
	std::wstring content = L"";
	
	void PrintMenuItem();
};

char PrintMenuVector(std::vector<MENU_ITEM>& menu, bool clearScreen = true);

char StructSubMenu(std::vector<MENU_ITEM>& menu, bool empty = true);
