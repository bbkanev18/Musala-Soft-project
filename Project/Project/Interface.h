#pragma once

#include <iostream>
#include <vector>
#include "windows.h"

std::vector<std::wstring> GenerateNameVector(std::string path);

#define BACKGROUND_COLOUR 0
#define BASE_COLOUR (7 + BACKGROUND_COLOUR * 16)
#define NAME_COLOUR (14 + BACKGROUND_COLOUR * 16)
#define CLASS_COLOUR (9 + BACKGROUND_COLOUR * 16)
#define ROLE_COLOUR (11 + BACKGROUND_COLOUR * 16)
#define EMAIL_COLOUR (6 + BACKGROUND_COLOUR * 16)

void PrintInBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content = L"", int baseColour = 7, int specialColour = 7);