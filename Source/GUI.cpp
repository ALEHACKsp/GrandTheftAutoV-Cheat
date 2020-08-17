#include "stdafx.h"

float Cheat::GUI::guiX					= 0.11f;
float Cheat::GUI::guiY					= 0.30f;
float Cheat::GUI::guiWidth				= 0.21f; //TODO: Text Scaling not implemented yet
bool Cheat::GUI::selectPressed			= false;
bool Cheat::GUI::leftPressed			= false;
bool Cheat::GUI::rightPressed			= false;
bool Cheat::GUI::ShowHeaderBackground	= true;
bool Cheat::GUI::ShowHeaderGUI			= true;
bool Cheat::GUI::ShowHeaderGlare		= true;
bool Cheat::GUI::CheatGUIHasBeenOpened	= false;
const char* OptionInformationText;
char* Cheat::GUI::CurrentTheme			= NULL;
int Cheat::GUI::maxVisOptions			= 10;
int Cheat::GUI::currentOption			= 0;
int Cheat::GUI::currentOptionMenuBottom = 0;
int Cheat::GUI::previousOption			= 0;
int Cheat::GUI::optionCount				= 0;
int Cheat::GUI::optionCountMenuBottom	= 0;
int Cheat::GUI::TotalOptionsCount		= 0;
int Cheat::GUI::menuLevel				= 0;
SubMenus Cheat::GUI::PreviousMenu		= NOMENU;
SubMenus Cheat::GUI::currentMenu;
int Cheat::GUI::PreviousMenuLevel;
int Cheat::GUI::optionsArray			[1000];
SubMenus Cheat::GUI::menusArray			[1000];
char* Cheat::GUI::ThemeFilesArray		[1000];


RGBAF Cheat::GUI::count				{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::titleText			{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::optionText		{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::breakText			{ 255, 255, 255, 255, FontChaletLondon };
RGBA Cheat::GUI::titleRect			{ 0, 0, 255, 255 };
RGBA Cheat::GUI::MainTitleRect		{ 0, 0, 0, 255 };
RGBA Cheat::GUI::headerRect			{ 0, 0, 255, 200 };                      
RGBA Cheat::GUI::optionRect			{ 0, 0, 0, 255 };
RGBA Cheat::GUI::MenuBackgroundRect	{ 0, 0, 0, 220 }; 
RGBA Cheat::GUI::MenuBottomRect		{ 0, 0, 0, 255 };
RGBA Cheat::GUI::scroller			{ 0, 0, 255, 255 };
RGBA Cheat::GUI::TopAndBottomLine	{ 0, 0, 255, 255 };



static fpFileRegister RegisterTextureFile = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(RegisterTextureFile)>());
void Cheat::Drawing::InitTextureFile()
{
	Cheat::LogFunctions::Message(xorstr_("Loading Texture File"));
	int textureID;
	if (Cheat::CheatFunctions::DoesFileExists(Cheat::CheatFunctions::TextureFilePath())) 
	{
		RegisterTextureFile(&textureID, Cheat::CheatFunctions::TextureFilePath().c_str(), true, xorstr_("Textures.ytd"), false);
	}
	else 
	{ 
		Cheat::GameFunctions::MinimapNotification(xorstr_("~r~Failed to load Texture")); 
		Cheat::LogFunctions::DebugMessage(xorstr_("Failed to load Textures.ytd"));
	}
}


void Cheat::Drawing::Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
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


void Cheat::Title(const char * title)
{
	Drawing::Text(title, { GUI::titleText }, { GUI::guiX, GUI::guiY - 0.17f }, { 0.50f, 0.35f }, true);

	if (Cheat::GUI::ShowHeaderBackground)		{ Drawing::Rect(GUI::headerRect, { Cheat::GUI::guiX, GUI::guiY - 0.208f }, { Cheat::GUI::guiWidth, 0.084f });  } // Header Rect
	if (GUI::ShowHeaderGlare)					{ Drawing::DrawScaleform(Cheat::GUI::guiX + .330f, GUI::guiY + 0.162f, 1.0f, 0.912f, 255, 255, 255); } // Header Glare
	if (Cheat::GUI::ShowHeaderGUI)				{ Cheat::Drawing::Spriter(xorstr_("Textures"), xorstr_("HeaderDefaultTransparent"), Cheat::GUI::guiX, GUI::guiY - 0.208f, Cheat::GUI::guiWidth, 0.084f, 0, 255, 255, 255, 255); }

	Drawing::Rect(GUI::MainTitleRect, { Cheat::GUI::guiX, GUI::guiY - 0.154f }, { Cheat::GUI::guiWidth, 0.023f }); // Title Rect
	Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY - 0.142f }, { Cheat::GUI::guiWidth, 0.002f });

	Cheat::GUI::CheatGUIHasBeenOpened = true;
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
	std::string CloseGUIString = xorstr_("Press ") + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::openKey) + xorstr_(" to close GUI");
	std::string CursorNavigationString;
	if (Cheat::CheatFeatures::CursorGUINavigationEnabled) { CursorNavigationString = xorstr_("Press ") + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::GUINavigationKey) + xorstr_(" to disable cursor"); }
	else { CursorNavigationString = xorstr_("Press ") + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::GUINavigationKey) + xorstr_(" to enable cursor"); }
	Cheat::GameFunctions::InstructionsInit();
	Cheat::GameFunctions::InstructionsAdd((char*)CloseGUIString.c_str(), 80);
	Cheat::GameFunctions::InstructionsAdd((char*)CursorNavigationString.c_str(), 80);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Back"), 136);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Up/Down"), 10);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Change Value"), 46);
	Cheat::GameFunctions::InstructionsAdd(xorstr_("Select"), 141);
	Cheat::GameFunctions::InstructionsEnd();
}


