#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "windows.h"

std::vector<std::wstring> GenerateNameVector(std::string path);

#define BACKGROUND_COLOUR 0
#define BASE_COLOUR        (7  + BACKGROUND_COLOUR * 16)
#define NAME_COLOUR        (14 + BACKGROUND_COLOUR * 16)
#define CLASS_COLOUR       (9  + BACKGROUND_COLOUR * 16)
#define ROLE_COLOUR        (11 + BACKGROUND_COLOUR * 16)
#define EMAIL_COLOUR       (6  + BACKGROUND_COLOUR * 16)
#define DESCRIPTION_COLOUR (10 + BACKGROUND_COLOUR * 16)
#define DATEOFSETUP_COLOUR (12 + BACKGROUND_COLOUR * 16)
#define INUSE_COLOUR       (9  + 6 * 16)
#define NOTACTIVE_COLOUR   (7  + 8 * 16)
#define ARCHIVED_COLOUR    (14  + 4 * 16)
#define UNDEFINED_COLOUR   (0  + 13 * 16)

void PrintInBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content = L"", int baseColour = 7, int specialColour = 7, wchar_t wall = L'|', size_t indent = 0);

std::wstring Add0BeforeIntSmallerThan10(int num);
//Pick a better name!!

/*
Args:
	1. second
	2. minute
	3. hour
	4. day of month
	5. month
	6. year
	7. day of week
	8. day of year
*/
std::wstring TmToWstring(tm tm, BYTE args);

void PrintIndent(size_t indent);