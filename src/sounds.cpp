/*******************************************************************************
 *  sounds.cpp
 *
 *  This file defines the functions that control the toggling and muting of
 *  all sound effects and music.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  TOGGLE MUSIC
--------------------------------------------------------------------------------
 *  Toggles the music on or off
*/
void toggle_music( void )
{
    /*  If the music is playing, set the volume to zero and display the OSD */
    if( gPlayMusic )
    {
        Mix_VolumeMusic( 0 );
        gPlayMusic = false;
    }

    /*  If the music is not playing, turn it up */
    else
    {
        Mix_VolumeMusic( MIX_MAX_VOLUME );
        gPlayMusic = true;
    }
}



/*
--------------------------------------------------------------------------------
                                 TOGGLE SOUNDS
--------------------------------------------------------------------------------
 *  Toggles the sound effects on or off
*/
void toggle_sounds( void )
{
    /*  If the sounds are playing, turn all sfx to zero and display OSD */
    if( gPlaySounds )
    {
        Mix_Volume( -1, 0 );
        gPlaySounds = false;
    }

    /*  Otherwise, turn them all to max volume */
    else
    {
        Mix_Volume( -1, MIX_MAX_VOLUME );
        gPlaySounds = true;
    }

}