bool Cheat::Option(const char * option, const char* InformationText, bool PlayerList)
{
	GUI::optionCount++;
	GUI::optionCountMenuBottom++;
	VECTOR2 ScrollerRectPosition;
	bool onThis = GUI::currentOption == GUI::optionCount ? true : false;
	int OptionCountDifference = GUI::optionCount - GUI::optionCountMenuBottom;
	if (onThis) { GUI::currentOptionMenuBottom = GUI::optionCount - OptionCountDifference; }
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (PlayerList)
		{
			Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.080f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
		}
		else
		{
			Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
		}

		if (onThis)
		{
			ScrollerRectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f };
			Drawing::Rect(GUI::scroller, ScrollerRectPosition, { Cheat::GUI::guiWidth, 0.035f });
		}
		else
		{
			ScrollerRectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f };
			Drawing::Rect(GUI::MenuBackgroundRect, ScrollerRectPosition, { Cheat::GUI::guiWidth, 0.035f });
		}
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		if (PlayerList)
		{
			Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.080f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
		}
		else
		{
			Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f- 0.175f }, { 0.35f, 0.35f }, false);
		}

		if (onThis)
		{
			ScrollerRectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f };
			Drawing::Rect(GUI::scroller, ScrollerRectPosition, { Cheat::GUI::guiWidth, 0.035f });
		}
		else
		{
			ScrollerRectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f };
			Drawing::Rect(GUI::MenuBackgroundRect, ScrollerRectPosition, { Cheat::GUI::guiWidth, 0.035f });
		}
	}
	if (GUI::currentOption == GUI::optionCount)
	{
		OptionInformationText = InformationText;
		GUI::previousOption = GUI::currentOption;
		if (GUI::selectPressed)
		{
			return true;
		}
	}

	/*
	if (CheatFeatures::CursorGUINavigationEnabled)
	{
		if (Cheat::GameFunctions::IsCursorAtXYPosition(ScrollerRectPosition, { Cheat::GUI::guiWidth, 0.035f }))
		{
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
			{
				return true;
			}
		}
	}
	*/
		

	return false;
}
char* VehiclePreviewDictName;
char* VehiclePreviewName;
bool Cheat::VehicleOption(const char* option, std::string ModelName)
{
	GUI::optionCount++;
	GUI::optionCountMenuBottom++;
	bool onThis = GUI::currentOption == GUI::optionCount ? true : false;
	int OptionCountDifference = GUI::optionCount - GUI::optionCountMenuBottom;
	if (onThis) { GUI::currentOptionMenuBottom = GUI::optionCount - OptionCountDifference; }
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
		Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		onThis ? Drawing::Rect(GUI::scroller, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f }) : NULL;
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false); // 0.45 0.45
		Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		onThis ? Drawing::Rect(GUI::scroller, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f }) : NULL;
	}
	if (GUI::currentOption == GUI::optionCount)
	{
		std::transform(ModelName.begin(), ModelName.end(), ModelName.begin(), ::tolower);
		VehiclePreviewDictName = "Textures";
		VehiclePreviewName	   = "NoVehiclePreviewAvailable";


		for (int i = 0; i < Cheat::GameArrays::VehicleModelPictures.size(); i++)
		{
			if (Cheat::GameArrays::VehicleModelPictures[i].PreviewName == ModelName)
			{ 
				VehiclePreviewDictName	= (char*)Cheat::GameArrays::VehicleModelPictures[i].DictName.c_str();
				VehiclePreviewName		= (char*)Cheat::GameArrays::VehicleModelPictures[i].PreviewName.c_str();
			}
		}
			
		 if (Cheat::CheatFeatures::ShowVehicleInfoAndPreview)
		 {
			 std::string ModelNameDrawingText = xorstr_("Model Name: ") + ModelName;
			 std::ostringstream ModelMaxSpeed;
			 if (Cheat::CheatFeatures::UseKMH)
			 {
				 ModelMaxSpeed << xorstr_("Max Speed: ") << Cheat::GameFunctions::MSToKMH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY((char*)ModelName.c_str()))) << xorstr_(" KM/H"); 
			 }
			 else
			 {
				 ModelMaxSpeed << xorstr_("Max Speed: ") << Cheat::GameFunctions::MSToMPH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY((char*)ModelName.c_str()))) << xorstr_(" MP/H");
			 }

			 if (Cheat::GUI::guiX < 0.71f) 
			 {
				 Drawing::Text(xorstr_("Vehicle Info & Preview"), GUI::count, { Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.168f }, { 0.50f, 0.35f }, true);
				 Drawing::Text(ModelNameDrawingText.c_str(), GUI::count, { Cheat::GUI::guiX + 0.111f,  GUI::guiY + 0.008f }, { 0.45f, 0.30f }, false);
				 Drawing::Text(ModelMaxSpeed.str().c_str(), GUI::count, { Cheat::GUI::guiX + 0.111f, GUI::guiY + 0.026f }, { 0.45f, 0.30f }, false);
				 Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.056f }, { 0.16f, 0.22f });
				 Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.068f, 0.15, 0.15, 0, 255, 255, 255, 255);
			 }
			 else
			 {
				 Drawing::Text(xorstr_("Vehicle Info & Preview"), GUI::count, { Cheat::GUI::guiX - 0.187f,GUI::guiY - 0.168f }, { 0.50f, 0.35f }, true);
				 Drawing::Text(ModelNameDrawingText.c_str(), GUI::count, { Cheat::GUI::guiX - 0.262f, GUI::guiY + 0.008f }, { 0.45f, 0.30f }, false);
				 Drawing::Text(ModelMaxSpeed.str().c_str(), GUI::count, { Cheat::GUI::guiX - 0.262f, GUI::guiY + 0.026f }, { 0.45f, 0.30f }, false);
				 Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX - 0.187f, GUI::guiY - 0.056f }, { 0.16f, 0.22f });
				 Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Cheat::GUI::guiX - 0.187f, GUI::guiY - 0.068f, 0.15, 0.15, 0, 255, 255, 255, 255);
			 }
		 }
		if (GUI::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool Cheat::Break(const char * option, bool TextCentered)
{
	GUI::optionCount++;

	if (GUI::optionCount == GUI::currentOption) 
	{ 
		OptionInformationText = "";
		if (GUI::previousOption < GUI::currentOption && GUI::optionCount > 1)
		{
			GUI::currentOption++;
			if (GUI::TotalOptionsCount < GUI::currentOption)
			{
				GUI::currentOption = 1;
			}
		}
		else if (GUI::previousOption > GUI::currentOption && GUI::optionCount > 1)
		{
			GUI::currentOption--;
			if (GUI::TotalOptionsCount < 1)
			{
				GUI::currentOption = GUI::optionCount;
			}
		}
	}

	bool onThis = GUI::currentOption == GUI::optionCount ? true : false;
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (TextCentered) { Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		else { Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		if (TextCentered) { Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX, (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		else { Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX - 0.100f, (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, TextCentered); }
		Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
	}
	return false;
}
bool Cheat::MenuOption(const char * option, SubMenus newSub)
{
	Option(option, "");

	if (GUI::optionCount == GUI::currentOption) 
	{
		if (GUI::selectPressed) 
		{
			GUI::MoveMenu(newSub);
			return true;
		}
	}
	return false;
}
bool Cheat::MenuOptionPlayerList(const char* option, SubMenus newSub, Player PlayerHandle)
{
	Option(option, "", true);

	char* CurrentOnlinePlayerPictureName = Cheat::GameFunctions::ReturnOnlinePlayerPictureString(PlayerHandle);

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Drawing::Spriter(CurrentOnlinePlayerPictureName, CurrentOnlinePlayerPictureName, Cheat::GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.02f, 0.03f, 0, 255, 255, 255, 255);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Spriter(CurrentOnlinePlayerPictureName, CurrentOnlinePlayerPictureName, Cheat::GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.160f, 0.02f, 0.03f, 0, 255, 255, 255, 255);
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		if (GUI::selectPressed) 
		{
			GUI::MoveMenu(newSub);
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
		if (Cheat::CheatFeatures::BoolOptionVectorPosition == 0) 
		{
			if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "shop_box_tick", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
			else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
			{
				Drawing::Spriter("commonmenu", "shop_box_tick", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.160f, 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
		}
		else if (Cheat::CheatFeatures::BoolOptionVectorPosition == 1) 
		{
			if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "common_medal", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.02f, 0.03f, 0, 43, 255, 0, 255);
			}
			else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
			{
				Drawing::Spriter("commonmenu", "common_medal", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.160f, 0.02f, 0.03f, 0, 43, 255, 0, 255);
			}
		}
	}
	else
	{
		if (Cheat::CheatFeatures::BoolOptionVectorPosition == 0) 
		{
			if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "shop_box_blank", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
			else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
			{
				Drawing::Spriter("commonmenu", "shop_box_blank", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.160f, 0.03f, 0.05f, 0, 255, 255, 255, 255);
			}
		}
		else if (Cheat::CheatFeatures::BoolOptionVectorPosition == 1) 
		{
			if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
			{
				Drawing::Spriter("commonmenu", "common_medal", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.02f, 0.03f, 0, 255, 0, 0, 255);
			}
			else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
			{
				Drawing::Spriter("commonmenu", "common_medal", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.160f, 0.02f, 0.03f, 0, 255, 0, 0, 255);
			}
		}
	}
	if (GUI::optionCount == GUI::currentOption) 
	{
		OptionInformationText = InformationText;

		if (GUI::selectPressed)
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
	if (b00l) { Drawing::Spriter("commonmenu", "shop_tick_icon", Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.03f, 0.05f, 0, 255, 255, 255, 255); }

	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed) 
	{
		b00l ^= 1;
		return true;
	}
	return false;
}


bool Cheat::Int(const char * option, int & _int, int min, int max, int step, bool DisableControl, const char* InformationText)
{
	Option(option, "");

	if (GUI::optionCount == GUI::currentOption) 
	{
		if (GUI::leftPressed && !DisableControl) 
		{
			if (_int < max)
			{
				if (step == 1) { _int++; }
				else
				{
					_int = _int + step;
				}
			}
		}
		if (GUI::rightPressed && !DisableControl) 
		{
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


	if (GUI::optionCount == GUI::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (DisableControl)
		{
			Drawing::Text(std::to_string(_int).c_str(), GUI::optionText, { Cheat::GUI::guiX + 0.080f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
		}
		else if (_int < 100)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.075f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.07f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.06f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
	}
	else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
	{
		if (DisableControl)
		{
			Drawing::Text(std::to_string(_int).c_str(), GUI::optionText, { Cheat::GUI::guiX + 0.080f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
		}
		else if (_int < 100)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.075f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.07f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + std::to_string(_int) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.06f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
	}
	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed && !DisableControl)
	{
		int KeyBoardInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInputInteger(CheatFunctions::ReturnNumberOfDigitsInValue(max));
		if (KeyBoardInput >= min && KeyBoardInput <= max)
		{
			_int = KeyBoardInput;
		}
		return true;
	}
	else if (GUI::optionCount == GUI::currentOption && GUI::leftPressed && !DisableControl) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::rightPressed && !DisableControl) return true;
	return false;
}

bool Cheat::Float(const char * option, float & _float, float min, float max, float steps, bool ReturnTrueWithValueChange, const char* InformationText)
{
	Option(option, "");
	if (GUI::optionCount == GUI::currentOption) {	
		if (GUI::leftPressed) {
			if (_float < max)
			{
				_float += steps;
			}
		}
		if (GUI::rightPressed) {
			if (_float > min)
			{
				_float -= steps;
			}
		}
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(_float)), GUI::optionText, { Cheat::GUI::guiX + 0.08f, GUI::guiY + GUI::optionCount * 0.035f - 0.172f }, { 0.32f, 0.32f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(_float)), GUI::optionText, { Cheat::GUI::guiX + 0.08f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.172f }, { 0.32f, 0.32f }, true);
	}

	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::leftPressed && ReturnTrueWithValueChange) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::rightPressed && ReturnTrueWithValueChange) return true;
	return false;
}
bool Cheat::IntVector(const char* option, std::vector<int> Vector, int& position)
{
	Option(option, "");

	if (GUI::optionCount == GUI::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (GUI::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (GUI::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}

	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::leftPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::rightPressed) return true;
	return false;
}
bool Cheat::FloatVector(const char * option, std::vector<float> Vector, int & position)
{
	Option(option, "");

	if (GUI::optionCount == GUI::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (GUI::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (GUI::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(Vector[position])), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}

	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::leftPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::rightPressed) return true;
	return false;
}
bool Cheat::StringVector(const char * option, std::vector<std::string> Vector, int & position, const char* InformationText)
{
	Option(option, "");

	if (GUI::optionCount == GUI::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (GUI::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (GUI::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		OptionInformationText = InformationText;
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions) 
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + (Vector[position]) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.055f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar("< " + (Vector[position]) + " >"), GUI::optionText, { Cheat::GUI::guiX + 0.055f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
	}
	if (GUI::optionCount == GUI::currentOption && GUI::selectPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::leftPressed) return true;
	else if (GUI::optionCount == GUI::currentOption && GUI::rightPressed) return true;
	return false;
}
void Cheat::GUI::End()
{
	GUI::TotalOptionsCount = GUI::optionCount;
	int opcount = GUI::optionCount;
	int currop = GUI::currentOption;
	if (opcount >= GUI::maxVisOptions)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(GUI::currentOptionMenuBottom) + " / " + std::to_string(GUI::optionCountMenuBottom)), GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.172f) }, { 0.30f, 0.30f }, true);
		Drawing::Text(Cheat::CheatFunctions::ReturnCheatBuildAsString().c_str(), GUI::count, { Cheat::GUI::guiX + 0.085f, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.172f) }, { 0.30f, 0.30f }, true);
		Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.1585f) }, { Cheat::GUI::guiWidth, 0.035f });
		Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.1765f) }, { Cheat::GUI::guiWidth, 0.002f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.160f), 0.020f, 0.035f, 180, GUI::TopAndBottomLine.r, GUI::TopAndBottomLine.g, GUI::TopAndBottomLine.b, GUI::TopAndBottomLine.a);

		if (OptionInformationText != "") 
		{
			Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.161f) }, { Cheat::GUI::guiWidth, 0.030f }); // Option Info Rect
			Drawing::Spriter("shared", "info_icon_32", { Cheat::GUI::guiX - 0.095f }, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.168f), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			Drawing::Text(OptionInformationText, GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.179f) }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
	else if (opcount > 0)
	{
		Drawing::Text(Cheat::CheatFunctions::StringToChar(std::to_string(GUI::currentOptionMenuBottom) + " / " + std::to_string(GUI::optionCountMenuBottom)), GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.172f }, { 0.30f, 0.30f }, true);
		Drawing::Text(Cheat::CheatFunctions::ReturnCheatBuildAsString().c_str(), GUI::count, { Cheat::GUI::guiX + 0.085f, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.172f }, { 0.30f, 0.30f }, true);
		Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.1765f }, { Cheat::GUI::guiWidth, 0.002f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Cheat::GUI::guiX, GUI::guiY + ((GUI::optionCount + 1) * 0.035f - 0.160f), 0.020f, 0.035f, 180, GUI::TopAndBottomLine.r, GUI::TopAndBottomLine.g, GUI::TopAndBottomLine.b, GUI::TopAndBottomLine.a);

		if (OptionInformationText != "") 
		{
			Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 2) * 0.035f - 0.161f }, { Cheat::GUI::guiWidth, 0.030f }); // Option Info Rect
			Drawing::Spriter("shared", "info_icon_32", { Cheat::GUI::guiX - 0.095f }, GUI::guiY + ((GUI::optionCount + 2) * 0.035f - 0.168), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			Drawing::Text(OptionInformationText, GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + (GUI::optionCount + 2) * 0.035f - 0.179f }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
}

