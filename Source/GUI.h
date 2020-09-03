#pragma once

enum SubMenus 
{
	NOMENU,
	MainMenu,
	SelfOptionsMenu,
	SettingsMenu,
	GUIColorsMenu,
	ThemeLoaderMenu,
	ThemeFilesMenu,
	GUITitleBackgroundColorMenu,
	settingsheaderbackground,
	settingssmalltitlebackground,
	settingsscroller,
	settingsmenubackground,
	settingsoptiontext,
	settingsbottomline,
	settingsmenubottombackground,
	PlayerListMenu,
	SelectedPlayerMenu,
	teleportmenu,
	weaponmenu,
	VehicleCustomizerColorMenu,
	miscmenu,
	worldmenu,
	vehiclemenu,
	scenarios,
	nearbyvehicles_menu, 
	nearbypeds_menu,
	iplloader,
	iplteleports,
	weathermenu,
	VehicleSpawnSettings,
	hotkeys,
	AllPlayersMenu,
	modelchanger,
	vehiclespawnermenu,
	Super,
	Sports,
	smugglersrun,
	SportClassic,
	Offroad,
	Sedans,
	Coupes,
	Muscle,
	Boats,
	Commercial,
	Compacts,
	Cycles,
	Emergency,
	Helicopters,
	Industrial,
	Military,
	Motorcycles,
	Planes,
	Service,
	SUV,
	Trailer,
	Trains,
	vehicle_lsc_neon_options,
	vehicle_lsc_color_options,
	Utility,
	Vans,
	SSASSSDLC, 
	doomsdayheistdlc,
	gunrunningdlc, 
	CunningStuntsDLCMenu,
	afterhoursdlc, 
	arenawardlc, 
	casinodlc,
	diamondcasinoheist,
	SummerSpecialDLCMenu,
	OnlineOptionsMenu,
	animations,
	timemenu,
	CommonTeleportLocations,
	attachoptions,
	SelectedPlayerTrollMenu,
	SelectedPlayerFriendlyMenu,
	protections,
	ESPMenu, 
	clothingmenu, 
	visionsmenu,
	outfitsmenu,
	componentschangermenu,
	playermoneymenu, 
	player_remoteoptions,
	sessionweathermenu,
	sessiontimemenu,
	vehicleweaponsmenu,
	allplayers_trolloptionsmenu,
	statsoptionsmenu, 
	vehicledooroptionsmenu,
	vehiclemultipliersmenus,
	custombulletsmenu, 
	vehiclegunmenu,
	aimbotsettingsmenu,
	rankmenu,
	miscstatsmenu, 
	player_teleportmenu,
	sessionoptionsmenu,
	hudmenu,
	guisettings, 
	menusettingsmenu,
	unlocksmenu,
	reportsmenu_stats, 
	allplayers_weaponoptionsmenu,
	headeroptionsmenu,
	VehicleCustomizerMenu,
	DLCVehiclesMenu,
	SUBMENUS_END //Used to get total size of SubMenus (SUBMENUS_END - 2) 
};
extern enum SubMenus;

typedef struct VECTOR2 
{
	float x, y;
};
typedef struct VECTOR2_2 
{
	float w, h;
};
typedef struct RGBAF 
{
	int r, g, b, a, f;
};
typedef struct RGBA 
{
	int r, g, b, a;
};
typedef struct RGB 
{
	int r, g, b;
};