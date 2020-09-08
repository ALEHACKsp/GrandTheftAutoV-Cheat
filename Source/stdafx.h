#pragma once

#pragma warning(disable : 4244)			//			'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 26812)		//			The enum type type-name is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(disable : 26495)		//			Variable '%variable%' is uninitialized. Always initialize a member variable.
#pragma warning(disable : 4091)	
#pragma warning(disable : 6262)


#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <atlstr.h>
#include <map>
#include <set>
#include <functional>
#include <winioctl.h>
#include <timeapi.h>
#include <time.h>
#include <conio.h>
#include <filesystem>
#include <fcntl.h>
#include <io.h>
#include <array>
#include <thread>
#pragma comment(lib, "Winmm.lib")

//XORSTR
#include "ThirdParty/XORSTR/xorstr.hpp"

//MinHook
#pragma comment(lib,"ThirdParty/MinHook/libMinHook-x64-v141-md.lib")
#include "ThirdParty/MinHook/MinHook.h"


//Project Header Files
#include "Memory.h"
#include "Types.h"
#include "Enums.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "NativeCaller.h"
#include "Natives.h"
#include "GameHooking.h"
#include "GUI.h"
#include "Types.h"
#include "GameFunctions.h"
#include "GameArrays.h"
#include "Offsets.h"




namespace Cheat 
{
	extern HMODULE CheatModuleHandle;
	void Main();
	namespace GUI 
	{
		namespace Drawing
		{
			void Text(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
			void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
			void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
			void InitTextureFile();
			void DrawScaleform(const float x, const float y, const float sx, const float sy, const int r, const int g, const int b);
		}

		extern void ControlsLoop();
		extern float guiX;
		extern float guiY;
		extern float guiWidth;
		extern std::vector <std::string> ThemeFilesVector;
		extern bool ShowHeaderBackground;
		extern bool ShowHeaderGUI;
		extern bool ShowHeaderGlare;
		extern bool CheatGUIHasBeenOpened;
		extern std::string CurrentTheme;
		extern bool GUIControlsDisabled;
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
		extern RGBA TopAndBottomLine;
		extern RGBA primary;
		extern RGBA secondary;
		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int GUINavigationKey;
		extern int SaveItemKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;
		extern void DeleteCurrentTheme();
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseGUI();
		void End();
		void EnableGUIControlsDisabled();
		void LoadThemeFilesLooped();
		void LoadTheme(std::string ThemeFileName, bool StartUp);
		void SaveTheme(std::string ThemeFileName);
	}
	namespace CheatFeatures
	{
		extern int BoolOptionVectorPosition;
		extern int SpeedometerVectorPosition;
		extern int selectedPlayer;
		extern int PlayerOpacityInt;
		extern bool HotkeyToggleBool;
		extern bool UseKMH;
		extern bool BlockMaliciousScriptEvents;
		extern bool BlockAllScriptEvents;
		extern bool ShowBlockedScriptEventNotifications;
		extern bool ShowPlayerTagsPlayerList;
		extern bool HideOwnIPAddress;
		extern bool ShowVehicleInfoAndPreview;
		extern bool CursorGUINavigationEnabled;
		extern bool ShowJoiningPlayersNotification;
		extern bool LogChatMessages;

