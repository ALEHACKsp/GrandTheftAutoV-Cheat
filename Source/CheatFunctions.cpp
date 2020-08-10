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

std::string Cheat::CheatFunctions::ReturnDateAndTimeAsString()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, xorstr_("[%d-%m-%Y - %H:%M:%S]"));
	return oss.str();;
}

std::string Cheat::CheatFunctions::ReturnCheatBuildAsString()
{
	return xorstr_("1.2.0.1");
}

std::string Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath()
{
	char CheatModuleFilePath[MAX_PATH];
	GetModuleFileNameA(CheatModuleHandle, CheatModuleFilePath, MAX_PATH);
	return std::filesystem::path{ CheatModuleFilePath }.parent_path().string();
}


const std::string Cheat::CheatFunctions::ReturnConfigFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav\\config.ini");
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
	globalHandle(4268190).As<BOOL>() = true;

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


__int64 Cheat::CheatFunctions::FileSize(const wchar_t* name)
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesEx(name, GetFileExInfoStandard, &fad)) { return -1; } 
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
}


bool Cheat::CheatFunctions::extractResource(const HINSTANCE hInstance, WORD resourceID, LPCSTR szFilename)
{
	bool bSuccess = false;
	try
	{
		// Find and load the resource
		HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(resourceID), xorstr_(L"CHEAT_DATA"));
		HGLOBAL hFileResource = LoadResource(hInstance, hResource);

		// Open and map this to a disk file
		LPVOID lpFile = LockResource(hFileResource);
		DWORD dwSize = SizeofResource(hInstance, hResource);

		// Open the file and filemap
		HANDLE hFile = CreateFileA(szFilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
		LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

		// Write the file
		CopyMemory(lpAddress, lpFile, dwSize);

		// Un-map the file and close the handles
		UnmapViewOfFile(lpAddress);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		bSuccess = true;
	}
	catch (...)
	{
		MessageBoxA(NULL, xorstr_("Failed to extract Texture data"), xorstr_("Error"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
	}
	return bSuccess;
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

void Cheat::CheatFunctions::SaveSettings()
{
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::GodmodeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("godmode"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::SuperJumpBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superjump"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::SuperRunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superrun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ExplosiveMeleeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("explosive_melee"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::VehicleGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehiclegun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::GravityGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("gravitygun"));
	Cheat::Files::WriteBoolToIni(Cheat::GUI::ControllerInput, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("controllerinput"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::NeverWantedBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("neverwanted"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::OrbitalCannonCooldownBypassBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("orbital_cannon_cooldown_bypass"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::NoWeaponReloadBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("weapon_noreload"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::UnlimitedRocketBoostBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("unlimitedrocketboost"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::UnlimitedSpecialAbilityBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("unlimited_special_ability"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::VehicleHornBoostBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehicle_boost"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::VehicleGodmodeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehicle_godmode"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::FastRunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("fastrun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::PlayerInvisibleBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("not_visible"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::MobileRadioBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("mobile_radio"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::PlayerIgnoredBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("ignored"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::TeleportGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("teleportgun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::EntityInformationGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("entity_information_gun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::NoRagdollAndSeatbeltBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("noragdollandseatbelt"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::TriggerBotBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::TriggerBot_ShootNPCBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot_shootnpc"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::TriggerBot_ShootPlayersBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot_shootplayers"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::SuperBrakesBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superbrakes"));
	Cheat::Files::WriteBoolToIni(VehicleSpawnerSpawnInsideVehicle, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawninvehicle"));
	Cheat::Files::WriteBoolToIni(spawnvehiclewithgodmode, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawnvehiclewithgodmode"));
	Cheat::Files::WriteBoolToIni(spawnmaxupgraded, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawnmaxupgraded"));
	Cheat::Files::WriteBoolToIni(VehicleSpawnerSpawnWithBlip, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawn_vehicle_with_blip"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::JumpAroundModeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("jumparoundmode"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::TinyPlayerBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("tinyplayer"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::PlayerESPBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("allplayersesp"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::PlayerNameESPBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("allplayersesp_names"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::OffRadarBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("offradar"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::RevealPlayersBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("reveal_players"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::DriveOnWaterBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("driveonwater"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::SuperManBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superman"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::RainbowGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("rainbowgun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::DisablePhoneBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("blockphonecalls"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::NoIdleKickBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("noidlekick"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ShowSessionInformationBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_session_information"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::VehicleWeapons_DrawLaser, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("drawlaserbool"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::WeaponRapidFireBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("rapidfire"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::FakeWantedLevelBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("fakewantedlevel6"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::PlayerForceFieldBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("forcefield"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::OneHitKillBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("onehitkill"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::AirstrikeGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("airstrikegun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionVoteKickBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_votekick"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionFreezeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_freeze"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionWorldEventsBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_worldevents"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionVehicleBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_vehicle"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionAlterWantedLevelBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_alterwantedlevel"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionSessionTimeBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_sessiontime"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionGiveRemoveWeaponsBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_giveremoveweapons"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ProtectionSessionWeatherBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_sessionweather"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::BlockScriptEvents, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_remote_events"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ShowBlockedScriptEventNotifications, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_blocked_script_events_messages"));
	Cheat::Files::WriteIntToIni(Cheat::CheatFeatures::SpeedometerVectorPosition, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("speedometer"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::AutoTeleportToWaypointBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autoteleporttowaypoint"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::NoGravityBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("nogravity"));
	Cheat::Files::WriteBoolToIni(VehicleSpawnerDeleteOldVehicle, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawner_deletecurrentvehicle"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::AutoGiveAllWeaponsBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autogiveallweapons"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ShowPlayerTagsPlayerList, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_player_tags_player_list"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ShowFPSBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("showfps"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::AutoSaveSettings, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autosavesettings"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::UseKMH, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("use_kmh"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::ShowVehicleInfoAndPreview, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_vehicle_previews"));
	Cheat::Files::WriteIntToIni(BailToSinglePlayerHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_bailtosingleplayer"));
	Cheat::Files::WriteIntToIni(SuicideHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_suicide"));
	Cheat::Files::WriteIntToIni(TeleportForward2mHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_teleportforward2m"));
	Cheat::Files::WriteIntToIni(MaxUpgradeVehicleHotKey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_maxupgradevehicle"));
	Cheat::Files::WriteIntToIni(GodModeToggleHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_godmodetoggle"));
	Cheat::Files::WriteIntToIni(RepairAndCleanVehicleHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_repairandcleanvehicle"));
	Cheat::Files::WriteIntToIni(TeleportToWaypointHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_teleporttowaypoint"));
	Cheat::Files::WriteIntToIni(AntiCrashCameraHotkey, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_anticrashcamera"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::DeleteGunBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("delete_gun"));
	Cheat::Files::WriteBoolToIni(Cheat::CheatFeatures::HotkeyToggleBool, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_toggle"));
	Cheat::Files::WriteBoolToIni(show_joining_players_notification, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_joining_players_notification"));
	if (Cheat::GUI::CurrentTheme != NULL) { Cheat::Files::WriteStringToIni(Cheat::GUI::CurrentTheme, Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("active_theme")); }
	else { Cheat::Files::WriteStringToIni(xorstr_("NULL"), Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("active_theme")); }
}

void Cheat::CheatFunctions::LoadSettings(bool StartUp)
{
	if (StartUp) { Cheat::LogFunctions::Message(xorstr_("Loading Config")); }
	else { Cheat::LogFunctions::Message(xorstr_("Reloading Config")); }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("godmode")) == xorstr_("true")) { Cheat::CheatFeatures::GodmodeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("weapon_noreload")) == xorstr_("true")) { Cheat::CheatFeatures::NoWeaponReloadBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autoteleporttowaypoint")) == xorstr_("true")) { Cheat::CheatFeatures::AutoTeleportToWaypointBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("gravitygun")) == xorstr_("true")) { Cheat::CheatFeatures::GravityGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("unlimitedrocketboost")) == xorstr_("true")) { Cheat::CheatFeatures::UnlimitedRocketBoostBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("unlimited_special_ability")) == "true") { Cheat::CheatFeatures::UnlimitedSpecialAbilityBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_player_information_player_list")) == xorstr_("true")) { ShowPlayerInformationPlayerList = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_player_tags_player_list")) == xorstr_("true")) { Cheat::CheatFeatures::ShowPlayerTagsPlayerList = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("neverwanted")) == xorstr_("true")) { Cheat::CheatFeatures::NeverWantedBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superjump")) == xorstr_("true")) { Cheat::CheatFeatures::SuperJumpBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superrun")) == xorstr_("true")) { Cheat::CheatFeatures::SuperRunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("orbital_cannon_cooldown_bypass")) == xorstr_("true")) { Cheat::CheatFeatures::OrbitalCannonCooldownBypassBool = true; }
	std::string SpeedoMeterSetting = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("speedometer")); if (Cheat::CheatFunctions::StringIsInteger(SpeedoMeterSetting)) { Cheat::CheatFeatures::SpeedometerVectorPosition = std::stoi(SpeedoMeterSetting.c_str()); }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehicle_boost")) == xorstr_("true")) { Cheat::CheatFeatures::VehicleHornBoostBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("showfps")) == xorstr_("true")) { Cheat::CheatFeatures::ShowFPSBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehiclegun")) == xorstr_("true")) { Cheat::CheatFeatures::VehicleGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("vehicle_godmode")) == xorstr_("true")) { Cheat::CheatFeatures::VehicleGodmodeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("fastrun")) == xorstr_("true")) { Cheat::CheatFeatures::FastRunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("not_visible")) == xorstr_("true")) { Cheat::CheatFeatures::PlayerInvisibleBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("mobile_radio")) == xorstr_("true")) { Cheat::CheatFeatures::MobileRadioBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("ignored")) == xorstr_("true")) { Cheat::CheatFeatures::PlayerIgnoredBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("controllerinput")) == xorstr_("true")) { Cheat::GUI::ControllerInput = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("teleportgun")) == xorstr_("true")) { Cheat::CheatFeatures::TeleportGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("entity_information_gun")) == xorstr_("true")) { Cheat::CheatFeatures::EntityInformationGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("noragdollandseatbelt")) == xorstr_("true")) { Cheat::CheatFeatures::NoRagdollAndSeatbeltBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot")) == xorstr_("true")) { Cheat::CheatFeatures::TriggerBotBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot_shootnpc")) == xorstr_("true")) { Cheat::CheatFeatures::TriggerBot_ShootNPCBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("triggerbot_shootplayers")) == xorstr_("true")) { Cheat::CheatFeatures::TriggerBot_ShootPlayersBool= true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superbrakes")) == xorstr_("true")) { Cheat::CheatFeatures::SuperBrakesBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawninvehicle")) == xorstr_("true")) { VehicleSpawnerSpawnInsideVehicle = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawn_vehicle_with_blip")) == xorstr_("true")) { VehicleSpawnerSpawnWithBlip = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawner_deletecurrentvehicle")) == xorstr_("true")) { VehicleSpawnerDeleteOldVehicle = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawnvehiclewithgodmode")) == xorstr_("true")) { spawnvehiclewithgodmode = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("spawnmaxupgraded")) == xorstr_("true")) { spawnmaxupgraded = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("tinyplayer")) == xorstr_("true")) { Cheat::CheatFeatures::TinyPlayerBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("allplayersesp")) == xorstr_("true")) { Cheat::CheatFeatures::PlayerESPBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("allplayersesp_names")) == xorstr_("true")) { Cheat::CheatFeatures::PlayerNameESPBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("jumparoundmode")) == xorstr_("true")) { Cheat::CheatFeatures::JumpAroundModeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("offradar")) == xorstr_("true")) { Cheat::CheatFeatures::OffRadarBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("reveal_players")) == xorstr_("true")) { Cheat::CheatFeatures::RevealPlayersBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("driveonwater")) == xorstr_("true")) { Cheat::CheatFeatures::DriveOnWaterBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autosavesettings")) == xorstr_("true")) { Cheat::CheatFeatures::AutoSaveSettings = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("superman")) == xorstr_("true")) { Cheat::CheatFeatures::SuperManBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("rainbowgun")) == xorstr_("true")) { Cheat::CheatFeatures::RainbowGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("blockphonecalls")) == xorstr_("true")) { Cheat::CheatFeatures::DisablePhoneBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("noidlekick")) == xorstr_("true")) { Cheat::CheatFeatures::NoIdleKickBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_session_information")) == xorstr_("true")) { Cheat::CheatFeatures::ShowSessionInformationBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("drawlaserbool")) == xorstr_("true")) { Cheat::CheatFeatures::VehicleWeapons_DrawLaser = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("rapidfire")) == xorstr_("true")) { Cheat::CheatFeatures::WeaponRapidFireBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("fakewantedlevel6")) == xorstr_("true")) { Cheat::CheatFeatures::FakeWantedLevelBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_remote_events")) == xorstr_("false")) { Cheat::CheatFeatures::BlockScriptEvents = false; } else { Cheat::CheatFeatures::BlockScriptEvents = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_blocked_script_events_messages")) == xorstr_("false")) { Cheat::CheatFeatures::ShowBlockedScriptEventNotifications = false; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("forcefield")) == xorstr_("true")) { Cheat::CheatFeatures::PlayerForceFieldBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("onehitkill")) == xorstr_("true")) { Cheat::CheatFeatures::OneHitKillBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("airstrikegun")) == xorstr_("true")) { Cheat::CheatFeatures::AirstrikeGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_freeze")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionFreezeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("use_kmh")) == xorstr_("true")) { Cheat::CheatFeatures::UseKMH = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_worldevents")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionWorldEventsBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_vehicle")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionVehicleBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_alterwantedlevel")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionAlterWantedLevelBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_sessiontime")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionSessionTimeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_giveremoveweapons")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionGiveRemoveWeaponsBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_sessionweather")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionSessionWeatherBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("protection_votekick")) == xorstr_("true")) { Cheat::CheatFeatures::ProtectionVoteKickBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("nogravity")) == xorstr_("true")) { Cheat::CheatFeatures::NoGravityBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("autogiveallweapons")) == xorstr_("true")) { Cheat::CheatFeatures::AutoGiveAllWeaponsBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("delete_gun")) == xorstr_("true")) { Cheat::CheatFeatures::DeleteGunBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("explosive_melee")) == xorstr_("true")) { Cheat::CheatFeatures::ExplosiveMeleeBool = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_toggle")) == xorstr_("false")) { Cheat::CheatFeatures::HotkeyToggleBool = false; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_joining_players_notification")) == xorstr_("true")) { show_joining_players_notification = true; }
	if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("show_vehicle_previews")) == xorstr_("true")) { Cheat::CheatFeatures::ShowVehicleInfoAndPreview = true; }
	else { if (Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), "show_vehicle_previews") == "false") Cheat::CheatFeatures::ShowVehicleInfoAndPreview = false; }
	std::string ActiveThemeSetting = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("active_theme")); char* ActiveThemeSettingChar = new char[Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("active_theme")).length() + 1]; strcpy(ActiveThemeSettingChar, ActiveThemeSetting.c_str()); if (ActiveThemeSetting != xorstr_("NULL")) { Cheat::LoadTheme((char*)ActiveThemeSettingChar, true); }


	//Load Hotkeys
	std::string LoadHotkey_BailToSinglePlayer = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_bailtosingleplayer")); if (Cheat::CheatFunctions::StringIsInteger(LoadHotkey_BailToSinglePlayer)) { BailToSinglePlayerHotkey = std::stoi(LoadHotkey_BailToSinglePlayer.c_str()); }
	std::string loadHotkey_teleporttowaypoint = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_teleporttowaypoint")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_teleporttowaypoint)) { TeleportToWaypointHotkey = std::stoi(loadHotkey_teleporttowaypoint.c_str()); }
	std::string LoadHotkey_Suicide = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_suicide")); if (Cheat::CheatFunctions::StringIsInteger(LoadHotkey_Suicide)) { SuicideHotkey = std::stoi(LoadHotkey_Suicide.c_str()); }
	std::string loadHotkey_teleportforward2m = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_teleportforward2m")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_teleportforward2m)) { TeleportForward2mHotkey = std::stoi(loadHotkey_teleportforward2m.c_str()); }
	std::string loadHotkey_maxupgradevehicle = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_maxupgradevehicle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_maxupgradevehicle)) { MaxUpgradeVehicleHotKey = std::stoi(loadHotkey_maxupgradevehicle.c_str()); }
	std::string loadHotkey_godmodetoggle = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_godmodetoggle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_godmodetoggle)) { GodModeToggleHotkey = std::stoi(loadHotkey_godmodetoggle.c_str()); }
	std::string loadHotkey_repairandcleanvehicle = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_repairandcleanvehicle")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_repairandcleanvehicle)) { RepairAndCleanVehicleHotkey = std::stoi(loadHotkey_repairandcleanvehicle.c_str()); }
	std::string loadHotkey_anticrashcamera = Cheat::Files::ReadStringFromIni(Cheat::CheatFunctions::ReturnConfigFilePath(), xorstr_("CHEAT"), xorstr_("hotkey_anticrashcamera")); if (Cheat::CheatFunctions::StringIsInteger(loadHotkey_anticrashcamera)) { AntiCrashCameraHotkey = std::stoi(loadHotkey_anticrashcamera.c_str()); }
}


void Cheat::CheatFunctions::PostInitCheat()
{
	Cheat::Drawing::InitTextureFile();
	Cheat::CheatFunctions::LoadSettings(true);
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


	// Print current build
	std::cout << xorstr_("Build: ") << Cheat::CheatFunctions::ReturnCheatBuildAsString() << std::endl;
}