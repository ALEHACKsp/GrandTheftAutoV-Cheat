#include "stdafx.h"


void Cheat::CheatFunctions::CreateNewDirectory(std::string Path)
{
	if (!std::filesystem::create_directory(Path))
	{
		std::string String = xorstr_("Failed to create directory '") + Path + xorstr_("' Error: ") + Cheat::CheatFunctions::GetLastErrorAsString();
		Cheat::LogFunctions::DebugMessage((char*)String.c_str());
	}
	else
	{
		std::string String = xorstr_("Created directory '") + Path + xorstr_("'");
		Cheat::LogFunctions::DebugMessage((char*)String.c_str());
	}
}


bool Cheat::CheatFunctions::DoesDirectoryExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) { return false; }
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) { return true;  }

	return false;   
}

//See https://en.cppreference.com/w/cpp/io/manip/put_time
std::string Cheat::CheatFunctions::ReturnDateTimeFormatAsString(const char* DateTimeFormat)
{
	struct tm NewTimeHandle;
	time_t CurrentTimeHandle = time(0);
	localtime_s(&NewTimeHandle, &CurrentTimeHandle);
	std::ostringstream TimeDateString;
	TimeDateString << std::put_time(&NewTimeHandle, DateTimeFormat);
	return TimeDateString.str();;
}

std::string Cheat::CheatFunctions::ReturnCheatBuildAsString()
{
	return xorstr_("1.2.0.3");
}

std::string Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath()
{
	char CheatModuleFilePath[MAX_PATH];
	GetModuleFileNameA(CheatModuleHandle, CheatModuleFilePath, MAX_PATH);
	return std::filesystem::path{ CheatModuleFilePath }.parent_path().string();
}


const std::string Cheat::CheatFunctions::ReturnConfigFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav\\Config.ini");
}


char str[200];
char str2[128];
char* Cheat::CheatFunctions::CombineTwoStrings(char* string1, char* string2)
{
	strcpy_s(str2, "");
	sprintf_s(str2, xorstr_("%s %s"), string1, string2);
	return str2;
}


bool Cheat::CheatFunctions::DoesFileExists(const std::string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}



std::string Cheat::CheatFunctions::GetLastErrorAsString()
{
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) { return std::string(); }

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				  NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)& messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);
	return message;
}


Player PlayerID;
Ped PlayerPedID;
void Cheat::CheatFunctions::CheatThreadLoopFunctions()
{
	//Load MP vehicles in SP bypass
	globalHandle(4268340).As<BOOL>() = true;

	//Player ID's and Ped
	PlayerID = PLAYER::PLAYER_ID();
	PlayerPedID = PLAYER::PLAYER_PED_ID();

	//Features
	Cheat::CheatFeatures::Looped();
}


bool Cheat::CheatFunctions::IsGameWindowFocussed()
{
	HWND GameWindowHandle = FindWindowA(0, xorstr_("Grand Theft Auto V"));
	HWND HandleProcessWithKeyboardFocus = GetForegroundWindow();
	if (GameWindowHandle == HandleProcessWithKeyboardFocus) { return true; } else { return false; }
}


