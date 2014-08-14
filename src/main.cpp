/*==============================================================================
 *  Flappy James    |   version 1.0     |   zlib license    |   2014-07-16
 *  James Hendrie   |                   hendrie.james@gmail.com
 *                                      http://www.someplacedumb.net/games
 *
 *  Flappy James is a Flappy Bird knockoff.  I wrote it both as practice and to
 *  amuse my 4-year-old neice, who it turns out is not terribly impressed by it.
 *  Oh well.
 *
 *  This game is licensed under the zlib license; see COPYING.txt for more info.
 *
 *  The music is by Kevin MacLeod, licensed under the CC:BY 3.0 license; see
 *  LICENSE_CC-BY-3.0.txt for more info.
 *
 *  In general, you can also peruse the CREDITS.txt file for additional details,
 *  including information about the sound effects used.
 *
 *                                                  Initial release:  2014-07-16
 =============================================================================*/
#ifndef UTIL_H
#include "util.h"
#endif



int main( int argc, char *argv[] )
{
    /*  Do some argument checking */
    int result = check_args( argc, argv );
    if( result == -1 )
        return( 0 );
    else if( result > 0 )
        return( result );

    /*  Initialize everything */
    if( ! init() )
    {
        printf("ERROR:  Could not init\n");
        return(1);
    }

    /*  Load all of the media */
    if( ! load_media() )
    {
        printf("ERROR:  Could not load media\n");
        return(1);
    }

    /*  Play the music */
    if( Mix_PlayMusic( gMusic, -1 ) == -1 )
    {
        printf("ERROR:  Unable to play music:  %s\n", Mix_GetError() );
        return( false );
    }


    /*  SDL event struct */
    SDL_Event e;

    /*  Timer to cap the FPS */
    Timer cap;

    /*  Main loop */
    while( gQuit == false )
    {
        /*  Start the timer at the top of every frame */
        cap.start();

        /*  Pass event struct to events handler */
        events( e );

        /*  Update everything */
        update();

        /*  Render everything */
        render();

        /*  Update the screen */
        SDL_RenderPresent( gRenderer );

        /*  If we're limiting FPS... limit the fps */
        if( gLimitFPS )
        {
            /*  Get the ticks */
            Uint32 ticks = cap.get_ticks();

            /*  Delay if necessary */
            if( ticks < gTPF )
                SDL_Delay( gTPF - ticks );
        }
    }


    /*  Close out everything */
    close();

    return(0);
}