void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, xorstr_("HUD_FRONTEND_DEFAULT_SOUNDSET"), 0);
}

int Cheat::GUI::keyPressDelay			= 200;
int Cheat::GUI::keyPressPreviousTick	= GetTickCount64();
int Cheat::GUI::keyPressDelay2			= 100;
int Cheat::GUI::keyPressPreviousTick2	= GetTickCount64();
int Cheat::GUI::keyPressDelay3			= 140;
int Cheat::GUI::keyPressPreviousTick3	= GetTickCount64();
int Cheat::GUI::openKey					= VK_F4;
int Cheat::GUI::GUINavigationKey		= VK_F5;
bool Cheat::GUI::ControllerInput		= true;
bool Cheat::GUI::RestorePreviousSubmenu = true;

void Cheat::GUI::ControlsLoop()
{
	GUI::selectPressed = false;
	GUI::leftPressed = false;
	GUI::rightPressed = false;

	if (GetTickCount64() - GUI::keyPressPreviousTick > GUI::keyPressDelay) {
	if (GetTickCount64() - GUI::keyPressPreviousTick2 > GUI::keyPressDelay2) {
		if (GetTickCount64() - GUI::keyPressPreviousTick3 > GUI::keyPressDelay3) {
			if (GetAsyncKeyState(GUI::openKey) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendX) && GUI::ControllerInput)
			{								
				if (GUI::menuLevel == 0)
				{
					if (GUI::PreviousMenu != NOMENU && Cheat::GUI::RestorePreviousSubmenu) 
					{ 
						GUI::MoveMenu(GUI::PreviousMenu);
						GUI::menuLevel = GUI::PreviousMenuLevel; 
						GUI::currentOption = GUI::previousOption; 
					}
					else 
					{ 
						GUI::MoveMenu(SubMenus::MainMenu);  
					}
				}
				else
				{
					if (Cheat::CheatFeatures::CursorGUINavigationEnabled) { Cheat::GameFunctions::EnableDisableCursorGUINavigation(); }
					GUI::CloseGUI();
				}
		
				PlaySoundFrontend_default("SELECT");
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD0) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && GUI::ControllerInput) 
			{
				if (GUI::menuLevel > 0) { GUI::BackMenu(); PlaySoundFrontend_default("BACK"); }

				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD8) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && GUI::ControllerInput) 
			{
				GUI::currentOption > 1 ? GUI::currentOption-- : GUI::currentOption = GUI::optionCount;
				if (GUI::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				GUI::keyPressPreviousTick2 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD2) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && GUI::ControllerInput) 
			{
				GUI::currentOption < GUI::optionCount ? GUI::currentOption++ : GUI::currentOption = 1;
				if (GUI::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				GUI::keyPressPreviousTick2 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD6) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && GUI::ControllerInput) 
			{
				GUI::leftPressed = true;
				if (GUI::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				GUI::keyPressPreviousTick3 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD4) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && GUI::ControllerInput) 
			{
				GUI::rightPressed = true;
				if (GUI::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				GUI::keyPressPreviousTick3 = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_NUMPAD5) & 1 && Cheat::CheatFunctions::IsGameWindowFocussed() || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && GUI::ControllerInput) 
			{
				GUI::selectPressed = true;
				if (GUI::menuLevel > 0)
					PlaySoundFrontend_default("SELECT");

				GUI::keyPressPreviousTick = GetTickCount64();
			}
		}
	}
	}
	GUI::optionCount = 0;
	GUI::optionCountMenuBottom = 0;
}
void Cheat::GUI::MoveMenu(SubMenus menu)
{
	GUI::menusArray[GUI::menuLevel] = GUI::currentMenu;
	GUI::optionsArray[GUI::menuLevel] = GUI::currentOption;
	GUI::menuLevel++;
	GUI::currentMenu = menu;
	GUI::currentOption = 1;
}

