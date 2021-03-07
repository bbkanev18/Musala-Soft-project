#pragma once

#include <fstream>

//Creates the directories where saves and logs are being stored
void CreateSaveDir();

//Severity of a log entry
enum class SEVERITY
{
	Critical = 0,	//Something that will cause major problems. Fix as soon as possible, high priority
	Error    = 1,	//Something that will cause small to medium problems. Fix as soon as possible, low priority
	Warning  = 2,	//Something that may cause problems. Fix if possible, no priority
	Debug    = 3,	//Debug info
	Info     = 4	//Just some helpful info
};

//Returns the wstring form of severity
std::wstring SeverityToWstring(SEVERITY severity);

//A struct that can be used to log events and errors
struct LOG
{
	tm timeStamp = {};								//Log's time stamp - Shows the time when the log was created
	enum SEVERITY severity = SEVERITY::Info;		//Log's severity - Shows how severe the log is
	enum SEVERITY severityFilter = SEVERITY::Info;	//Lowest severity to be logged
	std::wstring message;							//Log's message

	void MakeLog(SEVERITY inSeverity, std::wstring inMessage);	//Changes the log's properties and saves it to the file
	std::wstring LogToWstring(wchar_t delimiter = L' ');		//Returns the wstring form of the log
	void PrintLog();											//Prints the log on the standart output

	std::wfstream logWFStream;		//Wide File Stream

	bool Open(std::wstring fileName);	//Adds the starting header and closes the file
	void Close();						//Adds the ending header and closes the file
	void SaveLog();						//Appends the log information to the file
};