bool Cheat::CheatFunctions::StringIsInteger(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
bool Cheat::CheatFunctions::IsIntegerInRange(unsigned low, unsigned high, unsigned x)
{
	return  ((x - low) <= (high - low));
}


bool Cheat::CheatFunctions::ExtractResource(const HINSTANCE hInstance, WORD resourceID, LPCSTR szFilename)
{
	try
	{
		//Find and load the resource
		HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(resourceID), xorstr_(L"CHEAT_DATA"));
		if (!hResource) { throw; }
		HGLOBAL hFileResource = LoadResource(hInstance, hResource);
		if (!hFileResource) { throw; }

		//Open and map this to a disk file
		LPVOID lpFile = LockResource(hFileResource);
		DWORD dwSize = SizeofResource(hInstance, hResource);

		//Open the file and filemap
		HANDLE hFile = CreateFileA(szFilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
		if (!hFileMap) { throw; }

		LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
		if (!lpAddress) { throw; }

		//Write the file
		CopyMemory(lpAddress, lpFile, dwSize);

		//Un-map the file and close the handles
		UnmapViewOfFile(lpAddress);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		return true;
	}
	catch (...)
	{
		MessageBoxA(NULL, xorstr_("Failed to extract Texture File"), xorstr_("Error"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
	}
	return false;
}

std::string Cheat::CheatFunctions::TextureFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav\\Textures.ytd");
}

int AntiCrashCameraHotkey		= NULL;
int BailToSinglePlayerHotkey	= NULL;
int SuicideHotkey				= NULL;
int TeleportForward2mHotkey		= NULL;
int MaxUpgradeVehicleHotKey		= NULL;
int GodModeToggleHotkey			= NULL;
int RepairAndCleanVehicleHotkey = NULL;
int TeleportToWaypointHotkey	= NULL;
bool Cheat::CheatFunctions::ReturnPressedKey(int& PressedKey)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { PressedKey = VK_LBUTTON; return true; }
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) { PressedKey = VK_RBUTTON; return true; }
	else if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) { PressedKey = VK_MBUTTON;  return true; }
	else if (GetAsyncKeyState(VK_BACK) & 0x8000) { PressedKey = VK_BACK; return true; }
	else if (GetAsyncKeyState(VK_TAB) & 0x8000) { PressedKey = VK_TAB; return true; }
	else if (GetAsyncKeyState(VK_MENU) & 0x8000) { PressedKey = VK_MENU; return true; }
	else if (GetAsyncKeyState(VK_CAPITAL) & 0x8000) { PressedKey = VK_CAPITAL; return true; }
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { PressedKey = VK_ESCAPE; return true; }
	else if (GetAsyncKeyState(VK_SPACE) & 0x8000) { PressedKey = VK_SPACE; return true; }
	else if (GetAsyncKeyState(VK_PRIOR) & 0x8000) { PressedKey = VK_PRIOR; return true; }
	else if (GetAsyncKeyState(VK_NEXT) & 0x8000) { PressedKey = VK_NEXT; return true; }
	else if (GetAsyncKeyState(VK_END) & 0x8000) { PressedKey = VK_END; return true; }
	else if (GetAsyncKeyState(VK_HOME) & 0x8000) { PressedKey = VK_HOME; return true; }
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { PressedKey = VK_LEFT; return true; }
	else if (GetAsyncKeyState(VK_UP) & 0x8000) { PressedKey = VK_UP; return true; }
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { PressedKey = VK_RIGHT; return true; }
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { PressedKey = VK_DOWN; return true; }
	else if (GetAsyncKeyState(VK_SELECT) & 0x8000) { PressedKey = VK_SELECT; return true; }
	else if (GetAsyncKeyState(VK_PRINT) & 0x8000) { PressedKey = VK_PRINT; return true; }
	else if (GetAsyncKeyState(VK_SNAPSHOT) & 0x8000) { PressedKey = VK_SNAPSHOT; return true; }
	else if (GetAsyncKeyState(VK_INSERT) & 0x8000) { PressedKey = VK_INSERT; return true; }
	else if (GetAsyncKeyState(VK_DELETE) & 0x8000) { PressedKey = VK_DELETE; return true; }
	else if (GetAsyncKeyState(0x30) & 0x8000) { PressedKey = 0x30; return true; }
	else if (GetAsyncKeyState(0x31) & 0x8000) { PressedKey = 0x31; return true; }
	else if (GetAsyncKeyState(0x32) & 0x8000) { PressedKey = 0x32; return true; }
	else if (GetAsyncKeyState(0x32) & 0x8000) { PressedKey = 0x32; return true; }
	else if (GetAsyncKeyState(0x33) & 0x8000) { PressedKey = 0x33; return true; }
	else if (GetAsyncKeyState(0x34) & 0x8000) { PressedKey = 0x34; return true; }
	else if (GetAsyncKeyState(0x36) & 0x8000) { PressedKey = 0x36; return true; }
	else if (GetAsyncKeyState(0x37) & 0x8000) { PressedKey = 0x37; return true; }
	else if (GetAsyncKeyState(0x38) & 0x8000) { PressedKey = 0x38; return true; }
	else if (GetAsyncKeyState(0x39) & 0x8000) { PressedKey = 0x39; return true; }
	else if (GetAsyncKeyState(0x41) & 0x8000) { PressedKey = 0x41; return true; }
	else if (GetAsyncKeyState(0x42) & 0x8000) { PressedKey = 0x42; return true; }
	else if (GetAsyncKeyState(0x43) & 0x8000) { PressedKey = 0x43; return true; }
	else if (GetAsyncKeyState(0x44) & 0x8000) { PressedKey = 0x44; return true; }
	else if (GetAsyncKeyState(0x45) & 0x8000) { PressedKey = 0x45; return true; }
	else if (GetAsyncKeyState(0x46) & 0x8000) { PressedKey = 0x46; return true; }
	else if (GetAsyncKeyState(0x47) & 0x8000) { PressedKey = 0x47; return true; }
	else if (GetAsyncKeyState(0x48) & 0x8000) { PressedKey = 0x48; return true; }
	else if (GetAsyncKeyState(0x49) & 0x8000) { PressedKey = 0x49; return true; }
	else if (GetAsyncKeyState(0x4A) & 0x8000) { PressedKey = 0x4A; return true; }
	else if (GetAsyncKeyState(0x4B) & 0x8000) { PressedKey = 0x4B; return true; }
	else if (GetAsyncKeyState(0x4C) & 0x8000) { PressedKey = 0x4C; return true; }
	else if (GetAsyncKeyState(0x4D) & 0x8000) { PressedKey = 0x4D; return true; }
	else if (GetAsyncKeyState(0x4E) & 0x8000) { PressedKey = 0x4E; return true; }
	else if (GetAsyncKeyState(0x4F) & 0x8000) { PressedKey = 0x4F; return true; }
	else if (GetAsyncKeyState(0x50) & 0x8000) { PressedKey = 0x50; return true; }
	else if (GetAsyncKeyState(0x51) & 0x8000) { PressedKey = 0x51; return true; }
	else if (GetAsyncKeyState(0x52) & 0x8000) { PressedKey = 0x52; return true; }
	else if (GetAsyncKeyState(0x53) & 0x8000) { PressedKey = 0x53; return true; }
	else if (GetAsyncKeyState(0x54) & 0x8000) { PressedKey = 0x54; return true; }
	else if (GetAsyncKeyState(0x55) & 0x8000) { PressedKey = 0x55; return true; }
	else if (GetAsyncKeyState(0x56) & 0x8000) { PressedKey = 0x56; return true; }
	else if (GetAsyncKeyState(0x57) & 0x8000) { PressedKey = 0x57; return true; }
	else if (GetAsyncKeyState(0x58) & 0x8000) { PressedKey = 0x58; return true; }
	else if (GetAsyncKeyState(0x59) & 0x8000) { PressedKey = 0x59; return true; }
	else if (GetAsyncKeyState(0x5A) & 0x8000) { PressedKey = 0x5A; return true; }
	else if (GetAsyncKeyState(VK_LWIN) & 0x8000) { PressedKey = VK_LWIN; return true; }
	else if (GetAsyncKeyState(VK_RWIN) & 0x8000) { PressedKey = VK_RWIN; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000) { PressedKey = VK_NUMPAD0; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) { PressedKey = VK_NUMPAD1; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) { PressedKey = VK_NUMPAD2; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000) { PressedKey = VK_NUMPAD3; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000) { PressedKey = VK_NUMPAD4; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000) { PressedKey = VK_NUMPAD6; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000) { PressedKey = VK_NUMPAD7; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000) { PressedKey = VK_NUMPAD8; return true; }
	else if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000) { PressedKey = VK_NUMPAD9; return true; }
	else if (GetAsyncKeyState(VK_MULTIPLY) & 0x8000) { PressedKey = VK_MULTIPLY; return true; }
	else if (GetAsyncKeyState(VK_ADD) & 0x8000) { PressedKey = VK_ADD; return true; }
	else if (GetAsyncKeyState(VK_SEPARATOR) & 0x8000) { PressedKey = VK_SEPARATOR; return true; }
	else if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000) { PressedKey = VK_SUBTRACT; return true; }
	else if (GetAsyncKeyState(VK_DECIMAL) & 0x8000) { PressedKey = VK_DECIMAL; return true; }
	else if (GetAsyncKeyState(VK_DIVIDE) & 0x8000) { PressedKey = VK_DIVIDE; return true; }
	else if (GetAsyncKeyState(VK_F1) & 0x8000) { PressedKey = VK_F1; return true; }
	else if (GetAsyncKeyState(VK_F2) & 0x8000) { PressedKey = VK_F2; return true; }
	else if (GetAsyncKeyState(VK_F3) & 0x8000) { PressedKey = VK_F3; return true; }
	else if (GetAsyncKeyState(VK_F4) & 0x8000) { PressedKey = VK_F4; return true; }
	else if (GetAsyncKeyState(VK_F5) & 0x8000) { PressedKey = VK_F5; return true; }
	else if (GetAsyncKeyState(VK_F6) & 0x8000) { PressedKey = VK_F6; return true; }
	else if (GetAsyncKeyState(VK_F7) & 0x8000) { PressedKey = VK_F7; return true; }
	else if (GetAsyncKeyState(VK_F8) & 0x8000) { PressedKey = VK_F8; return true; }
	else if (GetAsyncKeyState(VK_F9) & 0x8000) { PressedKey = VK_F9; return true; }
	else if (GetAsyncKeyState(VK_F10) & 0x8000) { PressedKey = VK_F10; return true; }
	else if (GetAsyncKeyState(VK_F11) & 0x8000) { PressedKey = VK_F11; return true; }
	else if (GetAsyncKeyState(VK_F12) & 0x8000) { PressedKey = VK_F12; return true; }
	else if (GetAsyncKeyState(VK_F13) & 0x8000) { PressedKey = VK_F13; return true; }
	else if (GetAsyncKeyState(VK_F14) & 0x8000) { PressedKey = VK_F14; return true; }
	else if (GetAsyncKeyState(VK_F15) & 0x8000) { PressedKey = VK_F15; return true; }
	else if (GetAsyncKeyState(VK_F16) & 0x8000) { PressedKey = VK_F16; return true; }
	else if (GetAsyncKeyState(VK_F17) & 0x8000) { PressedKey = VK_F17; return true; }
	else if (GetAsyncKeyState(VK_F18) & 0x8000) { PressedKey = VK_F18; return true; }
	else if (GetAsyncKeyState(VK_F19) & 0x8000) { PressedKey = VK_F19; return true; }
	else if (GetAsyncKeyState(VK_F20) & 0x8000) { PressedKey = VK_F20; return true; }
	else if (GetAsyncKeyState(VK_F21) & 0x8000) { PressedKey = VK_F21; return true; }
	else if (GetAsyncKeyState(VK_F22) & 0x8000) { PressedKey = VK_F22; return true; }
	else if (GetAsyncKeyState(VK_F23) & 0x8000) { PressedKey = VK_F23; return true; }
	else if (GetAsyncKeyState(VK_F24) & 0x8000) { PressedKey = VK_F24; return true; }
	else if (GetAsyncKeyState(VK_NUMLOCK) & 0x8000) { PressedKey = VK_NUMLOCK; return true; }
	else if (GetAsyncKeyState(VK_SCROLL) & 0x8000) { PressedKey = VK_SCROLL; return true; }
	else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) { PressedKey = VK_LSHIFT; return true; }
	else if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) { PressedKey = VK_RSHIFT; return true; }
	else if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) { PressedKey = VK_LCONTROL; return true; }
	else if (GetAsyncKeyState(VK_OEM_CLEAR) & 0x8000) { PressedKey = VK_OEM_CLEAR; return true; }
	return false;
}


