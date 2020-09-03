#include "stdafx.h"

void Cheat::LogFunctions::Message(char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) << xorstr_(" [Info] ") << Message << std::endl;
}

void Cheat::LogFunctions::DebugMessage(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) << xorstr_(" [Debug] ") << Message << std::endl;
}

void Cheat::LogFunctions::Error(char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << CheatFunctions::ReturnDateTimeFormatAsString(xorstr_("[%d-%m-%Y - %H:%M:%S]")) << xorstr_(" [Error] ") << Message << " " << std::endl;
	MessageBoxA(NULL, Message, xorstr_("Cheat Error"), MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
}
