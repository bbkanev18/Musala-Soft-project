#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "windows.h"

std::vector<std::wstring> GenerateNameVector(std::string path);

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
#define INLINEPRINT_COLOUR (10 + BACKGROUND_COLOUR * 16) //Find a better colour!!!
#define INUSE_COLOUR       (9  + 6 * 16)
#define NOTACTIVE_COLOUR   (7  + 8 * 16)
#define ARCHIVED_COLOUR    (14  + 4 * 16)
#define UNDEFINED_COLOUR   (0  + 13 * 16)

void PrintBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content = L"", int baseColour = 7, int specialColour = 7, wchar_t wall = L'|', size_t indent = 0);

std::wstring AddLeadingZeroes(int num);
//Pick a better name!!

std::wstring TmToDateOfSetupWstring(tm tm);

std::wstring TmToDateWstring(tm tm, wchar_t delimiter = L'-');

std::wstring TmToTimeWstring(tm tm, wchar_t delimiter = L':');

void PrintIndent(size_t indent = 3);

void PrintInlineStyle(std::vector<std::wstring>& content, HANDLE hConsole, size_t indent = 0, wchar_t seperator = L'|');