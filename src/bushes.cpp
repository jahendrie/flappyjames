/*******************************************************************************
 *  bushes.cpp
 *
 *  This file defines the Bushes class, which creates, updates and displays the
 *  bushes that scroll in the background.
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
Bushes::Bushes( void )
{
    /*  Init the texture pointers to null */
    for( int i = 0; i < TOTAL_TIMES; ++i )
    {
        mBushTextures[ i ] = NULL;
    }

    /*  Clear the vector, because I am superstitious */
    mBushes.clear();

    /*  Set scale to two */
    mScale = 1;
}



/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Bushes::~Bushes( void )
{
    /*  Free the textures */
    free_textures();

    /*  Clear vector because why not */
    mBushes.clear();
}



/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  Free all of the textures used
*/
void Bushes::free_textures( void )
{
    /*  For each of the times of day */
    for( int i = 0; i < TOTAL_TIMES; ++i )
    {
        /*  Get rid of the texture if it exists */
        if( mBushTextures[ i ] != NULL )
        {
            delete mBushTextures[ i ];
            mBushTextures[ i ] = NULL;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
*/
bool Bushes::init( void )
{
    /*  Load daytime bush */
    mBushTextures[ TIME_DAY ] = new Texture();
    if( ! mBushTextures[ TIME_DAY ]->create_texture_from_file(
                "data/gfx/bushes-day.png" ))
    {
        printf("ERROR:  Could not load daytime bushes texture\n");
        return( false );
    }


    /*  Load nightime bush */
    mBushTextures[ TIME_NIGHT ] = new Texture();
    if( ! mBushTextures[ TIME_NIGHT ]->create_texture_from_file(
                "data/gfx/bushes-night.png" ))
    {
        printf("ERROR:  Could not load nighttime bushes texture\n");
        return( false );
    }


    /*  Init the clips */
    for( int i = 0; i < TOTAL_BUSHES; ++i )
    {
        mClips[ i ].x = 0;
        mClips[ i ].y = i * 64;
        mClips[ i ].w = 128;
        mClips[ i ].h = 64;
    }


    /*  Lay out the initial row of bushes */
    layout();


    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
*/
void Bushes::layout( void )
{
    /*  Make some bushes man */
    for( int i = 0; i < ( gWidth - ( 128 * mScale) ) + 1; ++i )
    {
        add_bush( i * ( 128 * mScale), bHeight - ( 64 * mScale ) );
    }
}



/*
--------------------------------------------------------------------------------
                                    ADD BUSH
--------------------------------------------------------------------------------
*/
void Bushes::add_bush( int x, int y )
{
    /*  Create an instance of the bush struct */
    struct BushStruct bush;

    /*  Set the position and dimensions */
    bush.x = x;
    bush.y = y;
    bush.w = 128 * mScale;
    bush.h = 64 * mScale;

    /*  Set its random clip */
    bush.clip = mClips[ rand() % 3 ];

    /*  Stick it onto the bushes vector */
    mBushes.push_back( bush );
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Bushes::update( void )
{
    /*  Create the bushes iterator */
    std::vector<BushStruct>::iterator b;

    /*  Check for dead bushes, move the rest, maybe add one */
    for( b = mBushes.begin(); b != mBushes.end(); )
    {
        /*  If a bush has gone too far left */
        if( b->x < -( b->w ) )
        {
            /*  Erase that bush */
            mBushes.erase( b );

            /*  Add a new one on the right */
            add_bush( gWidth, bHeight );
        }

        /*  Otherwise */
        else
        {
            /*  Move the bush to the left */
            if( gMoveSpeed > 0 )
                b->x -= gMoveSpeed / 2;

            /*  Increment the bush iterator */
            ++b;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Bushes::render( void )
{
    /*  Create the bushes iterator */
    std::vector<BushStruct>::iterator b;

    /*  Render all ze bushes */
    for( b = mBushes.begin(); b != mBushes.end(); ++b )
    {
        mBushTextures[ currentTimeOfDay ]->render(
                b->x, b->y, b->w, b->h, &b->clip );
    }
}
