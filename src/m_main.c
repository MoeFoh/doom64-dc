/* m_main.c -- menu routines */

#include "doomdef.h"
#include "r_local.h"
#include "st_main.h"

extern int extra_episodes;
extern int kneedeep_only;
//intermission
int DrawerStatus;

//static int button_code_to_symbol_index(u32 code);
static int dc_button_to_symbol(u32 code);
#define CT_TXT00 "default: %d"
#define CT_TXT01 "right"
#define CT_TXT02 "left"
#define CT_TXT03 "forward"
#define CT_TXT04 "backward"
#define CT_TXT05 "attack"
#define CT_TXT06 "use"
#define CT_TXT07 "map"
#define CT_TXT08 "speed"
#define CT_TXT09 "strafe on"
#define CT_TXT10 "strafe left"
#define CT_TXT11 "strafe right"
#define CT_TXT12 "weapon backward"
#define CT_TXT13 "weapon forward"

char *ControlText[] = //8007517C
	{ CT_TXT00, CT_TXT01, CT_TXT02, CT_TXT03, CT_TXT04, CT_TXT05, CT_TXT06,
	  CT_TXT07, CT_TXT08, CT_TXT09, CT_TXT10, CT_TXT11, CT_TXT12, CT_TXT13 };

#define M_TXT00 "Gamepad"
#define M_TXT01 "Volume"
#define M_TXT02 "Video"
#define M_TXT03 "Password"
#define M_TXT04 "Main Menu"
#define M_TXT05 "Restart Level"
#define M_TXT06 "\x90 Return"
#define M_TXT07 "Music Volume"
#define M_TXT08 "Sound Volume"
#define M_TXT09 "Brightness"
#define M_TXT10 "Resume"
#define M_TXT11 "Options"
#define M_TXT12 "Autorun:"
#define M_TXT13 "Defaults" // default for video
#define M_TXT14 "New Game"
#define M_TXT15 "Be Gentle!"
#define M_TXT16 "Bring It On!"
#define M_TXT17 "I Own Doom!"
#define M_TXT18 "Watch Me Die!"
#define M_TXT19 "Be Merciless!"
#define M_TXT20 "Yes"
#define M_TXT21 "No"
#define M_TXT22 "Features"
#define M_TXT23 "WARP TO LEVEL"
#define M_TXT24 "INVULNERABLE"
#define M_TXT25 "HEALTH BOOST"
#define M_TXT26 "SECURITY KEYS"
#define M_TXT27 "WEAPONS"
#define M_TXT28 "Exit"
#define M_TXT29 "DEBUG"
#define M_TXT30 "TEXTURE TEST"
#define M_TXT31 "WALL BLOCKING"
#define M_TXT32 "Center Display"
#define M_TXT33 "Messages:"
#define M_TXT34 "Opacity"
#define M_TXT35 "LOCK MONSTERS"
#define M_TXT36 "SCREENSHOT"
#define M_TXT37 "MAP EVERYTHING"
#define M_TXT38 "MACRO PEEK"
#define M_TXT39 "MUSIC TEST"
#define M_TXT40 "WARP TO FUN"
#define M_TXT41 "Movement"
#define M_TXT42 "Original" // Original default for Doom 64
#define M_TXT43 "Sensitivity"
#define M_TXT44 "Manage VMU"
#define M_TXT45 "Do not use VMU"
#define M_TXT46 "Try again"
#define M_TXT47 "Create game note"

// New additions to Doom 64 RE and Merciless Edition
#define M_TXT48 "COLORS" // [GEC] NEW CHEAT CODE
#define M_TXT49 "FULL BRIGHT" // [GEC] NEW CHEAT CODE
#define M_TXT50 "Filtering:" // [GEC] New video filter option
#define M_TXT51 "Display" // [Immorpher] New menu item
#define M_TXT52 "Motion Bob" // [Immorpher] New menu item
#define M_TXT53 "Dither Filter:" // [Immorpher] Dither Filter
#define M_TXT54 "Anti-Aliasing:" // [Immorpher] New anti-aliasing option
#define M_TXT55 "Interlacing:" // [Immorpher] New interlacing option
#define M_TXT56 "Color Dither:" // [Immorpher] New color dither options
#define M_TXT57 "Flash Brightness" // [Immorpher] New flash brightness option
#define M_TXT58 "Merciless" // [Immorpher] Merciless default settings
#define M_TXT59 "Immorpher" // [Immorpher] Immorpher default settings
#define M_TXT60 \
	"Accessible" // [Immorpher] Increased accessibility default settings
#define M_TXT61 "Story Text:" // [Immorpher] Skip cut scenes
#define M_TXT62 "Map Stats:" // [Immorpher] Display automap statistics
#define M_TXT63 "Status HUD" // [Immorpher] New menu option for HUD elements!
#define M_TXT64 "Margin" // [Immorpher] Adjust the margin for the HUD
#define M_TXT65 "WARP TO MOTHER" // [Immorpher] New features menu warps
#define M_TXT66 "WARP TO SECRET" // [Immorpher] New features menu warps
#define M_TXT67 "Colored:" // [Immorpher] Colored hud
#define M_TXT68 "GAMMA CORRECT" // [Immorpher] NEW CHEAT CODE

// Merciless Edition Credits
#define M_TXT69 "MERCILESS EDITION CREDITS" // [Immorpher] Credits
#define M_TXT70 "MERCILESS PROGRAMMING: IMMORPHER" // [Immorpher] Credits
#define M_TXT71 "REVERSE ENGINEERING: ERICK194" // [Immorpher] Credits
#define M_TXT72 "KAISER" // [Immorpher] Credits
#define M_TXT73 "BODB DEARG" // [Immorpher] Credits
#define M_TXT74 "QUASAR" // [Immorpher] Credits
#define M_TXT75 "COMPILER ASSETS: CRASHOVERIDE" // [Immorpher] Credits
#define M_TXT76 "ALPHATANGO" // [Immorpher] Credits
#define M_TXT77 "PLAY TESTING: SCD, BUU342" // [Immorpher] Credits
#define M_TXT78 "IRL RANDOM HAJILE" // [Immorpher] Credits
#define M_TXT79 "TAUFAN99" // [Immorpher] Credits
#define M_TXT80 "SPECIAL THANKS: GEC TEAM, DOOMWORLD" // [Immorpher] Credits
#define M_TXT81 "DOOM 64 DISCORD" // [Immorpher] Credits
#define M_TXT82 "NEIGH WINNY" // [Immorpher] Credits
#define M_TXT83 "ISANN KEKET" // [Immorpher] Credits
#define M_TXT84 "NEVANDER" // [Immorpher] Credits


#define M_TXT85 "Absolution"
#define M_TXT86 "Lost Levels"
#define M_TXT87 "Knee-Deep\nIn The Dead"

#define M_TXT88 "Quality"
#define M_TXT89 "Low"
#define M_TXT90 "Medium"
#define M_TXT91 "Ultra"

#define M_TXT92 "FPS"
#define M_TXT93 "30"
#define M_TXT94 "Uncapped"

#define M_TXT95 "Rumble:"
#define M_TXT96 "Deadzone:" // Analog stick deadzone

char *MenuText[] = // 8005ABA0
	{
		M_TXT00, M_TXT01, M_TXT02, M_TXT03, M_TXT04, M_TXT05, M_TXT06,
		M_TXT07, M_TXT08, M_TXT09, M_TXT10, M_TXT11, M_TXT12, M_TXT13,
		M_TXT14, M_TXT15, M_TXT16, M_TXT17, M_TXT18, M_TXT19, M_TXT20,
		M_TXT21, M_TXT22, M_TXT23, M_TXT24, M_TXT25, M_TXT26, M_TXT27,
		M_TXT28, M_TXT29, M_TXT30, M_TXT31, M_TXT32, M_TXT33, M_TXT34,
		M_TXT35, M_TXT36, M_TXT37, M_TXT38, M_TXT39, M_TXT40, M_TXT41,
		M_TXT42, M_TXT43, M_TXT44, M_TXT45, M_TXT46, M_TXT47, M_TXT48,
		M_TXT49, M_TXT50, M_TXT51, M_TXT52, M_TXT53, M_TXT54, M_TXT55,
		M_TXT56, M_TXT57, M_TXT58, M_TXT59, M_TXT60, M_TXT61, M_TXT62,
		M_TXT63, M_TXT64, M_TXT65, M_TXT66, M_TXT67, M_TXT68, M_TXT69,
		M_TXT70, M_TXT71, M_TXT72, M_TXT73, M_TXT74, M_TXT75, M_TXT76,
		M_TXT77, M_TXT78, M_TXT79, M_TXT80, M_TXT81, M_TXT82, M_TXT83,
		M_TXT84,
		M_TXT85, M_TXT86, M_TXT87,
		M_TXT88, M_TXT89, M_TXT90, M_TXT91,
		M_TXT92, M_TXT93, M_TXT94, M_TXT95, M_TXT96, ""
	};

#define NUM_MENU_TITLE 3
menuitem_t Menu_Title[NUM_MENU_TITLE] = // 8005A978
	{
		{ 14, 115, 170 }, // New Game
		{ 3, 115, 190 }, // Password
		{ 11, 115, 210 }, // Options
	};

#define NUM_MENU_SKILL 6
menuitem_t Menu_Skill[NUM_MENU_SKILL] = // 8005A990
	{
		{ 15, 102, 70 }, // Be Gentle!
		{ 16, 102, 90 }, // Bring it on!
		{ 17, 102, 110 }, // I own Doom!
		{ 18, 102, 130 }, // Watch me die!
		{ 19, 102, 150 }, // Be merciless!
		{ 6, 102, 180 }, // Return
	};

#define NUM_MENU_EPISODES 3
menuitem_t Menu_Episode[NUM_MENU_EPISODES] =
{
	{ 85, 102, 80 },    // Doom 64
	{ 87, 102, 100},    // Knee-Deep In The Dead
	{ 6, 102, 180 }, // Return
};

#define NUM_MENU_2EPISODES 4
menuitem_t Menu_2Episode[NUM_MENU_2EPISODES] =
{
	{ 85, 102, 80 },    // Doom 64
	{ 86, 102, 100},    // The Lost Levels
	{ 87, 102, 120},    // Knee-Deep In The Dead
	{ 6, 102, 200 }, // Return
};


#define NUM_MENU_OPTIONS 7
menuitem_t Menu_Options[NUM_MENU_OPTIONS] = // 8005A9C0
	{
		{ 0, 112, 60 }, // Gamepad
		{ 41, 112, 80 }, // Movement
		{ 1, 112, 100 }, // Volume
		{ 2, 112, 120 }, // Video
		{ 51, 112, 140 }, // Display
		{ 63, 112, 160 }, // Status HUD
		{ 6, 112, 180 /*200*/ }, // Return
	};

#define NUM_MENU_VOLUME 3
menuitem_t Menu_Volume[NUM_MENU_VOLUME] = // 8005AA08
	{
		{ 7, 82, 60 }, // Music Volume
		{ 8, 82, 100 }, // Sound Volume
		{ 6, 82, 140 }, // Return
	};

#define NUM_MENU_MOVEMENT 6
menuitem_t Menu_Movement[NUM_MENU_MOVEMENT] = // [Immorpher] Movement
	{
		{ 52, 82, 60 }, // Motion Bob
		{ 43, 82, 100 }, // Sensitivity
		{ 96, 82, 140 }, // Deadzone
		{ 12, 82, 160 }, // Autorun
		{ 95, 82, 180 }, // Rumble
		{ 6, 82, 200 }, // Return
	};

