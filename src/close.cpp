/*******************************************************************************
 *  close.cpp
 *
 *  This class defines the functions used to free memory and close out the
 *  program.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  KILL OBJECTS
--------------------------------------------------------------------------------
 *  Closes all of the custom objects in the game.
*/
void kill_objects( void )
{
    /*  Get rid of the face (player character) */
    if( gFace != NULL )
    {
        delete gFace;
        gFace = NULL;
    }

    /*  Get rid of the background pipes */
    if( gPipes != NULL )
    {
        delete gPipes;
        gPipes = NULL;
    }

    /*  The ground texture */
    if( gGround != NULL )
    {
        delete gGround;
        gGround = NULL;
    }

    /*  The score counter at the bottom of the screen */
    if( gHud != NULL )
    {
        delete gHud;
        gHud = NULL;
    }

    /*  The drop-down menu when you die */
    if( gMenu != NULL )
    {
        delete gMenu;
        gMenu = NULL;
    }

    /*  The clouds in the background */
    if( gClouds != NULL )
    {
        delete gClouds;
        gClouds = NULL;
    }

    /*  The buildings in the background */
    if( gBuildings != NULL )
    {
        delete gBuildings;
        gBuildings = NULL;
    }

    /*  The bushes in the background */
    if( gBushes != NULL )
    {
        delete gBushes;
        gBushes = NULL;
    }

    /*  The stars in the background */
    if( gStars != NULL )
    {
        delete gStars;
        gStars = NULL;
    }
}


/*
--------------------------------------------------------------------------------
                                     CLOSE
--------------------------------------------------------------------------------
 *  Close everything, quit SDL
*/
void close( void )
{
    /*  Free graphical textures */
    delete gAButton;
    gAButton = NULL;

    /*  Free text textures */
    delete gIntroText;
    delete gIntroTextShadow;
    delete gCreditsText1;
    delete gCreditsText2;
    delete gCreditsText3;
    gIntroText = NULL;
    gIntroTextShadow = NULL;
    gCreditsText1 = NULL;
    gCreditsText2 = NULL;
    gCreditsText3 = NULL;

    /*  Free the objects */
    kill_objects();

    /*  Write the high score to disk and delete the files object */
    gFiles->write_score();
    delete gFiles;
    gFiles = NULL;

    /*  Free the sound effects */
    if( Mix_Playing( -1 ) > 0 )
        Mix_HaltChannel( -1 );
    Mix_FreeChunk( gFaceKilled );
    Mix_FreeChunk( gFlap );
    Mix_FreeChunk( gScore );
    gFaceKilled = NULL;
    gFlap = NULL;
    gScore = NULL;

    /*  Free the music */
    if( Mix_PlayingMusic() > 0 )
        Mix_HaltMusic();
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    /*  Free the fonts */
    TTF_CloseFont( gFont );
    TTF_CloseFont( gFontSmall );
    TTF_CloseFont( gFontTiny );
    gFont = NULL;
    gFontSmall = NULL;
    gFontTiny = NULL;

    /*  Kill the renderer and window */
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    /*  Kill the joystick */
    SDL_JoystickClose( gPad1 );
    gPad1 = NULL;

    /*  Quit SDL and its subsystems */
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
