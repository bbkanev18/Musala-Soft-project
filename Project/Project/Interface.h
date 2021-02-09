#pragma once

#include <iostream>
#include <vector>

std::vector<std::wstring> GenerateNameVector(std::string path);

void PrintInBoxStyle(std::wstring header, std::wstring content = L"");