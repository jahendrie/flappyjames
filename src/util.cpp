/*******************************************************************************
 *  util.cpp
 *
 *  Defines global variables.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                   CONSTANTS
--------------------------------------------------------------------------------
*/
const int DEFAULT_SCREEN_WIDTH = 1280;      //  Default screen width
const int DEFAULT_SCREEN_HEIGHT = 720;      //  Default screen height
const int DEFAULT_FPS = 60;                 //  Default FPS
const int DEFAULT_TPF = 1000 / DEFAULT_FPS; //  Default TPF
const int GRAVITY = 1;                      //  Gravity constant
const int DEFAULT_MOVE_SPEED = 4;           //  Default movement speed

const std::string VERSION = "1.0";          //  Version number



/*
--------------------------------------------------------------------------------
                                VARIOUS INTEGERS
--------------------------------------------------------------------------------
*/
int gWidth = DEFAULT_SCREEN_WIDTH;          //  Set the global width to default
int gWidthOld = gWidth;                     //  Store width here for size change
int gHeight = DEFAULT_SCREEN_HEIGHT;
int gHeightOld = gHeight;
int bWidth = gWidth;                        //  Boundary width (same as gWidth)
int bWidthOld = bWidth;
int bHeight = gHeight - ( gHeight / 5 );    //  Boundary height (most of screen)
int bHeightOld = bHeight;
int gScale = 4;                             //  Scale for face and pipes dist.
int gFPS = DEFAULT_FPS;                     //  In case we want to change FPS
unsigned int gTPF = DEFAULT_TPF;            //  Global ticks per frame
int currentScreen = SCREEN_INTRO;           //  Set the first screen to intro
int currentTimeOfDay = TIME_DAY;            //  Set the first time to daytime
int gMoveSpeed = DEFAULT_MOVE_SPEED;        //  Movement speed
int gHighScore = 0;                         //  Highest score
Uint32 gPixelFormat = 0;                    //  Used later to create textures



/*
--------------------------------------------------------------------------------
                                VARIOUS BOOLEANS
--------------------------------------------------------------------------------
*/
bool gLimitFPS = false;         //  Do we purposely limit the FPS?
bool gQuit = false;             //  Do we want to quit?
bool gFullscreen = false;       //  Is the game window fullscreen?
bool gMute = false;             //  Do we started muted?
bool gPlaySounds = true;        //  Do we play sound effects?
bool gPlayMusic = true;         //  Do we play the music?


/*
--------------------------------------------------------------------------------
                                   SDL STUFF
--------------------------------------------------------------------------------
*/
SDL_Window *gWindow = NULL;             //  Global window
SDL_Renderer *gRenderer = NULL;         //  Global renderer
SDL_Joystick *gPad1 = NULL;             //  Gamepad
SDL_Color colors[ TOTAL_COLORS ];       //  All of the colors we want to use


/*
--------------------------------------------------------------------------------
                                   TTF STUFF
--------------------------------------------------------------------------------
*/
TTF_Font *gFont = NULL;             //  Biggest font
TTF_Font *gFontSmall = NULL;        //  Medium font
TTF_Font *gFontTiny = NULL;         //  Smallest font


/*
--------------------------------------------------------------------------------
                                 SOUND EFFECTS
--------------------------------------------------------------------------------
*/
Mix_Chunk *gFaceKilled = NULL;      //  'Punch' sound effect
Mix_Chunk *gFlap = NULL;            //  'Flap' sound effect
Mix_Chunk *gScore = NULL;           //  'Coin' sound effect



/*
--------------------------------------------------------------------------------
                                     MUSIC
--------------------------------------------------------------------------------
*/
Mix_Music *gMusic = NULL;       //  The music



/*
--------------------------------------------------------------------------------
                                  MY TEXTURES
--------------------------------------------------------------------------------
*/
Texture *gAButton = NULL;               //  Picture of a controller's 'A' btn
Texture *gIntroText = NULL;             //  'Press space'
Texture *gIntroTextShadow = NULL;       //  Intro text drop shadow
Texture *gCreditsText1 = NULL;          //  Who made the game
Texture *gCreditsText2 = NULL;          //  Who made the music
Texture *gCreditsText3 = NULL;          //  Misc


/*
--------------------------------------------------------------------------------
                                   MY OBJECTS
--------------------------------------------------------------------------------
*/
Face *gFace = NULL;                 //  The player character (face)
Pipes *gPipes = NULL;               //  The pipes
Ground *gGround = NULL;             //  The ground
Hud *gHud = NULL;                   //  The score counter
Menu *gMenu = NULL;                 //  The drop-down menu
Files *gFiles = NULL;               //  Handles reading/writing files
Clouds *gClouds = NULL;             //  The clouds
Buildings *gBuildings = NULL;       //  The buildings
Bushes *gBushes = NULL;             //  The bushes
Stars *gStars = NULL;               //  The stars
