#pragma once

#include <iostream>
#include <vector>

//Creates a wstring vector from a .txt file, path is the file's path
std::vector<std::wstring> GenerateWstringVector(std::string path);

//void SaveStudents(std::vector<STUDENT*>& stdVec, std::string path);
//
//void LoadStudents(std::vector<STUDENT*>& stdVec, std::string path);
