#include "stdafx.h"
std::vector <std::string> LogMessagesVector;

void Cheat::LogFunctions::Message(char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) + xorstr_(" [Info] ") + Message;
	std::cout << MessageString << std::endl;
	LogMessagesVector.push_back(MessageString);
}

void Cheat::LogFunctions::DebugMessage(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) + xorstr_(" [Debug] ") + Message;
	std::cout << MessageString << std::endl;
	LogMessagesVector.push_back(MessageString);
}

void Cheat::LogFunctions::Error(char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) + xorstr_(" [Error] ") + Message;
	std::cout << MessageString << std::endl;
	LogMessagesVector.push_back(MessageString);
	MessageBoxA(NULL, Message, xorstr_("GTAV Cheat Error"), MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
}

void Cheat::LogFunctions::DumpLogMessagesToFile()
{
	std::string LogFileFolder = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav");
	std::string LogFilePath = LogFileFolder + (std::string)xorstr_("\\DumpedLogData.txt");
	remove(LogFilePath.c_str());

	std::ofstream LogFileHandle;
	LogFileHandle.open(LogFilePath, std::ios_base::app);
	LogFileHandle << xorstr_("GTAV Cheat - Dumped Log Data | ") << CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("%d-%m-%Y - %H:%M:%S")) << std::endl;
	for (auto const& i : LogMessagesVector)
	{
		LogFileHandle << i << std::endl;
	}
	LogFileHandle.close();
	ShellExecuteA(NULL, "open", LogFileFolder.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}