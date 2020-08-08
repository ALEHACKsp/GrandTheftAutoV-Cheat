#include "stdafx.h"

static fpFileRegister file_register = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(file_register)>());

void Cheat::Drawing::YTD()
{
	Cheat::LogFunctions::Message(xorstr_("Loading GUI"));
	int textureID;
	if (Cheat::CheatFunctions::DoesFileExists(Cheat::CheatFunctions::TextureFilePath())) { file_register(&textureID, Cheat::CheatFunctions::TextureFilePath().c_str(), true, xorstr_("Textures.ytd"), false); }
	else { Cheat::GameFunctions::MinimapNotification(xorstr_("~r~Failed to load GUI")); }
}


void Cheat::Drawing::Text(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

void Cheat::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}

void Cheat::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

void Cheat::Drawing::DrawScaleform(const float x, const float y, const float sx, const float sy, const int r, const int g, const int b)
{
	int ScaleFormHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(xorstr_("MP_MENU_GLARE"));
	GRAPHICS::DRAW_SCALEFORM_MOVIE(ScaleFormHandle, x, y, sx, sy, r, g, b, 255, 0);
}


float Cheat::Settings::menuX = 0.11f;
const char* OptionInformationText;
bool ShowVehiclePreviews = true;
bool Cheat::Settings::selectPressed = false;
bool Cheat::Settings::leftPressed = false;
bool Cheat::Settings::rightPressed = false;
bool show_header_background = true;
bool shop_box_bool_option = true;
bool medal_bool_option = false;
bool show_header_gui = true;
bool ShowHeaderGlare = true;
bool CheatGUIHasBeenOpened = false;
char* CurrentTheme;
int Cheat::Settings::maxVisOptions = 10;
int Cheat::Settings::currentOption = 0;
int Cheat::Settings::currentOptionMenuBottom = 0;
int Cheat::Settings::previousOption = 0;
int Cheat::Settings::optionCount = 0;
int Cheat::Settings::optionCountMenuBottom = 0;
int Cheat::Settings::TotalOptionsCount = 0; // unlike OptionCount this will always contain total and can be called in the option functions
SubMenus Cheat::Settings::currentMenu;
int Cheat::Settings::menuLevel = 0;
SubMenus Cheat::Settings::PreviousMenu = NOMENU;
int Cheat::Settings::PreviousMenuLevel;
int Cheat::Settings::optionsArray[1000];
SubMenus Cheat::Settings::menusArray[1000];

RGBAF Cheat::Settings::count				{ 255, 255, 255, 255, 0 };
RGBAF Cheat::Settings::titleText			{ 255, 255, 255, 255, 0 };
RGBA Cheat::Settings::titleRect				{ 0, 0, 255, 255 };
RGBA Cheat::Settings::MainTitleRect			{ 0, 0, 0, 255 };
RGBA Cheat::Settings::headerRect			{ 0, 0, 255, 200 };
RGBAF Cheat::Settings::optionText			{ 255, 255, 255, 255, 0 };
RGBAF Cheat::Settings::breakText			{ 255, 255, 255, 255, 0 };
RGBAF Cheat::Settings::arrow				{ 255, 255, 255, 255, 3 };                          
RGBA Cheat::Settings::optionRect			{ 0, 0, 0, 255 }; 
RGBA Cheat::Settings::MenuBackgroundRect	{ 0, 0, 0, 220 }; 
RGBA Cheat::Settings::MenuBottomRect		{ 0, 0, 0, 255 };
RGBA Cheat::Settings::scroller				{ 0, 0, 255, 255 };
RGBAF Cheat::Settings::integre				{ 255, 255, 255, 255, 2 };
RGBA Cheat::Settings::line					{ 0, 0, 255, 255 };


void Cheat::Title(const char * title)
{
	Drawing::Text(title, { Settings::titleText }, { Settings::menuX, 0.130f }, { 0.50f, 0.35f }, true);
	if (show_header_background) { Drawing::Rect(Settings::headerRect, { Settings::menuX, 0.092f }, { 0.21f, 0.083f });  } // Header Rect
	if (ShowHeaderGlare) { Drawing::DrawScaleform(Settings::menuX + .330f, 0.457f, 1.0f, 0.900f, 255, 255, 255); } // Header Glare
	if (show_header_gui) { Cheat::Drawing::Spriter(xorstr_("Textures"), xorstr_("HeaderDefaultTransparent"), Cheat::Settings::menuX, 0.092f, 0.21f, 0.083f, 0, 255, 255, 255, 255); }
	Drawing::Rect(Settings::MainTitleRect, { Settings::menuX, 0.146f }, { 0.21f, 0.026f }); // Title Rect
	Drawing::Rect(Settings::line, { Settings::menuX, 0.158f }, { 0.21f, 0.002f });

	CheatGUIHasBeenOpened = true;
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);

	//Control Buttons
	std::string CloseGUIString = xorstr_("Press ") + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::Settings::openKey) + xorstr_(" to close GUI");
	Cheat::GameFunctions::InstructionsInit();
	Cheat::GameFunctions::InstructionsAdd((char*)CloseGUIString.c_str(), 80);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Back"), 136);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Up/Down"), 10);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Change Value"), 46);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Select"), 141);
	Cheat::GameFunctions::InstructionsEnd();
}