		void NoneLooped();
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
		extern bool EntityInformationGunBool;
		void EntityInformationGun();
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
		extern std::string VehicleGun_VehicleNameString;
		void VehicleGun();
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
		extern bool CartoonGunBool;
		void CartoonGun();
	}
	namespace CheatFunctions 
	{
		std::string ReturnCheatBuildAsString();
		const std::string ReturnConfigFilePath();
		void LoadSettings();
		void RegisterOptionAsLoaded(std::string OptionName);
		bool IsOptionRegisteredAsLoaded(std::string OptionName);
		std::string ReturnCheatModuleDirectoryPath();
		void SaveOptionToConfig(std::string OptionName, std::string OptionValue);
		std::string GetOptionValueFromConfig(std::string OptionName);
		void ShowItemSavingDisabledMessage(std::string OptionName);
		bool IsSaveItemHotKeyPressed();
		char* CombineTwoChars(char* string1, char* string2);
		bool DoesFileExists(const std::string& fileName);
		bool DoesDirectoryExists(const std::string& dirName_in);
		void CreateNewDirectory(std::string Path);
		std::string GetLastErrorAsString();
		void CheatThreadLoopFunctions();
		bool IsGameWindowFocussed();
		bool StringIsInteger(const std::string& s);
		bool IsIntegerInRange(unsigned low, unsigned high, unsigned x);
		bool ExtractResource(const HINSTANCE hInstance, WORD resourceID, LPCSTR szFilename);
		std::string TextureFilePath();
		bool ReturnPressedKey(int &PressedKey);
		char* StringToChar(std::string string);
		std::string VirtualKeyCodeToString(UCHAR virtualKey);
		void CreateConsole();
		int ReturnNumberOfDigitsInValue(double Number);
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		std::string ReturnDateTimeFormatAsString(const char* DateTimeFormat);
		bool StringToBool(std::string String);
	}
	namespace GameFunctions 
	{
		void GiveAllWeaponsToPlayer(Ped Player);
		void RepairAndCleanVehicle();
		void SubtitleNotification(char* Message, int ShowDuration = 4000);
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
		void TeleportToCoords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight);
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
		char* DisplayKeyboardAndReturnInput(int MaxInput);
		int DisplayKeyboardAndReturnInputInteger(int MaxInput);
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
		void InstructionalKeysInit();
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
		void AdvancedMinimapNotification(char* Message, char* PicName1, char* PicName2, bool Flash, int IconType, char* Sender, char* Subject, float Duration, char* ClanTag);
		void AddBlipToVehicle(Vehicle Vehicle);
		bool DeleteVehicle(Vehicle Vehicle);
		float MSToKMH(float MS);
		float MSToMPH(float MS);
		float KMHToMS(float MS);
		float MPHToMS(float MS);
		void ChangeEntityInvincibilityState(Entity EntityHandle, bool Enable);
		char* ReturnOnlinePlayerPictureString(Player PlayerHandle);
		VECTOR2 ReturnCursorYXCoords();
		void CursorGUINavigationLoop();
		void EnableDisableCursorGUINavigation();
		bool IsCursorAtXYPosition(VECTOR2 const& boxCentre, VECTOR2 const& boxSize);
		void ChangePedModelLocalPlayer(Hash PedModel);
		bool PlayerIsFreemodeScriptHost(Player Player);
		void RGBFader(int& r, int& g, int& b, int FadeSpeed);
		void CopySelectedPlayerOutfit(Player SelectedPlayer);
		int ReturnPlayerRockstarID(Player PlayerHandle);
		std::string ReturnPlayerIPAddressAsString(Player PlayerHandle);
		bool IsCurrentGTAOCharacterChar0();
	}
	namespace LogFunctions 
	{
		void Message(char* Message);
		void MessageCustomCategory(std::string CategoryName, std::string Message);
		void Error(char* Message, bool ShowMessageBox);
		void DebugMessage(std::string Message);
	}
	namespace GameArrays 
	{
		extern const int RankPointsArray[8000];
		extern const std::vector<std::string> SummerSpecialModels;
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
		extern const std::vector<VehicleModelPicturesStruct> VehicleModelPictures;
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
	void Title(std::string title);
	void Speedometer(std::string text);
	void AddPlayerInfoBoxTextEntry(std::string text, int Row1 = NULL, int Row2 = NULL, int Row3 = NULL, int Row4 = NULL);
	bool Break(std::string option, bool TextCentered);
	bool Option(std::string option, std::string InformationText);
	bool VehicleOption(std::string option, std::string ModelName);
	bool MenuOption(std::string option, SubMenus newSub);
	bool MenuOptionPlayerList(std::string option, SubMenus newSub, Player PlayerHandle);
	bool Toggle(std::string option, bool& b00l, std::string InformationText, bool IsSavable = true);
	bool Int(std::string option, int& _int, int min, int max, int step, bool DisableControl = false, bool IsSavable = true, std::string InformationText = xorstr_("Select to change"));
	bool Float(std::string option, float& _float, float min, float max, float steps, bool ReturnTrueWithValueChange, bool IsSavable = true, std::string InformationText = "");
	bool IntVector(std::string option, std::vector<int> Vector, int& position, bool IsSavable = true);
	bool FloatVector(std::string option, std::vector<float> Vector, int& position, bool IsSavable = true);
	bool StringVector(std::string option, std::vector<std::string> Vector, int& position, std::string InformationText, bool IsSavable = true);
}

extern Player PlayerID;
extern Ped PlayerPedID;
extern bool VehicleSpawnerSpawnInsideVehicle;
extern bool VehicleSpawnerDeleteOldVehicle;
extern bool VehicleSpawnerSpawnWithBlip;
extern bool spawnvehiclewithgodmode;
extern bool spawnmaxupgraded;
extern bool ShowPlayerInformationPlayerList;