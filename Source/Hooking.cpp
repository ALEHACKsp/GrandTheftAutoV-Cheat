#pragma once
#include "stdafx.h"


using namespace Memory;

ScriptThread*(*GetActiveThread)() = nullptr;
HANDLE mainFiber;
DWORD wakeAt;

std::vector<LPVOID>		Hooking::m_hooks;
uint64_t*				Hooking::m_frameCount;
fpIsDLCPresent			Hooking::is_DLC_present;
TriggerScriptEvent		Hooking::trigger_script_event;
SessionWeather			Hooking::session_weather;
RequestModel	        Hooking::request_model;
GetEventData	        Hooking::get_event_data;

static eGameState* 											m_gameState;
static uint64_t												m_worldPtr;
static BlipList*											m_blipList;
static Hooking::NativeRegistrationNew**						m_registrationTable;
static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_handlerCache;
static std::vector<LPVOID>									m_hookedNative;
static __int64**                                            m_globalPtr;
clockTime*													Hooking::ClockTime;
fpSetSessionTime											Hooking::set_session_time_info;


fpGetLabelText Hooking::GetLabelText = nullptr;
fpGetScriptHandlerIfNetworked Hooking::GetScriptHandlerIfNetworked = nullptr;
fpGetScriptHandler Hooking::GetScriptHandler = nullptr;
const int EVENT_COUNT = 78; 
static std::vector<void*> EventPtr;
static char EventRestore[EVENT_COUNT] = {};


int IntegrityCheck;
void Hooking::Start(HMODULE hmoduleDLL)
{
	MenuInitialization();
}
BOOL Hooking::InitializeHooks()
{
	BOOL returnVal = TRUE;
	if (MH_Initialize() != MH_OK) { Cheat::LogFunctions::Error(xorstr_("Failed to initialize MinHook")); returnVal = FALSE; }
	if (!HookNatives()) { Cheat::LogFunctions::Error(xorstr_("Failed to initialize Gamme Hooks")); returnVal = FALSE; }
	return returnVal;
}

template <typename T>
bool Native(DWORD64 hash, LPVOID hookFunction, T** trampoline)
{
	if (*reinterpret_cast<LPVOID*>(trampoline) != NULL)
		return true;
	auto originalFunction = Hooking::GetNativeHandler(hash);
	if (originalFunction != 0) {
		MH_STATUS createHookStatus = MH_CreateHook(originalFunction, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
		if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(originalFunction) == MH_OK))
		{
			m_hookedNative.push_back((LPVOID)originalFunction);
			DEBUGMSG(xorstr_("Hooked Native 0x%#p"), hash);
			return true;
		}
	}

	return false;
}


uint64_t CMetaData::m_begin = 0;
uint64_t CMetaData::m_end = 0;
DWORD CMetaData::m_size = 0;

uint64_t CMetaData::begin()
{
	return m_begin;
}
uint64_t CMetaData::end()
{
	return m_end;
}
DWORD CMetaData::size()
{
	return m_size;
}

void CMetaData::init()
{
	if (m_begin && m_size)
		return;

	m_begin = (uint64_t)GetModuleHandleA(nullptr);
	const IMAGE_DOS_HEADER*	headerDos = (const IMAGE_DOS_HEADER*)m_begin;
	const IMAGE_NT_HEADERS*	headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
	m_size = headerNt->OptionalHeader.SizeOfCode;
	m_end = m_begin + m_size;
	return;
}

fpIsDLCPresent OG_IS_DLC_PRESENT = nullptr;
bool HK_IS_DLC_PRESENT(std::uint32_t dlcHash)
{
	static uint64_t	last = 0;
	uint64_t		cur = *Hooking::m_frameCount;
	if (last != cur)
	{
		last = cur;
		Hooking::onTickInit();
	}
	return OG_IS_DLC_PRESENT(dlcHash);
}

fpGetScriptHandlerIfNetworked ogGetScriptHandlerIfNetworked = nullptr;
void* hkGetScriptHandlerIfNetworked()
{
	return Hooking::GetScriptHandler();
}