void Cheat::CheatFunctions::SaveOptionToConfig(std::string OptionName, std::string OptionValue)
{
	std::string LogMessage = xorstr_("'") + OptionName + xorstr_("' saved");
	Cheat::GameFunctions::AdvancedMinimapNotification((char*)LogMessage.c_str(), xorstr_("Textures"), xorstr_("AdvancedNotificationImage"), false, 4, xorstr_("Config"), "", 0.5f, "");
	WriteStringToIni(OptionValue, ReturnConfigFilePath(), xorstr_("SETTINGS"), OptionName);
}

std::string Cheat::CheatFunctions::GetOptionValueFromConfig(std::string OptionName)
{
	return ReadStringFromIni(ReturnConfigFilePath(), xorstr_("SETTINGS"), OptionName);
}

void Cheat::CheatFunctions::ShowItemSavingDisabledMessage(std::string OptionName)
{
	std::string DisableMessage = xorstr_("'") + OptionName + xorstr_("' cannot be saved");
	Cheat::GameFunctions::AdvancedMinimapNotification((char*)DisableMessage.c_str(), xorstr_("Textures"), xorstr_("AdvancedNotificationImage"), false, 4, xorstr_("Config"), "", 0.5f, "");
}

bool Cheat::CheatFunctions::IsSaveItemHotKeyPressed()
{
	if (GetAsyncKeyState(GUI::SaveItemKey) & 0x8000 && Cheat::CheatFunctions::IsGameWindowFocussed())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LoadSettingsThreadFunction()
{
	for (int SubMenuInt = MainMenu; SubMenuInt != SUBMENUS_END; SubMenuInt++)
	{
		SubMenus CurrentSubMenuInt = static_cast<SubMenus>(SubMenuInt);
		Cheat::GUI::MoveMenu(CurrentSubMenuInt);
		Sleep(50);
	}
	Cheat::GUI::CloseGUI();
	Cheat::GUI::PreviousMenu = NOMENU;
	Cheat::GUI::CheatGUIHasBeenOpened = false;
}

void Cheat::CheatFunctions::LoadSettings()
{
	Cheat::LogFunctions::Message(xorstr_("Loading Config"));
	std::thread LoadSettingsThreadHandle(LoadSettingsThreadFunction);
	LoadSettingsThreadHandle.detach();

	//Load Active Theme Name
	std::string ActiveThemeSetting = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("active_theme")); char* ActiveThemeSettingChar = new char[Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("active_theme")).length() + 1];
	strcpy_s(ActiveThemeSettingChar, sizeof(ActiveThemeSettingChar), ActiveThemeSetting.c_str());
	if (ActiveThemeSetting != xorstr_("NOT_FOUND")) { Cheat::LoadTheme((char*)ActiveThemeSettingChar, true); }

	//Hotkeys
	std::string LoadHotkey_BailToSinglePlayer = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_bailtosingleplayer")); if (Cheat::CheatFunctions::StringIsInteger(LoadHotkey_BailToSinglePlayer)) { BailToSinglePlayerHotkey = std::stoi(LoadHotkey_BailToSinglePlayer.c_str()); }
	std::string loadHotkey_teleporttowaypoint = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_teleporttowaypoint")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_teleporttowaypoint)) { TeleportToWaypointHotkey = std::stoi(loadHotkey_teleporttowaypoint.c_str()); }
	std::string LoadHotkey_Suicide = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_suicide")); if (Cheat::CheatFunctions::StringIsInteger(LoadHotkey_Suicide)) { SuicideHotkey = std::stoi(LoadHotkey_Suicide.c_str()); }
	std::string loadHotkey_teleportforward2m = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_teleportforward2m")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_teleportforward2m)) { TeleportForward2mHotkey = std::stoi(loadHotkey_teleportforward2m.c_str()); }
	std::string loadHotkey_maxupgradevehicle = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_maxupgradevehicle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_maxupgradevehicle)) { MaxUpgradeVehicleHotKey = std::stoi(loadHotkey_maxupgradevehicle.c_str()); }
	std::string loadHotkey_godmodetoggle = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_godmodetoggle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_godmodetoggle)) { GodModeToggleHotkey = std::stoi(loadHotkey_godmodetoggle.c_str()); }
	std::string loadHotkey_repairandcleanvehicle = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_repairandcleanvehicle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_repairandcleanvehicle)) { RepairAndCleanVehicleHotkey = std::stoi(loadHotkey_repairandcleanvehicle.c_str()); }
	std::string loadHotkey_anticrashcamera = Cheat::CheatFunctions::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("SETTINGS"), xorstr_("hotkey_anticrashcamera")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_anticrashcamera)) { AntiCrashCameraHotkey = std::stoi(loadHotkey_anticrashcamera.c_str()); }
}