#define NUM_MENU_VIDEO 5
menuitem_t Menu_Video[NUM_MENU_VIDEO] = {
	{ 9, 82, 60 }, // Brightness
	{ 50, 82, 100 }, // Video Filter
	{ 88, 82, 120 }, // Quality menu
	{ 92, 82, 140 }, // fps menu
	{ 6, 82, 160 }, // Return
};

#define NUM_MENU_DISPLAY 3
menuitem_t Menu_Display[NUM_MENU_DISPLAY] = // [Immorpher] Display menu
	{
		//    { 57, 82, 60},    	// Flash Brightness
		//    { 32, 82, 100-40},    // Center Display
		{ 61, 82, 120 - 60 }, // Story Text
		{ 62, 82, 140 - 60 }, // Map Stats
		{ 6, 82, 160 - 60 }, // Return
	};

#define NUM_MENU_STATUSHUD 5
menuitem_t Menu_StatusHUD[NUM_MENU_STATUSHUD] = // [Immorpher] Status HUD
	{
		{ 64, 82, 60 }, // Margin
		{ 34, 82, 100 }, // Opacity
		{ 67, 82, 140 }, // Colored HUD
		{ 33, 82, 160 }, // Messages
		{ 6, 82, 180 }, // Return
	};

#define NUM_MENU_GAME 5
menuitem_t Menu_Game[NUM_MENU_GAME] = // 8005AAA4
	{
		{ 3, 122, 60 }, // Password
		{ 11, 122, 80 }, // Options
		{ 4, 122, 100 }, // Main Menu
		{ 5, 122, 120 }, // Restart Level
		{ 22, 122, 140 }, // Features
	};

#define NUM_MENU_QUIT 2
menuitem_t Menu_Quit[NUM_MENU_QUIT] = // 8005AAD4
	{
		{ 20, 142, 100 }, // Yes
		{ 21, 142, 120 }, // No
	};

#define NUM_MENU_DELETENOTE 2
menuitem_t Menu_DeleteNote[NUM_MENU_DELETENOTE] = // 8005AAEC
	{
		{ 20, 142, 100 }, // Yes
		{ 21, 142, 120 }, // No
	};

#define NUM_MENU_CONTROLLERPAKBAD 2
menuitem_t Menu_ControllerPakBad[NUM_MENU_CONTROLLERPAKBAD] = // 8005AB04
	{
		{ 46, 120, 100 }, // Try again
		{ 45, 120, 120 }, // Do not use Pak
	};

#define NUM_MENU_CONTROLLERPAKFULL 3
menuitem_t Menu_ControllerPakFull[NUM_MENU_CONTROLLERPAKFULL] = // 8005AB1C
	{
		{ 44, 110, 90 }, // Manage Pak
		{ 47, 110, 110 }, // Create game note
		{ 45, 110, 130 }, // Do not use Pak
	};


#define NUM_MENU_CREATENOTE 3
menuitem_t Menu_CreateNote[NUM_MENU_CREATENOTE] = // 8005AB40
	{
		{ 20, 110, 90 }, // Yes
		{ 45, 110, 110 }, // Do not use Pak
		{ 44, 110, 130 }, // Manage Pak
	};

//#define MAXFEATURES 5 [Original]
//#define MAXFEATURES 9 [Doom 64 RE]
//#define MAXFEATURES 13
#define NUM_MENU_FEATURES 9
menuitem_t Menu_Features[NUM_MENU_FEATURES] = // 8005AB64
	{
		{ 23, 40, 50 }, // WARP TO LEVEL
		{ 24, 40, 60 }, // INVULNERABLE
		{ 25, 40, 70 }, // HEALTH BOOST
		{ 27, 40, 80 }, // WEAPONS
		{ 37, 40, 90 }, // MAP EVERYTHING
		//
		{ 26, 40, 100 }, // SECURITY KEYS
		{ 31, 40, 110 }, // WALL BLOCKING
		{ 35, 40, 120 }, // LOCK MONSTERS
		{ 39, 40, 130 }, // MUSIC TEST
		//
//		{ 69, 40,
//		  /*180*/ 140 }, // [Immorpher] Merciless Edition Credits
	};

#define NUM_MERCILESS_CREDITS 15
menuitem_t Merciless_Credits[NUM_MERCILESS_CREDITS] = // 8005AB64
	{
		{ 70, 20, 48 }, // Credits

		{ 71, 20, 65 }, // Credits
		{ 72, 188, 75 }, // Credits
		{ 73, 188, 85 }, // Credits
		{ 74, 188, 95 }, // Credits

		{ 75, 20, 112 }, // Credits
		{ 76, 156, 122 }, // Credits

		{ 77, 20, 139 }, // Credits
		{ 78, 133, 149 }, // Credits
		{ 79, 133, 159 }, // Credits

		{ 80, 20, 176 }, // Credits
		{ 81, 148, 186 }, // Credits
		{ 82, 148, 196 }, // Credits
		{ 83, 148, 206 }, // Credits
		{ 84, 148, 216 }, // Credits
	};

menudata_t MenuData[8]; // 800A54F0
int MenuAnimationTic; // 800a5570
int cursorpos; // 800A5574
float f_m_vframe1;
//int m_vframe1; // 800A5578
menuitem_t *MenuItem; // 800A5578
int itemlines; // 800A5580
menufunc_t MenuCall; // 800A5584

int linepos; // 800A5588
int text_alpha_change_value; // 800A558C
int MusicID; // 800A5590
int m_actualmap; // 800A5594
int last_ticon; // 800A5598

skill_t startskill; // 800A55A0
int startmap; // 800A55A4
int EnableExpPak; // 800A55A8

//-----------------------------------------


#define MAX_BRIGHTNESS 127

doom64_settings_t  __attribute__((aligned(32))) menu_settings;

void M_ResetSettings(doom64_settings_t *s) {
	s->version = SETTINGS_SAVE_VERSION;
	s->HUDopacity = 255;
	s->SfxVolume = 45;
	s->MusVolume = 45;
	s->brightness = MAX_BRIGHTNESS;
	s->enable_messages = 1;
	s->M_SENSITIVITY = 27;
	s->MotionBob = 16 << FRACBITS;
	s->Rumble = 0;
	s->VideoFilter = PVR_FILTER_BILINEAR;
	s->Autorun = 1;
	s->StoryText = 1;
	s->MapStats = 1;
	s->HUDmargin = 20;
	s->ColoredHUD = 0;
	s->Quality = 2;
	s->FpsUncap = 1;
	s->PlayDeadzone = 0;

	if (I_CheckControllerPak() == 0) {
		I_ReadPakSettings();
	}

	s->runintroduction = 0;
}

int MenuIdx = 0; // 8005A7A4
int text_alpha = 255; // 8005A7A8
int ConfgNumb = 0; // 8005A7AC
int Display_X = 0; // 8005A7B0
int Display_Y = 0; // 8005A7B4
const boolean FeaturesUnlocked = true; // 8005A7D0
int force_filter_flush = 0;
int FlashBrightness = 16; // [Immorpher] Strobe brightness adjustment, will need to change to float

int __attribute__((aligned(16))) ActualConfiguration[13] = // 8005A840
	{ PAD_RIGHT,   PAD_LEFT, PAD_UP,     PAD_DOWN,	 PAD_Z_TRIG,
	  PAD_RIGHT_C, PAD_UP_C, PAD_LEFT_C, PAD_DOWN_C, PAD_L_TRIG,
	  PAD_R_TRIG,  PAD_A,	 PAD_B };

int __attribute__((aligned(16)))
CustomConfiguration[13] = { PAD_RIGHT,	PAD_LEFT,    PAD_UP,	 PAD_DOWN,
			    PAD_Z_TRIG, PAD_RIGHT_C, PAD_UP_C,	 PAD_LEFT_C,
			    PAD_DOWN_C, PAD_L_TRIG,  PAD_R_TRIG, PAD_A,
			    PAD_B };

int __attribute__((aligned(16))) DefaultConfiguration[1][13] = // 8005A840
	{
		// Default 1
		{ PAD_RIGHT, PAD_LEFT, PAD_UP, PAD_DOWN, PAD_Z_TRIG,
		  PAD_RIGHT_C, PAD_UP_C, PAD_LEFT_C, PAD_DOWN_C, PAD_L_TRIG,
		  PAD_R_TRIG, PAD_A, PAD_B }
	};

//-----------------------------------------

extern void P_FlushAllCached(void);
int from_menu = 1;
int in_menu = 1;
int M_RunTitle(void) // 80007630
{
	int exit;
	P_FlushAllCached();
	DrawerStatus = 0;
	startskill = sk_easy;
	startmap = 1;

	MenuIdx = 0;
	MenuItem = Menu_Title;
	MenuCall = M_MenuTitleDrawer;
	text_alpha = 0;
	itemlines = NUM_MENU_TITLE;
	cursorpos = 0;
	last_ticon = 0;
	from_menu = 1;
	S_StartMusic(116);
	from_menu = 0;
	exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker,
			M_MenuGameDrawer);

	I_WIPE_FadeOutScreen();
	S_StopMusic();

	if (exit == ga_timeout)
		return ga_timeout;

	G_InitNew(startskill, startmap, (gametype_t)ga_nothing);
	G_RunGame();

	return 0;
}



int M_ControllerPak(void) // 80007724
{
    int exit;
    int ret;
    boolean PakBad;

    PakBad = false;

    while(1)
    {
        ret = I_CheckControllerPak();

        if ((ret != PFS_ERR_NOPACK)) //&& (ret != PFS_ERR_ID_FATAL))
            PakBad = true;

        if(ret == 0)
        {
            ret = I_ReadPakFile();

            // Free Pak_Data
            if (Pak_Data)
            {
                Z_Free(Pak_Data);
                Pak_Data = NULL;
            }

            if(ret == 0)
            {
                exit = ga_nothing;
                break;
            }

            // Create Controller Pak Note
            MenuItem = Menu_CreateNote;
            itemlines = NUM_MENU_CREATENOTE;
            MenuCall = M_MenuTitleDrawer;
            cursorpos = 0;

            MiniLoop(M_FadeInStart, NULL, M_MenuTicker, M_MenuGameDrawer);
            M_FadeOutStart(8);

            if (cursorpos != 0)
            {
                exit = ga_exit;
                break;
            }

            // Check Memory and Files Used on Controller Pak
            if ((Pak_Memory > 0) && (FilesUsed != 200))
            {
                if (I_CreatePakFile() != 0)
                    goto ControllerPakBad;

                exit = ga_nothing;
                break;
            }

            // Show Controller Pak Full
            MenuItem = Menu_ControllerPakFull;
            itemlines = NUM_MENU_CONTROLLERPAKFULL;
            MenuCall = M_MenuTitleDrawer;
            cursorpos = 0;

            MiniLoop(M_FadeInStart, NULL, M_MenuTicker, M_MenuGameDrawer);
            M_FadeOutStart(8);

            if (cursorpos != 1)
            {
                exit = ga_exit;
                break;
            }
        }
        else
        {
            if (PakBad == false)
            {
                exit = ga_exit;
                break;
            }

            // Show Controller Pak Bad
        ControllerPakBad:
            MenuItem = Menu_ControllerPakBad;
            itemlines = NUM_MENU_CONTROLLERPAKBAD;
            MenuCall = M_MenuTitleDrawer;
            cursorpos = 0;

            MiniLoop(M_FadeInStart, NULL, M_MenuTicker, M_MenuGameDrawer);
            M_FadeOutStart(8);

            if (cursorpos != 0)
            {
                exit = ga_exit;
                break;
            }
        }
    }

    return exit;
}

#define MAXSENSITIVITY 20