fpGetLabelText ogGetLabelText = nullptr;
const char* hkGetLabelText(void* this_, const char* label)
{
	if (std::strcmp(label, "HUD_MPREENTER") == 0)
	{
		return "Joining A New GTA Online Session with GTAV Cheat";
	}
	if (std::strcmp(label, "HUD_JOINING") == 0)
	{
		return "Loading GTA Online With GTAV Cheat (Cloud Simulator 2021)";
	}
	if (std::strcmp(label, "HUD_QUITTING") == 0)
	{
		return "Leave Online With GTAV Cheat";
	}
	if (std::strcmp(label, "PM_QUIT_MP") == 0)
	{
		return "Leave Online with GTAV Cheat";
	}
	if (std::strcmp(label, "PM_ENTER_MP") == 0)
	{
		return "Join GTA Online with GTAV Cheat";
	}
	if (std::strcmp(label, "PM_EXIT_GAME") == 0)
	{
		return "Exit Game with GTAV Cheat";
	}
	if (std::strcmp(label, "PM_GO") == 0)
	{
		return "Go Online with GTAV Cheat";
	}
	if (std::strcmp(label, "PM_FRIEND_FM") == 0)
	{
		return "Join Friend with GTAV Cheat";
	}
	if (std::strcmp(label, "PM_FIND_SESS") == 0)
	{
		return "Find New Session with GTAV Cheat";
	}
	return ogGetLabelText(this_, label);
}

int MiscScriptsArray[] = { 297770348, 498709856, -1297785021, 143196100, -1818550779, 1432301416, 2037380969, 1818550779, -1964956981, -1010395481, 1070706073,
						   -1933245257, 380850754, -1924332863, -1704719905, 709335341, 1152017566, -1246838892, 1667907776, -2017629233, -297770348, -815817885,
						   774421744, 4136296512, 3763470309, 3030904167, 4566469881341411328, 4528819783743622349, 140698833649664, 3990864803781410816, 7218762434461302784,
						   140733193388032, 394650472960, -1542848512, -4294967296, -2063859712, -941739545, 732781082, 693546501, 693546501, 149365611, -1941292498,
						   1953937033, -498955166, 20218675039, -1424895288, -1264063129, 423635655, 400031869, -531496987, 1062544784, -803645682, -771910813, 1476326089,
						   1800294560, 1209128713, -123645928, -332594529, -327286343, -701823896, -2066829834, -125347541, -552065831, 189238289, 561831609, -2105858993,
						   564131320, -1089379066, -348418057, -615431083, 121406262, -163616977, -1961284186, 1663317123, 297770348, 498709856, -1297785021, 143196100
						   - 1818550779, 1432301416, 2037380969, 1818550779, -1964956981, -1010395481, 1070706073, -1933245257, 380850754, -1924332863, -1704719905,
						   709335341, 1152017566, -1246838892, 1667907776, -2017629233, -297770348, -815817885, 774421744, 4136296512, 3763470309, 3030904167, 140733193388032,
						   394650472960, -1542848512, -4294967296, -2063859712, -941739545, 1062333317
						};
bool block_script_events = true;
bool show_blocked_script_events_messages = true;
void* m_OriginalGetEventData = nullptr;
bool GED(int eventGroup, int eventIndex, int* argStruct, int argStructSize)
{
	auto result = static_cast<decltype(&GED)>(m_OriginalGetEventData)(eventGroup, eventIndex, argStruct, argStructSize);
	bool IsBlackListedScript = std::find(std::begin(MiscScriptsArray), std::end(MiscScriptsArray), argStruct[0]) != std::end(MiscScriptsArray);
	if (result && block_script_events && IsBlackListedScript)
	{
		if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(argStruct[1]) != PlayerPedID) {
			if (show_blocked_script_events_messages) { Cheat::GameFunctions::MinimapNotification(xorstr_("~r~Script Event Blocked")); }
			return false;
		}
	}

	return result;
}


