#pragma once

#include <fstream>

void CreateSaveDir();

enum class SEVERITY
{
	Critical = 0,
	Error    = 1,
	Warning  = 2,
	Debug    = 3,
	Info     = 4
};

std::wstring SeverityToWstring(SEVERITY severity);

//Date Time Severity Message
struct LOG
{
	tm timeStamp; //Log's time stamp
	enum SEVERITY severity; //Log's severity
	enum SEVERITY severityFilter; //Log's severity Filter
	std::wstring message; //Log's message

	std::wstring LogToWstring(wchar_t delimiter = L' ');
	void PrintLog();
	void MakeLog(SEVERITY inSeverity, std::wstring inMessage);

	std::wfstream logWFStream;

	void Close();
	bool Open(std::wstring fileName);
	void SaveLog();
};