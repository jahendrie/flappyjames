/*******************************************************************************
 *  events.cpp
 *
 *  This file defines the functions used to handle all events for the program,
 *  other than those few methods of classes that do similar.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  EVENTS INTRO
--------------------------------------------------------------------------------
 *  This handles the events on the intro screen.
*/
void events_intro( SDL_Event &e )
{
    /*  If they've struck a key */
    if( e.type == SDL_KEYUP )
    {
        /*  The space key starts the game */
        if( e.key.keysym.sym == SDLK_SPACE )
        {
            /*
             *  Flap the face, set the face to allow additional flapping
             *  immediately, and switch the screen to the main screen.
             */
            gFace->flap();
            gFace->set_flapped( false );
            currentScreen = SCREEN_MAIN;
        }
    }


    /*  If they click the mouse or press a joystick button */
    else if( e.type == SDL_MOUSEBUTTONUP || e.type == SDL_JOYBUTTONUP )
    {
        /*  Same as above */
        gFace->flap();
        gFace->set_flapped( false );
        currentScreen = SCREEN_MAIN;
    }
}


/*
--------------------------------------------------------------------------------
                                  EVENTS MAIN
--------------------------------------------------------------------------------
 *  Handle all events on the main screen
*/
void events_main( SDL_Event &e )
{
    /*
     *  The face is the only thing that needs to worry about events outside of
     *  quitting the game or changing the resolution, so just pass the events
     *  structs to the face.
     */
    gFace->events( e );
}


/*
--------------------------------------------------------------------------------
                                     EVENTS
--------------------------------------------------------------------------------
 *  
*/
void events( SDL_Event &e )
{
    /*  Poll for events */
    while( SDL_PollEvent( &e ) != 0 )
    {
        /*  If the user clicks the X button */
        if( e.type == SDL_QUIT )
            gQuit = true;

        /*  If they press (and then release) a key */
        if( e.type == SDL_KEYUP )
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    /*  ----    FALL THROUGH    ---- */
                case SDLK_q:
                    gQuit = true;
                    break;
                case SDLK_f:
                    toggle_fullscreen();
                    break;

                case SDLK_r:
                    reset();
                    break;

                case SDLK_m:
                    toggle_music();
                    break;

                case SDLK_s:
                    toggle_sounds();
                    break;

                case SDLK_g:

                    /*  Toggle input grabbing */
                    if( SDL_GetRelativeMouseMode() == SDL_TRUE )
                    {
                        SDL_SetRelativeMouseMode( SDL_FALSE );
                        SDL_SetWindowGrab( gWindow, SDL_FALSE );
                    }

                    else
                    {
                        SDL_SetRelativeMouseMode( SDL_TRUE );
                        SDL_SetWindowGrab( gWindow, SDL_TRUE );
                    }

                    break;

            }
        }

        /*  This is here to gather data whenever the window is resized */
        if( e.type == SDL_WINDOWEVENT )
        {
            switch( e.window.event )
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED:

                    /*  Get the width and height */
                    gWidth = e.window.data1;
                    gHeight = e.window.data2;

                    /*  Readjust the play boundaries */
                    bWidth = gWidth;
                    bHeight = gHeight - ( gHeight / 5 );

                    /*  Reset the game so that the readjustments take effect */
                    reset();

                    break;
            }
        }


        /*  Pass the event struct elsewhere */
        switch( currentScreen )
        {
            case SCREEN_MAIN:
                events_main( e );
                break;
            case SCREEN_INTRO:
                events_intro( e );
                break;
        }
    }
}