bool Hooking::HookNatives()
{
	MH_STATUS status = MH_CreateHook(Hooking::is_DLC_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::is_DLC_present) != MH_OK) { return false; }
	Hooking::m_hooks.push_back(Hooking::is_DLC_present);
	status = MH_CreateHook(Hooking::get_event_data, GED, &m_OriginalGetEventData);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::get_event_data) != MH_OK) { return false; }
	Hooking::m_hooks.push_back(Hooking::get_event_data);
	status = MH_CreateHook(Hooking::GetScriptHandlerIfNetworked, hkGetScriptHandlerIfNetworked, (void**)&ogGetScriptHandlerIfNetworked);
	if (status != MH_OK || MH_EnableHook(Hooking::GetScriptHandlerIfNetworked) != MH_OK) { return false;  }
	Hooking::m_hooks.push_back(Hooking::GetScriptHandlerIfNetworked);
	status = MH_CreateHook(Hooking::GetLabelText, hkGetLabelText, (void**)&ogGetLabelText);
	if (status != MH_OK || MH_EnableHook(Hooking::GetLabelText) != MH_OK) { return false; }
	Hooking::m_hooks.push_back(Hooking::GetLabelText);
	return true;
}


void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		Cheat::ScriptMain();
	}
	catch (...)
	{
		char Message[100];
		snprintf(Message, sizeof(Message), xorstr_("Unhandled Exception. WinAPI error code (if any) %s"), (char*)Cheat::CheatFunctions::GetLastErrorAsString().c_str());
		Cheat::LogFunctions::Error(Message);
		std::exit(EXIT_SUCCESS);
	}
}



void Hooking::onTickInit()
{
	if (mainFiber == nullptr)
	{
		mainFiber = ConvertThreadToFiber(nullptr);
	}

	if (timeGetTime() < wakeAt)
	{
		return;
	}

	static HANDLE scriptFiber;
	if (scriptFiber)
	{
		SwitchToFiber(scriptFiber);
	}
	else 
	{ 
		scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr); 
	}
}

/*
//CPatternResult
*/

CPatternResult::CPatternResult(void* pVoid) :
	m_pVoid(pVoid)
{}
CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
	m_pVoid(pVoid),
	m_pBegin(pBegin),
	m_pEnd(pEnd)
{}
CPatternResult::~CPatternResult() {}

/*
//CPattern Public
*/

CPattern::CPattern(char* szByte, char* szMask) :
	m_szByte(szByte),
	m_szMask(szMask),
	m_bSet(false)
{}
CPattern::~CPattern() {}

CPattern&	CPattern::find(int i, uint64_t startAddress)
{
	match(i, startAddress, false);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPattern&	CPattern::virtual_find(int i, uint64_t startAddress)
{
	match(i, startAddress, true);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPatternResult	CPattern::get(int i)
{
	if (m_result.size() > i)
		return m_result[i];
	return nullptr;
}


/*
//CPattern Private
*/
bool	CPattern::match(int i, uint64_t startAddress, bool virt)
{
	if (m_bSet)
		return false;
	uint64_t	begin = 0;
	uint64_t	end = 0;
	if (!virt)
	{
		CMetaData::init();
		begin = CMetaData::begin() + startAddress;
		end = CMetaData::end();
		if (begin >= end)
			return false;
	}
	int		j = 0;
	do
	{
		if (virt)
			begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
		else
			begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
		if (begin == NULL)
			break;
		j++;
	} while (j < i);

	m_bSet = true;
	return true;
}

bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++btMask)
		if (*szMask == 'x' && *pData != *btMask)
			break;
	if ((*szMask) != 0)
		return false;
	return true;
}


uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE *btMask, char *szMask)
{
	size_t len = strlen(szMask) + 1;
	for (uint64_t i = 0; i < (end - address - len); i++)
	{
		BYTE*	ptr = (BYTE*)(address + i);
		if (byte_compare(ptr, btMask, szMask))
		{
			m_result.push_back(CPatternResult((void*)(address + i)));
			return address + i;
		}
	}
	return NULL;
}

uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE *btMask, char *szMask)
{
	MEMORY_BASIC_INFORMATION mbi;
	char*	pStart = nullptr;
	char*	pEnd = nullptr;
	char*	res = nullptr;
	size_t	maskLen = strlen(szMask);

	while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
	{
		pStart = pEnd;
		pEnd += mbi.RegionSize;
		if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
			continue;

		for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
		{
			if (byte_compare((BYTE*)pStart, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
				res = pStart;
			}
		}

		mbi = {};
	}
	return (uint64_t)res;
}

void failPat(const char* name)
{
	char Message[100];
	snprintf(Message, sizeof(Message), xorstr_("Failed to find game pattern\n\nPattern: %s"), name);
	Cheat::LogFunctions::Error(Message);
	std::exit(EXIT_SUCCESS);
}

template <typename T>
void	setPat
(
	const char*	name,
	char*		pat,
	char*		mask,
	T**			out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)
{
	T*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPat(name);

		if (deref <= 0)
			break;
		ptr = *(T**)ptr;
		--deref;
	}
	
	*out = ptr;
	return;
}

template <typename T>
void	setFn
(
	const char*	name,
	char*		pat,
	char*		mask,
	T*			out,
	int			skip = 0
)
{
	char*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	ptr = pattern.get(skip).get<char>(0);

	if (ptr == nullptr)
		failPat(name);

	*out = (T)ptr;
	return;
}

void Hooking::MenuInitialization()
{
	Cheat::LogFunctions::Message(xorstr_("Allocating Console"));
	CreateConsole();
	Cheat::LogFunctions::Init();
	Cheat::LogFunctions::Message(xorstr_("Creating Cheat Main Fiber"));
	DoGameHooking();
}


