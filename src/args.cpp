/*******************************************************************************
 *  args.cpp
 *
 *  This file defines how the arguments are parsed by the program.  Only a few
 *  are checked for; anything else triggers a warning but the program continues
 *  to execute as normal.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



/*
--------------------------------------------------------------------------------
                                   PRINT HELP
--------------------------------------------------------------------------------
 *  Prints help text.
*/
void print_help( void )
{
    printf("Usage:  flappyjames [OPTION]\n\n");
    printf("Flappy James is a Flappy Bird knockoff.  If you aren't familar\n");
    printf("with the genre, your goal in this game is to pilot the face ");
    printf("between\npairs of pipes.  The more pipes you pass, the higher ");
    printf("your score.\n\n");

    printf("To flap the head, you can press the spacebar, click the mouse or ");
    printf("push a button\non your gamepad (assuming it's plugged in).  ");
    printf("To quit, press ESCAPE or 'Q'.\n\n");

    printf("Additionally, you may press 'S' to mute sound effects, 'M' to ");
    printf("mute the music,\n'G' to toggle mouse grabbing and 'R' to reset ");
    printf("the game.\n\n");

    printf("Options:\n\n");
    printf("  -h or --help:\t\tPrint this help text\n");
    printf("  -v or --version:\tPrint version and author info\n");
    printf("  -l or --limit-fps:\tLimit FPS to 60, disable vsync\n");
    printf("  -m or --mute:\t\tStart with music and sound muted\n");
}


/*
--------------------------------------------------------------------------------
                                 PRINT VERSION
--------------------------------------------------------------------------------
 *  Prints version and author info.
*/
void print_version( void )
{
    printf("Flappy James version %s\n", VERSION.c_str() );
    printf("James Hendrie <hendrie.james@gmail.com>\n");
    printf("http://www.someplacedumb.net/games\n");
}


/*
--------------------------------------------------------------------------------
                                   CHECK ARGS
--------------------------------------------------------------------------------
 *  The 'master' function for this file; decides how to handle each of the valid
 *  arguments and calls the appropriate function if necessary.  Invalid
 *  arguments generate a warning but are otherwise ignored.
*/
int check_args( int argc, char *argv[] )
{
    /*  String to hold the arg in for easy string comparison */
    std::string arg;

    /*  While (/if) there's at least one argument (not incl. the program) */
    while( argc > 1 )
    {
        /*  Copy the arg string constant to the std::string object */
        arg.assign( argv[1] );

        /*  If they want help */
        if( arg == "-h" || arg == "--help" )
        {
            print_help();
            return( -1 );
        }

        /*  If they want version and author info */
        else if( arg == "-v" || arg == "--version" )
        {
            print_version();
            return( -1 );
        }

        /*  If they want to mute the sound effects and music */
        else if( arg == "-m" || arg == "--mute" )
        {
            /*  Mute the stuff */
            gMute = true;
        }

        /*  If they want to limit FPS */
        else if( arg == "-l" || arg == "--limit-fps" )
        {
            gLimitFPS = true;
        }


        /*  Any other argument generates a warning */
        else
            printf("WARNING:  Unknown option:  '%s'\n", argv[1] );

        /*
         *  By decrementing the arg count we let the program know when it needs
         *  to quit checking for args.  By increasing the arg pointer, we make
         *  sure we're pointing at a new arg every loop.
         */
        --argc;
        ++argv;
    }

    /*  Return success by default */
    return( 0 );
}
