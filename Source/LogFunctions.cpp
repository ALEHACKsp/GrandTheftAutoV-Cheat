#include "stdafx.h"

void Cheat::LogFunctions::Message(char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString("[%d-%m-%Y - %H:%M:%S]") << " [Info] " << Message << std::endl;
}
void
Cheat::LogFunctions::MessageCustomCategory(std::string CategoryName, std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString("[%d-%m-%Y - %H:%M:%S]") << " [" << CategoryName << "] " << Message << std::endl;
}

void Cheat::LogFunctions::DebugMessage(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString("[%d-%m-%Y - %H:%M:%S]") << " [Debug] " << Message << std::endl;
}

void Cheat::LogFunctions::Error(char* Message, bool ShowMessageBox)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString("[%d-%m-%Y - %H:%M:%S]") << " [Error] " << Message << std::endl;
	if (ShowMessageBox)
	{
		MessageBoxA(NULL, Message, "GTAV Cheat Error", MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
	}
}