bool Cheat::Option(const char * option, const char* InformationText)
{
	Settings::optionCount++;
	Settings::optionCountMenuBottom++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	int OptionCountDifference = Settings::optionCount - Settings::optionCountMenuBottom;
	if (onThis) { Settings::currentOptionMenuBottom = Settings::optionCount - OptionCountDifference; }
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount)*0.035f + 0.125f }, { 0.35f, 0.35f }, false);
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.125f }, { 0.35f, 0.35f }, false);
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		OptionInformationText = InformationText;
		Settings::previousOption = Settings::currentOption;
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
char* VehiclePreviewDictName;
char* VehiclePreviewName;
bool Cheat::VehicleOption(const char* option, std::string ModelName)
{
	Settings::optionCount++;
	Settings::optionCountMenuBottom++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	int OptionCountDifference = Settings::optionCount - Settings::optionCountMenuBottom;
	if (onThis) { Settings::currentOptionMenuBottom = Settings::optionCount - OptionCountDifference; }
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.35f, 0.35f }, false);
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, false); // 0.45 0.45
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		VehiclePreviewDictName = "Textures";
		VehiclePreviewName = "NoVehiclePreviewAvailable";

		if (ModelName == "gp1")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "gp1";
		}
		if (ModelName == "turismo2")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "turismo2";
		}
		 if (ModelName == "ruston")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "ruston";
		}
		 if (ModelName == "infernus2")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "ALPHAZ1")
		{
			VehiclePreviewDictName = "elt_dlc_smuggler";
			VehiclePreviewName = "alphaz1";
		}
		 if (ModelName == "BOMBUSHKA")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "bombushka";
		}
		 if (ModelName == "CYCLONE")
		{
			VehiclePreviewDictName = "lgm_dlc_smuggler";
			VehiclePreviewName = "cyclone";
		}
		 if (ModelName == "HAVOK")
		{
			VehiclePreviewDictName = "elt_dlc_smuggler";
			VehiclePreviewName = "havok";
		}
		 if (ModelName == "HOWARD")
		{
			VehiclePreviewDictName = "elt_dlc_smuggler";
			VehiclePreviewName = "howard";
		}
		 if (ModelName == "HUNTER")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "hunter";
		}
		 if (ModelName == "MICROLIGHT")
		{
			VehiclePreviewDictName = "elt_dlc_smuggler";
			VehiclePreviewName = "microlight";
		}
		 if (ModelName == "MOGUL")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "mogul";
		}
		 if (ModelName == "MOLOTOK")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "molotok";
		}
		 if (ModelName == "NOKOTA")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "nokota";
		}
		if (ModelName == "PYRO")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "pyro";
		}
		if (ModelName == "RAPIDGT3")
		{
			VehiclePreviewDictName = "lgm_dlc_smuggler";
			VehiclePreviewName = "rapidgt3";
		}
		if (ModelName == "RETINUE")
		{
			VehiclePreviewDictName = "sssa_dlc_smuggler";
			VehiclePreviewName = "retinue";
		}
		if (ModelName == "ROGUE")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "rogue";
		}
		if (ModelName == "SEABREEZE")
		{
			VehiclePreviewDictName = "elt_dlc_smuggler";
			VehiclePreviewName = "seabreeze";
		}
		if (ModelName == "STARLING")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "starling";
		}
		if (ModelName == "TULA")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "tula";
		}
		if (ModelName == "VIGILANTE")
		{
			VehiclePreviewDictName = "candc_smuggler";
			VehiclePreviewName = "vigilante";
		}
		 if (ModelName == "VISIONE")
		{
		VehiclePreviewDictName = "lgm_dlc_smuggler";
		VehiclePreviewName = "visione";
		}
		 if (ModelName == "ASBO")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "asbo";
		}
		 if (ModelName == "EVERON")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "everon";
		}
		 if (ModelName == "FORMULA")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "formula";
		}
		 if (ModelName == "formula2")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "formula2";
		}
		 if (ModelName == "furia")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "furia";
		}
		 if (ModelName == "imorgon")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "imorgon";
		}
		 if (ModelName == "jb7002")
		{
		VehiclePreviewDictName = "candc_casinoheist";
		VehiclePreviewName = "jb7002";
		}
		 if (ModelName == "kanjo")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "kanjo";
		}
		 if (ModelName == "komoda")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "komoda";
		}
		 if (ModelName == "minitank")
		{
		VehiclePreviewDictName = "candc_casinoheist";
		VehiclePreviewName = "minitank";
		}
		 if (ModelName == "outlaw")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "outlaw";
		}
		 if (ModelName == "rebla")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "rebla";
		}
		 if (ModelName == "retinue2")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "retinue2";
		}
		 if (ModelName == "stryder")
		{
		VehiclePreviewDictName = "lgm_dlc_casinoheist";
		VehiclePreviewName = "stryder";
		}
		 if (ModelName == "sugoi")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "sugoi";
		}
		if (ModelName == "sultan2")
		{
			VehiclePreviewDictName = "sssa_dlc_casinoheist";
			VehiclePreviewName = "sultan2";
		}
		if (ModelName == "vagrant")
		{
			VehiclePreviewDictName = "sssa_dlc_casinoheist";
			VehiclePreviewName = "vagrant";
		}
		if (ModelName == "vstr")
		{
			VehiclePreviewDictName = "lgm_dlc_casinoheist";
			VehiclePreviewName = "vstr";
		}
		if (ModelName == "yousemite2")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "infernus2";
		}
		if (ModelName == "zhaba")
		{
			VehiclePreviewDictName = "candc_casinoheist";
			VehiclePreviewName = "zhaba";
		}
		if (ModelName == "caracara2")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "caracara2";
		}
		if (ModelName == "drafter")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "drafter";
		}
		if (ModelName == "dynasty")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "dynasty";
		}
		if (ModelName == "emerus")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "emerus";
		}
		if (ModelName == "hellion")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "hellion";
		}
		if (ModelName == "issi7")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "issi7";
		}
		 if (ModelName == "jugular")
		{
		VehiclePreviewDictName = "lgm_dlc_vinewood";
		VehiclePreviewName = "jugular";
		}
		 if (ModelName == "krieger")
		{
		VehiclePreviewDictName = "lgm_dlc_vinewood";
		VehiclePreviewName = "krieger";
		}
		 if (ModelName == "locust")
		{
		VehiclePreviewDictName = "lgm_dlc_vinewood";
		VehiclePreviewName = "locust";
		}
		 if (ModelName == "nebula")
		{
		VehiclePreviewDictName = "sssa_dlc_vinewood";
		VehiclePreviewName = "nebula";
		}
		 if (ModelName == "neo")
		{
		VehiclePreviewDictName = "lgm_dlc_vinewood";
		VehiclePreviewName = "neo";
		}
		 if (ModelName == "novak")
		{
		VehiclePreviewDictName = "lgm_dlc_vinewood";
		VehiclePreviewName = "novak";
		}
		if (ModelName == "paragon")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "paragon";
		}
		if (ModelName == "paragon2")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "paragon";
		}
		if (ModelName == "peyote2")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "peyote2";
		}
		if (ModelName == "rrocket")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "rrocket";
		}
		if (ModelName == "s80")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "s80";
		}
		if (ModelName == "thrax")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "thrax";
		}
		if (ModelName == "zion3")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "zion3";
		}
		if (ModelName == "zorrusso")
		{
			VehiclePreviewDictName = "lgm_dlc_vinewood";
			VehiclePreviewName = "zorrusso";
		}
		if (ModelName == "BRUISER")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "bruiser_c_1";
		}
		if (ModelName == "BRUISER2")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "bruiser_c_2";
		}
		if (ModelName == "BRUISER3")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "bruiser_c_3";
		}
		if (ModelName == "BRUTUS")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "brutus1";
		}
		 if (ModelName == "BRUTUS2")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "brutus2";
		}
		 if (ModelName == "BRUTUS3")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "brutus3";
		}
		 if (ModelName == "CERBERUS")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "cerberus1";
		}
		 if (ModelName == "CERBERUS2")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "cerberus2";
		}
		 if (ModelName == "CERBERUS3")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "cerberus3";
		}
		 if (ModelName == "CLIQUE")
		{
		VehiclePreviewDictName = "lgm_dlc_arena";
		VehiclePreviewName = "clique";
		}
		 if (ModelName == "DEATHBIKE")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "deathbike_c_1";
		}
		 if (ModelName == "DEATHBIKE2")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "deathbike_c_2";
		}
		 if (ModelName == "DEATHBIKE3")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "deathbike_c_3";
		}
		 if (ModelName == "DEVESTE")
		{
		VehiclePreviewDictName = "lgm_dlc_arena";
		VehiclePreviewName = "deveste";
		}
		 if (ModelName == "DEVIANT")
		{
		VehiclePreviewDictName = "lgm_dlc_arena";
		VehiclePreviewName = "deviant";
		}
		 if (ModelName == "DOMINATOR4")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "dominato_c_1";
		}
		 if (ModelName == "DOMINATOR5")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "dominato_c_2";
		}
		if (ModelName == "DOMINATOR6")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "dominato_c_3";
		}
		if (ModelName == "IMPALER")
		{
			VehiclePreviewDictName = "sssa_dlc_vinewood";
			VehiclePreviewName = "impaler";
		}
		if (ModelName == "IMPALER2")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "impaler_c_2";
		}
		if (ModelName == "IMPALER3")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "impaler_c_2";
		}
		if (ModelName == "IMPALER4")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "impaler_c_3";
		}
		if (ModelName == "IMPERATOR")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "imperator1_c";
		}
		if (ModelName == "IMPERATOR2")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "imperator2_c";
		}
		if (ModelName == "IMPERATOR3")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "imperator3_c";
		}
		if (ModelName == "ISSI4")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "issi3_c_1";
		}
		if (ModelName == "ISSI5")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "issi3_c_2";
		}
		if (ModelName == "ISSI6")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "issi3_c_3";
		}
		if (ModelName == "ITALIGTO")
		{
			VehiclePreviewDictName = "lgm_dlc_arena";
			VehiclePreviewName = "italigto";
		}
		if (ModelName == "MONSTER3")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "monster_c_1";
		}
		 if (ModelName == "MONSTER4")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "monster_c_2";
		}
		 if (ModelName == "MONSTER5")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "monster_c_3";
		}
		 if (ModelName == "RCBANDITO")
		{
		VehiclePreviewDictName = "sssa_dlc_arena";
		VehiclePreviewName = "rcbandito";
		}
		 if (ModelName == "SCARAB2")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "scarab2_c";
		}
		 if (ModelName == "SCARAB3")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "scarab3_c";
		}
		 if (ModelName == "SCHLAGEN")
		{
		VehiclePreviewDictName = "lgm_dlc_arena";
		VehiclePreviewName = "schlagen";
		}
		 if (ModelName == "SLAMVAN4")
		{
			VehiclePreviewDictName = "mba_vehicles";
			VehiclePreviewName = "slamvan_c_1";
		}
		 if (ModelName == "SLAMVAN5")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "slamvan_c_2";
		}
		 if (ModelName == "SLAMVAN6")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "slamvan_c_3";
		}
		 if (ModelName == "TOROS")
		{
		VehiclePreviewDictName = "lgm_dlc_arena";
		VehiclePreviewName = "toros";
		}
		 if (ModelName == "TULIP")
		{
		VehiclePreviewDictName = "sssa_dlc_arena";
		VehiclePreviewName = "tulip";
		}
		 if (ModelName == "VAMOS")
		{
		VehiclePreviewDictName = "sssa_dlc_arena";
		VehiclePreviewName = "vamos";
		}
		 if (ModelName == "ZR380")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "zr3801_c";
		}
		 if (ModelName == "ZR3802")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "zr3802_c";
		}
		 if (ModelName == "ZR3803")
		{
		VehiclePreviewDictName = "mba_vehicles";
		VehiclePreviewName = "zr3803_c";
		}
		 if (ModelName == "BLIMP3")
		{
		VehiclePreviewDictName = "elt_dlc_battle";
		VehiclePreviewName = "blimp3";
		}
		 if (ModelName == "MENACER")
		{
		VehiclePreviewDictName = "candc_battle";
		VehiclePreviewName = "menacer";
		}
		 if (ModelName == "MULE4")
		{
			VehiclePreviewDictName = "candc_battle";
			VehiclePreviewName = "mule4";
		}
		 if (ModelName == "PATRIOT2")
		{
			VehiclePreviewDictName = "sssa_dlc_battle";
			VehiclePreviewName = "patriot2";
		}
		 if (ModelName == "POUNDER2")
		{
			VehiclePreviewDictName = "candc_battle";
			VehiclePreviewName = "pounder2";
		}
		 if (ModelName == "STRIKEFORCE")
		{
			VehiclePreviewDictName = "candc_battle";
			VehiclePreviewName = "strikeforce";
		}
		 if (ModelName == "SCRAMJET")
		{
		VehiclePreviewDictName = "candc_battle";
		VehiclePreviewName = "scramjet";
		}
		 if (ModelName == "STAFFORD")
		{
		VehiclePreviewDictName = "lgm_dlc_battle";
		VehiclePreviewName = "stafford";
		}
		 if (ModelName == "SWINGER")
		{
		VehiclePreviewDictName = "lgm_dlc_battle";
		VehiclePreviewName = "swinger";
		}
		 if (ModelName == "TERBYTE")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "oppressor2")
		{
		VehiclePreviewDictName = "candc_battle";
		VehiclePreviewName = "oppressor2";
		}
		 if (ModelName == "scramjet")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "jester3")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "hauler2")
		{
		VehiclePreviewDictName = "candc_truck";
		VehiclePreviewName = "cab_1";
		}
		 if (ModelName == "phantom3")
		{
		VehiclePreviewDictName = "candc_truck";
		VehiclePreviewName = "cab_0";
		}
		 if (ModelName == "APC")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "apc";
		}
		 if (ModelName == "Halftrack")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "halftrack";
		}
		 if (ModelName == "Trailersmall2")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "trsmall2";
		}
		 if (ModelName == "oppressor")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "oppressor";
		}
		 if (ModelName == "tampa3")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "tampa3";
		}
		 if (ModelName == "dune3")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "dune3";
		}
		 if (ModelName == "nightshark")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "nightshark";
		}
		 if (ModelName == "ardent")
		{
		VehiclePreviewDictName = "candc_gunrunning";
		VehiclePreviewName = "ardent";
		}
		 if (ModelName == "cheetah2")
		{
		VehiclePreviewDictName = "lgm_dlc_gunrunning";
		VehiclePreviewName = "cheetah2";
		}
		 if (ModelName == "torero")
		{
		VehiclePreviewDictName = "lgm_dlc_gunrunning";
		VehiclePreviewName = "torero";
		}
		 if (ModelName == "vagner")
		{
		VehiclePreviewDictName = "lgm_dlc_gunrunning";
		VehiclePreviewName = "vagner";
		}
		 if (ModelName == "XA21")
		{
		VehiclePreviewDictName = "lgm_dlc_gunrunning";
		VehiclePreviewName = "xa21";
		}
		 if (ModelName == "caddy3")
		{
		VehiclePreviewDictName = "foreclosures_bunker";
		VehiclePreviewName = "transportation_2";
		}
		 if (ModelName == "autarch")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "autarch";
		}
		 if (ModelName == "barrage")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "barrage";
		}
		 if (ModelName == "chernobog")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "chernobog";
		}
		 if (ModelName == "comet4")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "comet4";
		}
		 if (ModelName == "comet5")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "comet5";
		}
		 if (ModelName == "deluxo")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "deluxo";
		}
		 if (ModelName == "gt500")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "gt500";
		}
		 if (ModelName == "hermes")
		{
		VehiclePreviewDictName = "sssa_dlc_xmas2017";
		VehiclePreviewName = "hermes";
		}
		 if (ModelName == "hustler")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "hustler";
		}
		 if (ModelName == "kamacho")
		{
		VehiclePreviewDictName = "sssa_dlc_xmas2017";
		VehiclePreviewName = "kamacho";
		}
		 if (ModelName == "khanjali")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "khanjali";
		}
		 if (ModelName == "neon")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "neon";
		}
		 if (ModelName == "pariah")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "pariah";
		}
		 if (ModelName == "raiden")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "raiden";
		}
		 if (ModelName == "revolter")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "revolter";
		}
		 if (ModelName == "riata")
		{
		VehiclePreviewDictName = "sssa_dlc_xmas2017";
		VehiclePreviewName = "riata";
		}
		 if (ModelName == "riot2")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "riot2";
		}
		 if (ModelName == "savestra")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "savestra";
		}
		 if (ModelName == "sc1")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "sc1";
		}
		 if (ModelName == "sentinel3")
		{
		VehiclePreviewDictName = "sssa_dlc_xmas2017";
		VehiclePreviewName = "sentinel3";
		}
		 if (ModelName == "streiter")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "streiter";
		}
		 if (ModelName == "stromberg")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "stromberg";
		}
		 if (ModelName == "thruster")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "thruster";
		}
		 if (ModelName == "viseris")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "viseris";
		}
		 if (ModelName == "volatol")
		{
		VehiclePreviewDictName = "candc_xmas2017";
		VehiclePreviewName = "volatol";
		}
		 if (ModelName == "yosemite2")
		{
		VehiclePreviewDictName = "sssa_dlc_casinoheist";
		VehiclePreviewName = "yosemite2";
		}
		 if (ModelName == "z190")
		{
		VehiclePreviewDictName = "lgm_dlc_xmas2017";
		VehiclePreviewName = "z190";
		}
		 if (ModelName == "caracara")
		{
		VehiclePreviewDictName = "candc_assault";
		VehiclePreviewName = "caracara";
		}
		 if (ModelName == "cheburek")
		{
		VehiclePreviewDictName = "sssa_dlc_assault";
		VehiclePreviewName = "cheburek";
		}
		 if (ModelName == "dominator3")
		{
		VehiclePreviewDictName = "sssa_dlc_assault";
		VehiclePreviewName = "dominator3";
		}
		 if (ModelName == "ellie")
		{
		VehiclePreviewDictName = "sssa_dlc_assault";
		VehiclePreviewName = "ellie";
		}
		 if (ModelName == "entity2")
		{
		VehiclePreviewDictName = "lgm_dlc_assault";
		VehiclePreviewName = "entity2";
		}
		 if (ModelName == "fagaloa")
		{
		VehiclePreviewDictName = "sssa_dlc_assault";
		VehiclePreviewName = "fagaloa";
		}
		if (ModelName == "flashgt")
		{
			VehiclePreviewDictName = "lgm_dlc_assault";
			VehiclePreviewName = "flashgt";
		}
		if (ModelName == "gb200")
		{
			VehiclePreviewDictName = "lgm_dlc_assault";
			VehiclePreviewName = "gb200";
		}
		if (ModelName == "hotring")
		{
			VehiclePreviewDictName = "sssa_dlc_assault";
			VehiclePreviewName = "hotring";
		}
		if (ModelName == "issi3")
		{
			VehiclePreviewDictName = "sssa_dlc_assault";
			VehiclePreviewName = "issi3";
		}
		 if (ModelName == "jester3")
		{
		VehiclePreviewDictName = "lgm_dlc_assault";
		VehiclePreviewName = "jester3";
		}
		 if (ModelName == "michelli")
		{
		VehiclePreviewDictName = "sssa_dlc_assault";
		VehiclePreviewName = "michelli";
		}
		 if (ModelName == "seasparrow")
		{
		VehiclePreviewDictName = "elt_dlc_assault";
		VehiclePreviewName = "sparrow";
		}
		 if (ModelName == "tezeract")
		{
		VehiclePreviewDictName = "lgm_dlc_assault";
		VehiclePreviewName = "tezeract";
		}
		 if (ModelName == "taipan")
		{
		VehiclePreviewDictName = "lgm_dlc_assault";
		VehiclePreviewName = "taipan";
		}
		 if (ModelName == "tyrant")
		{
		VehiclePreviewDictName = "lgm_dlc_assault";
		VehiclePreviewName = "tyrant";
		}
		 if (ModelName == "BISON")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "bison";
		}
		 if (ModelName == "BOBCATXL")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "bobcatx1";
		}
		if (ModelName == "BOXVILLE")
		{
			VehiclePreviewDictName = "candc_casinoheist";
			VehiclePreviewName = "boxville";
		}
		if (ModelName == "BOXVILLE4")
		{
			VehiclePreviewDictName = "candc_default";
			VehiclePreviewName = "boxville4";
		}
		if (ModelName == "BURRITO")
		{
			VehiclePreviewDictName = "sssa_dlc_heist";
			VehiclePreviewName = "gburrito2";
		}
		if (ModelName == "BURRITO2")
		{
			VehiclePreviewDictName = "candc_casinoheist";
			VehiclePreviewName = "burrito2";
		}
		 if (ModelName == "GBURRITO")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "gburrito2";
		}
		 if (ModelName == "MINIVAN")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "minivan";
		}
		 if (ModelName == "MINIVAN2")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "minivan2";
		}
		 if (ModelName == "PARADISE")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "paradise";
		}
		 if (ModelName == "RUMPO")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "rumpo";
		}
		 if (ModelName == "RUMPO3")
		{
		VehiclePreviewDictName = "sssa_dlc_executive_1";
		VehiclePreviewName = "rumpo3";
		}
		 if (ModelName == "SURFER")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "surfer";
		}
		 if (ModelName == "YOUGA")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "youga";
		}
		 if (ModelName == "YOUGA2")
		{
		VehiclePreviewDictName = "sssa_dlc_biker";
		VehiclePreviewName = "youga2";
		}
		 if (ModelName == "FORKLIFT")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "SADLER")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "sadler";
		}
		 if (ModelName == "BALLER2")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "baller2";
		}
		 if (ModelName == "BALLER3")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "baller3";
		}
		 if (ModelName == "BALLER4")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "baller4";
		}
		 if (ModelName == "BALLER6")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "BJXL")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "bjxl";
		}
		 if (ModelName == "CAVALCADE")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "cavcade2";
		}
		 if (ModelName == "CAVALCADE2")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "cavcade2";
		}
		 if (ModelName == "CONTENDER")
		{
		VehiclePreviewDictName = "sssa_dlc_stunt";
		VehiclePreviewName = "contender";
		}
		 if (ModelName == "FQ2")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "fq2";
		}
		else if (ModelName == "GRANGER")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "granger";
		}
		 if (ModelName == "GRESLEY")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "gresley";
		}
		 if (ModelName == "HABANERO")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "habanero";
		}
		 if (ModelName == "HUNTLEY")
		{
		VehiclePreviewDictName = "lgm_dlc_business2";
		VehiclePreviewName = "huntley";
		}
		 if (ModelName == "LANDSTALKER")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "landstalker";
		}
		 if (ModelName == "MESA")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "mesa";
		}
		 if (ModelName == "MESA2")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "mesa";
		}
		 if (ModelName == "PATRIOT")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "patriot";
		}
		 if (ModelName == "RADI")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "radi";
		}
		 if (ModelName == "ROCOTO")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "rocoto";
		}
		 if (ModelName == "SERRANO")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "serrano";
		}
		 if (ModelName == "XLS")
		{
		VehiclePreviewDictName = "lgm_dlc_executive1";
		VehiclePreviewName = "xls";
		}
		 if (ModelName == "XLS2")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "ADDER")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "adder";
		}
		 if (ModelName == "BANSHEE2")
		{
		VehiclePreviewDictName = "lsc_jan2016";
		VehiclePreviewName = "banshee2";
		}
		 if (ModelName == "BULLET")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "bullet";
		}
		 if (ModelName == "CHEETAH")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "cheetah";
		}
		 if (ModelName == "ENTITYXF")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "entityxf";
		}
		 if (ModelName == "FMJ")
		{
		VehiclePreviewDictName = "lgm_dlc_executive1";
		VehiclePreviewName = "fmj";
		}
		 if (ModelName == "SHEAVA")
		{
		VehiclePreviewDictName = "lgm_dlc_stunt";
		VehiclePreviewName = "sheava";
		}
		 if (ModelName == "INFERNUS")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "infernus";
		}
		 if (ModelName == "NERO")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "nero2";
		}
		 if (ModelName == "NERO2")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "nero2";
		}
		 if (ModelName == "OSIRIS")
		{
		VehiclePreviewDictName = "lgm_dlc_luxe";
		VehiclePreviewName = "osiris";
		}
		 if (ModelName == "LE7B")
		{
		VehiclePreviewDictName = "lgm_dlc_stunt";
		VehiclePreviewName = "le7b";
		}
		 if (ModelName == "ITALIGTB")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "italigtb2";
		}
		if (ModelName == "ITALIGTB2")
		{
			VehiclePreviewDictName = "lsc_dlc_import_export";
			VehiclePreviewName = "italigtb2";
		}
		if (ModelName == "PFISTER811")
		{
			VehiclePreviewDictName = "lgm_dlc_executive1";
			VehiclePreviewName = "pfister811";
		}
		if (ModelName == "PROTOTIPO")
		{
			VehiclePreviewDictName = "lgm_dlc_executive1";
			VehiclePreviewName = "prototipo";
		}
		if (ModelName == "REAPER")
		{
			VehiclePreviewDictName = "lgm_dlc_executive1";
			VehiclePreviewName = "reaper";
		}
		if (ModelName == "T20")
		{
			VehiclePreviewDictName = "lgm_dlc_luxe";
			VehiclePreviewName = "t20";
		}
		if (ModelName == "TEMPESTA")
		{
			VehiclePreviewDictName = "lgm_dlc_importexport";
			VehiclePreviewName = "tempesta";
		}
		if (ModelName == "TURISMOR")
		{
			VehiclePreviewDictName = "lgm_dlc_business";
			VehiclePreviewName = "turismor";
		}
		if (ModelName == "TYRUS")
		{
			VehiclePreviewDictName = "lgm_dlc_stunt";
			VehiclePreviewName = "tyrus";
		}
		if (ModelName == "VACCA")
		{
			VehiclePreviewDictName = "lgm_default";
			VehiclePreviewName = "vacca";
		}
		if (ModelName == "VOLTIC")
		{
			VehiclePreviewDictName = "lgm_default";
			VehiclePreviewName = "voltic_tless";
		}
		if (ModelName == "ZENTORNO")
		{
			VehiclePreviewDictName = "lgm_dlc_business2";
			VehiclePreviewName = "zentorno";
		}
		if (ModelName == "VOLTIC2")
		{
			VehiclePreviewDictName = "candc_importexport";
			VehiclePreviewName = "voltic2";
		}
		if (ModelName == "PENETRATOR")
		{
			VehiclePreviewDictName = "lgm_dlc_importexport";
			VehiclePreviewName = "penetrator";
		}
		if (ModelName == "GP1")
		{
			VehiclePreviewDictName = "lgm_dlc_specialraces";
			VehiclePreviewName = "gp1";
		}
		if (ModelName == "BTYPE")
		{
			VehiclePreviewDictName = "lgm_dlc_valentines";
			VehiclePreviewName = "roosevelt";
		}
		if (ModelName == "BTYPE2")
		{
			VehiclePreviewDictName = "lgm_dlc_valentines";
			VehiclePreviewName = "roosevelt";
		}
		if (ModelName == "BTYPE3")
		{
			VehiclePreviewDictName = "lgm_dlc_valentines";
			VehiclePreviewName = "roosevelt";
		}
		 if (ModelName == "CASCO")
		{
		VehiclePreviewDictName = "lgm_dlc_heist";
		VehiclePreviewName = "casco";
		}
		 if (ModelName == "COQUETTE2")
		{
		VehiclePreviewDictName = "lgm_dlc_pilot";
		VehiclePreviewName = "coquette2";
		}
		 if (ModelName == "FELTZER3")
		{
		VehiclePreviewDictName = "lgm_dlc_luxe";
		VehiclePreviewName = "feltzer3";
		}
		 if (ModelName == "JB700")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "jb700";
		}
		 if (ModelName == "MAMBA")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "mamba";
		}
		 if (ModelName == "MONROE")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "monroe";
		}
		 if (ModelName == "PIGALLE")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "pigalle";
		}
		 if (ModelName == "STINGER")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "stinger";
		}
		 if (ModelName == "STINGERGT")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "stingerg";
		}
		 if (ModelName == "TORNADO")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "TORNADO2")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "TORNADO3")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "TORNADO4")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "TORNADO5")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "TORNADO6")
		{
		VehiclePreviewDictName = "lsc_lowrider2";
		VehiclePreviewName = "tornado5";
		}
		 if (ModelName == "ZTYPE")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "ztype";
		}
		 if (ModelName == "INFERNUS2")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "TURISMO2")
		{
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "turismo2";
		}
		 if (ModelName == "ALPHA")
		{
		VehiclePreviewDictName = "lgm_dlc_business";
		VehiclePreviewName = "alpha";
		}
		 if (ModelName == "BANSHEE")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "banshee";
		}
		 if (ModelName == "BESTIAGTS")
		{
		VehiclePreviewDictName = "lgm_dlc_executive1";
		VehiclePreviewName = "bestiagts";
		}
		 if (ModelName == "BLISTA2")
		{
		VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
		VehiclePreviewName = "blista2";
		}
		 if (ModelName == "BLISTA3")
		{
		VehiclePreviewDictName = "sssa_dlc_arena";
		VehiclePreviewName = "blista3";
		}
		 if (ModelName == "BUFFALO")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "buffalo";
		}
		 if (ModelName == "BUFFALO2")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "buffalo2";
		}
		 if (ModelName == "BUFFALO3")
		{
		VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
		VehiclePreviewName = "buffalo3";
		}
		 if (ModelName == "CARBONIZZARE")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "carboniz";
		}
		 if (ModelName == "COMET2")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "comet2";
		}
		 if (ModelName == "COQUETTE")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "coquette";
		}
		 if (ModelName == "ELEGY")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "elegy";
		}
		 if (ModelName == "ELEGY2")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "elegy2";
		}
		 if (ModelName == "FELTZER2")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "feltzer";
		}
		 if (ModelName == "FUROREGT")
		{
		VehiclePreviewDictName = "lgm_dlc_lts_creator";
		VehiclePreviewName = "furore";
		}
		 if (ModelName == "FUSILADE")
		{
		VehiclePreviewDictName = "sssa_dlc_business2";
		VehiclePreviewName = "fusilade";
		}
		 if (ModelName == "FUTO")
		{
		VehiclePreviewDictName = "sssa_dlc_battle";
		VehiclePreviewName = "futo";
		}
		 if (ModelName == "JESTER")
		{
		VehiclePreviewDictName = "lgm_dlc_business";
		VehiclePreviewName = "jester";
		}
		 if (ModelName == "JESTER2")
		{
		VehiclePreviewDictName = "sssa_dlc_christmas_2";
		VehiclePreviewName = "jester2";
		}
		 if (ModelName == "KHAMELION")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "khamel";
		}
		 if (ModelName == "KURUMA")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "kuruma";
		}
		 if (ModelName == "KURUMA2")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "kuruma2";
		}
		 if (ModelName == "LYNX")
		{
		VehiclePreviewDictName = "lgm_dlc_stunt";
		VehiclePreviewName = "lynx";
		}
		 if (ModelName == "MASSACRO")
		{
		VehiclePreviewDictName = "lgm_dlc_business2";
		VehiclePreviewName = "massacro";
		}
		 if (ModelName == "MASSACRO2")
		{
		VehiclePreviewDictName = "sssa_dlc_christmas_2";
		VehiclePreviewName = "massacro2";
		}
		 if (ModelName == "NINEF")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "ninef";
		}
		 if (ModelName == "NINEF2")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "ninef2";
		}
		 if (ModelName == "OMNIS")
		{
		VehiclePreviewDictName = "sssa_dlc_stunt";
		VehiclePreviewName = "omnis";
		}
		 if (ModelName == "PENUMBRA")
		{
		VehiclePreviewDictName = "sssa_dlc_business2";
		VehiclePreviewName = "penumbra";
		}
		 if (ModelName == "RAPIDGT")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "rapidgt";
		}
		 if (ModelName == "RAPIDGT2")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "rapidgt2";
		}
		 if (ModelName == "RAPTOR")
		{
		VehiclePreviewDictName = "lgm_dlc_biker";
		VehiclePreviewName = "raptor";
		}
		 if (ModelName == "SCHAFTER3")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "schafter3";
		}
		 if (ModelName == "SCHAFTER4")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "schafter4";
		}
		 if (ModelName == "SCHWARTZER")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "schwarze";
		}
		 if (ModelName == "SEVEN70")
		{
		VehiclePreviewDictName = "lgm_dlc_executive1";
		VehiclePreviewName = "seven70";
		}
		 if (ModelName == "SULTAN")
		{
		VehiclePreviewDictName = "lsc_jan2016";
		VehiclePreviewName = "sultan2";
		}
		if (ModelName == "SURANO")
		{
			VehiclePreviewDictName = "lgm_default";
			VehiclePreviewName = "surano_convertable";
		}
		 if (ModelName == "SPECTER")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "specter2";
		}
		 if (ModelName == "SPECTER2")
		{
		VehiclePreviewDictName = "lsc_dlc_import_export";
		VehiclePreviewName = "specter2_a";
		}
		 if (ModelName == "TAMPA2")
		{
		VehiclePreviewDictName = "sssa_dlc_stunt";
		VehiclePreviewName = "tampa2";
		}
		 if (ModelName == "TROPOS")
		{
		VehiclePreviewDictName = "sssa_dlc_stunt";
		VehiclePreviewName = "tropos";
		}
		 if (ModelName == "VERLIERER2")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "verlier";
		}
		 if (ModelName == "RUINER2")
		{
		VehiclePreviewDictName = "lgm_dlc_specialraces";
		VehiclePreviewName = "infernus2";
		}
		 if (ModelName == "PHANTOM2")
		{
		VehiclePreviewDictName = "candc_importexport";
		VehiclePreviewName = "phantom2";
		}
		if (ModelName == "RUSTON")
		{
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "ruston";
		}
		if (ModelName == "AIRBUS")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "airbus";
		}
		 if (ModelName == "BRICKADE")
		{
		VehiclePreviewDictName = "candc_executive1";
		VehiclePreviewName = "brickade";
		}
		 if (ModelName == "BUS")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "bus";
		}
		 if (ModelName == "COACH")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "coach";
		}
		 if (ModelName == "RALLYTRUCK")
		{
		VehiclePreviewDictName = "sssa_dlc_stunt";
		VehiclePreviewName = "rallytruck";
		}
		 if (ModelName == "RENTALBUS")
		{
		VehiclePreviewDictName = "candc_default";
		VehiclePreviewName = "rentbus";
		}
		 if (ModelName == "WASTELANDER")
		{
		VehiclePreviewDictName = "candc_importexport";
		VehiclePreviewName = "wastlndr";
		}
		 if (ModelName == "ASEA")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "asea";
		}
		 if (ModelName == "ASTEROPE")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "astrope";
		}
		 if (ModelName == "COG55")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "cog55";
		}
		 if (ModelName == "COG552")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "cog55";
		}
		 if (ModelName == "COGNOSCENTI")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "cog55";
		}
		 if (ModelName == "COGNOSCENTI2")
		{
		VehiclePreviewDictName = "lgm_dlc_apartments";
		VehiclePreviewName = "cog55";
		}
		 if (ModelName == "FUGITIVE")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "fugitive";
		}
		 if (ModelName == "GLENDALE")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "glendale";
		}
		 if (ModelName == "INGOT")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "ingot";
		}
		 if (ModelName == "INTRUDER")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "intruder";
		}
		 if (ModelName == "LIMO2")
		{
			VehiclePreviewDictName = "candc_apartments";
			VehiclePreviewName = "limo2";
		}
		if (ModelName == "PREMIER")
		{
			VehiclePreviewDictName = "sssa_dlc_business";
			VehiclePreviewName = "premier";
		}
		if (ModelName == "PRIMO")
		{
			VehiclePreviewDictName = "sssa_dlc_hipster";
			VehiclePreviewName = "primo";
		}
		if (ModelName == "PRIMO2")
		{
			VehiclePreviewDictName = "lsc_default";
			VehiclePreviewName = "primo2";
		}
		if (ModelName == "REGINA")
		{
			VehiclePreviewDictName = "sssa_dlc_hipster";
			VehiclePreviewName = "regina";
		}
		if (ModelName == "ROMERO")
		{
			VehiclePreviewDictName = "sssa_dlc_battle";
			VehiclePreviewName = "romero";
		}
		if (ModelName == "SCHAFTER2")
		{
			VehiclePreviewDictName = "sssa_dlc_heist";
			VehiclePreviewName = "schafter2";
		}
		if (ModelName == "SCHAFTER5")
		{
			VehiclePreviewDictName = "sssa_dlc_heist";
			VehiclePreviewName = "schafter2";
		}
		 if (ModelName == "SCHAFTER6")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "schafter2";
		}
		 if (ModelName == "STANIER")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "stanier";
		}
		 if (ModelName == "STRATUM")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "stratum";
		}
		 if (ModelName == "STRETCH")
		{
		VehiclePreviewDictName = "sssa_default";
		VehiclePreviewName = "stretch";
		}
		 if (ModelName == "SUPERD")
		{
		VehiclePreviewDictName = "lgm_default";
		VehiclePreviewName = "superd";
		}
		 if (ModelName == "SURGE")
		{
		VehiclePreviewDictName = "sssa_dlc_heist";
		VehiclePreviewName = "surge";
		}
		 if (ModelName == "TAILGATER")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "tailgater";
		}
		 if (ModelName == "WARRENER")
		{
		VehiclePreviewDictName = "sssa_dlc_hipster";
		VehiclePreviewName = "warrener";
		}
		 if (ModelName == "WASHINGTON")
		{
		VehiclePreviewDictName = "sssa_dlc_business";
		VehiclePreviewName = "washingt";
		}
		 if (ModelName == "BESRA")
		{
		VehiclePreviewDictName = "elt_dlc_pilot";
		VehiclePreviewName = "besra";
		}
		 if (ModelName == "CUBAN800")
		{
		VehiclePreviewDictName = "elt_default";
		VehiclePreviewName = "cuban800";
		}
		 if (ModelName == "DODO")
		{
		VehiclePreviewDictName = "elt_default";
		VehiclePreviewName = "dodo";
		}
		 if (ModelName == "DUSTER")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "duster";
		 }
		 if (ModelName == "HYDRA")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "hydra";
		 }
		 if (ModelName == "LAZER")
		 {
			 VehiclePreviewDictName = "candc_smuggler";
			 VehiclePreviewName = "lazer";
		 }
		 if (ModelName == "LUXOR")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "luxor";
		 }
		 if (ModelName == "LUXOR2")
		 {
			 VehiclePreviewDictName = "elt_dlc_luxe";
			 VehiclePreviewName = "luxor2";
		 }
		 if (ModelName == "MAMMATUS")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "mammatus";
		 }
		 if (ModelName == "MILJET")
		 {
			 VehiclePreviewDictName = "elt_dlc_pilot";
			 VehiclePreviewName = "miljet";
		 }
		 if (ModelName == "NIMBUS")
		 {
			 VehiclePreviewDictName = "elt_dlc_executive1";
			 VehiclePreviewName = "nimbus";
		 }
		 if (ModelName == "SHAMAL")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "shamal";
		 }
		 if (ModelName == "STUNT")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "stunt";
		 }
		 if (ModelName == "TITAN")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "titan";
		 }
		 if (ModelName == "VELUM")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "velum";
		 }
		 if (ModelName == "VELUM2")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "velum2";
		 }
		 if (ModelName == "VESTRA")
		 {
			 VehiclePreviewDictName = "elt_dlc_business";
			 VehiclePreviewName = "vestra";
		 }
		 if (ModelName == "BFINJECTION")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "bfinject";
		 }
		 if (ModelName == "BIFTA")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "bifta";
		 }
		 if (ModelName == "BLAZER")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "blazer";
		 }
		 if (ModelName == "BLAZER2")
		 {
			 VehiclePreviewDictName = "candc_casinoheist";
			 VehiclePreviewName = "blazer2";
		 }
		 if (ModelName == "BLAZER3")
		 {
			 VehiclePreviewDictName = "sssa_dlc_hipster";
			 VehiclePreviewName = "blazer3";
		 }
		 if (ModelName == "BLAZER4")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "blazer4";
		 }
		 if (ModelName == "BODHI2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "bodhi2";
		 }
		 if (ModelName == "BRAWLER")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "brawler";
		 }
		 if (ModelName == "DUBSTA3")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "dubsta3";
		 }
		 if (ModelName == "DUNE")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "dune";
		 }
		 if (ModelName == "INSURGENT")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "insurgent";
		 }
		 if (ModelName == "INSURGENT2")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "insurgent2";
		 }
		 if (ModelName == "KALAHARI")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "kalahari";
		 }
		 if (ModelName == "MARSHALL")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "marshall";
		 }
		 if (ModelName == "MESA3")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "mesa3";
		 }
		 if (ModelName == "MONSTER")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "monster";
		 }
		 if (ModelName == "RANCHERXL")
		 {
			 VehiclePreviewDictName = "sssa_dlc_business";
			 VehiclePreviewName = "rancherx";
		 }
		 if (ModelName == "REBEL")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "rebel";
		 }
		 if (ModelName == "REBEL2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_hipster";
			 VehiclePreviewName = "rebel2";
		 }
		 if (ModelName == "SANDKING")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "sandking";
		 }
		 if (ModelName == "SANDKING2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "sandkin2";
		 }
		 if (ModelName == "TECHNICAL")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "technical";
		 }
		 if (ModelName == "TROPHYTRUCK")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "trophy";
		 }
		 if (ModelName == "TROPHYTRUCK2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "trophy2";
		 }
		 if (ModelName == "TECHNICAL2")
		 {
			 VehiclePreviewDictName = "candc_importexport";
			 VehiclePreviewName = "technical2";
		 }
		 if (ModelName == "DUNE5")
		 {
			 VehiclePreviewDictName = "candc_importexport";
			 VehiclePreviewName = "dune5";
		 }
		 if (ModelName == "BLAZER5")
		 {
			 VehiclePreviewDictName = "candc_importexport";
			 VehiclePreviewName = "blazer5";
		 }
		 if (ModelName == "BLADE")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "blade";
		 }
		 if (ModelName == "BUCCANEER")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "buccaneer2";
		 }
		 if (ModelName == "BUCCANEER2")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "buccaneer2_a";
		 }
		 if (ModelName == "CHINO")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "chino";
		 }
		 if (ModelName == "CHINO2")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "chino2";
		 }
		 if (ModelName == "COQUETTE3")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "coquette3";
		 }
		 if (ModelName == "DOMINATOR")
		 {
			 VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
			 VehiclePreviewName = "dominator2";
		 }
		 if (ModelName == "DOMINATOR2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
			 VehiclePreviewName = "dominator2";
		 }
		 if (ModelName == "DUKES")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "dukes";
		 }
		 if (ModelName == "DUKES2")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "dukes";
		 }
		 if (ModelName == "GAUNTLET")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "gauntlet";
		 }
		 if (ModelName == "GAUNTLET2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
			 VehiclePreviewName = "gauntlet2";
		 }
		 if (ModelName == "gauntlet3")
		 {
			 VehiclePreviewDictName = "sssa_dlc_vinewood";
			 VehiclePreviewName = "gauntlet3";
		 }
		 if (ModelName == "gauntlet4")
		 {
			 VehiclePreviewDictName = "sssa_dlc_vinewood";
			 VehiclePreviewName = "gauntlet4";
		 }
		 if (ModelName == "FACTION")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "faction2";
		 }
		 if (ModelName == "FACTION2")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "faction2";
		 }
		 if (ModelName == "FACTION3")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "faction3";
		 }
		 if (ModelName == "HOTKNIFE")
		 {
			 VehiclePreviewDictName = "lgm_default";
			 VehiclePreviewName = "hotknife";
		 }
		 if (ModelName == "LURCHER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_halloween";
			 VehiclePreviewName = "lurcher";
		 }
		 if (ModelName == "MOONBEAM")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "moonbeam2";
		 }
		 if (ModelName == "MOONBEAM2")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "moonbeam2";
		 }
		 if (ModelName == "NIGHTSHADE")
		 {
			 VehiclePreviewDictName = "lgm_dlc_apartments";
			 VehiclePreviewName = "niteshad";
		 }
		 if (ModelName == "PICADOR")
		 {
			 VehiclePreviewDictName = "sssa_dlc_hipster";
			 VehiclePreviewName = "picador";
		 }
		 if (ModelName == "RATLOADER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_valentines";
			 VehiclePreviewName = "rloader";
		 }
		 if (ModelName == "RATLOADER2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_christmas_2";
			 VehiclePreviewName = "rloader2";
		 }
		 if (ModelName == "RUINER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_battle";
			 VehiclePreviewName = "ruiner";
		 }
		 if (ModelName == "RUINER2")
		 {
			 VehiclePreviewDictName = "candc_importexport";
			 VehiclePreviewName = "ruiner2";
		 }
		 if (ModelName == "SABREGT")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "sabregt2";
		 }
		 if (ModelName == "SABREGT2")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "sabregt2";
		 }
		 if (ModelName == "SLAMVAN")
		 {
			 VehiclePreviewDictName = "sssa_dlc_christmas_2";
			 VehiclePreviewName = "slamvan";
		 }
		 if (ModelName == "SLAMVAN3")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "slamvan3";
		 }
		 if (ModelName == "STALION")
		 {
			 VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
			 VehiclePreviewName = "stalion2";
		 }
		 if (ModelName == "STALION2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_mp_to_sp";
			 VehiclePreviewName = "stalion2";
		 }
		 if (ModelName == "TAMPA")
		 {
			 VehiclePreviewDictName = "sssa_dlc_christmas_3";
			 VehiclePreviewName = "tampa";
		 }
		 if (ModelName == "VIGERO")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "vigero";
		 }
		 if (ModelName == "VIRGO")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "virgo";
		 }
		 if (ModelName == "VIRGO2")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "virgo2";
		 }
		 if (ModelName == "VIRGO3")
		 {
			 VehiclePreviewDictName = "lsc_lowrider2";
			 VehiclePreviewName = "virgo2";
		 }
		 if (ModelName == "VOODOO")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "voodoo";
		 }
		 if (ModelName == "VOODOO2")
		 {
			 VehiclePreviewDictName = "lsc_default";
			 VehiclePreviewName = "voodoo";
		 }
		 if (ModelName == "AKUMA")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "akuma";
		 }
		 if (ModelName == "AVARUS")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "avarus";
		 }
		 if (ModelName == "BAGGER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "bagger";
		 }
		 if (ModelName == "BATI2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "bati2";
		 }
		 if (ModelName == "BF400")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "bf400";
		 }
		 if (ModelName == "CARBONRS")
		 {
			 VehiclePreviewDictName = "lgm_default";
			 VehiclePreviewName = "carbon";
		 }
		 if (ModelName == "CHIMERA")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "chimera";
		 }
		 if (ModelName == "CLIFFHANGER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "cliffhanger";
		 }
		 if (ModelName == "DAEMON")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "DAEMON2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "daemon2";
		 }
		 if (ModelName == "DEFILER")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "defiler";
		 }
		 if (ModelName == "DOUBLE")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "double";
		 }
		 if (ModelName == "ENDURO")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "enduro";
		 }
		 if (ModelName == "ESSKEY")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "esskey";
		 }
		 if (ModelName == "FAGGIO")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "faggio";
		 }
		 if (ModelName == "FAGGIO2")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "FAGGIO3")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "faggio3";
		 }
		 if (ModelName == "GARGOYLE")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "gargoyle";
		 }
		 if (ModelName == "HAKUCHOU")
		 {
			 VehiclePreviewDictName = "sssa_dlc_lts_creator";
			 VehiclePreviewName = "hakuchou";
		 }
		 if (ModelName == "HAKUCHOU2")
		 {
			 VehiclePreviewDictName = "lgm_dlc_biker";
			 VehiclePreviewName = "hakuchou2";
		 }
		 if (ModelName == "HEXER")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "hexer";
		 }
		 if (ModelName == "INNOVATION")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "innovation";
		 }
		 if (ModelName == "LECTRO")
		 {
			 VehiclePreviewDictName = "lgm_dlc_heist";
			 VehiclePreviewName = "lectro";
		 }
		 if (ModelName == "MANCHEZ")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "manchez";
		 }
		 if (ModelName == "NEMESIS")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "nemesis";
		 }
		 if (ModelName == "NIGHTBLADE")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "nightblade";
		 }
		 if (ModelName == "PCJ")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "pcj";
		 }
		 if (ModelName == "RATBIKE")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "ratbike";
		 }
		 if (ModelName == "RUFFIAN")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "ruffian";
		 }
		 if (ModelName == "SANCHEZ")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "sanchez";
		 }
		 if (ModelName == "SANCHEZ2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "sanchez2";
		 }
		 if (ModelName == "SANCTUS")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "SHOTARO")
		 {
			 VehiclePreviewDictName = "lgm_dlc_biker";
			 VehiclePreviewName = "shotaro";
		 }
		 if (ModelName == "SOVEREIGN")
		 {
			 VehiclePreviewDictName = "sssa_dlc_independence";
			 VehiclePreviewName = "sovereign";
		 }
		 if (ModelName == "THRUST")
		 {
			 VehiclePreviewDictName = "lgm_dlc_business2";
			 VehiclePreviewName = "thrust";
		 }
		 if (ModelName == "VADER")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "vader";
		 }
		 if (ModelName == "VINDICATOR")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "vindicator";
		 }
		 if (ModelName == "VORTEX")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "WOLFSBANE")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "ZOMBIEA")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "zombiea";
		 }
		 if (ModelName == "ZOMBIEB")
		 {
			 VehiclePreviewDictName = "sssa_dlc_biker";
			 VehiclePreviewName = "zombieb";
		 }
		 if (ModelName == "DIABLOUS")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "DIABLOUS2")
		 {
			 VehiclePreviewDictName = "lsc_dlc_import_export";
			 VehiclePreviewName = "diablous2";
		 }
		 if (ModelName == "FCR")
		 {
			 VehiclePreviewDictName = "lgm_dlc_specialraces";
			 VehiclePreviewName = "infernus2";
		 }
		 if (ModelName == "FCR2")
		 {
			 VehiclePreviewDictName = "lsc_dlc_import_export";
			 VehiclePreviewName = "fcr2";
		 }
		 if (ModelName == "BARRACKS")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "barracks";
		 }
		 if (ModelName == "BARRACKS3")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "barracks";
		 }
		 if (ModelName == "CRUSADER")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "crusader";
		 }
		 if (ModelName == "RHINO")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "rhino";
		 }
		 if (ModelName == "DUMP")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "dump";
		 }
		 if (ModelName == "GUARDIAN")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "guardian";
		 }
		 if (ModelName == "ANNIHILATOR")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "annihl";
		 }
		 if (ModelName == "BUZZARD")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "buzzard";
		 }
		 if (ModelName == "BUZZARD2")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "buzzard";
		 }
		 if (ModelName == "CARGOBOB")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "cargobob";
		 }
		 if (ModelName == "CARGOBOB2")
		 {
			 VehiclePreviewDictName = "candc_executive1";
			 VehiclePreviewName = "cargobob2";
		 }
		 if (ModelName == "CARGOBOB3")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "cargobob";
		 }
		 if (ModelName == "CARGOBOB4")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "cargobob";
		 }
		 if (ModelName == "FROGGER")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "frogger";
		 }
		 if (ModelName == "MAVERICK")
		 {
			 VehiclePreviewDictName = "elt_default";
			 VehiclePreviewName = "maverick";
		 }
		 if (ModelName == "avenger")
		 {
			 VehiclePreviewDictName = "candc_chopper";
			 VehiclePreviewName = "banner_0";
		 }
		 if (ModelName == "SAVAGE")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "savage";
		 }
		 if (ModelName == "SUPERVOLITO")
		 {
			 VehiclePreviewDictName = "elt_dlc_apartments";
			 VehiclePreviewName = "svolito";
		 }
		 if (ModelName == "SUPERVOLITO2")
		 {
			 VehiclePreviewDictName = "elt_dlc_apartments";
			 VehiclePreviewName = "svolito2";
		 }
		 if (ModelName == "SWIFT")
		 {
			 VehiclePreviewDictName = "elt_dlc_pilot";
			 VehiclePreviewName = "swift";
		 }
		 if (ModelName == "SWIFT2")
		 {
			 VehiclePreviewDictName = "elt_dlc_luxe";
			 VehiclePreviewName = "swift2";
		 }
		 if (ModelName == "VALKYRIE")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "valkyrie";
		 }
		 if (ModelName == "VALKYRIE2")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "valkyrie";
		 }
		 if (ModelName == "VOLATUS")
		 {
			 VehiclePreviewDictName = "elt_dlc_executive1";
			 VehiclePreviewName = "volatus";
		 }
		 if (ModelName == "FIRETRUK")
		 {
			 VehiclePreviewDictName = "candc_casinoheist";
			 VehiclePreviewName = "firetruk";
		 }
		 if (ModelName == "LGUARD")
		 {
			 VehiclePreviewDictName = "candc_casinoheist";
			 VehiclePreviewName = "lguard";
		 }
		 if (ModelName == "PBUS")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "pbus";
		 }
		 if (ModelName == "BMX")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "bmx";
		 }
		 if (ModelName == "CRUISER")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "cruiser";
		 }
		 if (ModelName == "SCORCHER")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "scorcher";
		 }
		 if (ModelName == "TRIBIKE")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "tribike";
		 }
		 if (ModelName == "TRIBIKE2")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "tribike2";
		 }
		 if (ModelName == "TRIBIKE3")
		 {
			 VehiclePreviewDictName = "pandm_default";
			 VehiclePreviewName = "tribike3";
		 }
		 if (ModelName == "COGCABRIO")
		 {
			 VehiclePreviewDictName = "lgm_default";
			 VehiclePreviewName = "cogcabri";
		 }
		 if (ModelName == "EXEMPLAR")
		 {
			 VehiclePreviewDictName = "lgm_default";
			 VehiclePreviewName = "exemplar";
		 }
		 if (ModelName == "F620")
		 {
			 VehiclePreviewDictName = "sssa_dlc_business2";
			 VehiclePreviewName = "f620";
		 }
		 if (ModelName == "FELON")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "felon";
		 }
		 if (ModelName == "FELON2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "felon2";
		 }
		 if (ModelName == "JACKAL")
		 {
			 VehiclePreviewDictName = "sssa_dlc_heist";
			 VehiclePreviewName = "jackal";
		 }
		 if (ModelName == "ORACLE")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "oracle";
		 }
		 if (ModelName == "ORACLE2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "oracle";
		 }
		 if (ModelName == "SENTINEL")
		 {
			 VehiclePreviewDictName = "sssa_dlc_business2";
			 VehiclePreviewName = "sentinel";
		 }
		 if (ModelName == "SENTINEL2")
		 {
			 VehiclePreviewDictName = "sssa_dlc_business2";
			 VehiclePreviewName = "sentinel";
		 }
		 if (ModelName == "WINDSOR")
		 {
			 VehiclePreviewDictName = "lgm_dlc_luxe";
			 VehiclePreviewName = "windsor";
		 }
		 if (ModelName == "WINDSOR2")
		 {
			 VehiclePreviewDictName = "lgm_dlc_executive1";
			 VehiclePreviewName = "windsor2";
		 }
		 if (ModelName == "ZION")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "zion";
		 }
		 if (ModelName == "ZION2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "zion2";
		 }
		 if (ModelName == "BRIOSO")
		 {
			 VehiclePreviewDictName = "sssa_dlc_stunt";
			 VehiclePreviewName = "brioso";
		 }
		 if (ModelName == "DILETTANTE")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "dilettan";
		 }
		 if (ModelName == "ISSI2")
		 {
			 VehiclePreviewDictName = "sssa_default";
			 VehiclePreviewName = "issi2";
		 }
		 if (ModelName == "PANTO")
		 {
			 VehiclePreviewDictName = "sssa_dlc_hipster";
			 VehiclePreviewName = "panto";
		 }
		 if (ModelName == "PRAIRIE")
		 {
			 VehiclePreviewDictName = "sssa_dlc_battle";
			 VehiclePreviewName = "prairie";
		 }
		 if (ModelName == "RHAPSODY")
		 {
			 VehiclePreviewDictName = "sssa_dlc_hipster";
			 VehiclePreviewName = "rhapsody";
		 }
		 if (ModelName == "MULE")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "mule";
		 }
		 if (ModelName == "MULE2")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "mule";
		 }
		 if (ModelName == "MULE3")
		 {
			 VehiclePreviewDictName = "candc_default";
			 VehiclePreviewName = "mule";
		 }
		 if (ModelName == "STOCKADE")
		 {
			 VehiclePreviewDictName = "candc_casinoheist";
			 VehiclePreviewName = "stockade";
		 }
		 if (ModelName == "DINGHY")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "dinghy3";
		 }
		 if (ModelName == "DINGHY2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "dinghy3";
		 }
		 if (ModelName == "DINGHY3")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "dinghy3";
		 }
		 if (ModelName == "DINGHY4")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "dinghy3";
		 }
		 if (ModelName == "JETMAX")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "jetmax";
		 }
		 if (ModelName == "MARQUIS")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "marquis";
		 }
		 if (ModelName == "SEASHARK")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "seashark";
		 }
		 if (ModelName == "SEASHARK2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "seashark";
		 }
		 if (ModelName == "SEASHARK3")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "seashark";
		 }
		 if (ModelName == "SPEEDER")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "speeder";
		 }
		 if (ModelName == "SPEEDER2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "speeder";
		 }
		 if (ModelName == "SQUALO")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "squalo";
		 }
		 if (ModelName == "SUBMERSIBLE2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "sub2";
		 }
		 if (ModelName == "SUNTRAP")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "suntrap";
		 }
		 if (ModelName == "TORO")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "toro";
		 }
		 if (ModelName == "TORO2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "toro";
		 }
		 if (ModelName == "TROPIC")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "tropic";
		 }
		 if (ModelName == "TROPIC2")
		 {
			 VehiclePreviewDictName = "dock_default";
			 VehiclePreviewName = "tropic";
		 }
		 if (ModelName == "TUG")
		 {
			 VehiclePreviewDictName = "dock_dlc_executive1";
			 VehiclePreviewName = "tug";
		 }
		
		 if (ShowVehiclePreviews)
		 {
			 std::transform(ModelName.begin(), ModelName.end(), ModelName.begin(), ::tolower);
			 std::string ModelNameDrawingText = "Model name: " + ModelName;
			 if (Cheat::Settings::menuX < 0.71f) {
				 Drawing::Text("Vehicle Preview", Settings::count, { Settings::menuX + 0.187f, 0.130f }, { 0.115f, 16 * 0.035f + -0.193f }, true);
				 Drawing::Text(ModelNameDrawingText.c_str(), Settings::count, { Settings::menuX + 0.111f, 0.308f }, { 0.45f, 0.30f }, false);
				 Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX + 0.187f, 0.233f }, { 0.16f, 0.20f });
				 Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Settings::menuX + 0.187f, 0.232f, 0.15, 0.15, 0, 255, 255, 255, 255);
			 }
			 else
			 {
				 Drawing::Text("Vehicle Preview", Settings::count, { Settings::menuX - 0.187f, 0.130f }, { 0.115f, 16 * 0.035f + -0.193f }, true);
				 Drawing::Text(ModelNameDrawingText.c_str(), Settings::count, { Settings::menuX - 0.262f, 0.308f }, { 0.45f, 0.30f }, false);
				 Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX - 0.187f, 0.233f }, { 0.16f, 0.20f });
				 Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Settings::menuX - 0.187f, 0.232f, 0.15, 0.15, 0, 255, 255, 255, 255);
			 }
		 }
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool Cheat::Break(const char * option, bool TextCentered)
{
	Settings::optionCount++;

	if (Settings::optionCount == Settings::currentOption) 
	{ 
		OptionInformationText = "";
		if (Settings::previousOption < Settings::currentOption && Settings::optionCount > 1)
		{
			Settings::currentOption++;
			if (Settings::TotalOptionsCount < Settings::currentOption)
			{
				Settings::currentOption = 1;
			}
		}
		else if (Settings::previousOption > Settings::currentOption && Settings::optionCount > 1)
		{
			Settings::currentOption--;
			if (Settings::TotalOptionsCount < 1)
			{
				Settings::currentOption = Settings::optionCount;
			}
		}
	}

	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		if (TextCentered) { Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		else { Drawing::Text(option, Settings::breakText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f });
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		if (TextCentered) { Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		else { Drawing::Text(option, Settings::breakText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		Drawing::Rect(Settings::MenuBackgroundRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.1415f }, { 0.21f, 0.035f });
	}
	return false;
}

bool Cheat::MenuOption(const char * option, SubMenus newSub)
{
	Option(option, "");

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text("", Settings::titleText, { Settings::menuX + 0.099f, Settings::optionCount * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text("", Settings::titleText, { Settings::menuX + 0.099f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.12f }, { 0.35f, 0.35f }, true);

	if (Settings::optionCount == Settings::currentOption) {
		OptionInformationText = "";

		if (Settings::selectPressed) {
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
	}
	return false;
}


bool Cheat::Toggle(const char * option, bool & b00l, const char* InformationText)
{
	Option(option, "");
	if (b00l)
	{
		if (shop_box_bool_option) {
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.140f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
			else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			{
				Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.140f, 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
		}
		else if (medal_bool_option) {
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.140f), 0.02f, 0.03f, 0, 43, 255, 0, 255);
			}
			else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			{
				Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.140f, 0.02f, 0.03f, 0, 43, 255, 0, 255);
			}
		}
	}
	else
	{
		if (shop_box_bool_option) {
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.140f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
			else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			{
				Drawing::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.140f, 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
		}
		else if (medal_bool_option) {
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.140f), 0.02f, 0.03f, 0, 255, 0, 0, 255);
			}
			else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			{
				Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.140f, 0.02f, 0.03f, 0, 255, 0, 0, 255);
			}
		}
	}
	if (Settings::optionCount == Settings::currentOption) {
		OptionInformationText = InformationText;

		if (Settings::selectPressed)
		{
			b00l ^= 1;
			return true;
		}
	}
	return false;
}