void Hooking::DoGameHooking()
{
	Cheat::LogFunctions::Message(xorstr_("Hooking Game Functions"));
	auto p_activeThread = pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");
	auto p_blipList = pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
	auto p_fixVector3Result = pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
	auto p_gameLegals = pattern("72 1F E8 ? ? ? ? 8B 0D");
	auto p_gameLogos = pattern("70 6C 61 74 66 6F 72 6D 3A");
	auto p_gameState = pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
	auto p_nativeTable = pattern("76 32 48 8B 53 40 48 8D 0D");
	auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
	auto p_globalPtr = pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
	auto p_eventHook = pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03");

	Hooking::GetLabelText = static_cast<fpGetLabelText>(Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").count(1).get(0).get<void>(0));
	Hooking::GetScriptHandlerIfNetworked = static_cast<fpGetScriptHandlerIfNetworked>(Memory::pattern("40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12 48 8B 10 48 8B C8").count(1).get(0).get<void>(0));
	Hooking::GetScriptHandler = static_cast<fpGetScriptHandler>(Memory::pattern("48 83 EC 28 E8 ? ? ? ? 33 C9 48 85 C0 74 0C E8 ? ? ? ? 48 8B 88 ? ? ? ?").count(1).get(0).get<void>(0));
	setPat<uint64_t>(xorstr_("frame count"),
		xorstr_("\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF"),
		xorstr_("xx????xxx"),
		&Hooking::m_frameCount,
		true,
		2); 
	setFn<fpIsDLCPresent>(xorstr_("is_DLC_present"),
		xorstr_("\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00"),
		xorstr_("xxxx?xxxxxxx????"),
		&Hooking::is_DLC_present);
	setFn<TriggerScriptEvent>(xorstr_("trigger_script_event"), xorstr_("\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x70\x18\x48\x89\x78\x20\x41\x56\x48\x81\xEC\x00\x00\x00\x00\x45\x8B\xF0\x41\x8B\xF9"), xorstr_("xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx"), &Hooking::trigger_script_event);
	setFn<SessionWeather>(xorstr_("session_weather"), xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x40\x8A\xE9"), xorstr_("xxxx?xxxx?xxxx?xxxxxxxx"), &Hooking::session_weather);
	setFn<RequestModel>(xorstr_("request_model"),
		xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x7C\x24\x00\x55\x48\x8B\xEC\x48\x83\xEC\x50\x8B\x45\x18"),
		xorstr_("xxxx?xxxx?xxxxxxxxxxx"),
		&Hooking::request_model);
	setFn<GetEventData>(xorstr_("get_event_data"),
		xorstr_("\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x49\x8B\xF8\x4C\x8D\x05\x00\x00\x00\x00\x41\x8B\xD9\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x14\x4C\x8B\x10\x44\x8B\xC3\x48\x8B\xD7\x41\xC1\xE0\x03\x48\x8B\xC8\x41\xFF\x52\x30\x48\x8B\x5C\x24\x00"),
		xorstr_("xxxx?xxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxx?"),
		&Hooking::get_event_data);
	setPat<clockTime>(xorstr_("clock_time"),
		xorstr_("\x48\x8D\x0D\x00\x00\x00\x00\x8B\xFA\xE8\x00\x00\x00\x00\x44\x8D\x0C\x5B"),
		xorstr_("xxx????xxx????xxxx"),
		&Hooking::ClockTime,
		true,
		3);
	setFn<fpSetSessionTime>(xorstr_("session_time_set"),
		xorstr_("\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x8B\xF9\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\xDA\x33\xD2\xE9\x00\x00\x00\x00"),
		xorstr_("xxxxxxxxxxxxxxx????xxxxxx????"),
		&Hooking::set_session_time_info);
	
	char * c_location = nullptr;
	void * v_location = nullptr;


	//Hook GameState
	c_location = p_gameState.count(1).get(0).get<char>(2);
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #1")) : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);
	
	//Hook Vector3 Bypass
	v_location = p_fixVector3Result.count(1).get(0).get<void>(0);
	if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

	//Hook Native Registration Table
	c_location = p_nativeTable.count(1).get(0).get<char>(9);
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #2")) : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	//Hook Game World Pointer
	c_location = p_worldPtr.count(1).get(0).get<char>(0);
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #3")) : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	//Hook Game Blip List
	c_location = p_blipList.count(1).get(0).get<char>(0);
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #4")) : m_blipList = (BlipList*)(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);

	// Hook Active Game Thread
	c_location = p_activeThread.count(1).get(0).get<char>(1);
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #5")) : GetActiveThread = reinterpret_cast<decltype(GetActiveThread)>(c_location + *(int32_t*)c_location + 4);

	//Get Game World Pointer
	c_location = p_globalPtr.count(1).get(0).get<char>(0);
	__int64 patternAddr = NULL;
	c_location == nullptr ? Cheat::LogFunctions::Error(xorstr_("Failed to hook game function #6")) : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
	m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);


	//Get Game Event Hook
	if ((c_location = p_eventHook.count(1).get(0).get<char>(0)))
	{
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EVENT_COUNT)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}

	//Init Natives
	CrossMapping::initNativeMap();

	bool WaitingGameLoadLogPrinted = false;
	while (*m_gameState != GameStatePlaying) {
		if (!WaitingGameLoadLogPrinted) {
			Cheat::LogFunctions::Message(xorstr_("Waiting until the game has finished loading"));
			WaitingGameLoadLogPrinted = true;
		}
		Sleep(200);
	}
	
	Cheat::LogFunctions::Message(xorstr_("Grand Theft Auto V Completed Loading"));


	if (!InitializeHooks()) { std::exit(EXIT_SUCCESS); }
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0)
	{
		return nullptr;
	}

	Hooking::NativeRegistrationNew * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration())
	{
		for (uint32_t i = 0; i < table->getNumEntries(); i++)
		{
			if (newHash == table->getHash(i))
			{
				return table->handlers[i];
			}
		}
	}
	return nullptr;
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];

	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}

	return handler;
}

eGameState Hooking::GetGameState()
{
	return *m_gameState;
}

uint64_t Hooking::getWorldPtr()
{
	return m_worldPtr;
}
void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}


void Hooking::defuseEvent(RockstarEvent e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = (char*)EventPtr[e];
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			*p = EventRestore[e];
	}
}

__int64** Hooking::getGlobalPtr()
{
	return m_globalPtr;
}


void Hooking::CreateConsole()
{
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
	HANDLE ConsoleOutput	= GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput		= _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE* COutputHandle		= _fdopen(SystemOutput, xorstr_("w"));
	HANDLE ConsoleError		= GetStdHandle(STD_ERROR_HANDLE);
	int SystemError			= _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE* CErrorHandle		= _fdopen(SystemError, xorstr_("w"));
	HANDLE ConsoleInput		= GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput			= _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE* CInputHandle		= _fdopen(SystemInput, xorstr_("r"));
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