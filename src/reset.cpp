/*******************************************************************************
 *  reset.cpp
 *
 *  This file is here to handle the reset() function, which resets everything
 *  important at certain points of the game.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CHANGE TIME
--------------------------------------------------------------------------------
 *  1/4 chance of switching from day to night or vis-versa
*/
void change_time( void )
{
    if( rand() % 4 == 0 )
    {
        if( currentTimeOfDay == TIME_DAY )
            currentTimeOfDay = TIME_NIGHT;
        else if( currentTimeOfDay == TIME_NIGHT )
            currentTimeOfDay = TIME_DAY;
    }
}


/*
--------------------------------------------------------------------------------
                                     RESET
--------------------------------------------------------------------------------
*/
void reset( void )
{
    /*  Delete all the things */
    kill_objects();

    /*  Switch time of day (or try to) */
    change_time();

    /*  Load all of our objects back up */
    if( ! load_objects() )
        printf("ERROR:  Could not load objects\n");

    /*  Reset movement speed */
    gMoveSpeed = DEFAULT_MOVE_SPEED;
}