std::vector <std::string> LoadedOptionsVector;
void Cheat::CheatFunctions::RegisterOptionAsLoaded(std::string OptionName)
{
	for (auto const& i : LoadedOptionsVector)
	{
		if (i == OptionName)
		{
			return;
		}
	}
	LoadedOptionsVector.push_back(OptionName);
	Cheat::LogFunctions::DebugMessage(xorstr_("Loaded savable option '") + OptionName + xorstr_("'"));
}
bool Cheat::CheatFunctions::IsOptionRegisteredAsLoaded(std::string OptionName)
{
	for (auto const& i : LoadedOptionsVector)
	{
		if (i == OptionName)
		{
			return true;
		}
	}
	return false;
}

void Cheat::CheatFunctions::PostInitCheat()
{
	Cheat::GUI::Drawing::InitTextureFile();
	Cheat::CheatFunctions::LoadSettings();
	Cheat::LogFunctions::Message(xorstr_("GTAV Cheat Initialization Completed"));
	Cheat::CheatFeatures::PostInitScaleFormStart = std::chrono::high_resolution_clock::now();
}

char* Cheat::CheatFunctions::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

std::string Cheat::CheatFunctions::VirtualKeyCodeToString(UCHAR virtualKey)
{
	UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	CHAR szName[128];
	int result = 0;
	switch (virtualKey)
	{
	case VK_LEFT:		case VK_UP: case VK_RIGHT: case VK_DOWN:
	case VK_RCONTROL:	case VK_RMENU:
	case VK_LWIN:		case VK_RWIN: case VK_APPS:
	case VK_PRIOR:		case VK_NEXT:
	case VK_END:		case VK_HOME:
	case VK_INSERT:		case VK_DELETE:
	case VK_DIVIDE:
	case VK_NUMLOCK:
		scanCode |= KF_EXTENDED;
		break;
	default:
		result = GetKeyNameTextA(scanCode << 16, szName, 128);
	}
	if (result == 0) { return xorstr_("Unknown"); }
	return szName;
}