bool Cheat::ToggleCheckMark(const char * option, bool & b00l) 
{
	Option(option, "");
	if (b00l) { Drawing::Spriter("commonmenu", "shop_tick_icon", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.140f), 0.03f, 0.05f, 0, 255, 255, 255, 255); }

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}


bool Cheat::IntNoControl(const char* option, int& _int, int min, int max, const char* InformationText)
{
	Option(option, "");

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(" " + std::to_string(_int) + " "), Settings::optionText, { Settings::menuX + 0.080f, Settings::optionCount * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(" " + std::to_string(_int) + " "), Settings::optionText, { Settings::menuX + 0.080f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
	}

	if (Settings::optionCount == Settings::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Cheat::Int(const char * option, int & _int, int min, int max, int step, const char* InformationText)
{
	Option(option, "");

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			if (_int < max)
			{
				if (step == 1) { _int++; }
				else
				{
					_int = _int + step;
				}
			}
		}
		if (Settings::rightPressed) {
			if (_int > min)
			{
				if (step == 1) { _int--; }
				else
				{
					_int = _int - step;
				}
			}
		}
	}


	if (Settings::optionCount == Settings::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		if (_int < 100)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.075f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.07f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.06f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
	}
	else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
	{
		if (_int < 100)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.075f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.07f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), Settings::optionText, { Settings::menuX + 0.06f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, false);
		}
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Cheat::Float(const char * option, float & _float, float min, float max, float steps, bool ReturnTrueWithValueChange, const char* InformationText)
{
	Option(option, "");
	if (Settings::optionCount == Settings::currentOption) {	
		if (Settings::leftPressed) {
			if (_float < max)
			{
				_float += steps;
			}
		}
		if (Settings::rightPressed) {
			if (_float > min)
			{
				_float -= steps;
			}
		}
	}

	if (Settings::optionCount == Settings::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.08f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.08f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed && ReturnTrueWithValueChange) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed && ReturnTrueWithValueChange) return true;
	return false;
}
#pragma warning(disable: 4267)
bool Cheat::IntVector(const char * option, std::vector<int> Vector, int & position)
{
	Option(option, "");

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Cheat::FloatVector(const char * option, std::vector<float> Vector, int & position)
{
	Option(option, "");

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Cheat::StringVector(const char * option, std::vector<std::string> Vector, int & position, const char* InformationText)
{
	Option(option, "");

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::optionCount == Settings::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
		Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + (Vector[position]) + " >"), Settings::optionText, { Settings::menuX + 0.055f, Settings::optionCount * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
		Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + (Vector[position]) + " >"), Settings::optionText, { Settings::menuX + 0.055f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4267)
void Cheat::End()
{
	Settings::TotalOptionsCount = Settings::optionCount;
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	if (opcount >= Settings::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Settings::currentOptionMenuBottom) + " / " + std::to_string(Settings::optionCountMenuBottom)), Settings::count, { Settings::menuX - 0.085f, ((Settings::maxVisOptions + 1) * 0.035f + 0.128f) }, { 0.30f, 0.30f }, true);
		Drawing::Text(Cheat::CheatFunctions::ReturnCheatBuildAsString().c_str(), Settings::count, { Settings::menuX + 0.085f, ((Settings::maxVisOptions + 1) * 0.035f + 0.128f) }, { 0.30f, 0.30f }, true);
		Drawing::Rect(Settings::MenuBottomRect, { Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.1415f) }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.1235f) }, { 0.21f, 0.002f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);

		if (OptionInformationText != "") {
			Drawing::Rect(Settings::MenuBottomRect, { Settings::menuX, ((Settings::maxVisOptions + 2) * 0.035f + 0.1390f) }, { 0.21f, 0.030f }); // Option Info Rect
			Drawing::Spriter("shared", "info_icon_32", { Settings::menuX - 0.095f }, ((Settings::maxVisOptions + 2) * 0.035f + 0.1320f), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			Drawing::Text(OptionInformationText, Settings::count, { Settings::menuX - 0.085f, ((Settings::maxVisOptions + 2) * 0.035f + 0.1210f) }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
	else if (opcount > 0)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Settings::currentOptionMenuBottom) + " / " + std::to_string(Settings::optionCountMenuBottom)), Settings::count, { Settings::menuX - 0.085f, (Settings::optionCount + 1) * 0.035f + 0.128f }, { 0.30f, 0.30f }, true);
		Drawing::Text(Cheat::CheatFunctions::ReturnCheatBuildAsString().c_str(), Settings::count, { Settings::menuX + 0.085f, (Settings::optionCount + 1) * 0.035f + 0.128f }, { 0.30f, 0.30f }, true);
		Drawing::Rect(Settings::MenuBottomRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1235f }, { 0.21f, 0.002f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);

		if (OptionInformationText != "") {
			Drawing::Rect(Settings::MenuBottomRect, { Settings::menuX, (Settings::optionCount + 2) * 0.035f + 0.1390f }, { 0.21f, 0.030f }); // Option Info Rect
			Drawing::Spriter("shared", "info_icon_32", { Settings::menuX - 0.095f }, ((Settings::optionCount + 2) * 0.035f + 0.1320), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			Drawing::Text(OptionInformationText, Settings::count, { Settings::menuX - 0.085f, (Settings::optionCount + 2) * 0.035f + 0.1210f }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
}

void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, xorstr_("HUD_FRONTEND_DEFAULT_SOUNDSET"), 0);
}

