/*******************************************************************************
 *  resize.cpp
 *
 *  This file defines the toggle_fullscreen() function, which switches
 *  fullscreen on/off and sets the gScale variable.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


void toggle_fullscreen( void )
{
    /*  If we're turning fullscreen on */
    if( ! gFullscreen )
    {
        SDL_SetWindowFullscreen( gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP );
        gFullscreen = true;
        gScale = 3;
    }

    /*  If we're turning it off */
    else
    {
        SDL_SetWindowFullscreen( gWindow, SDL_FALSE );
        gFullscreen = false;
        gScale = 4;
    }
}