int M_ButtonResponder(int buttons) // 80007960
{
	int sensitivity;
	int NewButtons;

	/* Copy Default Buttons */
	NewButtons = (buttons);

	/* Analyze Analog Stick (up / down) */
	sensitivity = (int)((buttons) << 24) >> 24;

	if (sensitivity <= -MAXSENSITIVITY)
		NewButtons |= PAD_DOWN;
	else if (sensitivity >= MAXSENSITIVITY)
		NewButtons |= PAD_UP;

	/* Analyze Analog Stick (left / right) */
	sensitivity = (int)(((buttons & 0xff00) >> 8) << 24) >> 24;

	if (sensitivity <= -MAXSENSITIVITY)
		NewButtons |= PAD_LEFT;
	else if (sensitivity >= MAXSENSITIVITY)
		NewButtons |= PAD_RIGHT;

	return NewButtons & 0xffff0000;
}

void M_AlphaInStart(void) // 800079E0
{
	text_alpha = 0;
	text_alpha_change_value = 20;
}

void M_AlphaOutStart(void) // 800079F8
{
	text_alpha = 255;
	text_alpha_change_value = -20;
}

int M_AlphaInOutTicker(void) // 80007A14
{
	static int last_f_gametic = 0;

//	if ((gamevbls < gametic) && ((gametic & 3) == 0)) {
	if (((int)f_gamevbls < (int)f_gametic) && (((int)f_gametic & 3) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
	}

	text_alpha += text_alpha_change_value;
	if (text_alpha_change_value < 0) {
		if (text_alpha < 0) {
			text_alpha = 0;
			return 8;
		}
	} else {
		if ((text_alpha_change_value > 0) && (text_alpha >= 256)) {
			text_alpha = 255;
			return 8;
		}
	}

	return 0;
}

void M_FadeInStart(void) // 80007AB4
{
	MiniLoop(M_AlphaInStart, NULL, M_AlphaInOutTicker, M_MenuGameDrawer);
}

void M_FadeOutStart(int exitmode) // 80007AEC
{
	if (exitmode == 8)
		MiniLoop(M_AlphaOutStart, NULL, M_AlphaInOutTicker,
			 M_MenuGameDrawer);
}

void M_SaveMenuData(void) // 80007B2C
{
	menudata_t *mdat;

	// Save Actual Menu Page
	mdat = &MenuData[MenuIdx];
	MenuIdx += 1;

	mdat->menu_item = MenuItem;
	mdat->item_lines = itemlines;
	mdat->menu_call = MenuCall;
	mdat->cursor_pos = cursorpos;

	// Start Menu Fade Out
	MiniLoop(M_AlphaOutStart, NULL, M_AlphaInOutTicker, M_MenuGameDrawer);
}

void M_RestoreMenuData(boolean alpha_in) // 80007BB8
{
	menudata_t *mdat;

	// Restore Previous Save Menu Page
	MenuIdx -= 1;
	mdat = &MenuData[MenuIdx];

	MenuItem = mdat->menu_item;
	itemlines = mdat->item_lines;
	MenuCall = mdat->menu_call;
	cursorpos = mdat->cursor_pos;
	// Start Menu Fade In
	if (alpha_in)
		MiniLoop(M_AlphaInStart, NULL, M_AlphaInOutTicker,
			 M_MenuGameDrawer);
}

void M_MenuGameDrawer(void)
{
	if (DrawerStatus == 1) {
		P_Drawer();
	} else if (DrawerStatus == 2) {
		F_DrawerIntermission();
	} else if (DrawerStatus == 3) {
		F_Drawer();
	} else {
		I_ClearFrame();

		M_DrawBackground(56, 57, 80, "TITLE", 8.999999, 0);

		if (MenuItem != Menu_Title) {
			M_DrawOverlay(0, 0, 320, 240, 96);
		}

		MenuCall();
		I_DrawFrame();
	}
}

extern mobj_t mobjhead;
extern mapthing_t *spawnlist;
extern int spawncount;
extern int gobalcheats;

int M_MenuTicker(void)
{
	static int last_f_gametic = 0;
	unsigned int buttons, oldbuttons;
	int exit;
	int truebuttons;
	int ret;
	int i;
	mobj_t *m;

	/* animate skull */
//	if ((gamevbls < gametic) && ((gametic & 3U) == 0))
	if (((int)f_gamevbls < (int)f_gametic) && (((int)f_gametic & 3U) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
	}

	buttons = M_ButtonResponder(ticbuttons[0]);
	oldbuttons = oldticbuttons[0] & 0xffff0000;

	/* exit menu if button press */
	if (buttons != 0)
		last_ticon = ticon;

	/* exit menu if time out */
	if ((MenuItem == Menu_Title) &&
	    ((ticon - last_ticon) >= 900)) // 30 * TICRATE
	{
		exit = ga_timeout;
	} else {
		/* check for movement */
		if (!(buttons & (PAD_Z_TRIG | ALL_JPAD)))
			f_m_vframe1 = 0.0f;
		else {
			f_m_vframe1 = f_m_vframe1 - f_vblsinframe[0];
			if (f_m_vframe1 <= 0.0f) {
				f_m_vframe1 = (float)(TICRATE / 2);

				if (buttons & PAD_DOWN) {
					cursorpos += 1;

					if (cursorpos >= itemlines)
						cursorpos = 0;

					S_StartSound(NULL, sfx_switch1);
				} else if (buttons & PAD_UP) {
					cursorpos -= 1;

					if (cursorpos < 0)
						cursorpos = itemlines - 1;

					S_StartSound(NULL, sfx_switch1);
				}
			}
		}

		if ((buttons & PAD_START) && !(oldticbuttons[0] & PAD_START)) {
			if ((MenuItem == Menu_Title) ||
			    (MenuItem == Menu_ControllerPakBad) ||
			    (MenuItem == Menu_CreateNote) ||
			    (MenuItem == Menu_ControllerPakFull)) {
				return ga_nothing;
			} else {

				if (MenuIdx != 0)
					S_StartSound(NULL, sfx_pistol);

				return ga_exit;
			}
		} else {
			truebuttons = (0 < (buttons ^ oldbuttons));

			if (truebuttons)
				truebuttons = (0 < (buttons & ALL_BUTTONS));

			switch (MenuItem[cursorpos].casepos) {
			case 0: // Gamepad
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuCall = M_ControlPadDrawer;
					cursorpos = 0;
					linepos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_ControlPadTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);
					return ga_nothing;
				}
				break;

			case 1: // Volume
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Volume;
					itemlines = NUM_MENU_VOLUME;
					MenuCall = M_VolumeDrawer;
					cursorpos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_MenuTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);
					return ga_nothing;
				}
				break;

			case 2: // Video
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Video;
					itemlines = NUM_MENU_VIDEO;
					MenuCall = M_VideoDrawer;
					cursorpos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_MenuTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);
					return ga_nothing;
				}
				break;

			case 3: // Password
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					ret = I_CheckControllerPak();
					exit = ga_exit;

					if (ret == 0) {
						if (I_ReadPakFile() == 0) {
							EnableExpPak = 1;
							MenuCall =
								M_LoadPakDrawer;
							exit = MiniLoop(
								M_LoadPakStart,
								M_LoadPakStop,
								M_LoadPakTicker,
								M_MenuGameDrawer);
						} else
							exit = ga_exit;
					}

					if (exit == ga_exit) {
						MenuCall = M_PasswordDrawer;
						exit = MiniLoop(
							M_PasswordStart,
							M_PasswordStop,
							M_PasswordTicker,
							M_MenuGameDrawer);
					}

					if (exit == ga_exit) {
						M_RestoreMenuData(true);
						return ga_nothing;
					}

					if (EnableExpPak != 0) {
						return exit;
					}

					EnableExpPak = (M_ControllerPak() == 0);
					return exit;
				}
				break;

			case 4: // Main Menu
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Quit;
					itemlines = NUM_MENU_QUIT;
					MenuCall = M_MenuTitleDrawer;
					cursorpos = 1;

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_MenuTicker,
							M_MenuGameDrawer);
					M_RestoreMenuData((exit == ga_exit));

					// have to exit eventually, good enough place to hook this
					I_SavePakSettings();

					if (exit == ga_exit) {
						return ga_nothing;
					}
					return 5; //ga_exitdemo;
				}
				break;

			case 5: // [Immorpher] Updated Restart Level
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Skill;
					itemlines = NUM_MENU_SKILL;
					MenuCall = M_MenuTitleDrawer;
					cursorpos =
						gameskill; // Set default to current difficulty

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_MenuTicker,
							M_MenuGameDrawer);

					if (exit == ga_exit &&
					    cursorpos ==
						    5) { // [Immorpher] 5th to exit menu
						M_RestoreMenuData(
							(exit == ga_exit));
						return ga_nothing;
					}

					gameskill = cursorpos;

					startmap = gamemap;
					startskill = gameskill;
					G_InitSkill(
						gameskill); // [Immorpher] initialize new skill

					return ga_warped;
				}
				break;

			case 6: // Return
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					// have to exit eventually, good enough place to hook this
					I_SavePakSettings();
					return ga_exit;
				}
				break;

			case 7: // Music Volume
				if (buttons & PAD_RIGHT) {
					menu_settings.MusVolume += 1;
					if (menu_settings.MusVolume <= 100) {
						S_SetMusicVolume(menu_settings.MusVolume);
						if (menu_settings.MusVolume & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.MusVolume = 100;
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.MusVolume -= 1;
					if (menu_settings.MusVolume < 0) {
						menu_settings.MusVolume = 0;
					} else {
						S_SetMusicVolume(menu_settings.MusVolume);
						if (menu_settings.MusVolume & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 8: // Sound Volume
				if (buttons & PAD_RIGHT) {
					menu_settings.SfxVolume += 1;
					if (menu_settings.SfxVolume <= 75) {
						S_SetSoundVolume(menu_settings.SfxVolume);
						if (menu_settings.SfxVolume & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.SfxVolume = 75;
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.SfxVolume -= 1;
					if (menu_settings.SfxVolume < 0) {
						menu_settings.SfxVolume = 0;
					} else {
						S_SetSoundVolume(menu_settings.SfxVolume);
						if (menu_settings.SfxVolume & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 9: // Brightness
				if (buttons & PAD_RIGHT) {
					menu_settings.brightness += 1;
					if (menu_settings.brightness <= MAX_BRIGHTNESS) {
						P_RefreshBrightness();
						if (menu_settings.brightness & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.brightness = MAX_BRIGHTNESS;
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.brightness -= 1;
					if (menu_settings.brightness < 0) {
						menu_settings.brightness = 0;
					} else {
						P_RefreshBrightness();
						if (menu_settings.brightness & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 11: // Options
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Options;
					itemlines = NUM_MENU_OPTIONS;
					MenuCall = M_MenuTitleDrawer;
					cursorpos = 0;

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_MenuTicker,
							M_MenuGameDrawer);
					M_RestoreMenuData((exit == ga_exit));

					// have to exit eventually, good enough place to hook this
					I_SavePakSettings();

					if (exit == ga_exit)
						return ga_nothing;

					return exit;
				}
				break;

			case 12: // Autorun
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					menu_settings.Autorun ^= true;
					return ga_nothing;
				}
				break;

			case 14: // New Game
				if (truebuttons)
				{
					// Check ControllerPak
                    EnableExpPak = (M_ControllerPak() == 0);

					if (extra_episodes) {
						S_StartSound(NULL, sfx_pistol);
						M_SaveMenuData();

						if (extra_episodes == 1) {
							MenuItem = Menu_Episode;
							itemlines = NUM_MENU_EPISODES;
						} else {
							MenuItem = Menu_2Episode;
							itemlines = NUM_MENU_2EPISODES;
						}
						MenuCall = M_MenuTitleDrawer;
						cursorpos = 0;

						exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker, M_MenuGameDrawer);
						M_RestoreMenuData((exit == ga_exit));

						if (exit == ga_exit)
							return ga_nothing;

						return exit;
					} else {
						startmap = 1;

						S_StartSound(NULL, sfx_pistol);
						M_SaveMenuData();

						MenuItem = Menu_Skill;
						itemlines = NUM_MENU_SKILL;
						MenuCall = M_MenuTitleDrawer;
						cursorpos = 2;

						exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker, M_MenuGameDrawer);
						M_RestoreMenuData((exit == ga_exit));

						if (exit == ga_exit)
							return ga_nothing;

						nextmap = 1;			// [Immorpher] For running introduction for Doom 64
						menu_settings.runintroduction = true; // [Immorpher] turn introduction on

						return exit;
					}
				}
				break;

			case 15: // Be Gentle!
			case 16: // Bring it on!
			case 17: // I own Doom!
			case 18: // Watch me die!
			case 19: // Be merciless!
				if (truebuttons) {
						startskill = MenuItem[cursorpos].casepos - 15;
						S_StartSound(NULL, sfx_pistol);
						return ga_restart;
				}
				break;

			case 20: // Yes
			case 46: // Try again
			case 47: // Create game note
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					return 5; //ga_exitdemo;
				}
				break;

			case 21: // No
			case 45: // Do not use Pak
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					return ga_exit;
				}
				break;

			case 22: // Features
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					players[0].cheats &= 0xffff1fff;

					MenuItem = Menu_Features;
					itemlines = NUM_MENU_FEATURES;
					MenuCall = M_FeaturesDrawer;
					cursorpos = 0;
					m_actualmap = gamemap;

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_MenuTicker,
							M_MenuGameDrawer);
					M_RestoreMenuData((exit == 8));

					if (exit == 8)
						return ga_nothing;

					return exit;
				}
				break;

			case 23: // WARP TO LEVEL
				if (buttons ^ oldbuttons) {
					if (buttons & PAD_LEFT) {
						m_actualmap -= 1;

						if (kneedeep_only) {
							if (m_actualmap > 33 && m_actualmap < 41) {
								m_actualmap = 33;
							}
						}


						if (m_actualmap < 1) {
							m_actualmap = 1;
						} 
						return ga_nothing;
					} else if (buttons & PAD_RIGHT) {
						m_actualmap += 1;

						if (kneedeep_only) {
							if (m_actualmap > 33 && m_actualmap < 41) {
								m_actualmap = 41;
							}
						}

						if (extra_episodes) {
							if (m_actualmap > 49) {
								m_actualmap = 49;
							}
						} else if (m_actualmap > ABS_LASTLEVEL) {
							m_actualmap = ABS_LASTLEVEL;
						}

						return ga_nothing;
					} else if (truebuttons) {
						gamemap = m_actualmap;
						startmap = m_actualmap;
						return ga_warped;
					}
				}
				break;

			case 24: // INVULNERABLE
				if (((gamemap != 32) & truebuttons)) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats ^= CF_GODMODE;
					return ga_nothing;
				}
				break;

			case 25: // HEALTH BOOST
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats |= CF_HEALTH;
					players[0].health = 100;
					players[0].mo->health = 100;
					return ga_nothing;
				}
				break;

			case 26: // SECURITY KEYS
				/* Not available in the release code */
				/*
                    Reconstructed code based on Psx Doom
                    */
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats |= CF_ALLKEYS;

					for (m = mobjhead.next; m != &mobjhead;
					     m = m->next) {
						switch (m->type) {
						case MT_ITEM_BLUECARDKEY:
							players[0].cards
								[it_bluecard] =
								true;
							break;
						case MT_ITEM_REDCARDKEY:
							players[0].cards
								[it_redcard] =
								true;
							break;
						case MT_ITEM_YELLOWCARDKEY:
							players[0].cards
								[it_yellowcard] =
								true;
							break;
						case MT_ITEM_YELLOWSKULLKEY:
							players[0].cards
								[it_yellowskull] =
								true;
							break;
						case MT_ITEM_REDSKULLKEY:
							players[0].cards
								[it_redskull] =
								true;
							break;
						case MT_ITEM_BLUESKULLKEY:
							players[0].cards
								[it_blueskull] =
								true;
							break;
						default:
							break;
						}
					}

					for (i = 0; i < spawncount; i++) {
						switch (spawnlist[i].type) {
						case 5:
							players[0].cards
								[it_bluecard] =
								true;
							break;
						case 13:
							players[0].cards
								[it_redcard] =
								true;
							break;
						case 6:
							players[0].cards
								[it_yellowcard] =
								true;
							break;
						case 39:
							players[0].cards
								[it_yellowskull] =
								true;
							break;
						case 38:
							players[0].cards
								[it_redskull] =
								true;
							break;
						case 40:
							players[0].cards
								[it_blueskull] =
								true;
							break;
						default:
							break;
						}
					}

					return ga_nothing;
				}
				break;

			case 27: // WEAPONS
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats |= CF_WEAPONS;

					for (i = 0; i < NUMWEAPONS; i++) {
						players[0].weaponowned[i] =
							true;
					}

					for (i = 0; i < NUMAMMO; i++) {
						players[0].ammo[i] =
							players[0].maxammo[i];
					}

					return ga_nothing;
				}
				break;

			case 28: // Exit
				/* nothing special */
				break;


			case 31: // WALL BLOCKING
				/* Not available in the release code */
				/*
                    In my opinion it must have been the NOCLIP cheat code
                    */
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats ^= CF_WALLBLOCKING;
					players[0].mo->flags ^= MF_NOCLIP;
					return ga_nothing;
				}
				break;

			case 33: // Messages
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					menu_settings.enable_messages ^= true;
					return ga_nothing;
				}
				break;

			case 34: // [Immorpher] HUD opacity
				if (buttons & PAD_RIGHT) {
					menu_settings.HUDopacity += 4;
					if (menu_settings.HUDopacity <= 255) {
						if (menu_settings.HUDopacity & 4) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.HUDopacity = 255;
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.HUDopacity -= 4;
					if (menu_settings.HUDopacity < 0) {
						menu_settings.HUDopacity = 0;
					} else {
						if (menu_settings.HUDopacity & 4) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 35: // LOCK MONSTERS
				/* Not available in the release code */
				/*
                    Reconstructed code based on Doom 64 Ex
                    */
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats ^= CF_LOCKMOSTERS;
					return ga_nothing;
				}
				break;

			case 37: // MAP EVERYTHING
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					players[0].cheats ^= CF_ALLMAP;
					return ga_nothing;
				}
				break;

			case 39: // MUSIC TEST
				/* Not available in the release code */
				/*
                    Reconstructed code in my interpretation
                    */
				if (buttons ^ oldbuttons) {
					if (buttons & PAD_LEFT) {
						MusicID -= 1;
						if (MusicID > 0) {
							S_StartSound(
								NULL,
								sfx_switch2);
							return ga_nothing;
						}
						MusicID = 1;
					} else if (buttons & PAD_RIGHT) {
						MusicID += 1;
						if (MusicID < 25) {
							S_StartSound(
								NULL,
								sfx_switch2);
							return ga_nothing;
						}
						MusicID = 24;
					} else if (truebuttons) {
						S_StopMusic();
						from_menu = 1;
						S_StartMusic(MusicID + 92);
						from_menu = 0;
						return ga_nothing;
					}
				}
				break;

			case 41: // Control Stick
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Movement;
					itemlines = NUM_MENU_MOVEMENT;
					MenuCall = M_MovementDrawer;
					cursorpos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_MenuTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);

					return ga_nothing;
				}
				break;

			case 43: // Sensitivity
				if (buttons & PAD_RIGHT) {
					menu_settings.M_SENSITIVITY += 1;
					if (menu_settings.M_SENSITIVITY <= 127) {
						if (menu_settings.M_SENSITIVITY & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.M_SENSITIVITY = 127;
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.M_SENSITIVITY -= 1;
					if (menu_settings.M_SENSITIVITY < 0) {
						menu_settings.M_SENSITIVITY = 0;
					} else {
						if (menu_settings.M_SENSITIVITY & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 44: // Manage Pak
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuCall = M_ControllerPakDrawer;
					linepos = 0;
					cursorpos = 0;

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_ScreenTicker,
							M_MenuGameDrawer);
					M_RestoreMenuData((exit == 8));

					if (exit == 8)
						return ga_nothing;

					return exit;
				}
				break;

			case 50: // [GEC and Immorpher] Video filtering mode
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					if (menu_settings.VideoFilter == PVR_FILTER_BILINEAR) {
						menu_settings.VideoFilter = PVR_FILTER_NONE;
					} else {
						menu_settings.VideoFilter = PVR_FILTER_BILINEAR;
					}
					force_filter_flush = 1;
					return ga_nothing;
				}
				break;

			case 51: // Display
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Display;
					itemlines = NUM_MENU_DISPLAY;
					MenuCall = M_DisplayDrawer;
					cursorpos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_MenuTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);
					return ga_nothing;
				}
				break;

			case 52: // Motion Bob
				if (buttons & PAD_RIGHT) {
					menu_settings.MotionBob += 0x8000; // increments 1/2 fixed point
					if (menu_settings.MotionBob <=
					    0x100000) // Maximum is 16 fixed point
					{
						if (menu_settings.MotionBob & 0x8000) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.MotionBob =
							0x100000; // The Limit
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.MotionBob -= 0x8000; // decrements 1/2 fixed point
					if (menu_settings.MotionBob < 0x0) {
						menu_settings.MotionBob = 0x0;
					} else {
						if (menu_settings.MotionBob & 0x8000) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

#if 0
			case 57: // Flash Brightness
				if (buttons & PAD_RIGHT) {
					FlashBrightness += 1; // increments
					if (FlashBrightness <=
					    32) // Maximum is 32
					{
						if (FlashBrightness & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						FlashBrightness =
							32; // The Limit
					}
				} else if (buttons & PAD_LEFT) {
					FlashBrightness -= 1; // decrements
					if (FlashBrightness < 0) {
						FlashBrightness = 0;
					} else {
						if (FlashBrightness & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;
#endif

			case 61: // [Immorpher] Story Text
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					menu_settings.StoryText ^= true;
					return ga_nothing;
				}
				break;

			case 62: // [Immorpher] Map stats
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					menu_settings.MapStats ^= true;
					return ga_nothing;
				}
				break;

			case 63: // [Immorpher] Status HUD
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_StatusHUD;
					itemlines = NUM_MENU_STATUSHUD;
					MenuCall = M_StatusHUDDrawer;
					cursorpos = 0;

					MiniLoop(M_FadeInStart, M_FadeOutStart,
						 M_MenuTicker,
						 M_MenuGameDrawer);
					M_RestoreMenuData(true);
					return ga_nothing;
				}
				break;

			case 64: // HUDmargin
				if (buttons & PAD_RIGHT) {
					menu_settings.HUDmargin += 1; // increments
					if (menu_settings.HUDmargin <= 20) // Maximum is 20
					{
						if (menu_settings.HUDmargin & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					} else {
						menu_settings.HUDmargin = 20; // The Limit
					}
				} else if (buttons & PAD_LEFT) {
					menu_settings.HUDmargin -= 1; // decrements
					if (menu_settings.HUDmargin < 0) {
						menu_settings.HUDmargin = 0;
					} else {
						if (menu_settings.HUDmargin & 1) {
							S_StartSound(
								NULL,
								sfx_secmove);
							return ga_nothing;
						}
					}
				}
				break;

			case 67: // [Immorpher] Colored HUD
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					menu_settings.ColoredHUD ^= true;
					return ga_nothing;
				}
				break;

#if 0
			// TODO FIXME
			case 69: // Credits
				if (truebuttons) {
					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Merciless_Credits;
					itemlines = NUM_MERCILESS_CREDITS;
					MenuCall = M_CreditsDrawer;
					cursorpos = 0;

					exit = MiniLoop(M_FadeInStart,
							M_FadeOutStart,
							M_MenuTicker,
							M_MenuGameDrawer);
					M_RestoreMenuData((exit == 8));

					if (exit == 8)
						return ga_nothing;

					return exit;
				}
				break;
#endif
			case 85:
				if (truebuttons) {
					startmap = 1;

					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Skill;
					itemlines = NUM_MENU_SKILL;
					MenuCall = M_MenuTitleDrawer;
					cursorpos = 2;

					exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker, M_MenuGameDrawer);
					M_RestoreMenuData((exit == ga_exit));

					if (exit == ga_exit)
						return ga_nothing;

					nextmap = 1;			// [Immorpher] For running introduction for Doom 64
					menu_settings.runintroduction = true; // [Immorpher] turn introduction on

					return exit;
				}
				break;

			case 86:
				if (truebuttons) {
					startmap = 34;

					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Skill;
					itemlines = NUM_MENU_SKILL;
					MenuCall = M_MenuTitleDrawer;
					cursorpos = 2;

					exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker, M_MenuGameDrawer);
					M_RestoreMenuData((exit == ga_exit));

					if (exit == ga_exit)
						return ga_nothing;

					nextmap = LOSTLEVEL;	// [Immorpher] For running introduction for Lost Levels
					menu_settings.runintroduction = true; // [Immorpher] turn introduction on

					return exit;
				}
				break;

			case 87:
				if (truebuttons) {
					startmap = 41;

					S_StartSound(NULL, sfx_pistol);
					M_SaveMenuData();

					MenuItem = Menu_Skill;
					itemlines = NUM_MENU_SKILL;
					MenuCall = M_MenuTitleDrawer;
					cursorpos = 2;

					exit = MiniLoop(M_FadeInStart, M_MenuClearCall, M_MenuTicker, M_MenuGameDrawer);
					M_RestoreMenuData((exit == ga_exit));

					if (exit == ga_exit)
						return ga_nothing;

					nextmap = 41;			// [Immorpher] For running introduction for Lost Levels
					menu_settings.runintroduction = true; // [Immorpher] turn introduction on

					return exit;
				}
				break;

			case 88: // Quality mode
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					if (global_render_state.quality == 0) {
						global_render_state.quality = 1;
						menu_settings.Quality = 1;
					} else if (global_render_state.quality == 1) {
						global_render_state.quality = 2;
						menu_settings.Quality = 2;
					} else if (global_render_state.quality == 2) {
						global_render_state.quality = 0;
						menu_settings.Quality = 0;
					}
					return ga_nothing;
				}
				break;

			case 92: // FPS cap
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					if (global_render_state.fps_uncap == 0) {
						global_render_state.fps_uncap = 1;
						menu_settings.FpsUncap = 1;
					} else if (global_render_state.fps_uncap == 1) {
						global_render_state.fps_uncap = 0;
						menu_settings.FpsUncap = 0;
					}
					return ga_nothing;
				}
				break;

			case 95:
				if (truebuttons) {
					S_StartSound(NULL, sfx_switch2);
					if (menu_settings.Rumble == 0) {
						menu_settings.Rumble = 1;
					} else if (menu_settings.Rumble == 1) {
						menu_settings.Rumble = 0;
					}
					return ga_nothing;
				}
				break;
				
			case 96: // Analog Stick Deadzone
				if ((buttons ^ oldbuttons) && (buttons & PAD_RIGHT)) {
					if (menu_settings.PlayDeadzone < 14) {
						menu_settings.PlayDeadzone += 2;
						S_StartSound(NULL, sfx_switch2);
						return ga_nothing;
					}
				} else if ((buttons ^ oldbuttons) && (buttons & PAD_LEFT)) {
					if (menu_settings.PlayDeadzone > 0) {
						menu_settings.PlayDeadzone -= 2;
						S_StartSound(NULL, sfx_switch2);
						return ga_nothing;
					}
				}
				break;

			}
			exit = ga_nothing;
		}
	}
	return exit;
}

