/*******************************************************************************
 *  util.h
 *
 *  This file declares all of the global variables and includes the various
 *  other headers that this game needs.
 *
*******************************************************************************/
#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>



/*
--------------------------------------------------------------------------------
                                    STRUCTS
--------------------------------------------------------------------------------
*/

/*
 *  Collider struct
 *      Used for per-pixel collision detection
 */
struct Collider
{
    int x;              //  X position
    int y;              //  Y position
    int w;              //  Width
    int h;              //  Height
    bool a;             //  Whether or not alpha in the rect has been activated
};


/*
 *  Circle struct
 *      Theoretically used for circular collision detection, though I don't
 *      think I actually use any in the game.  Still, I guess it's a good thing
 *      to have around.
 */
struct Circle
{
    int x;      //  X position
    int y;      //  Y position
    int r;      //  Radius
};




/*
--------------------------------------------------------------------------------
                                     ENUMS
--------------------------------------------------------------------------------
*/

/*  Used to determine which screen we're on */
enum screensEnum
{
    SCREEN_MAIN,
    SCREEN_INTRO,
    TOTAL_SCREENS
};

/*  Used for an SDL_Color array; convenient for the simple-minded like me */
enum colors
{
    COLOR_WHITE,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_VIOLET,
    COLOR_CYAN,
    COLOR_ORANGE,
    COLOR_HOT_PINK,
    COLOR_LIME,
    COLOR_TAN,
    COLOR_SKY_BLUE,
    COLOR_NIGHT_SKY,
    COLOR_NIGHT_GROUND,
    COLOR_BLACK,
    TOTAL_COLORS
};


/*  Which time of day it is */
enum timesOfDay
{
    TIME_DAY,
    TIME_NIGHT,
    TOTAL_TIMES
};


/*
--------------------------------------------------------------------------------
                                   CONSTANTS
--------------------------------------------------------------------------------
*/
extern const int DEFAULT_SCREEN_WIDTH;      //  Default screen width
extern const int DEFAULT_SCREEN_HEIGHT;     //  Default screen height
extern const int DEFAULT_FPS;               //  Default FPS
extern const int DEFAULT_TPF;               //  Default ticks per frame
extern const int GRAVITY;                   //  Default gravity constant
extern const int DEFAULT_MOVE_SPEED;        //  Default movement speed

extern const std::string VERSION;           //  Version number


/*
--------------------------------------------------------------------------------
                                VARIOUS INTEGERS
--------------------------------------------------------------------------------
*/
extern int gWidth;                  //  Screen width
extern int gHeight;                 //  Screen height
extern int gWidthOld;               //  Store screen width when screen changes
extern int gHeightOld;              //  Store screen height when screen changes
extern int bWidth;                  //  Boundary width (play area)
extern int bHeight;                 //  Boundary height
extern int bWidthOld;
extern int bHeightOld;
extern int gScale;                  //  How to scale the head / pipes distance
extern int gFPS;                    //  FPS
extern unsigned int gTPF;           //  Ticks per frame
extern int currentScreen;           //  Which screen we're on
extern int currentTimeOfDay;        //  Which time of day it is
extern int gMoveSpeed;              //  The current movement speed
extern int gHighScore;              //  The high score
extern Uint32 gPixelFormat;         //  Used to create textures


/*
--------------------------------------------------------------------------------
                                VARIOUS BOOLEANS
--------------------------------------------------------------------------------
*/
extern bool gLimitFPS;      //  Do we limit FPS?
extern bool gQuit;          //  Do we want to quit?
extern bool gFullscreen;    //  Is the window in fullscreen mode?
extern bool gMute;          //  Does the game start muted?
extern bool gPlaySounds;    //  Do we want to play sound effects?
extern bool gPlayMusic;     //  Do we want to play music?


/*
--------------------------------------------------------------------------------
                                   SDL STUFF
--------------------------------------------------------------------------------
*/
extern SDL_Window *gWindow;                 //  Global window
extern SDL_Renderer *gRenderer;             //  Global renderer
extern SDL_Joystick *gPad1;                 //  Gamepad
extern SDL_Color colors[ TOTAL_COLORS ];    //  The colors we want to use


/*
--------------------------------------------------------------------------------
                                   TTF STUFF
--------------------------------------------------------------------------------
*/
extern TTF_Font *gFont;         //  Biggest font
extern TTF_Font *gFontSmall;    //  Medium font
extern TTF_Font *gFontTiny;     //  Smallest font


/*
--------------------------------------------------------------------------------
                                 SOUND EFFECTS
--------------------------------------------------------------------------------
*/
extern Mix_Chunk *gFaceKilled;      //  'Punch' sound effect
extern Mix_Chunk *gFlap;            //  'Flap' sound effect
extern Mix_Chunk *gScore;           //  'Coin' sound effect



/*
--------------------------------------------------------------------------------
                                     MUSIC
--------------------------------------------------------------------------------
*/
extern Mix_Music *gMusic;           //  The music



/*
--------------------------------------------------------------------------------
                                   MY HEADERS
--------------------------------------------------------------------------------
*/

/*  Include all the custom classes */
#ifndef CLASSES_H
#include "classes.h"
#endif

/*  Include this to define functions used globally */
#ifndef PROTOTYPES_H
#include "prototypes.h"
#endif


/*
--------------------------------------------------------------------------------
                                  MY TEXTURES
--------------------------------------------------------------------------------
*/
extern Texture *gAButton;           //  'A' button picture
extern Texture *gIntroText;         //  Intro text (press space/press 'A')
extern Texture *gIntroTextShadow;   //  Intro text drop shadow
extern Texture *gCreditsText1;      //  Who made the game
extern Texture *gCreditsText2;      //  Who made the music
extern Texture *gCreditsText3;      //  Misc



/*
--------------------------------------------------------------------------------
                                   MY OBJECTS
--------------------------------------------------------------------------------
*/
extern Face *gFace;                 //  The face (player character)
extern Pipes *gPipes;               //  The pipes
extern Ground *gGround;             //  The ground
extern Hud *gHud;                   //  The score counter
extern Menu *gMenu;                 //  The dropdown menu
extern Files *gFiles;               //  Handles file IO
extern Clouds *gClouds;             //  The clouds
extern Buildings *gBuildings;       //  The buildings
extern Bushes *gBushes;             //  The bushes
extern Stars *gStars;               //  The stars

#endif