void Cheat::GUI::CloseGUI()
{
	GUI::PreviousMenu = Cheat::GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel = 0;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
}

void Cheat::GUI::BackMenu()
{
	GUI::PreviousMenu = GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel--;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
}


void Cheat::Speedometer(char* text)
{
	Drawing::Text(text, { 0, 0, 255, 255 }, { 0.90, 0.5000f }, { 0.70f, 0.70f }, false);
	
}
void Cheat::fps(char* text)
{
	Drawing::Text(text, { 255, 255, 255, 255 }, { 0.50f, 0.002f }, { 0.30f, 0.30f }, false);
}
void Cheat::AddPlayerInfoBoxTextEntry(char* text, int Row1, int Row2, int Row3, int Row4)
{
	if (Cheat::GUI::guiX < 0.54f)
	{		
		if (Row1 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.110f, GUI::guiY + (Row1 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.210f, GUI::guiY + (Row2 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.310f, GUI::guiY + (Row3 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.385f, GUI::guiY + (Row4 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
	}
	else
	{
		if (Row1 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.420f, GUI::guiY + (Row1 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.340f, GUI::guiY + (Row2 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.260f, GUI::guiY + (Row3 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.160f, GUI::guiY + (Row4 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
	}
}

void Cheat::LoadThemeFilesLooped()
{
	memset(GUI::ThemeFilesArray, 0, sizeof(GUI::ThemeFilesArray));
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";

	if (!Cheat::CheatFunctions::DoesDirectoryExists(ThemeFolderPath)) { Cheat::CheatFunctions::CreateNewDirectory(ThemeFolderPath); }

	int i = 0;
	for (const auto & file : std::filesystem::directory_iterator(ThemeFolderPath.c_str())) {
		if (file.path().extension() == ".ini")
		{
			GUI::ThemeFilesArray[i] = new char[file.path().stem().string().length() + 1];
			strcpy(GUI::ThemeFilesArray[i], file.path().stem().string().c_str());
			++i;
		}
	}
}

void Cheat::LoadTheme(char* ThemeFileName, bool StartUp)
{
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	std::string ThemeFilePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + ThemeFileName + ".ini";

	if (!Cheat::CheatFunctions::DoesFileExists(ThemeFilePath)) { Cheat::GameFunctions::MinimapNotification("~r~Failed to load theme: theme file does not exist"); return; }

	Cheat::GUI::CurrentTheme = ThemeFileName;

	std::string TitleBackgroundRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_red");
	std::string TitleBackgroundGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_green");
	std::string TitleBackgroundBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_blue");
	std::string TitleBackgroundOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "title_background_opacity");

	std::string HeaderBackgroundRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_red");
	std::string HeaderBackgroundGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_green");
	std::string HeaderBackgroundBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_blue");
	std::string HeaderBackgroundOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "header_background_opacity");

	std::string SmallTitleBackgroundRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_red");
	std::string SmallTitleBackgroundGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_green");
	std::string SmallTitleBackgroundBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_blue");
	std::string SmallTitleBackgroundOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "small_title_background_opacity");

	std::string OptionTextRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_red");
	std::string OptionTextGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_green");
	std::string OptionTextBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_blue");
	std::string OptionTextOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "option_text_opacity");

	std::string SelectionBoxRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_red");
	std::string SelectionBoxGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_green");
	std::string SelectionBoxBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_blue");
	std::string SelectionBoxOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_opacity");

	std::string SelectionBoxBackgroundRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_red");
	std::string SelectionBoxBackgroundGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_green");
	std::string SelectionBoxBackgroundBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_blue");
	std::string SelectionBoxBackgroundOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "selection_box_background_opacity");

	std::string BottomLineRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_red");
	std::string BottomLineGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_green");
	std::string BottomLineBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_blue");
	std::string BottomLineOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "bottom_line_opacity");

	std::string MenuBottomBackgroundRed = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_red");
	std::string MenuBottomBackgroundGreen = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_green");
	std::string MenuBottomBackgroundBlue = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_blue");
	std::string MenuBottomBackgroundOpacity = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	
	if (SmallTitleBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundRed))) { Cheat::GUI::titleRect.r = std::stoi(SmallTitleBackgroundRed); } } }
	if (SmallTitleBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundGreen))) { Cheat::GUI::titleRect.g = std::stoi(SmallTitleBackgroundGreen); } } }
	if (SmallTitleBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundBlue))) { Cheat::GUI::titleRect.b = std::stoi(SmallTitleBackgroundBlue); } } }
	if (SmallTitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SmallTitleBackgroundOpacity))) { Cheat::GUI::titleRect.a = std::stoi(SmallTitleBackgroundOpacity); } } }
	if (HeaderBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundRed))) { Cheat::GUI::headerRect.r = std::stoi(HeaderBackgroundRed); } } }
	if (HeaderBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundGreen))) { Cheat::GUI::headerRect.g = std::stoi(HeaderBackgroundGreen); } } }
	if (HeaderBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundBlue))) { Cheat::GUI::headerRect.b = std::stoi(HeaderBackgroundBlue); } } }
	if (HeaderBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(HeaderBackgroundOpacity))) { Cheat::GUI::headerRect.a = std::stoi(HeaderBackgroundOpacity); } } }
	if (BottomLineRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineRed))) { Cheat::GUI::TopAndBottomLine.r = std::stoi(BottomLineRed); } } }
	if (BottomLineGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineGreen))) { Cheat::GUI::TopAndBottomLine.g = std::stoi(BottomLineGreen); } } }
	if (BottomLineBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineBlue))) { Cheat::GUI::TopAndBottomLine.b = std::stoi(BottomLineBlue); } } }
	if (BottomLineOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(BottomLineOpacity))) { Cheat::GUI::TopAndBottomLine.a = std::stoi(BottomLineOpacity); } } }
	if (TitleBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundRed))) { Cheat::GUI::MainTitleRect.r = std::stoi(TitleBackgroundRed); } } }
	if (TitleBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundGreen))) { Cheat::GUI::MainTitleRect.g = std::stoi(TitleBackgroundGreen); } } }
	if (TitleBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundBlue))) { Cheat::GUI::MainTitleRect.b = std::stoi(TitleBackgroundBlue); } } }
	if (TitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundOpacity))) { Cheat::GUI::MainTitleRect.a = std::stoi(TitleBackgroundOpacity); } } }
	if (OptionTextRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextRed))) { Cheat::GUI::optionText.r = std::stoi(OptionTextRed); } } }
	if (OptionTextGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextGreen))) { Cheat::GUI::optionText.g = std::stoi(OptionTextGreen); } } }
	if (OptionTextBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextBlue))) { Cheat::GUI::optionText.b = std::stoi(OptionTextBlue); } } }
	if (OptionTextOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(OptionTextOpacity))) { Cheat::GUI::optionText.a = std::stoi(OptionTextOpacity); } } }
	if (TitleBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(TitleBackgroundOpacity))) { Cheat::GUI::MainTitleRect.a = std::stoi(TitleBackgroundOpacity); } } }
	if (SelectionBoxRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxRed))) { Cheat::GUI::scroller.r = std::stoi(SelectionBoxRed); } } }
	if (SelectionBoxGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxGreen))) { Cheat::GUI::scroller.g = std::stoi(SelectionBoxGreen); } } }
	if (SelectionBoxBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBlue))) { Cheat::GUI::scroller.b = std::stoi(SelectionBoxBlue); } } }
	if (SelectionBoxOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxOpacity))) { Cheat::GUI::scroller.a = std::stoi(SelectionBoxOpacity); } } }
	if (SelectionBoxBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundRed))) { Cheat::GUI::MenuBackgroundRect.r = std::stoi(SelectionBoxBackgroundRed); } } }
	if (SelectionBoxBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundGreen))) { Cheat::GUI::MenuBackgroundRect.g = std::stoi(SelectionBoxBackgroundGreen); } } }
	if (SelectionBoxBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundBlue))) { Cheat::GUI::MenuBackgroundRect.b = std::stoi(SelectionBoxBackgroundBlue); } } }
	if (SelectionBoxBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(SelectionBoxBackgroundOpacity))) { Cheat::GUI::MenuBackgroundRect.a = std::stoi(SelectionBoxBackgroundOpacity); } } }
	if (MenuBottomBackgroundRed != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundRed))) { Cheat::GUI::MenuBottomRect.r = std::stoi(MenuBottomBackgroundRed); } } }
	if (MenuBottomBackgroundGreen != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundGreen))) { Cheat::GUI::MenuBottomRect.g = std::stoi(MenuBottomBackgroundGreen); } } }
	if (MenuBottomBackgroundBlue != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundBlue))) { Cheat::GUI::MenuBottomRect.b = std::stoi(MenuBottomBackgroundBlue); } } }
	if (MenuBottomBackgroundOpacity != "NULL") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, std::stoi(MenuBottomBackgroundOpacity))) { Cheat::GUI::MenuBottomRect.a = std::stoi(MenuBottomBackgroundOpacity); } } }

	std::string ScrollDelaySetting = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "scroll_delay"); if (Cheat::CheatFunctions::StringIsInteger(ScrollDelaySetting)) { if (Cheat::CheatFunctions::IsIntegerInRange(1, 200, std::stoi(ScrollDelaySetting))) { Cheat::GUI::keyPressDelay2 = std::stoi(ScrollDelaySetting.c_str()); } }
	std::string IntDelaySetting = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "int_delay"); if (Cheat::CheatFunctions::StringIsInteger(IntDelaySetting)) { if (Cheat::CheatFunctions::IsIntegerInRange(1, 200, std::stoi(IntDelaySetting))) { Cheat::GUI::keyPressDelay3 = std::stoi(IntDelaySetting.c_str()); } }
	std::string BooleanToggleSetting = Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, xorstr_("THEME"), xorstr_("boolean_toggle")); if (Cheat::CheatFunctions::StringIsInteger(BooleanToggleSetting)) { Cheat::CheatFeatures::BoolOptionVectorPosition = std::stoi(BooleanToggleSetting.c_str()); }
	if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_background") == "true") { Cheat::GUI::ShowHeaderBackground = true; }
	if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_gui") == "true") { Cheat::GUI::ShowHeaderGUI = true; } else { Cheat::GUI::ShowHeaderGUI = false; }
	if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "restore_previous_submenu") == "false") { Cheat::GUI::RestorePreviousSubmenu = false; } else { Cheat::GUI::RestorePreviousSubmenu = true; }
	if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "show_header_glare") == "false") { Cheat::GUI::ShowHeaderGlare = false; } else { Cheat::GUI::ShowHeaderGlare = true; }

	try
	{ 
		float X			= std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_x"));
		float Y			= std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_y"));
		float Width		= std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_width"));


		if (Cheat::CheatFunctions::IsIntegerInRange(0.110000, 0.86000, X))
		{
			Cheat::GUI::guiX = std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_x"));
		}

		if (Cheat::CheatFunctions::IsIntegerInRange(0.100000, 0.80000, Y))
		{
			Cheat::GUI::guiY = std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_y"));
		}

		if (Cheat::CheatFunctions::IsIntegerInRange(0.210000, 0.31000, Width))
		{
			Cheat::GUI::guiWidth = std::stod(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "gui_width"));
		}

		Cheat::GUI::maxVisOptions = std::stoi(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "max_vis_options"));
		if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "open_key") != "NULL")
		{
			Cheat::GUI::openKey = std::stoi(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "open_key"));
		}
		if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "cursor_navigation_toggle_key") != "NULL")
		{
			Cheat::GUI::GUINavigationKey = std::stoi(Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "cursor_navigation_toggle_key"));
		}
	}
	catch (...) {}

	//Check Theme File Version
	if (Cheat::CheatFunctions::ReadStringFromIni(ThemeFilePath, "THEME", "theme_file_version") != xorstr_("1.5"))
	{
		DeleteFileA(ThemeFilePath.c_str());
		SaveTheme(ThemeFileName);
		Cheat::GameFunctions::SubtitleNotification("~b~Active theme outdated, it has been resaved to update for the changes", 5000);
	}

	if (!StartUp) { Cheat::GameFunctions::MinimapNotification("Theme Loaded"); }
}


