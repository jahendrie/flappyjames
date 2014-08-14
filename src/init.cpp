/*******************************************************************************
 *  init.cpp
 *
 *  This file controls the initialization for all of the SDL stuff and various
 *  other global things that just need to be set somewhere.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                   INIT COLOR
--------------------------------------------------------------------------------
 *  This function initializes an individual color.  It's only here because I
 *  didn't want to compile with -std=c++11.
*/
SDL_Color init_color( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_Color color = { r, g, b, 255 };

    return( color );
}



/*
--------------------------------------------------------------------------------
                                  INIT COLORS
--------------------------------------------------------------------------------
 *  This inits all of the colors used in the global colors array.
*/
void init_colors( void )
{
    colors[ COLOR_WHITE ] = init_color( 255, 255, 255 );
    colors[ COLOR_RED ] = init_color( 255, 0, 0 );
    colors[ COLOR_GREEN ] = init_color( 0, 255, 0 );
    colors[ COLOR_BLUE ] = init_color( 0, 0, 255 );
    colors[ COLOR_YELLOW ] = init_color( 255, 255, 0 );
    colors[ COLOR_VIOLET ] = init_color( 255, 0, 255 );
    colors[ COLOR_CYAN ] = init_color( 0, 255, 255 );
    colors[ COLOR_ORANGE ] = init_color( 255, 127, 0 );
    colors[ COLOR_HOT_PINK ] = init_color( 255, 0, 127 );
    colors[ COLOR_LIME ] = init_color( 127, 255, 0 );
    colors[ COLOR_TAN ] = init_color( 0xd2, 0xb4, 0x8c );
    colors[ COLOR_SKY_BLUE ] = init_color( 0x99, 0xcc, 0xff );
    colors[ COLOR_NIGHT_SKY ] = init_color( 0x3b, 0x59, 0x98 );
    colors[ COLOR_NIGHT_GROUND ] = init_color( 0x92, 0x7f, 0x70 );
    colors[ COLOR_BLACK ] = init_color( 0, 0, 0 );
}


/*
--------------------------------------------------------------------------------
                                    INIT SDL
--------------------------------------------------------------------------------
 *  Function to initialize SDL and its subsystems
*/
bool init_sdl( void )
{
    /*  Init SDL itself */
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK ) < 0 )
    {
        printf("ERROR:  Could not init SDL:  %s\n", SDL_GetError() );
        return( false );
    }

    /*  Init SDL_image */
    if( ! ( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        printf("ERROR:  Could not init SDL_image:  %s\n", IMG_GetError() );
        return( false );
    }

    /*  Init SDL_mixer */
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf("ERROR:  Could not init SDL_mixer:  %s\n", Mix_GetError() );
        return( false );
    }

    /*  Init SDL_ttf */
    if( TTF_Init() == -1 )
    {
        printf("ERROR:  Could not init SDL_ttf:  %s\n", TTF_GetError() );
        return( false );
    }


    /*  Joystick stuff */
    if( SDL_NumJoysticks() > 0 )
    {
        gPad1 = SDL_JoystickOpen( 0 );
        if( gPad1 == NULL )
            printf("WARNING:  Unable to open controller 0\n");
    }

    /*  Return true if we're good */
    return( true );
}


/*
--------------------------------------------------------------------------------
                               INIT WINDOW STUFF
--------------------------------------------------------------------------------
 *  This function creats the window and renderer for the game, assigning the
 *  global pointers created elsewhere to them.
*/
bool init_window_stuff( void )
{
    /*  Create the window */
    gWindow = SDL_CreateWindow( "Flappy James", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, gWidth, gHeight,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if( gWindow == NULL )
    {
        printf("ERROR:  Could not create window:  %s\n", SDL_GetError() );
        return( false );
    }

    /*  Create the renderer */
    if( gLimitFPS )
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    else
        gRenderer = SDL_CreateRenderer( gWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf("ERROR:  Could not create renderer:  %s\n", SDL_GetError() );
        return( false );
    }

    /*  Return true if successful */
    return( true );
}


/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Master init function, calls all of the other initialization functions in
 *  this file.
*/
bool init( void )
{
    /*  Init SDL stuff */
    if( ! init_sdl() )
        return( false );

    /*  Create the window and renderer */
    if( ! init_window_stuff() )
        return( false );

    /*  Init the colors */
    init_colors();

    /*  Seed rand */
    srand( (unsigned int)time(NULL) );

    /*  Set blend mode to blended */
    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

    /*  Choose which time of day we want */
    currentTimeOfDay = rand() % 2;

    /*  Grab all input */
    SDL_SetRelativeMouseMode( SDL_TRUE );
    SDL_SetWindowGrab( gWindow, SDL_TRUE );

    /*  If the player wants the music and all that to be muted, do so */
    if( gMute )
    {
        /*  Set the volumes to nil */
        Mix_Volume( -1, 0 );
        Mix_VolumeMusic( 0 );

        /*  Set their bools to false */
        gPlaySounds = false;
        gPlayMusic = false;
    }


    return( true );
}