void Cheat::CheatFunctions::CreateConsole()
{
	Cheat::LogFunctions::Message(xorstr_("Allocating Console"));
	AllocConsole();
	SetConsoleTitleA(xorstr_("GTAV Cheat Console"));

	// Set Console Dimensions so all text is properly visible
	HWND ConsoleWindowHandle = GetConsoleWindow();
	RECT CurrentRect;
	GetWindowRect(ConsoleWindowHandle, &CurrentRect);
	MoveWindow(ConsoleWindowHandle, CurrentRect.left, CurrentRect.top, 1100, 500, TRUE);
	CloseHandle(ConsoleWindowHandle);

	//Disable Close Button Console Window And Set Max Window Size
	HWND hwnd = ::GetConsoleWindow();
	if (hwnd != NULL)
	{
		SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

		HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
		if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);


		//Disable Console Quick Edit Mode
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		if (stdIn != INVALID_HANDLE_VALUE) {
			DWORD dwMode = 0;
			if (GetConsoleMode(stdIn, &dwMode)) {
				dwMode &= ~ENABLE_QUICK_EDIT_MODE;
				SetConsoleMode(stdIn, dwMode | ENABLE_EXTENDED_FLAGS);
			}
		}
	}

	//Redirect Std Outputs to Console
	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE* COutputHandle = _fdopen(SystemOutput, xorstr_("w"));
	HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
	int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE* CErrorHandle = _fdopen(SystemError, xorstr_("w"));
	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE* CInputHandle = _fdopen(SystemInput, xorstr_("r"));
	std::ios::sync_with_stdio(true);
	freopen_s(&CInputHandle, xorstr_("CONIN$"), xorstr_("r"), stdin);
	freopen_s(&COutputHandle, xorstr_("CONOUT$"), xorstr_("w"), stdout);
	freopen_s(&CErrorHandle, xorstr_("CONOUT$"), xorstr_("w"), stderr);
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();


	//Print current build
	std::cout << xorstr_("Build: ") << Cheat::CheatFunctions::ReturnCheatBuildAsString() << std::endl;
}


int Cheat::CheatFunctions::ReturnNumberOfDigitsInValue(double Number) 
{
	int i = 0;
	if (Number < 0)
	{
		Number *= -1;
	}
	while (Number > pow(10, i))
	{
		i++;
	}
	return i;
}

void Cheat::CheatFunctions::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}

std::string Cheat::CheatFunctions::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), xorstr_("NOT_FOUND"), buf, 100, file.c_str());
	return (std::string)buf;
}

void Cheat::CheatFunctions::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool Cheat::CheatFunctions::StringToBool(std::string String)
{
	std::transform(String.begin(), String.end(), String.begin(), ::tolower);
	if (String == xorstr_("true"))
	{
		return true;
	}
	else if (String == xorstr_("false"))
	{
		return false;
	}
	else if (String == xorstr_("1"))
	{
		return true;
	}
	else if (String == xorstr_("0"))
	{
		return false;
	}
}