#pragma once

#pragma warning(disable : 4244)			//			'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 26812)		//			The enum type type-name is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(disable : 4996)			//			Your code uses a function, class member, variable, or typedef that's marked deprecated.
#pragma warning(disable : 26495)		//			Variable '%variable%' is uninitialized. Always initialize a member variable.
#pragma warning(disable : 4091)	
#pragma warning(disable: 6262)

#include <windows.h>
#include <Mmsystem.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <atlstr.h>
#include <iomanip>
#include <direct.h>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <thread>
#include <Psapi.h>
#include <winioctl.h>
#include <timeapi.h>
#include <time.h>
#include <conio.h>
#include <filesystem>
#include <fcntl.h>
#include <pathcch.h>
#include <io.h>
#include <tlhelp32.h>
#include <array>
#pragma comment(lib, "Winmm.lib")

// XORSTR
#include "ThirdParty\XORSTR\xorstr.hpp"
// MinHook
#pragma comment(lib,"ThirdParty/MinHook/libMinHook-x64-v141-md.lib")
#include "ThirdParty/MinHook/MinHook.h"

// Additional Header Files
#include "Memory.h"
#include "types.h"
#include "enums.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "nativeCaller.h"
#include "natives.h"
#include "Hooking.h"
#include "GUI.h"
#include "types.h"
#include "GameFunctions.h"



class globalHandle
{
private:
	void* _handle;

public:
	globalHandle(int index)
		: _handle(&Hooking::getGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: _handle(p)
	{ }

	globalHandle(const globalHandle& copy)
		: _handle(copy._handle)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<void**>(this->_handle) + (index));
	}

	globalHandle At(int index, int size)
	{
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As()
	{
		return *this->Get<T>();
	}
};



