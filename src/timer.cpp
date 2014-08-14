/*******************************************************************************
 *  timer.cpp
 *
 *  This file defines the methods of the Timer class.  The timer is used to cap
 *  the frame rate in the absence of vsync.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*/
Timer::Timer( void )
{
    /*  Init ticks */
    mTicksStart = mTicksPaused = 0;

    /*  Init status */
    mStarted = mPaused = false;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Timer::~Timer( void )
{
    /*  Reset everything to zero / false */
    mTicksStart = mTicksPaused = 0;
    mStarted = mPaused = false;
}


/*
--------------------------------------------------------------------------------
                                     START
--------------------------------------------------------------------------------
*/
void Timer::start( void )
{
    /*  Start the timer and set paused status to false */
    mStarted = true;
    mPaused = false;

    /*  Get the current ticks */
    mTicksStart = SDL_GetTicks();

    /*  Reset paused ticks */
    mTicksPaused = 0;
}



/*
--------------------------------------------------------------------------------
                                      STOP
--------------------------------------------------------------------------------
*/
void Timer::stop( void )
{
    /*  Set started and paused status to false */
    mStarted = false;
    mPaused = false;

    /*  Set all ticks to zero */
    mTicksStart = 0;
    mTicksPaused = 0;
}



/*
--------------------------------------------------------------------------------
                                     TOGGLE
--------------------------------------------------------------------------------
 *  Toggles the timer paused / unpaused
*/
void Timer::toggle( void )
{
    /*  Can't toggle if the timer hasn't even started yet */
    if( mStarted )
    {
        /*  If it's not paused */
        if( ! mPaused )
        {
            /*  Pause the timer */
            mPaused = true;

            /*  Calculate ticks */
            mTicksPaused = SDL_GetTicks() - mTicksStart;

            /*  Reset start ticks */
            mTicksStart = 0;
        }

        /*  If it IS paused */
        else if( mPaused )
        {
            /*  Unpause timer */
            mPaused = false;

            /*  Reset start ticks */
            mTicksStart = SDL_GetTicks() - mTicksPaused;

            /*  Reset paused ticks */
            mTicksPaused = 0;
        }
    }
}


/*
--------------------------------------------------------------------------------
                                   GET TICKS
--------------------------------------------------------------------------------
*/
Uint32 Timer::get_ticks( void )
{
    /*  If the timer has been started */
    if( mStarted )
    {
        /*  If it's paused, get the ticks from when it was paused */
        if( mPaused )
            return( mTicksPaused );

        /*  Otherwise, get the current timer ticks */
        else if( ! mPaused )
            return( SDL_GetTicks() - mTicksStart );
    }

    /*  If the timer wasn't started yet, just return zero */
    return( 0 );
}



/*
--------------------------------------------------------------------------------
                                  TIMER STATUS
--------------------------------------------------------------------------------
*/
bool Timer::is_started( void )
{
    /*  Has the timer been started ? */
    return( mStarted );
}


bool Timer::is_paused( void )
{
    /*  Is the timer running and paused? */
    return( ( mStarted && mPaused ) );
}