int Cheat::Settings::keyPressDelay = 200;
int Cheat::Settings::keyPressPreviousTick = GetTickCount();
int Cheat::Settings::keyPressDelay2 = 100;
int Cheat::Settings::keyPressPreviousTick2 = GetTickCount();
int Cheat::Settings::keyPressDelay3 = 140;
int Cheat::Settings::keyPressPreviousTick3 = GetTickCount();
int Cheat::Settings::openKey = VK_F4;
bool Cheat::Settings::ControllerInput = true;
bool Cheat::Settings::RestorePreviousSubmenu = true;

void Cheat::Checks::Controls()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;

	if (GetTickCount64() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
	if (GetTickCount64() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
		if (GetTickCount64() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
			if (GetAsyncKeyState(Settings::openKey) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendX) && Settings::ControllerInput)
			{								
				if (Settings::menuLevel == 0)
				{
					if (Settings::PreviousMenu != NOMENU && Cheat::Settings::RestorePreviousSubmenu) { MenuLevelHandler::MoveMenu(Settings::PreviousMenu); Settings::menuLevel = Settings::PreviousMenuLevel; Settings::currentOption = Settings::previousOption; }
					else { MenuLevelHandler::MoveMenu(SubMenus::MainMenu);  }
				}
				else
				{
					MenuLevelHandler::CloseMenu();
				}
		
				PlaySoundFrontend_default("SELECT");
				Settings::keyPressPreviousTick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD0) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::ControllerInput) {
				if (Settings::menuLevel > 0) { MenuLevelHandler::BackMenu(); PlaySoundFrontend_default("BACK"); }

				Settings::keyPressPreviousTick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD8) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::ControllerInput) {
				Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD2) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::ControllerInput) {
				Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD6) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::ControllerInput) {
				Settings::leftPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD4) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::ControllerInput) {
				Settings::rightPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD5) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::ControllerInput) {
				Settings::selectPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("SELECT");

				Settings::keyPressPreviousTick = GetTickCount64();
			}
		}
	}
	}
	Settings::optionCount = 0;
	Settings::optionCountMenuBottom = 0;
}
#pragma warning(default : 4018)
void Cheat::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void Cheat::MenuLevelHandler::CloseMenu()
{
	Settings::PreviousMenu = Cheat::Settings::currentMenu;
	Settings::PreviousMenuLevel = Settings::menuLevel;
	Settings::previousOption = Settings::currentOption;
	Settings::menuLevel = 0;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}