namespace Cheat {
	void ScriptMain();
	namespace Drawing {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
		void YTD();
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool ControllerInput;
		extern bool RestorePreviousSubmenu;
		extern int maxVisOptions;
		extern int currentOption;
		extern int currentOptionMenuBottom;
		extern int previousOption;
		extern int optionCount;
		extern int optionCountMenuBottom;
		extern int TotalOptionsCount;
		extern int PreviousSubMenu;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int PreviousMenuLevel;
		extern SubMenus PreviousMenu;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];
		extern float menuX;
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBA MainTitleRect;
		extern RGBA headerRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA MenuBackgroundRect;
		extern RGBA MenuBottomRect;
		extern RGBA scroller;
		extern RGBA line;
		extern RGBA primary;
		extern RGBA secondary;
		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;
	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseMenu();
	}
	namespace Checks {
		void Controls();
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}
	namespace CheatFeatures {
		extern int speedometer_vector_position;
		extern int selectedPlayer;
		extern int PlayerOpacityInt;
		extern bool HotkeyToggleBool;
		extern bool UseKMH;
		extern bool BlockScriptEvents;
		extern bool ShowBlockedScriptEventNotifications;
		extern bool ShowPlayerTagsPlayerList;
		extern bool AutoSaveSettings;

		void Looped();
		extern bool GodmodeBool;
		void Godmode(bool toggle);
		extern bool NeverWantedBool;
		void NeverWanted(bool toggle);
		extern bool NoWeaponReloadBool;
		void NoWeaponReload();
		extern bool SlowMotionBool;
		void SlowMotion(bool toggle);
		extern bool WorldBlackoutBool;
		void WorldBlackout(bool toggle);
		extern bool GravityGunBool;
		void GravityGun();
		extern bool HideHUDBool;
		void HideHUD();
		extern bool NoGravityBool;
		void NoGravity(bool toggle);
		extern bool WorldSnowLocalBool;
		void WorldSnowLocal(bool toggle);
		extern bool AutoTeleportToWaypointBool;
		void AutoTeleportToWaypoint();
		extern bool OneHitKillBool;
		void OneHitKill(bool toggle);
		extern bool PauseTimeBool;
		void PauseTime(bool toggle);
		extern bool ExplosiveMeleeBool;
		void ExplosiveMelee();
		extern bool OrbitalCannonCooldownBypassBool;
		void OrbitalCannonCooldownBypass();
		extern bool ProtectionVoteKickBool;
		void ProtectionVoteKick(bool toggle);
		extern bool ProtectionFreezeBool;
		void ProtectionFreeze(bool toggle);
		extern bool ProtectionWorldEventsBool;
		void ProtectionWorldEvents(bool toggle);
		extern bool ProtectionVehicleBool;
		void ProtectionVehicle(bool toggle);
		extern bool ProtectionAlterWantedLevelBool;
		void ProtectionAlterWantedLevel(bool toggle);
		extern bool ProtectionSessionTimeBool;
		void ProtectionSessionTime(bool toggle);
		extern bool ProtectionGiveRemoveWeaponsBool;
		void ProtectionGiveRemoveWeapons(bool toggle);
		extern bool ProtectionSessionWeatherBool;
		void ProtectionSessionWeather(bool toggle);
		extern bool SuperJumpBool;
		void SuperJump();
		extern bool PlayerForceFieldBool;
		void PlayerForceField();
		extern bool FastRunBool;
		void FastRun(bool toggle);
		extern bool ShowFPSBool;
		void ShowFPS();
		extern bool JumpAroundModeBool;
		void JumpAroundMode();
		extern bool VehicleHornBoostBool;
		void VehicleHornBoost();
		extern bool FakeWantedLevelBool;
		void FakeWantedLevel(bool toggle);
		extern bool VehicleGodmodeBool;
		void VehicleGodmode(bool toggle);
		extern bool VehicleInvisibleBool;
		void VehicleInvisible(bool toggle);
		extern bool PlayerInvisibleBool;
		void PlayerInvisible(bool toggle);
		extern bool MobileRadioBool;
		void MobileRadio(bool toggle);
		extern bool WeaponRapidFireBool;
		void WeaponRapidFire();
		extern bool PlayerIgnoredBool;
		void PlayerIgnored(bool toggle);
		extern bool NoClipBool;
		void NoClip();
		extern bool RainbowVehicleBool;
		void RainbowVehicle();
		extern bool TeleportGunBool;
		void TeleportGun();
		extern bool DeleteGunBool;
		void DeleteGun();
		extern bool UnlimitedSpecialAbilityBool;
		void UnlimitedSpecialAbility();
		extern bool SpectatePlayerBool;
		void SpectatePlayer(bool toggle);
		extern bool NoRagdollAndSeatbeltBool;
		void NoRagdollAndSeatbelt(bool toggle);
		extern bool FreezeSelectedPlayerBool;
		void FreezeSelectedPlayer();
		extern bool FreezeAllPlayersBool;
		void FreezeAllPlayers();
		extern bool TriggerBot_ShootNPCBool;
		extern bool TriggerBot_ShootPlayersBool;
		extern bool TriggerBotBool;
		void TriggerBot();
		extern bool SuperBrakesBool;
		void SuperBrakes();
		extern bool TinyPlayerBool;
		void TinyPlayer(bool toggle);
		extern bool UnlimitedRocketBoostBool;
		void UnlimitedRocketBoost();
		extern bool VehicleGunBool;
		extern char* VehicleGun_VehicleNameChar;
		void VehicleGun();
		extern bool PlayerNameESPBool;
		void PlayerNameESP();
		extern bool PlayerESPBool;
		void PlayerESP();
		extern bool OffRadarBool;
		void OffRadar();
		extern bool RevealPlayersBool;
		void RevealPlayers();
		extern bool ExplodeLoopSelectedPlayerBool;
		void ExplodeLoopSelectedPlayer();
		extern bool DriveOnWaterBool;
		void DriveOnWater();
		extern bool SuperManBool;
		void SuperMan();
		extern bool ShakeCamSelectedPlayerBool;
		void ShakeCamSelectedPlayer();
		extern bool RainbowGunBool;
		void RainbowGun();
		extern bool DisablePhoneBool;
		void DisablePhone();
		extern bool NoIdleKickBool;
		void NoIdleKick();
		extern bool BribeAuthoritiesBool;
		void BribeAuthorities();
		extern bool MoneyDropBool;
		extern int MoneyDropDelay;
		extern int MoneyDropDelayPreviousTick;
		void MoneyDrop();
		extern bool MoneyDropAllPlayersBool;
		void MoneyDropAllPlayers();
		extern bool MoneyGunBool;
		void MoneyGun();
		extern bool VehicleWeaponsBool;
		extern bool VehicleWeapons_TankRounds;
		extern bool VehicleWeapons_VehicleRockets;
		extern bool VehicleWeapons_Fireworks;
		extern bool VehicleWeapons_DrawLaser;
		void VehicleWeapons();
		extern bool AirstrikeGunBool;
		void AirstrikeGun();
		extern bool SuperRunBool;
		void SuperRun();
		extern bool CustomWeaponBulletsBool;
		extern bool CustomWeaponBullets_ValkyrieGun;
		extern bool CustomWeaponBullets_TankBullets;
		extern bool CustomWeaponBullets_RpgBullets;
		extern bool CustomWeaponBullets_FireworkBullets;
		void CustomWeaponBullets();
		extern bool ShowSessionInformationBool;
		void ShowSessionInformation();
		extern bool AutoGiveAllWeaponsBool;
		void AutoGiveAllWeapons();
		extern bool FreeCamBool;
		void FreeCam(bool toggle);
	}
	namespace CheatFunctions {
		std::string ReturnCheatBuildAsString();
		const std::string ReturnConfigFilePath();
		void LoadSettings(bool StartUp);
		std::string ReturnCheatModuleDirectoryPath();
		void SaveSettings();
		char* CombineTwoStrings(char* string1, char* string2);
		bool DoesFileExists(const std::string& fileName);
		bool DoesDirectoryExists(const std::string& dirName_in);
		void CreateNewDirectory(std::string Path);
		std::string ReturnDateAndTimeAsString();
		std::string GetLastErrorAsString();
		void CheatThreadLoopFunctions();
		bool IsGameWindowFocussed();
		bool StringIsInteger(const std::string& s);
		bool IsIntegerInRange(unsigned low, unsigned high, unsigned x);
		_int64 FileSize(const wchar_t* name);
		bool extractResource(const HINSTANCE hInstance, WORD resourceID, LPCSTR szFilename);
		std::string TextureFilePath();
		bool ReturnPressedKey(int &PressedKey);
		void PostInitCheat();
		char* StringToChar(std::string string);
		std::string VirtualKeyCodeToString(UCHAR virtualKey);
		void CreateConsole();
	}
	namespace GameFunctions {
		float GetGameFramesPerSecond();
		void DrawGameFramesPerSecond();
		void GiveAllWeaponsToPlayer(Ped Player);
		void RepairAndCleanVehicle();
		void notifyBottom(char* Message, int ShowDuration = 4000);
		void TeleportToObjective();
		void BurstSelectedPlayerTires(Ped selectedPed);
		void SetOffAlarmPlayerVehicle(Ped selectedPed);
		bool IsPlayerFriend(Player player);
		double DegreeToRadian(double n);
		Vector3 MultiplyVector(Vector3 vector, float inc);
		Vector3 AddVector(Vector3 vector, Vector3 vector2);
		Vector3 RotationToDirection(Vector3 rot);
		void SetRankRockstarGift(int RPValue);
		void DrawVehicleLasers();
		void RequestControl(Entity input);
		Vector3 RotToDirection(Vector3* rot);
		Vector3 AddTwoVectors(Vector3* vectorA, Vector3* vectorB);
		Vector3 MultiplyVector(Vector3* vector, float x);
		float GetDistanceBetweenTwoVectors(Vector3* pointA, Vector3* pointB);
		float GetVectorLength(Vector3* vector);
		Vector3 GetBlipMarker();
		void TeleportToCoords(Entity e, Vector3 coords);
		int ReturnRandomInteger(int start, int end);
		float GetDistanceBetweenTwoPoints(Vector3 A, Vector3 B);
		Vector3 GetEntityCoords(Entity entity);
		float DegreesToRadians(float degs);
		void GetCameraDirection(float* dirX, float* dirY, float* dirZ);
		void RequestControlOfEnt(Entity entity);
		void RequestControlOfId(Entity netid);
		bool RequestNetworkControl(uint vehID);
		Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle);
		Ped ClonePed(Ped ped);
		char* CharKeyboard(char* windowName, int maxInput, char* defaultText);
		void ClearAllAnimations();
		void LoadPlayerInformation(char* playerName, Player p);
		float Get3DDistance(Vector3 a, Vector3 b);
		void ApplyForceToEntity(Entity e, float x, float y, float z);
		void DrawMarkerAbovePlayer(int Type, Player player, RGBA Color);
		void SpawnVehicle(char* ModelHash);
		void NearbyPedsCommitSuicide();
		void TeleportToWaypoint();
		void SetPedTexture(Ped Ped, int ComponentID, int DrawableID, int TextureID);
		void MaxDowngradeVehicle(int VehicleHandle);
		void MaxUpgradeVehicle(int VehicleHandle);
		void EnableDisableAntiCrashCamera();
		void CheckNewSessionMembersLoop();
		bool IsEntityInInterior(Entity Entity);
		void InstructionsInit();
		void InstructionsAdd(char* text, int button);
		void InstructionsEnd();
		void SetSessionTime(int h, int m, int s);
		void ClearNearbyPedAnimations();
		void DoNearbyPedsAnimation(char* AnimationName, char* AnimationID);
		void DoLocalPedAnimation(char* AnimationName, char* AnimationID);
		void AttachObjectToPed(Ped Ped, char* ObjectName);
		void DetachObjectFromPed(Ped Ped, char* ObjectName);
		void TPto(Vector3 Coords);
		void MinimapNotification(char* Message);
	}
	namespace LogFunctions {
		void Init();
		void Message(char* Message);
		void Error(char* Message);
		void DebugMessage(char* Message);
	}
	namespace GameArrays {
		extern int RankPointsArray[8000];
		extern const std::vector<std::string> PedModels;
		extern const std::vector<std::string> BoatModels;
		extern const std::vector<std::string> SmugglersRunModels;
		extern const std::vector<std::string> CunningStuntsDLCModels;
		extern const std::vector<std::string> DiamondCasinoHeistDLCModels;
		extern const std::vector<std::string> CasinoDLCModels;
		extern const std::vector<std::string> ArenaWarModels;
		extern const std::vector<std::string> AfterHoursModels;
		extern const std::vector<std::string> GunrunningModels;
		extern const std::vector<std::string> DoomsdayModels;
		extern const std::vector<std::string> SSASSSModels;
		extern const std::vector<std::string> VanModels;
		extern const std::vector<std::string> UtilityModels;
		extern const std::vector<std::string> TrainModels;
		extern const std::vector<std::string> SUVModels;
		extern const std::vector<std::string> SuperModels;
		extern const std::vector<std::string> TrailerModels;
		extern const std::vector<std::string> SportClassicModels;
		extern const std::vector<std::string> SportModels;
		extern const std::vector<std::string> ServiceModels;
		extern const std::vector<std::string> SedanModels;
		extern const std::vector<std::string> PlaneModels;
		extern const std::vector<std::string> OffRoadModels;
		extern const std::vector<std::string> MuscleModels;
		extern const std::vector<std::string> MotorcycleModels;
		extern const std::vector<std::string> MilitaryModels;
		extern const std::vector<std::string> IndustrialModels;
		extern const std::vector<std::string> HelicopterModels;
		extern const std::vector<std::string> EmergencyModels;
		extern const std::vector<std::string> CycleModels;
		extern const std::vector<std::string> CoupesModels;
		extern const std::vector<std::string> CompactsModels;
		extern const std::vector<std::string> CommercialModels;
		static Hash WeaponsHashList[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263,
		0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9,
		0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, 0x1B06D571,
		0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054,
		0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8,
		0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF,
		0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318,
		0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0xBFEFFF6D, 0x394F415C,
		0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,
		0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2, 0xA914799,
		0xC734385A, 0x6A6C02E0, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5,
		0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0x93E220BD, 0xA0973D5E, 0x24B17070,
		0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,
		0x34A67B97, 0xFBAB5776, 0x060EC506, 0xBA536372
		};
	}
	void Title(const char* title);
	void Speedometer(char* text);
	void fps(char* text);
	void AddSmallTitle(char* text);
	void PlayerInfoBoxTitle(char* text);
	void PlayerInfoBoxText(char* text, short line);
	void AddSmallInfo(char* text, short line);
	void AddSmallTitle2(char* text);
	void AddSmallInfo2(char* text, short line);
	void AddSmallTitle3(char* text);
	void AddSmallInfo3(char* text, short line);
	bool Break(const char* option, bool TextCentered);
	bool Option(const char* option, const char* InformationText);
	bool Option(const char* option, const char* InformationText, std::function<void()> function);
	bool VehicleOption(const char* option, std::string ModelName);
	bool VehicleOption(const char* option, std::string ModelName, std::function<void()> function);
	bool MenuOption(const char* option, SubMenus newSub);
	bool MenuOption(const char* option, SubMenus newSub, std::function<void()> function);
	bool Toggle(const char* option, bool& b00l, const char* InformationText);
	bool ToggleCheckMark(const char* option, bool& b00l);
	bool Toggle(const char* option, bool& b00l, const char* InformationText, std::function<void()> function);
	bool IntNoControl(const char* option, int& _int, int min, int max, const char* InformationText);
	bool Int(const char* option, int& _int, int min, int max, int step, const char* InformationText);
	bool Int(const char* option, int& _int, int min, int max, int step, const char* InformationText, std::function<void()> function);
	bool Float(const char* option, float& _float, float min, float max, float steps, bool ReturnTrueWithValueChange, const char* InformationText);
	bool Float(const char* option, float& _float, float min, float max, float steps, bool ReturnTrueWithValueChange, const char* InformationText, std::function<void()> function);
	bool IntVector(const char* option, std::vector<int> Vector, int& position);
	bool IntVector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, const char* InformationText);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, const char* InformationText, std::function<void()> function);
	void End();
	void LoadThemeFilesLooped();
	void LoadTheme(char* ThemeFileName, bool StartUp);
	void SaveTheme(char* ThemeFileName);
}

extern Player PlayerID;
extern Ped PlayerPedID;
extern bool spawninvehicle;
extern bool spawner_deletecurrentvehicle;
extern bool spawnvehiclewithgodmode;
extern bool spawnmaxupgraded;
extern bool show_joining_players_notification;
extern bool ShowPlayerInformationPlayerList;
extern bool CheatGUIHasBeenOpened;
extern HMODULE CheatModuleHandle;