void M_MenuClearCall(void) // 80008E6C
{
	MenuCall = NULL;
}

void M_MenuTitleDrawer(void) // 80008E7C
{
	menuitem_t *item = MenuItem;
	int i;
	if (MenuItem == Menu_Game) {
		ST_DrawString(-1, 20, "Pause", text_alpha | 0xc0000000,1);
		ST_DrawString(-1, 200, "press \x8d to resume",
			      text_alpha | 0xffffff00,1);
	} else if (MenuItem == Menu_Skill) {
		ST_DrawString(-1, 20, "Choose Your Skill...",
			      text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_Options) {
		ST_DrawString(-1, 20, "Options", text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_Quit) {
		ST_DrawString(-1, 20, "Quit Game?", text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_DeleteNote) {
		ST_DrawString(-1, 20, "Delete Game Note?",
			      text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_ControllerPakBad) {
		ST_DrawString(-1, 20, "VMU Bad",
			      text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_ControllerPakFull) {
		ST_DrawString(-1, 20, "VMU Full",
			      text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_CreateNote) {
		ST_DrawString(-1, 20, "Create Game Note?",
			      text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_Episode) {
		ST_DrawString(-1, 20, "Choose Campaign", text_alpha | 0xc0000000,1);
	} else if (MenuItem == Menu_2Episode) {
		ST_DrawString(-1, 20, "Choose Campaign", text_alpha | 0xc0000000,1);
	}

	for (i = 0; i < itemlines; i++) {
		ST_DrawString(item->x, item->y, MenuText[item->casepos],
			      text_alpha | 0xc0000000,1);
		item++;
	}

	ST_DrawSymbol(MenuItem[0].x - 37, MenuItem[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);
}

void M_FeaturesDrawer(void) // 800091C0
{
	char *text, textbuff[256];
	menuitem_t *item = MenuItem;
	int i;

	D_memset(textbuff, 0, 256);

	ST_DrawString(-1, 20, "Features", text_alpha | 0xc0000000,1);

	for (i = 0; i < itemlines; i++) {
		if ((item->casepos == 23) && FUNLEVEL(m_actualmap)) {
			/* Show "WARP TO FUN" text */
			ST_Message(item->x, item->y, MenuText[40],
				   text_alpha | 0xffffff00,1);
		} else if ((item->casepos == 23) && (m_actualmap == 28)) {
			// [Immorpher] Show "WARP TO MOTHER" text
			ST_Message(item->x, item->y, MenuText[65],
				   text_alpha | 0xffffff00,1);
		} else if ((item->casepos == 23) && (m_actualmap > 28) &&
			   (m_actualmap < 34)) {
			// [Immorpher] Show "WARP TO SECRET" text
			ST_Message(item->x, item->y, MenuText[66],
				   text_alpha | 0xffffff00,1);
		} else if (item->casepos == 23) {
			/* Show "WARP TO LEVEL" text */
			ST_Message(item->x, item->y, MenuText[23],
				   text_alpha | 0xffffff00,1);
		} else {
			ST_Message(item->x, item->y, MenuText[item->casepos],
				   text_alpha | 0xffffff00,1);
		}

		text = textbuff;
		switch (item->casepos) {
		case 23: /* WARP TO LEVEL */
			sprintf(textbuff, "%s", MapInfo[m_actualmap].name);
			break;
		case 24: /* INVULNERABLE */
			text = (!(players[0].cheats & CF_GODMODE)) ? "OFF" :
								     "ON";
			break;
		case 25: /* HEALTH BOOST */
			text = (!(players[0].cheats & CF_HEALTH)) ? "-" :
								    "100%";
			break;
		case 26: /* SECURITY KEYS */
			text = (!(players[0].cheats & CF_ALLKEYS)) ? "-" :
								     "100%";
			break;
		case 27: /* WEAPONS */
			text = (!(players[0].cheats & CF_WEAPONS)) ? "-" :
								     "100%";
			break;
		case 28: /* Exit */
			break;
		case 31: /* WALL BLOCKING */
			text = (!(players[0].cheats & CF_WALLBLOCKING)) ? "ON" :
									  "OFF";
			break;
		case 35: /* LOCK MONSTERS */
			text = (!(players[0].cheats & CF_LOCKMOSTERS)) ? "OFF" :
									 "ON";
			break;
		case 37: /* MAP EVERYTHING */
			text = (!(players[0].cheats & CF_ALLMAP)) ? "OFF" :
								    "ON";
			break;
		case 39: /* MUSIC TEST */
			sprintf(textbuff, "%d", MusicID);
			break;

		// [GEC] NEW CHEAT CODES
		case 48: /* COLORS */
			text = (!(players[0].cheats & CF_NOCOLORS)) ? "ON" :
								      "OFF";
			break;

		case 49: /* FULL BRIGHT */
			text = (!(players[0].cheats & CF_FULLBRIGHT)) ? "OFF" :
									"ON";
			break;

		case 68: /* Gamma Correction */
			text = (!(players[0].cheats & CF_GAMMA)) ? "OFF" : "ON";
			break;

		default:
			text = ""; // [Immorpher] set to null for credits menu
			break;
		}

		ST_Message(item->x + 130, item->y, text,
			   text_alpha | 0xffffff00,1);
		item++;
	}

	ST_DrawSymbol(MenuItem->x - 10, MenuItem[cursorpos].y - 1, 78,
		      text_alpha | 0xffffff00,1);
}

void M_CreditsDrawer(void) // 800091C0
{
#if 0
	char *text, textbuff[256];
	menuitem_t *item;
	int i;

	D_memset(textbuff, 0, 256);

	ST_DrawString(-1, 20, "Merciless Credits", text_alpha | 0xc0000000,1);
	item = MenuItem;

	for (i = 0; i < itemlines; i++) {
		/* Show "WARP TO LEVEL" text */
		ST_Message(item->x, item->y, MenuText[item->casepos],
			   text_alpha | 0xffffff00,1);

		text = textbuff;

		ST_Message(item->x + 130, item->y, text,
			   text_alpha | 0xffffff00,1);
		item++;
	}
#endif
}

void M_VolumeDrawer(void) // 800095B4
{
	menuitem_t *item;
	int i;

	ST_DrawString(-1, 20, "Volume", text_alpha | 0xc0000000,1);
	item = Menu_Volume;

	for (i = 0; i < itemlines; i++) {
		ST_DrawString(item->x, item->y, MenuText[item->casepos],
			      text_alpha | 0xc0000000,1);
		item++;
	}

	ST_DrawSymbol(MenuItem->x - 37, MenuItem[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);

	ST_DrawSymbol(82, 80, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(menu_settings.MusVolume + 83, 80, 69, text_alpha | 0xffffff00,1);

	ST_DrawSymbol(82, 120, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(((menu_settings.SfxVolume*100)/75) + 83, 120, 69,
		      text_alpha | 0xffffff00,1);
}

void M_MovementDrawer(void) // 80009738
{
	char *text = NULL;
	menuitem_t *item = Menu_Movement;
	int i, casepos;

	ST_DrawString(-1, 20, "Movement", text_alpha | 0xc0000000,1);

	for (i = 0; i < itemlines; i++) {
		casepos = item->casepos;

		if (casepos == 12) {
			if (menu_settings.Autorun)
				text = "On";
			else
				text = "Off";
		} else if (casepos == 95) {
			if (menu_settings.Rumble)
				text = "On";
			else
				text = "Off";
		} else {
			text = NULL;
		}

		if (casepos == 96) { // Deadzone
			ST_DrawNumber(item->x + 120, item->y,
						menu_settings.PlayDeadzone >> 1,
						0, text_alpha | 0xff000000, 1);
		}

		if (text)
			ST_DrawString(item->x + 100, item->y, text,
				      text_alpha | 0xc0000000,1);

		ST_DrawString(item->x, item->y, MenuText[item->casepos],
			      text_alpha | 0xc0000000,1);
		item++;
	}

	ST_DrawSymbol(MenuItem->x - 37, MenuItem[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);

	// Sensitivity
	ST_DrawSymbol(82, 120, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(((101 * menu_settings.M_SENSITIVITY) >> 7) + 83, 120, 69, text_alpha | 0xffffff00,1);

	// Motion bob
	ST_DrawSymbol(82, 80, 68, text_alpha | 0xffffff00, 1);
	ST_DrawSymbol(menu_settings.MotionBob / 0x28F6 + 83, 80, 69, text_alpha | 0xffffff00,1);
}

void M_VideoDrawer(void)
{
	char *text = NULL;
	menuitem_t *item = Menu_Video;
	int i, casepos;

	ST_DrawString(-1, 20, "Video", text_alpha | 0xc0000000,1);

	for (i = 0; i < NUM_MENU_VIDEO; i++) {
		casepos = item->casepos;

		if (casepos == 92) { // fps cap menu
			if (global_render_state.fps_uncap == 0)
				text = M_TXT93;//"30";
			else
				text = M_TXT94;//"Uncapped";
		} else if (casepos == 88) { // quality menu
			if (global_render_state.quality == 0)
				text = "Low";
			else if (global_render_state.quality == 1)
				text = "Medium";
			else if (global_render_state.quality == 2)
				text = "Ultra";
		} else if (casepos == 50) { // [GEC and Immorpher] New video filter
			if (menu_settings.VideoFilter == PVR_FILTER_BILINEAR)
				text = "On";
			else
				text = "Off";
		} else {
			text = NULL;
		}

		if (text)
			ST_DrawString(item->x + 140, item->y, text,
				      text_alpha | 0xc0000000,1);

		ST_DrawString(item->x, item->y, MenuText[casepos],
			      text_alpha | 0xc0000000,1);

		item++;
	}

	ST_DrawSymbol(82, 80, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(((101 * menu_settings.brightness) >> 7) + 83, 80, 69,
		      text_alpha | 0xffffff00,1);

	ST_DrawSymbol(Menu_Video[0].x - 37, Menu_Video[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);
}

void M_DisplayDrawer(void) // 80009884
{
	char *text = NULL;
	menuitem_t *item = Menu_Display;
	int i, casepos;

	ST_DrawString(-1, 20, "Display", text_alpha | 0xc0000000,1);

	for (i = 0; i < itemlines; i++) {
		casepos = item->casepos;

		if (casepos == 61) { // Story Text:
			if (menu_settings.StoryText)
				text = "On";
			else
				text = "Off";
		} else if (casepos == 62) { // Map stats:
			if (menu_settings.MapStats)
				text = "On";
			else
				text = "Off";
		} else {
			text = NULL;
		}

		if (text)
			ST_DrawString(item->x + 130, item->y, text,
				      text_alpha | 0xc0000000,1);

		ST_DrawString(item->x, item->y, MenuText[casepos],
			      text_alpha | 0xc0000000,1);

		item++;
	}

	// Flash brightness
	//    ST_DrawSymbol(82, 80, 68, text_alpha | 0xffffff00);
	//	ST_DrawSymbol(100*FlashBrightness/32 + 83, 80, 69, text_alpha | 0xffffff00);

	ST_DrawSymbol(Menu_Display[0].x - 37, Menu_Display[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);
}

void M_StatusHUDDrawer(void) // 80009884
{
	char *text = NULL;
	menuitem_t *item = Menu_StatusHUD;
	int i, casepos;

	ST_DrawString(-1, 20, "Status HUD", text_alpha | 0xc0000000,1);

	for (i = 0; i < itemlines; i++) {
		casepos = item->casepos;

		if (casepos == 33) { // Messages:
			if (menu_settings.enable_messages)
				text = "On";
			else
				text = "Off";
		} else if (casepos == 67) { // Colored HUD:
			if (menu_settings.ColoredHUD)
				text = "On";
			else
				text = "Off";
		} else {
			text = NULL;
		}

		if (text)
			ST_DrawString(item->x + 130, item->y, text,
				      text_alpha | 0xc0000000,1);

		ST_DrawString(item->x, item->y, MenuText[casepos],
			      text_alpha | 0xc0000000,1);

		item++;
	}

	// HUD Margin
	ST_DrawSymbol(82, 80, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(100 * menu_settings.HUDmargin / 20 + 83, 80, 69,
		      text_alpha | 0xffffff00,1);

	// HUD Opacity
	ST_DrawSymbol(82, 120, 68, text_alpha | 0xffffff00,1);
	ST_DrawSymbol(100 * menu_settings.HUDopacity / 255 + 83, 120, 69,
		      text_alpha | 0xffffff00,1);

	ST_DrawSymbol(Menu_StatusHUD[0].x - 37, Menu_StatusHUD[cursorpos].y - 9,
		      MenuAnimationTic + 70, text_alpha | 0xffffff00,1);
}

uint32_t next_pow2(uint32_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

uint16_t bgpal[256];
uint16_t biggest_bg[512 * 256];
pvr_poly_cxt_t pvrbgcxt[2];
pvr_poly_hdr_t __attribute__((aligned(32))) pvrbghdr[2];
uint64_t lastname[2] = { 0xffffffff, 0xffffffff };
int bg_last_width[2];
int bg_last_height[2];
pvr_ptr_t pvrbg[2] = { 0, 0 };
#define _PAD8(x) x += (8 - ((uint)x & 7)) & 7

pvr_sprite_hdr_t bg_shdr[2];
pvr_sprite_cxt_t bg_scxt[2];
pvr_sprite_txr_t bg_stxr[2];

void M_DrawBackground(int x, int y, int color, char *name, float z,
		      int num)
{
	int width, height;
	int offset;
	byte *data;
	byte *gfxsrc;
	short *palsrc;
	float u1, v1, u2, v2;
	float x1, y1, x2, y2;
	uint8_t a1;
	a1 = color & 0xff;

	if (!pvrbg[num]) {
		pvrbg[num] = pvr_mem_malloc(512 * 512);
		if (!pvrbg[num]) {
			I_Error("PVR OOM for background %s [%d]", name, num);
		}
		pvr_sprite_cxt_txr(&bg_scxt[num], PVR_LIST_TR_POLY,
							PVR_TXRFMT_ARGB1555 | PVR_TXRFMT_TWIDDLED,
							512, 256, pvrbg[num],
							PVR_FILTER_NONE);
		pvr_sprite_compile(&bg_shdr[num], &bg_scxt[num]);
	}

	//uint32_t wasnt enough to differentiate between the credit screens
	if (*(uint64_t *)(name) != lastname[num]) {
		lastname[num] = *(uint64_t *)name;
		data = (byte *)W_CacheLumpName(name, PU_CACHE, dec_jag);

		width = SwapShort(((gfxN64_t *)data)->width);
		height = SwapShort(((gfxN64_t *)data)->height);
		if (height > 256)
			height = 256;
		bg_last_width[num] = width;
		bg_last_height[num] = height;
		offset = (width * height);
		offset = (offset + 7) & ~7;
		gfxsrc = data + sizeof(gfxN64_t);
		palsrc = (short *)((void *)data + offset + sizeof(gfxN64_t));

		for (int j = 0; j < 256; j++) {
			short val = *palsrc;
			palsrc++;
			val = SwapShort(val);
			// Unpack and expand to 8bpp, then flip from BGR to RGB.
			u8 b = (val & 0x003E) << 2;
			u8 g = (val & 0x07C0) >> 3;
			u8 r = (val & 0xF800) >> 8;
			u8 a = 0xff; // Alpha is always 255..
			if (j == 0 && r == 0 && g == 0 && b == 0) {
				bgpal[j] = get_color_argb1555(0, 0, 0, 0);
			} else { // always brighten the backgrounds
#if 0
				//				if (r && g && b) {
				int hsv = LightGetHSV(r, g, b);
				int h = (hsv >> 16) & 0xff;
				int s = (hsv >> 8) & 0xff;
				int v = hsv & 0xff;

				v = (v * 102) / 100;
				if (v > 255)
					v = 255;
				int rgb = LightGetRGB(h, s, v);
				r = (rgb >> 16) & 0xff;
				g = (rgb >> 8) & 0xff;
				b = rgb & 0xff;
//				}
#endif
				bgpal[j] = get_color_argb1555(r, g, b, a);
			}
		}

		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				biggest_bg[w + (h * 512)] =
					bgpal[gfxsrc[w + (h * width)]];
			}
		}

		pvr_txr_load_ex(biggest_bg, pvrbg[num], 512, 256,
				PVR_TXRLOAD_16BPP);
	}

	u1 = 0.0f;
	v1 = 0.0f;
	u2 = (float)bg_last_width[num] / 512.0f;
	v2 = (float)bg_last_height[num] / 256.0f;
	
	bg_stxr[num].flags = PVR_CMD_VERTEX_EOL;
	bg_stxr[num].az = z;
	bg_stxr[num].bz = z;
	bg_stxr[num].cz = z;
	bg_stxr[num].dummy = 0;
	bg_shdr[num].argb = (a1 << 24) | 0x00ffffff;
	
	x1 = (float)(x * RES_RATIO);
	y1 = (float)(y * RES_RATIO);
	x2 = (float)((x + bg_last_width[num]) * RES_RATIO);
	y2 = (float)((y + bg_last_height[num]) * RES_RATIO);

	bg_stxr[num].ax = x1;
	bg_stxr[num].ay = y2;
	bg_stxr[num].bx = x1;
	bg_stxr[num].by = y1;
	bg_stxr[num].cx = x2;
	bg_stxr[num].cy = y1;
	bg_stxr[num].dx = x2;
	bg_stxr[num].dy = y2;
	bg_stxr[num].auv = PVR_PACK_16BIT_UV(u1, v2);
	bg_stxr[num].buv = PVR_PACK_16BIT_UV(u1, v1);
	bg_stxr[num].cuv = PVR_PACK_16BIT_UV(u2, v1);
	pvr_list_prim(PVR_LIST_TR_POLY, &bg_shdr[num],
				sizeof(pvr_sprite_hdr_t));
	pvr_list_prim(PVR_LIST_TR_POLY, &bg_stxr[num],
				sizeof(pvr_sprite_txr_t));

	globallump = -1;
}

void M_DrawOverlay(int x, int y, int w, int h, int color)
{
	// kind of stupid to generate these dynamically
	pvr_poly_cxt_t cxt;
	pvr_poly_hdr_t __attribute__((aligned(32))) hdr;
	pvr_vertex_t __attribute__((aligned(32))) verts[4];
	pvr_poly_cxt_col(&cxt, PVR_LIST_TR_POLY);
	pvr_poly_compile(&hdr, &cxt);

	float u0, v0, u1, v1;
	uint8_t r1, g1, b1, a1;
	r1 = color >> 24;
	g1 = color >> 16 & 0xff;
	b1 = color >> 8 & 0xff;
	a1 = color & 0xff;

	u0 = 0.0f;
	v0 = 0.0f;
	u1 = (float)w / 320.0f;
	v1 = (float)h / 240.0f;
	for (int vn = 0; vn < 4; vn++) {
		verts[vn].z = 9.9f;
		verts[vn].oargb = 0;
		verts[vn].argb =
			PVR_PACK_COLOR((float)a1 / 255, (float)r1 / 255,
				       (float)g1 / 255, (float)b1 / 255);
		verts[vn].flags = PVR_CMD_VERTEX;
	}
	verts[3].flags = PVR_CMD_VERTEX_EOL;

	pvr_vertex_t *vert = verts;

	vert->x = (float)(x * RES_RATIO);
	vert->y = (float)((y + h) * RES_RATIO);
	vert->u = u0;
	vert->v = v1;
	vert++;

	vert->x = (float)(x * RES_RATIO);
	vert->y = (float)(y * RES_RATIO);
	vert->u = u0;
	vert->v = v0;
	vert++;

	vert->x = (float)((x + w) * RES_RATIO);
	vert->y = (float)((y + h) * RES_RATIO);
	vert->u = u1;
	vert->v = v1;
	vert++;

	vert->x = (float)((x + w) * RES_RATIO);
	vert->y = (float)(y * RES_RATIO);
	vert->u = u1;
	vert->v = v0;

	pvr_list_prim(PVR_LIST_TR_POLY, &hdr, sizeof(pvr_poly_hdr_t));
	pvr_list_prim(PVR_LIST_TR_POLY, &verts, sizeof(verts));

	globallump = -1;
}

int M_ScreenTicker(void) // 8000A0F8
{
	static int last_f_gametic = 0;
	int exit;
	unsigned int buttons;
	unsigned int oldbuttons;
	//    OSPfsState *fState;

	if ((FilesUsed == -1) && (I_CheckControllerPak() == 0)) {
		cursorpos = 0;
		linepos = 0;
	}

//	if ((gamevbls < gametic) && ((gametic & 3) == 0))
	if (((int)f_gamevbls < (int)f_gametic) && (((int)f_gametic & 3) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
	}
	buttons = M_ButtonResponder(ticbuttons[0]);
	oldbuttons = oldticbuttons[0] & 0xffff0000;

	if (!(buttons & ALL_JPAD)) {
		f_m_vframe1 = 0.0f;
	} else {
		f_m_vframe1 -= f_vblsinframe[0];

		if (f_m_vframe1 <= 0.0f) {
			f_m_vframe1 = (float)TICRATE / 2;

			if (buttons & PAD_DOWN) {
				cursorpos += 1;

				if (cursorpos < 16)
					S_StartSound(NULL, sfx_switch1);
				else
					cursorpos = 15;

				if ((linepos + 5) < cursorpos)
					linepos += 1;
			} else if (buttons & PAD_UP) {
				cursorpos -= 1;

				if (cursorpos < 0)
					cursorpos = 0;
				else
					S_StartSound(NULL, sfx_switch1);

				if (cursorpos < linepos)
					linepos -= 1;
			}
		}
	}

	if (!(buttons ^ oldbuttons) || !(buttons & PAD_START)) {
		if (buttons ^ oldbuttons) {
			if (buttons == (PAD_DREAMCAST_Y | PAD_DREAMCAST_A)) {
                dirent_t *fState = &FileState[cursorpos];

                if(fState->size != 0)
                {
                    S_StartSound(NULL, sfx_pistol);
                    M_SaveMenuData();

                    MenuItem = Menu_DeleteNote;
                    itemlines = NUM_MENU_DELETENOTE;
                    MenuCall = M_MenuTitleDrawer;
                    cursorpos = 1;
                    MiniLoop(M_FadeInStart, NULL, M_MenuTicker, M_MenuGameDrawer);

                    M_FadeOutStart(8);
                    if (cursorpos == 0)
                    {
                        if (I_DeletePakFile(fState) == 0)
                        {
                            fState->size = 0;
                        }
                        else
                        {
                            FilesUsed = -1;
                        }
                    }
                    M_RestoreMenuData(true);
                }
			}
		}
		exit = 0;
	} else {
		S_StartSound(NULL, sfx_pistol);
		exit = 8;
	}
	return exit;
}

void M_ControllerPakDrawer(void) // 8000A3E4
{
	char buffer[32];
	char *tmpbuf;
	int i,j;
	byte idx;
    ST_DrawString(-1, 20, "VMU", text_alpha | 0xc0000000, 1);

    if (FilesUsed == -1)
    {
        if ((MenuAnimationTic & 2) != 0)
            ST_DrawString(-1, 114, "VMU removed!", text_alpha | 0xc0000000, 1);

        ST_DrawString(-1, 210, "press \x8d to exit", text_alpha | 0xffffff00, 1);
    }
    else
	{
//		ST_DrawString(-1, 114, "Please use", text_alpha | 0xc0000000, 1);
//		ST_DrawString(-1, 130, "Dreamcast BIOS", text_alpha | 0xc0000000, 1);
//		ST_DrawString(-1, 146, "for VMU management.", text_alpha | 0xc0000000, 1);
//		ST_DrawString(-1, 210, "press \x8d to exit", text_alpha | 0xffffff00, 1);

		dirent_t *fState = &FileState[linepos];
        for(i = linepos; i < (linepos + 6); i++)
        {
            if (fState->size == 0)
            {
                strcpy(buffer, "empty");
            }
            else
            {
                tmpbuf = buffer;

                for(j = 0; j < 16; j++)
                {
                    idx = (byte) fState->name[j];
                    if(idx == 0)
                        break;

                    tmpbuf[0] = idx;
                    tmpbuf++;
                }

                *tmpbuf = '\0';
            }

            ST_DrawString(60, (i - linepos) * 15 + 60, buffer, text_alpha | 0xc0000000, 1);

            fState++;
        }

		if (linepos != 0)
        {
            ST_DrawString(60, 45, "\x8F more...", text_alpha | 0xffffff00, 1);
        }

        if ((linepos + 6) < 16)
        {
            ST_DrawString(60, 150, "\x8E more...", text_alpha | 0xffffff00, 1);
        }

        sprintf(buffer, "pages used: %d   free: %ld", FileState[cursorpos].size >> 9, Pak_Memory);

        ST_DrawString(-1, 170, buffer, text_alpha | 0xc0000000, 1);
        ST_DrawSymbol(23, (cursorpos - linepos) * 15 + 51, MenuAnimationTic + 70, text_alpha | 0xffffff00, 1);

        ST_DrawString(-1, 200, "press \x8d to exit", text_alpha | 0xffffff00, 1);
        ST_DrawString(-1, 215, "press \x8b\x8c to delete", text_alpha | 0xffffff00, 1);
    }
}
extern s32 Pak_Size;
void M_SavePakStart(void) // 8000A6E8
{
    int i;
    int ret;
    int size;

    cursorpos = 0;
    linepos = 0;
    last_ticon = 0;

    ret = I_CheckControllerPak();
    if (ret == 0)
    {
        if (I_ReadPakFile() == 0)
        {
            size = Pak_Size / 32;

            i = 0;
            if (size != 0)
            {
                do
                {
                    if (Pak_Data[i * 32] == 0)
                        break;

                    i++;
                } while (i != size);
            }

            if (i < size)
            {
                cursorpos = i;

                if (!(size < (i+6)))
                    linepos = i;
                else
                    linepos = (size-6);
            }
        }
    }
    else
    {
        FilesUsed = -1;
    }
}

void M_SavePakStop(void) // 8000A7B4
{
    S_StartSound(NULL, sfx_pistol);
    if (Pak_Data) {
        Z_Free(Pak_Data);
        Pak_Data = NULL;
    }
}

int M_SavePakTicker(void) // 8000A804
{
	static int last_f_gametic = 0;
    unsigned int buttons;
    unsigned int oldbuttons;
    int size;

    if (((int)f_gamevbls < (int)f_gametic) && (((int)f_gametic & 3) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
    }

    buttons = M_ButtonResponder(ticbuttons[0]);
    oldbuttons = oldticbuttons[0] & 0xffff0000;

    if ((buttons != oldbuttons) && (buttons & PAD_START)) {
        return ga_exit;
    }

    if (FilesUsed == -1) {
        if (I_CheckControllerPak()) {
            return ga_nothing;
        }

        if (I_ReadPakFile()) {
            FilesUsed = -1;
            return ga_nothing;
        }

        cursorpos = 0;
        linepos = 0;
    }

    if (!(buttons & ALL_JPAD)) {
        f_m_vframe1 = 0;
    } else {
        f_m_vframe1 -= f_vblsinframe[0];

        if (f_m_vframe1 <= 0) {
            f_m_vframe1 = (float)(TICRATE / 2);

            if (buttons & PAD_DOWN) {
                cursorpos += 1;

                size = (Pak_Size / 32) - 1;

                if (size < cursorpos)
                    cursorpos = size;
                else
                    S_StartSound(NULL, sfx_switch1);


                if ((linepos + 5) < cursorpos)
                    linepos += 1;
            } else if (buttons & PAD_UP) {
                cursorpos -= 1;

                if (cursorpos < 0)
                    cursorpos = 0;
                else
                    S_StartSound(NULL, sfx_switch1);

                if(cursorpos < linepos)
                    linepos -= 1;
            }
        }
    }

    if (last_ticon == 0) {
		// press Dreamcast A button to save
        if ((buttons != oldbuttons) && (buttons == PAD_Z_TRIG)) {
			// clear the entry before putting any data in it
			D_memset((char *)&Pak_Data[cursorpos * 32], 0, 32);

            // save the next level number and password data in text format
			if (gameskill == sk_baby) {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d - bg", nextmap);
			} else if (gameskill == sk_easy) {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d - bio", nextmap);
			} else if (gameskill == sk_medium) {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d - iod", nextmap);
			} else if (gameskill == sk_hard) {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d - wmd", nextmap);
			} else if (gameskill == sk_nightmare) {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d - bm", nextmap);
			} else {
				sprintf((char *)&Pak_Data[cursorpos * 32], "level %2.2d", nextmap);
			}
			
            D_memcpy((char *)&Pak_Data[(cursorpos * 32) + 16], (char *)&Passwordbuff, 16);

            if (I_SavePakFile() == 0) {
                last_ticon = ticon;
            } else {
                FilesUsed = -1;
                if (Pak_Data) {
                    Z_Free(Pak_Data);
                    Pak_Data = NULL;
                }
            }
        }
    } else if ((ticon - last_ticon) >= 60) { // 2 * TICRATE
        return ga_exit;
    }

	return ga_nothing;
}

void M_SavePakDrawer(void)
{
    int i;
    char buffer[33];

    I_ClearFrame();
	// Fill borders with black
	pvr_set_bg_color(0,0,0);
	pvr_fog_table_color(0.0f,0.0f,0.0f,0.0f);
    M_DrawBackground(63, 25, 128, "EVIL", 0.00015f, 0);

    ST_DrawString(-1, 20, "VMU", text_alpha | 0xc0000000, 1);

    if (FilesUsed == -1) {
        if (MenuAnimationTic & 2) {
            ST_DrawString(-1, 100, "VMU removed!", 0xc00000ff, 1);
            ST_DrawString(-1, 120, "Game cannot be saved.", 0xc00000ff, 1);
        }

        ST_DrawString(-1, 210, "press \x8d to exit", text_alpha | 0xffffff00, 1);
    } else {
        for(i = linepos; i < (linepos + 6); i++) {
			D_memset(buffer, 0, 33);
            if (Pak_Data[i * 32] == 0) {
                memcpy(buffer, "empty", 5);
            } else {
                memcpy(buffer, (char *)&Pak_Data[i * 32], 32);
            }

            ST_DrawString(60, (i - linepos) * 15 + 65, buffer, text_alpha | 0xc0000000, 1);
        }

        if (linepos != 0) {
            ST_DrawString(60, 50, "\x8f more...", text_alpha | 0xffffff00, 1);
        }

        if ((linepos + 6) <= ((Pak_Size >> 5) - 1)) {
            ST_DrawString(60, 155, "\x8e more...", text_alpha | 0xffffff00, 1);
        }

        ST_DrawSymbol(23, (cursorpos - linepos) * 15 + 56, MenuAnimationTic + 70, text_alpha | 0xffffff00, 1);

        ST_DrawString(-1, 195, "press \x8d to exit", text_alpha | 0xffffff00, 1);
		// changed to z trigger
        ST_DrawString(-1, 210, "press \x8c to save", text_alpha | 0xffffff00, 1);
    }

    I_DrawFrame();
}

void M_LoadPakStart(void) // 8000AEEC
{
    int i;
    int size;

    cursorpos = 0;
    linepos = 0;

    size = Pak_Size / 32;

    i = 0;
    if (size != 0) {
        do {
            if (Pak_Data[i * 32])
                break;

            i++;
        } while (i != size);
    }

    if (i < size) {
        cursorpos = i;

        if (!(size < (i+6)))
            linepos = i;
        else
            linepos = (size-6);
    }

    M_FadeInStart();
}

void M_LoadPakStop(void) // 8000AF8C
{
    S_StartSound(NULL, sfx_pistol);
    M_FadeOutStart(ga_exit);

    if (Pak_Data) {
        Z_Free(Pak_Data);
        Pak_Data = NULL;
    }
}

int M_LoadPakTicker(void) // 8000AFE4
{
	static int last_f_gametic = 0;
    unsigned int buttons;
    unsigned int oldbuttons;
    int size;
    int skill;
    int levelnum;
    int exit;

    if (((int)f_gamevbls < (int)f_gametic) && (((int)f_gametic & 3U) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
    }

    buttons = M_ButtonResponder(ticbuttons[0]);
    oldbuttons = oldticbuttons[0] & 0xffff0000;

    if (!(buttons & ALL_JPAD)) {
        f_m_vframe1 = 0;
    } else {
        f_m_vframe1 -= f_vblsinframe[0];

        if (f_m_vframe1 <= 0) {
            f_m_vframe1 = (float)(TICRATE/2);

            if (buttons & PAD_DOWN) {
                cursorpos += 1;

                size = (Pak_Size / 32) - 1;

                if (size < cursorpos)
                    cursorpos = size;
                else
                    S_StartSound(NULL, sfx_switch1);

                if ((linepos + 5) < cursorpos)
                    linepos += 1;

            } else if (buttons & PAD_UP) {
                cursorpos -= 1;

                if (cursorpos < 0)
                    cursorpos = 0;
                else
                    S_StartSound(NULL, sfx_switch1);

                if(cursorpos < linepos)
                    linepos -= 1;
            }
        }
    }

    if (!(buttons ^ oldbuttons) || !(buttons & PAD_START)) {
        if (!(buttons ^ oldbuttons) || buttons != PAD_Z_TRIG ||
            (Pak_Data[cursorpos * 32] == 0)) {
            exit = ga_nothing;
        } else {
            // load the password data in text format
            D_memcpy(&Passwordbuff, &Pak_Data[((cursorpos * 32) + 16)], 16);

            if (M_DecodePassword(Passwordbuff, &levelnum, &skill, 0) == 0) {
                CurPasswordSlot = 0;
                exit = ga_exit;
            } else {
                doPassword = true;
                CurPasswordSlot = 16;

                startmap = gamemap = levelnum;
                startskill = gameskill = skill;

				G_InitSkill (gameskill); // [Immorpher] Initialize new game skill
                exit = ga_warped;
            }
        }
    } else {
        exit = ga_exit;
    }

    return exit;
}

void M_LoadPakDrawer(void) // 8000B270
{
    int i;
    char buffer[33];

    ST_DrawString(-1, 20, "VMU", text_alpha | 0xc0000000, 1);

    for(i = linepos; i < (linepos + 6); i++) {
		D_memset(buffer, 0, 33);

        if (FilesUsed == -1) {
            memcpy(buffer, "-", 1);
        } else if (Pak_Data[i * 32] == 0) {
            memcpy(buffer, "no save", 7);
        } else {
            memcpy(buffer, (char *)&Pak_Data[i * 32], 32);
        }

        ST_DrawString(60, (i - linepos) * 15 + 65, buffer, text_alpha | 0xc0000000, 1);
    }

    if (linepos != 0) {
        ST_DrawString(60, 50, "\x8f more...", text_alpha | 0xffffff00, 1);
    }

    if ((linepos + 6) <= ((Pak_Size >> 5) - 1)) {
        ST_DrawString(60, 155, "\x8e more...", text_alpha | 0xffffff00, 1);
    }

    ST_DrawSymbol(23, (cursorpos - linepos) * 15 + 56, MenuAnimationTic + 70, text_alpha | 0xffffff00, 1);

    ST_DrawString(-1, 195, "press \x8D to exit", text_alpha | 0xffffff00, 1);
    ST_DrawString(-1, 210, "press \x8c to load", text_alpha | 0xffffff00, 1);
}

int M_CenterDisplayTicker(void) // 8000B4C4
{
	unsigned int buttons, oldbuttons;
	int exit;

	buttons = M_ButtonResponder(ticbuttons[0]);
	oldbuttons = oldticbuttons[0] & 0xffff0000;

	if ((buttons == oldbuttons) || !(buttons & PAD_START)) {
		if (buttons & PAD_LEFT) {
			Display_X -= 1;
			if (Display_X < -16)
				Display_X = -16;
		} else if (buttons & PAD_RIGHT) {
			Display_X += 1;
			if (Display_X > 24)
				Display_X = 24;
		}

		if (buttons & PAD_UP) {
			Display_Y -= 1;
			if (Display_Y < -20)
				Display_Y = -20;
		} else if (buttons & PAD_DOWN) {
			Display_Y += 1;
			if (Display_Y > 12)
				Display_Y = 12;
		}

//		if (buttons & ALL_JPAD)
//			I_MoveDisplay(Display_X, Display_Y);

		exit = 0;
	} else {
		S_StartSound(NULL, sfx_pistol);
		exit = 8;
	}

	return exit;
}

void M_CenterDisplayDrawer(void) // 8000B604
{
	ST_DrawString(-1, 20, "Center Display", text_alpha | 0xc0000000,1);
	ST_DrawString(-1, 114, "use gamepad to adjust",
		      text_alpha | 0xffffff00,1);
	ST_DrawString(-1, 210, "press \x8d to exit", text_alpha | 0xffffff00,1);
}

int M_ControlPadTicker(void) // 8000B694
{
	static int last_f_gametic = 0;
	unsigned int buttons;
	unsigned int oldbuttons;
	int exit;
//	int *tmpcfg, code;

//	if ((gamevbls < gametic) && ((gametic & 3U) == 0)) {
	if (((int)f_gamevbls < (int)f_gametic) && ((((int)f_gametic) & 3U) == 0)) {
		if (last_f_gametic != (int)f_gametic) {
			last_f_gametic = (int)f_gametic;
			MenuAnimationTic = (MenuAnimationTic + 1) & 7;
		}
	}

	buttons = M_ButtonResponder(ticbuttons[0] & 0xffff);

	if (!(buttons & ALL_JPAD)) {
		f_m_vframe1 = 0.0f;
	} else {
		f_m_vframe1 = f_m_vframe1 - f_vblsinframe[0];
		if (f_m_vframe1 <= 0.0f) {
			f_m_vframe1 = (float)TICRATE / 2;

			if (buttons & PAD_DOWN) {
				cursorpos += 1;
				if (cursorpos < 14)
					S_StartSound(NULL, sfx_switch1);
				else
					cursorpos = 13;

				if (cursorpos > (linepos + 5))
					linepos += 1;
			} else {
				if (buttons & PAD_UP) {
					cursorpos -= 1;
					if (cursorpos < 0)
						cursorpos = 0;
					else
						S_StartSound(NULL, sfx_switch1);

					if (cursorpos < linepos)
						linepos -= 1;
				}
			}
		}
	}

	buttons = ticbuttons[0] & 0xffff0000;
	oldbuttons = oldticbuttons[0] & 0xffff0000;

	if (buttons & PAD_START) {
		S_StartSound(NULL, sfx_pistol);
		exit = 8;
	} else {
		if (buttons == oldbuttons)
			exit = 0;
		else {
			if (cursorpos == 0) // Set Default Configuration
			{
				D_memcpy(ActualConfiguration,
					 DefaultConfiguration[0],
					 (13 * sizeof(int)));

				D_memcpy(CustomConfiguration,
					 DefaultConfiguration[0],
					 (13 * sizeof(int)));

				if ((buttons & (ALL_BUTTONS | ALL_JPAD)) != 0) {
					S_StartSound(NULL, sfx_switch2);
					return 0;
				}
			}
			exit = 0;
		}
	}
	return exit;
}

static int dc_button_to_symbol(u32 code) {
	switch (code) {
	case PAD_DREAMCAST_DPAD_LEFT:
		return 80;
	case PAD_DREAMCAST_DPAD_RIGHT:
		return 81;
	case PAD_DREAMCAST_DPAD_UP:
		return 82;
	case PAD_DREAMCAST_DPAD_DOWN:
		return 83;
	case PAD_DREAMCAST_BUTTON_B:
		return 85;
	case PAD_DREAMCAST_TRIGGER_L:
		return 88;
	case PAD_DREAMCAST_TRIGGER_R:
		return 89;
	case PAD_DREAMCAST_BUTTON_X:
		return 90;
	case PAD_DREAMCAST_BUTTON_Y:
		return 91;
	case PAD_DREAMCAST_BUTTON_A:
		return 92;
	default:
		// N/A
		return 84;
	}
}

void M_ControlPadDrawer(void) // 8000B988
{
	int lpos;
	char **text;
	char buffer[256];
	D_memset(buffer, 0, 256);
	ST_DrawString(-1, 20, "Gamepad", text_alpha | 0xc0000000,1);

	if (linepos < (linepos + 6)) {
		text = &ControlText[linepos];
		lpos = linepos;
		do {
			if (lpos != 0) {
				dc_n64_map_t *next_map = &(((dc_n64_map_t *)&ingame_mapping)[lpos - 1]);
				if (next_map->dcused == 0) {
						ST_DrawSymbol(60, ((lpos - linepos) * 18) + 68,
						84,
						text_alpha | 0xffffff00,1); 
				} else {
					for (int bc=0;bc<next_map->dcused;bc++) {
						ST_DrawSymbol(60 + (bc*16), ((lpos - linepos) * 18) + 68,
						dc_button_to_symbol(next_map->dcbuttons[bc]),
						text_alpha | 0xffffff00,1); 
					}
				}
			}

			if (lpos == 0) {
				if (text) {
					sprintf(buffer, "Your Configuration");
				}
			} else {
				if (text) {
					sprintf(buffer, *text);
				}
			}

			ST_DrawString(96, ((lpos - linepos) * 18) + 68, buffer,
				      text_alpha | 0xc0000000,1);

			lpos += 1;
			text += 1;
		} while (lpos < (linepos + 6));
	}

	if (linepos != 0) {
		ST_DrawString(80, 50, "\x8f more...", text_alpha | 0xffffff00,1);
	}

	if ((linepos + 6) < 14) {
		ST_DrawString(80, 176, "\x8e more...", text_alpha | 0xffffff00,1);
	}

	ST_DrawSymbol(23, (cursorpos - linepos) * 0x12 + 0x3b,
		      MenuAnimationTic + 0x46, text_alpha | 0xffffff00,1);

	ST_DrawString(-1, 210, "press \x8d to exit", text_alpha | 0xffffff00,1);
}
