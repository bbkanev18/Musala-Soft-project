#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

#include "Interface.h"
#include "Log.h"
#include "DataTypes.h"

void CreateSaveDir()
{
	system("mkdir c:\\ProjectSaveFiles");
	system("mkdir c:\\ProjectSaveFiles\\Musala_Soft_Project");
	system("mkdir c:\\ProjectSaveFiles\\Musala_Soft_Project\\Saves");
	system("mkdir c:\\ProjectSaveFiles\\Musala_Soft_Project\\Logs");
	system("cls");
}

std::wstring SeverityToWstring(SEVERITY severity)
{
	switch (severity)
	{
	case SEVERITY::Critical:
		return L"CRITICAL";
	case SEVERITY::Error:
		return L"ERROR";
	case SEVERITY::Warning:
		return L"WARNING";
	case SEVERITY::Debug:
		return L"DEBUG";
	case SEVERITY::Info:
		return L"INFO";
	default:
		return L"UNKNOWN";
	}
}

//Log

void LOG::MakeLog(SEVERITY inSeverity, std::wstring inMessage)
{
	if (inSeverity <= severityFilter)
	{
		severity = inSeverity;
		message = inMessage;
		time_t _t;
		time(&_t);
		localtime_s(&timeStamp, &_t);
		SaveLog();
	}
}

std::wstring LOG::LogToWstring(wchar_t delimiter)
{
	return (TmToDateWstring(timeStamp) + delimiter + TmToTimeWstring(timeStamp) + delimiter + SeverityToWstring(severity) + delimiter + message);
}

void LOG::PrintLog()
{
	if (severity <= severityFilter)
		std::wcout << LogToWstring() << std::endl;
}

bool LOG::Open(std::wstring fileName)
{
	logWFStream.open(fileName, std::ios::out | std::ios::app);
	if (logWFStream.is_open())
	{
		tm tm;
		time_t _t;
		time(&_t);
		localtime_s(&tm, &_t);
		logWFStream << "\n==============================================================================\nStart of log (" << TmToDateWstring(tm) << " " << TmToTimeWstring(tm) << ")\n\n";
	}
	return logWFStream.is_open();
}

void LOG::Close()
{
	tm tm;
	time_t _t;
	time(&_t);
	localtime_s(&tm, &_t);
	logWFStream << " \nEnd of log   (" << TmToDateWstring(tm) << " " << TmToTimeWstring(tm) << ")\n";
	logWFStream.close();
}

void LOG::SaveLog()
{
	logWFStream << LogToWstring() << '\n';
}