void Cheat::MenuLevelHandler::BackMenu()
{
	Settings::PreviousMenu = Settings::currentMenu;
	Settings::PreviousMenuLevel = Settings::menuLevel;
	Settings::previousOption = Settings::currentOption;
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}


void Cheat::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}

std::string Cheat::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), xorstr_("NULL"), buf, 100, file.c_str());
	return (std::string)buf;
}

void Cheat::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}

int Cheat::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	std::string ReturnTempString = ReadStringFromIni(file, app, key);
	if (Cheat::CheatFunctions::StringIsInteger(ReturnTempString))
	{
		return std::stoi(ReturnTempString);
	}
	else
	{
		return 0;
	}
}


void Cheat::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}

float Cheat::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}

void Cheat::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool Cheat::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}

void Cheat::Speedometer(char* text)
{
	Drawing::Text(text, { 0, 0, 255, 255 }, { 0.90, 0.5000f }, { 0.70f, 0.70f }, false);
	
}
void Cheat::fps(char* text)
{
	Drawing::Text(text, { 255, 255, 255, 255 }, { 0.50f, 0.002f }, { 0.30f, 0.30f }, false);
}
void Cheat::AddSmallTitle(char* text)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);		
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}
void Cheat::PlayerInfoBoxTitle(char* text)
{
	if (Cheat::Settings::menuX < 0.70f)
	{
		Drawing::Text(text, { Settings::titleText }, { Settings::menuX + 0.200f, 0.130f }, { 0.50f, 0.35f }, true);
		Drawing::Rect(Settings::MainTitleRect, { Settings::menuX + 0.203f, 0.145f }, { 0.19f, 0.024f });
	}
	else
	{
		Drawing::Text(text, { Settings::titleText }, { Settings::menuX - 0.200f, 0.130f }, { 0.50f, 0.35f }, true);
		Drawing::Rect(Settings::MainTitleRect, { Settings::menuX - 0.203f, 0.145f }, { 0.19f, 0.024f });
	}
}
void Cheat::PlayerInfoBoxText(char* text, short line)
{
	if (Cheat::Settings::menuX < 0.70f)
	{
		if (line == 1) { Drawing::Rect(Settings::scroller, { Settings::menuX + 0.203f, ((16 * 0.035f) / 2.0f) + 0.060f }, { 0.19f, 16 * 0.035f + -0.193f }); }
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.110f, (line * 0.020f) + 0.140f }, { 0.30f, 0.30f }, false);
	}
	else
	{
		if (line == 1) { Drawing::Rect(Settings::scroller, { Settings::menuX - 0.203f, ((16 * 0.035f) / 2.0f) + 0.060f }, { 0.19f, 16 * 0.035f + -0.193f }); }
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.295f, (line * 0.020f) + 0.140f }, { 0.30f, 0.30f }, false);
	}
}
void Cheat::AddSmallInfo(char* text, short line)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((16 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((16 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}
void Cheat::AddSmallTitle2(char* text)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Cheat::AddSmallInfo2(char* text, short line)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void Cheat::AddSmallTitle3(char* text)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Cheat::AddSmallInfo3(char* text, short line)
{
	if (Cheat::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}




char* ThemeFilesArray[100] = {};
void Cheat::LoadThemeFilesLooped()
{
	memset(ThemeFilesArray, 0, sizeof ThemeFilesArray);
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	std::string GTAVCheatFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav");

	if (!Cheat::CheatFunctions::DoesDirectoryExists(GTAVCheatFolderPath)) { Cheat::CheatFunctions::CreateNewDirectory(GTAVCheatFolderPath); }
	if (!Cheat::CheatFunctions::DoesDirectoryExists(ThemeFolderPath)) { Cheat::CheatFunctions::CreateNewDirectory(ThemeFolderPath); }

	int i = 0;
	for (const auto & file : std::filesystem::directory_iterator(ThemeFolderPath.c_str())) {
		if (file.path().extension() == ".ini")
		{
			ThemeFilesArray[i] = new char[file.path().stem().string().length() + 1];
			strcpy(ThemeFilesArray[i], file.path().stem().string().c_str());
			++i;
		}
	}
}


void Cheat::LoadTheme(char* ThemeFileName, bool StartUp)
{
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	std::string ThemeFilePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + ThemeFileName + ".ini";

	if (!Cheat::CheatFunctions::DoesFileExists(ThemeFilePath)) { Cheat::GameFunctions::MinimapNotification("~r~Failed to load theme: theme file does not exist"); return; }

	CurrentTheme = ThemeFileName;

	std::string ThemeLoaderVersionCheck = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "theme_loader_version");
	if (ThemeLoaderVersionCheck != xorstr_("1.2")) { Cheat::GameFunctions::MinimapNotification("~o~Loaded theme file is outdated"); Cheat::GameFunctions::MinimapNotification("~o~Some theme settings might not have loaded correctly"); }

	std::string TitleBackgroundRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_red");
	std::string TitleBackgroundGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_green");
	std::string TitleBackgroundBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_blue");
	std::string TitleBackgroundOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_opacity");

	std::string HeaderBackgroundRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_red");
	std::string HeaderBackgroundGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_green");
	std::string HeaderBackgroundBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_blue");
	std::string HeaderBackgroundOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_opacity");

	std::string SmallTitleBackgroundRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_red");
	std::string SmallTitleBackgroundGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_green");
	std::string SmallTitleBackgroundBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_blue");
	std::string SmallTitleBackgroundOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_opacity");

	std::string OptionTextRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_red");
	std::string OptionTextGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_green");
	std::string OptionTextBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_blue");
	std::string OptionTextOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_opacity");

	std::string SelectionBoxRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_red");
	std::string SelectionBoxGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_green");
	std::string SelectionBoxBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_blue");
	std::string SelectionBoxOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_opacity");

	std::string SelectionBoxBackgroundRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_red");
	std::string SelectionBoxBackgroundGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_green");
	std::string SelectionBoxBackgroundBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_blue");
	std::string SelectionBoxBackgroundOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_opacity");

	std::string BottomLineRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_red");
	std::string BottomLineGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_green");
	std::string BottomLineBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_blue");
	std::string BottomLineOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_opacity");

	std::string MenuBottomBackgroundRed = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_red");
	std::string MenuBottomBackgroundGreen = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_green");
	std::string MenuBottomBackgroundBlue = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_blue");
	std::string MenuBottomBackgroundOpacity = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	
	if (SmallTitleBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundRed))) { Cheat::Settings::titleRect.r = std::stoi(SmallTitleBackgroundRed); } } }
	if (SmallTitleBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundGreen))) { Cheat::Settings::titleRect.g = std::stoi(SmallTitleBackgroundGreen); } } }
	if (SmallTitleBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundBlue))) { Cheat::Settings::titleRect.b = std::stoi(SmallTitleBackgroundBlue); } } }
	if (SmallTitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundOpacity))) { Cheat::Settings::titleRect.a = std::stoi(SmallTitleBackgroundOpacity); } } }
	if (HeaderBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundRed))) { Cheat::Settings::headerRect.r = std::stoi(HeaderBackgroundRed); } } }
	if (HeaderBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundGreen))) { Cheat::Settings::headerRect.g = std::stoi(HeaderBackgroundGreen); } } }
	if (HeaderBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundBlue))) { Cheat::Settings::headerRect.b = std::stoi(HeaderBackgroundBlue); } } }
	if (HeaderBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundOpacity))) { Cheat::Settings::headerRect.a = std::stoi(HeaderBackgroundOpacity); } } }
	if (BottomLineRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineRed))) { Cheat::Settings::line.r = std::stoi(BottomLineRed); } } }
	if (BottomLineGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineGreen))) { Cheat::Settings::line.g = std::stoi(BottomLineGreen); } } }
	if (BottomLineBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineBlue))) { Cheat::Settings::line.b = std::stoi(BottomLineBlue); } } }
	if (BottomLineOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineOpacity))) { Cheat::Settings::line.a = std::stoi(BottomLineOpacity); } } }
	if (TitleBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundRed))) { Cheat::Settings::MainTitleRect.r = std::stoi(TitleBackgroundRed); } } }
	if (TitleBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundGreen))) { Cheat::Settings::MainTitleRect.g = std::stoi(TitleBackgroundGreen); } } }
	if (TitleBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundBlue))) { Cheat::Settings::MainTitleRect.b = std::stoi(TitleBackgroundBlue); } } }
	if (TitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundOpacity))) { Cheat::Settings::MainTitleRect.a = std::stoi(TitleBackgroundOpacity); } } }
	if (OptionTextRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextRed))) { Cheat::Settings::optionText.r = std::stoi(OptionTextRed); } } }
	if (OptionTextGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextGreen))) { Cheat::Settings::optionText.g = std::stoi(OptionTextGreen); } } }
	if (OptionTextBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextBlue))) { Cheat::Settings::optionText.b = std::stoi(OptionTextBlue); } } }
	if (OptionTextOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextOpacity))) { Cheat::Settings::optionText.a = std::stoi(OptionTextOpacity); } } }
	if (TitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundOpacity))) { Cheat::Settings::MainTitleRect.a = std::stoi(TitleBackgroundOpacity); } } }
	if (SelectionBoxRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxRed))) { Cheat::Settings::scroller.r = std::stoi(SelectionBoxRed); } } }
	if (SelectionBoxGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxGreen))) { Cheat::Settings::scroller.g = std::stoi(SelectionBoxGreen); } } }
	if (SelectionBoxBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBlue))) { Cheat::Settings::scroller.b = std::stoi(SelectionBoxBlue); } } }
	if (SelectionBoxOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxOpacity))) { Cheat::Settings::scroller.a = std::stoi(SelectionBoxOpacity); } } }
	if (SelectionBoxBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundRed))) { Cheat::Settings::MenuBackgroundRect.r = std::stoi(SelectionBoxBackgroundRed); } } }
	if (SelectionBoxBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundGreen))) { Cheat::Settings::MenuBackgroundRect.g = std::stoi(SelectionBoxBackgroundGreen); } } }
	if (SelectionBoxBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundBlue))) { Cheat::Settings::MenuBackgroundRect.b = std::stoi(SelectionBoxBackgroundBlue); } } }
	if (SelectionBoxBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundOpacity))) { Cheat::Settings::MenuBackgroundRect.a = std::stoi(SelectionBoxBackgroundOpacity); } } }
	if (MenuBottomBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundRed))) { Cheat::Settings::MenuBottomRect.r = std::stoi(MenuBottomBackgroundRed); } } }
	if (MenuBottomBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundGreen))) { Cheat::Settings::MenuBottomRect.g = std::stoi(MenuBottomBackgroundGreen); } } }
	if (MenuBottomBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundBlue))) { Cheat::Settings::MenuBottomRect.b = std::stoi(MenuBottomBackgroundBlue); } } }
	if (MenuBottomBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundOpacity))) { Cheat::Settings::MenuBottomRect.a = std::stoi(MenuBottomBackgroundOpacity); } } }

	std::string MenuXSetting = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "menu_x"); if (Cheat::CheatFunctions::IsIntegerInRange(0.170000, 0.820000, std::stod(MenuXSetting))) { double MenuXDouble = std::stod(MenuXSetting);  Cheat::Settings::menuX = MenuXDouble; }
	std::string ScrollDelaySetting = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "scroll_delay"); if (Cheat::CheatFunctions::StringIsInteger(ScrollDelaySetting)) { if (Cheat::CheatFunctions::IsIntegerInRange(1, 200, std::stoi(ScrollDelaySetting))) { Cheat::Settings::keyPressDelay2 = std::stoi(ScrollDelaySetting.c_str()); } }
	std::string IntDelaySetting = Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "int_delay"); if (Cheat::CheatFunctions::StringIsInteger(IntDelaySetting)) { if (Cheat::CheatFunctions::IsIntegerInRange(1, 200, std::stoi(IntDelaySetting))) { Cheat::Settings::keyPressDelay3 = std::stoi(IntDelaySetting.c_str()); } }
	if (Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_background") == "true") { show_header_background = true; }
	if (Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_gui") == "true") { show_header_gui = true; }
	if (Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "restore_previous_submenu") == "false") { Cheat::Settings::RestorePreviousSubmenu = false; } else { Cheat::Settings::RestorePreviousSubmenu = true; }
	if (Cheat::Files::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_glare") == "false") { ShowHeaderGlare = false; } else { ShowHeaderGlare = true; }

	Cheat::Settings::maxVisOptions = Cheat::Files::ReadIntFromIni(ThemeFilePath, "THEME", "max_vis_options");
	if (Cheat::Files::ReadIntFromIni(ThemeFilePath, "THEME", "open_key") != 0)
	{
		Cheat::Settings::openKey = Cheat::Files::ReadIntFromIni(ThemeFilePath, "THEME", "open_key");
	}
	if (!StartUp) { Cheat::GameFunctions::MinimapNotification("Theme Loaded"); }
}


void Cheat::SaveTheme(char* ThemeFileName)
{
	std::string ThemeFilePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + ThemeFileName + ".ini";
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	if (!Cheat::CheatFunctions::DoesDirectoryExists(Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes")) { Cheat::CheatFunctions::CreateNewDirectory(ThemeFolderPath); }

	Cheat::Files::WriteStringToIni(xorstr_("1.2"), ThemeFilePath, "THEME", "theme_loader_version");
	Cheat::Files::WriteBoolToIni(show_header_background, ThemeFilePath, "THEME", "show_header_background");
	Cheat::Files::WriteBoolToIni(show_header_gui, ThemeFilePath, "THEME", "show_header_gui");
	Cheat::Files::WriteBoolToIni(Cheat::Settings::RestorePreviousSubmenu, ThemeFilePath, "THEME", "restore_previous_submenu");
	Cheat::Files::WriteBoolToIni(ShowHeaderGlare, ThemeFilePath, "THEME", "show_header_glare");
	Cheat::Files::WriteFloatToIni(Cheat::Settings::menuX, ThemeFilePath, "THEME", "menu_x");
	Cheat::Files::WriteIntToIni(Cheat::Settings::keyPressDelay2, ThemeFilePath, "THEME", "scroll_delay");
	Cheat::Files::WriteIntToIni(Cheat::Settings::keyPressDelay3, ThemeFilePath, "THEME", "int_delay");
	Cheat::Files::WriteIntToIni(Cheat::Settings::maxVisOptions, ThemeFilePath, "THEME", "max_vis_options");
	Cheat::Files::WriteIntToIni(Cheat::Settings::openKey, ThemeFilePath, "THEME", "open_key");

	Cheat::Files::WriteIntToIni(Cheat::Settings::MainTitleRect.r, ThemeFilePath, "THEME", "title_background_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MainTitleRect.g, ThemeFilePath, "THEME", "title_background_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MainTitleRect.b, ThemeFilePath, "THEME", "title_background_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MainTitleRect.a, ThemeFilePath, "THEME", "title_background_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::headerRect.r, ThemeFilePath, "THEME", "header_background_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::headerRect.g, ThemeFilePath, "THEME", "header_background_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::headerRect.b, ThemeFilePath, "THEME", "header_background_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::headerRect.a, ThemeFilePath, "THEME", "header_background_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::titleRect.r, ThemeFilePath, "THEME", "small_title_background_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::titleRect.g, ThemeFilePath, "THEME", "small_title_background_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::titleRect.b, ThemeFilePath, "THEME", "small_title_background_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::titleRect.a, ThemeFilePath, "THEME", "small_title_background_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::optionText.r, ThemeFilePath, "THEME", "option_text_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::optionText.g, ThemeFilePath, "THEME", "option_text_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::optionText.b, ThemeFilePath, "THEME", "option_text_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::optionText.a, ThemeFilePath, "THEME", "option_text_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::scroller.r, ThemeFilePath, "THEME", "selection_box_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::scroller.g, ThemeFilePath, "THEME", "selection_box_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::scroller.b, ThemeFilePath, "THEME", "selection_box_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::scroller.a, ThemeFilePath, "THEME", "selection_box_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBackgroundRect.r, ThemeFilePath, "THEME", "selection_box_background_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBackgroundRect.g, ThemeFilePath, "THEME", "selection_box_background_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBackgroundRect.b, ThemeFilePath, "THEME", "selection_box_background_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBackgroundRect.a, ThemeFilePath, "THEME", "selection_box_background_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::line.r, ThemeFilePath, "THEME", "bottom_line_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::line.g, ThemeFilePath, "THEME", "bottom_line_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::line.b, ThemeFilePath, "THEME", "bottom_line_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::line.a, ThemeFilePath, "THEME", "bottom_line_opacity");

	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBottomRect.r, ThemeFilePath, "THEME", "menu_bottom_background_red");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBottomRect.g, ThemeFilePath, "THEME", "menu_bottom_background_green");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBottomRect.b, ThemeFilePath, "THEME", "menu_bottom_background_blue");
	Cheat::Files::WriteIntToIni(Cheat::Settings::MenuBottomRect.a, ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	Cheat::GameFunctions::MinimapNotification(xorstr_("Theme Saved"));
}