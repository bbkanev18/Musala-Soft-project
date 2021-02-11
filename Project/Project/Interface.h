#pragma once

#include <iostream>
#include <vector>
#include "windows.h"

std::vector<std::wstring> GenerateNameVector(std::string path);

#define BASE_COLOUR 7
#define NAME_COLOUR 14
#define CLASS_COLOUR 9
#define ROLE_COLOUR 11
#define EMAIL_COLOUR 6

void PrintInBoxStyle(std::wstring header, HANDLE hConsole, std::wstring content = L"", int baseColour = 7, int specialColour = 7);