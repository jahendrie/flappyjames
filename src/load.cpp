/*******************************************************************************
 *  load.cpp
 *
 *  This file handles the loading of all media and creation of various special
 *  objects used throughout the program.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                    LOAD GFX
--------------------------------------------------------------------------------
 *      Load all non-class graphics in the game
*/
bool load_gfx( void )
{
    gAButton = new Texture();
    if( ! gAButton->create_texture_from_file( "data/gfx/abutton.png" ) )
    {
        printf("ERROR:  Could not load 'A Button' texture\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD TEXT
--------------------------------------------------------------------------------
*/
bool load_text( void )
{
    /*  Create the textures */
    gIntroText = new Texture();
    gIntroTextShadow = new Texture();

    /*  If we have a joystick plugged in, alter the intro text a bit */
    if( SDL_NumJoysticks() > 0 )
    {
        /*  Main intro text */
        if( ! gIntroText->create_texture_from_string( gFont,
                    "Press      to start", colors[ COLOR_WHITE ] ) )
        {
            printf("ERROR:  Could not load intro text\n");
            return( false );
        }


        /*  Drop shadow text */
        if( ! gIntroTextShadow->create_texture_from_string( gFont,
                    "Press      to start", colors[ COLOR_BLACK ] ))
        {
            printf("ERROR:  Could not load intro text shadow\n");
            return( false );
        }
    }

    /*  Otherwise, create the 'default' intro text */
    else
    {
        /*  Main intro text */
        if( ! gIntroText->create_texture_from_string( gFont,
                    "Press SPACE to start", colors[ COLOR_WHITE ] ) )
        {
            printf("ERROR:  Could not load intro text\n");
            return( false );
        }


        /*  Drop shadow text */
        if( ! gIntroTextShadow->create_texture_from_string( gFont,
                    "Press SPACE to start", colors[ COLOR_BLACK ] ))
        {
            printf("ERROR:  Could not load intro text shadow\n");
            return( false );
        }
    }

    /*  Now do the credits text strings */
    gCreditsText1 = new Texture();
    gCreditsText2 = new Texture();
    gCreditsText3 = new Texture();

    if( ! gCreditsText1->create_texture_from_string( gFontTiny,
                "Programming, art, etc by James Hendrie", colors[ COLOR_WHITE] ))
    {
        printf("ERROR:  Could not load credits text 1\n");
        return( false );
    }

    if( ! gCreditsText2->create_texture_from_string( gFontTiny,
                "Music by Kevin MacLeod", colors[ COLOR_WHITE] ))
    {
        printf("ERROR:  Could not load credits text 2\n");
        return( false );
    }

    if( ! gCreditsText3->create_texture_from_string( gFontTiny,
                "See CREDITS.txt for details", colors[ COLOR_WHITE] ))
    {
        printf("ERROR:  Could not load credits text 3\n");
        return( false );
    }


    return( true );
}


/*
--------------------------------------------------------------------------------
                                   LOAD FONTS
--------------------------------------------------------------------------------
 *  Load global fonts
*/
bool load_fonts( void )
{
    /*  Biggest font */
    gFont = TTF_OpenFont( "data/fonts/Minercraftory.ttf", 64 );
    if( gFont == NULL )
    {
        printf("ERROR:  Could not load font:  %s\n", TTF_GetError() );
        return( false );
    }

    /*  Smaller (medium) */
    gFontSmall = TTF_OpenFont( "data/fonts/Minercraftory.ttf", 32 );
    if( gFontSmall == NULL )
    {
        printf("ERROR:  Could not load font:  %s\n", TTF_GetError() );
        return( false );
    }

    /*  'Tiny' (smallest) */
    gFontTiny = TTF_OpenFont( "data/fonts/Minercraftory.ttf", 24 );
    if( gFontTiny == NULL )
    {
        printf("ERROR:  Could not load font:  %s\n", TTF_GetError() );
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                  LOAD PLAYER
--------------------------------------------------------------------------------
 *  Load the player object and media
*/
bool load_player( void )
{
    /*  Create the face object */
    gFace = new Face();
    
    /*  Initialize the face */
    if( ! gFace->init() )
    {
        printf("ERROR:  Could not load face\n");
        return( false );
    }

    /*  Scale the face down (relative scaling) */
    gFace->set_scale( gScale );

    /*  Position the face */
    gFace->set_default_position(
            ( gWidth - gFace->get_width() ) / 2,
            ( gHeight - gFace->get_width() ) / 2 );
    gFace->set_position(
            ( gWidth - gFace->get_width() ) / 2,
            ( gHeight - gFace->get_width() ) / 2 );

    /*  Scale the face's pixel colliders */
    gFace->scale_colliders( gScale );


    /*  Return true if we were successful */
    return( true );
}


/*
--------------------------------------------------------------------------------
                                   LOAD PIPES
--------------------------------------------------------------------------------
 *  Load the game's pipes!
*/
bool load_pipes( void )
{
    /*  Create the pipes object */
    gPipes = new Pipes();

    /*  Initialize it */
    if( ! gPipes->init() )
    {
        printf("ERROR:  Could not init pipes\n");
        return( false );
    }

    return( true );
}


/*
--------------------------------------------------------------------------------
                                  LOAD GROUND
--------------------------------------------------------------------------------
 *  Load the goddamn ground
*/
bool load_ground( void )
{
    gGround = new Ground();

    if( ! gGround->init() )
    {
        printf("ERROR:  Could not init ground\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                    LOAD HUD
--------------------------------------------------------------------------------
 *  Load the Heads Up Display
*/
bool load_hud( void )
{
    gHud = new Hud();

    if( ! gHud->init() )
    {
        printf("ERROR:  Could not init HUD\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                  LOAD SOUNDS
--------------------------------------------------------------------------------
 *  Load all of the sound effects in the game
*/
bool load_sounds( void )
{
    /*  Sound played when the player hits a pipe or the ground */
    gFaceKilled = Mix_LoadWAV( "data/sfx/sound_punch.ogg" );
    if( gFaceKilled == NULL )
    {
        printf("ERROR:  Could not load the face killed sound effect:  %s\n",
                Mix_GetError() );
        return( false );
    }

    /*  Sound played when the player 'flaps' the head */
    gFlap = Mix_LoadWAV( "data/sfx/sound_flap.ogg" );
    if( gFlap == NULL )
    {
        printf("ERROR:  Could not load the flap sound:  %s\n", Mix_GetError() );
        return( false );
    }

    /*  Sound played when the player successfully passes through pipes */
    gScore = Mix_LoadWAV( "data/sfx/sound_score.ogg" );
    if( gScore == NULL )
    {
        printf("ERROR:  Could not load the score sound:  %s\n", Mix_GetError());
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD MUSIC
--------------------------------------------------------------------------------
 *  Load the music for the game
*/
bool load_music( void )
{
    /*  Main theme */
    gMusic = Mix_LoadMUS( "data/music/silly-fun.ogg" );
    if( gMusic == NULL )
    {
        printf("ERROR:  Unable to load music file:  %s\n", Mix_GetError() );
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD FILES
--------------------------------------------------------------------------------
 *  Load the object that reads from and writes to files
*/
bool load_files( void )
{
    /*  Create the files object */
    gFiles = new Files();

    /*  Restore the high score if it exists */
    if( ! gFiles->read_score() )
    {
        /*  If the score file cannot be read from, create it */
        if( gFiles->write_score() )
            printf("Created file '%s'\n", gFiles->get_data_path() );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                   LOAD MENU
--------------------------------------------------------------------------------
 *  Load the menu object - drop-down menu after the player dies
*/
bool load_menu( void )
{
    gMenu = new Menu();

    if( ! gMenu->init() )
    {
        printf("ERROR:  Could not init menu object\n");
        return( false );
    }

    return( true );
}


/*
--------------------------------------------------------------------------------
                                  LOAD CLOUDS
--------------------------------------------------------------------------------
 *  Loads the game's clouds
*/
bool load_clouds( void )
{
    gClouds = new Clouds();

    if( ! gClouds->init() )
    {
        printf("ERROR:  Could not init clouds\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                 LOAD BUILDINGS
--------------------------------------------------------------------------------
 *  Load the game's background buildings
*/
bool load_buildings( void )
{
    gBuildings = new Buildings();

    if( ! gBuildings->init() )
    {
        printf("ERROR:  Could not init buildings\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                                  LOAD BUSHES
--------------------------------------------------------------------------------
 *  Load the bushes displayed in the background
*/
bool load_bushes( void )
{
    gBushes = new Bushes();

    if( ! gBushes->init() )
    {
        printf("ERROR:  Could not init bushes\n");
        return( false );
    }

    return( true );
}




/*
--------------------------------------------------------------------------------
                                   LOAD STARS
--------------------------------------------------------------------------------
*/
void load_stars( void )
{
    gStars = new Stars();
}



/*
--------------------------------------------------------------------------------
                                  LOAD OBJECTS
--------------------------------------------------------------------------------
 *  Load global objects
*/
bool load_objects( void )
{
    /*  Load player object */
    if( ! load_player() )
    {
        printf("ERROR:  Could not load player object\n");
        return( false );
    }

    /*  Load the global pipes object */
    if( ! load_pipes() )
    {
        printf("ERROR:  Could not load pipes\n");
        return( false );
    }

    /*  Load the ground */
    if( ! load_ground() )
    {
        printf("ERROR:  Could not load ground\n");
        return( false );
    }

    /*  Load the HUD */
    if( ! load_hud() )
    {
        printf("ERROR:  Could not load HUD\n");
        return( false );
    }

    /*  Load the menu object */
    if( ! load_menu() )
    {
        printf("ERROR:  Could not load menu object\n");
        return( false );
    }

    /*  Load the clouds, man */
    if( ! load_clouds() )
    {
        printf("ERROR:  Could not load clouds\n");
        return( false );
    }

    /*  Load the buildings */
    if( ! load_buildings() )
    {
        printf("ERROR:  Could not load buildings\n");
        return( false );
    }

    /*  Load the bushes */
    if( ! load_bushes() )
    {
        printf("ERROR:  Could not load bushes\n");
        return( false );
    }

    /*  Load the stars, if appropriate */
    if( currentTimeOfDay == TIME_NIGHT )
        load_stars();

    return( true );
}


/*
--------------------------------------------------------------------------------
                                   LOAD MEDIA
--------------------------------------------------------------------------------
 *  Master media loading function; calls other functions to load graphics, sound
 *  effects, music and text.
*/
bool load_media( void )
{
    /*  Load graphics */
    if( ! load_gfx() )
    {
        printf("ERROR:  Could not load graphics\n");
        return( false );
    }

    /*  Load sounds */
    if( ! load_sounds() )
    {
        printf("ERROR:  Could not load sounds\n");
        return( false );
    }

    /*  Load the music */
    if( ! load_music() )
    {
        printf("ERROR:  Could not load the music\n");
        return( false );
    }

    /*  Load fonts */
    if( ! load_fonts() )
    {
        printf("ERROR:  Could not load fonts\n");
        return( false );
    }

    /*  Load text texture objects */
    if( ! load_text() )
    {
        printf("ERROR:  Could not load text textures\n");
        return( false );
    }

    /*  Load the files object */
    if( ! load_files() )
    {
        printf("ERROR:  Could not load files object\n");
        return( false );
    }

    /*  Load global objects */
    if( ! load_objects() )
    {
        printf("ERROR:  Could not load global objects\n");
        return( false );
    }


    return( true );
}