void Cheat::GUI::DeleteCurrentTheme()
{
	std::string ThemeFileNamePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)xorstr_("\\gtav\\Themes\\") + Cheat::GUI::CurrentTheme + xorstr_(".ini");
	if (remove(ThemeFileNamePath.c_str()) != 0) 
	{ 
		Cheat::GameFunctions::MinimapNotification("~r~Failed To Delete Theme File"); 
	}
	else 
	{ 
		Cheat::GUI::CurrentTheme = NULL; 
		GUI::currentOption = 1;
		Cheat::GameFunctions::MinimapNotification("Theme File Removed"); 
	}
}

void Cheat::SaveTheme(char* ThemeFileName)
{
	std::string ThemeFilePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + ThemeFileName + ".ini";
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	if (!Cheat::CheatFunctions::DoesDirectoryExists(Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes")) { Cheat::CheatFunctions::CreateNewDirectory(ThemeFolderPath); }

	Cheat::CheatFunctions::WriteStringToIni(xorstr_("1.5"), ThemeFilePath, "THEME", "theme_file_version");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderBackground, ThemeFilePath, "THEME", "show_header_background");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderGUI, ThemeFilePath, "THEME", "show_header_gui");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::RestorePreviousSubmenu, ThemeFilePath, "THEME", "restore_previous_submenu");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderGlare, ThemeFilePath, "THEME", "show_header_glare");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::guiX), ThemeFilePath, "THEME", "gui_x");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::guiY), ThemeFilePath, "THEME", "gui_y");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::guiWidth), ThemeFilePath, "THEME", "gui_width");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::keyPressDelay2), ThemeFilePath, "THEME", "scroll_delay");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::keyPressDelay3), ThemeFilePath, "THEME", "int_delay");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::maxVisOptions), ThemeFilePath, "THEME", "max_vis_options");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::openKey), ThemeFilePath, "THEME", "open_key");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::GUINavigationKey), ThemeFilePath, "THEME", "cursor_navigation_toggle_key");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::CheatFeatures::BoolOptionVectorPosition), ThemeFilePath, xorstr_("THEME"), xorstr_("boolean_toggle"));

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MainTitleRect.r), ThemeFilePath, "THEME", "title_background_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MainTitleRect.g), ThemeFilePath, "THEME", "title_background_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MainTitleRect.b), ThemeFilePath, "THEME", "title_background_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MainTitleRect.a), ThemeFilePath, "THEME", "title_background_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::headerRect.r), ThemeFilePath, "THEME", "header_background_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::headerRect.g), ThemeFilePath, "THEME", "header_background_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::headerRect.b), ThemeFilePath, "THEME", "header_background_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::headerRect.a), ThemeFilePath, "THEME", "header_background_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::titleRect.r), ThemeFilePath, "THEME", "small_title_background_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::titleRect.g), ThemeFilePath, "THEME", "small_title_background_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::titleRect.b), ThemeFilePath, "THEME", "small_title_background_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::titleRect.a), ThemeFilePath, "THEME", "small_title_background_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::optionText.r), ThemeFilePath, "THEME", "option_text_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::optionText.g), ThemeFilePath, "THEME", "option_text_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::optionText.b), ThemeFilePath, "THEME", "option_text_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::optionText.a), ThemeFilePath, "THEME", "option_text_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::scroller.r), ThemeFilePath, "THEME", "selection_box_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::scroller.g), ThemeFilePath, "THEME", "selection_box_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::scroller.b), ThemeFilePath, "THEME", "selection_box_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::scroller.a), ThemeFilePath, "THEME", "selection_box_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBackgroundRect.r), ThemeFilePath, "THEME", "selection_box_background_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBackgroundRect.g), ThemeFilePath, "THEME", "selection_box_background_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBackgroundRect.b), ThemeFilePath, "THEME", "selection_box_background_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBackgroundRect.a), ThemeFilePath, "THEME", "selection_box_background_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::TopAndBottomLine.r), ThemeFilePath, "THEME", "bottom_line_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::TopAndBottomLine.g), ThemeFilePath, "THEME", "bottom_line_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::TopAndBottomLine.b), ThemeFilePath, "THEME", "bottom_line_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::TopAndBottomLine.a), ThemeFilePath, "THEME", "bottom_line_opacity");

	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBottomRect.r), ThemeFilePath, "THEME", "menu_bottom_background_red");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBottomRect.g), ThemeFilePath, "THEME", "menu_bottom_background_green");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBottomRect.b), ThemeFilePath, "THEME", "menu_bottom_background_blue");
	Cheat::CheatFunctions::WriteStringToIni(std::to_string(Cheat::GUI::MenuBottomRect.a), ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	Cheat::GameFunctions::MinimapNotification(xorstr_("Theme Saved"));
}