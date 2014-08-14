/*******************************************************************************
 *  ground.cpp
 *
 *  This file defines the methods used to create, update and render the ground.
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
Ground::Ground( void )
{
    /*  Null our the ground texture pointer */
    mGroundTexture = NULL;

    /*  Change the dirt color depending on the time of day */
    if( currentTimeOfDay == TIME_DAY )
        mColor = colors[ COLOR_TAN ];
    else if( currentTimeOfDay == TIME_NIGHT )
        mColor = colors[ COLOR_NIGHT_GROUND ];
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Ground::~Ground( void )
{
    free_texture();
    mTiles.clear();
}


/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
 *  Frees our one and only texture
*/
void Ground::free_texture( void )
{
    if( mGroundTexture != NULL )
    {
        delete mGroundTexture;
        mGroundTexture = NULL;
    }
}


/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Create and load our texture object
*/
bool Ground::init( void )
{
    /*  Create and load the ground texture object */
    mGroundTexture = new Texture();
    if( ! mGroundTexture->create_texture_from_file( "data/gfx/ground1.png" ) )
    {
        printf("ERROR:  Could not load ground texture\n");
        return( false );
    }

    /*  If it's night time, adjust the color */
    if( currentTimeOfDay == TIME_NIGHT )
    {
        mGroundTexture->set_color_mod(
                colors[ COLOR_NIGHT_SKY ].r,
                colors[ COLOR_NIGHT_SKY ].g,
                colors[ COLOR_NIGHT_SKY ].b );
    }


    /*  Populate our vector */
    for( int t = 0; t <= gWidth / mGroundTexture->get_width(); ++t )
    {
        /*  Create our rect */
        SDL_Rect tRect = {
            t * mGroundTexture->get_width(),
            bHeight,
            mGroundTexture->get_width(),
            mGroundTexture->get_height() };

        /*  Push the rect onto the vector */
        mTiles.push_back( tRect );
    }

    return( true );
}


/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Update the ground tiles
*/
void Ground::update( void )
{
    /*  Create the iterator */
    std::vector<SDL_Rect>::iterator t;

    /*
     *  Go through the vector.  When we find one that's gone too far left, we
     *  erase it and add a new one on the right.
     */
    for( t = mTiles.begin(); t != mTiles.end(); )
    {
        /*  Move this 'tile' to the left */
        t->x -= gMoveSpeed;

        /*  If the tile's gone too far left */
        if( t->x < -mGroundTexture->get_width() )
        {
            /*  Erase the old one */
            mTiles.erase( t );

            /*  Create the new one */
            SDL_Rect tRect = {
                mTiles.end()->x + mGroundTexture->get_width(),
                bHeight,
                mGroundTexture->get_width(),
                mGroundTexture->get_height() };

            /*  Push it onto the vector */
            mTiles.push_back( tRect );
        }

        /*  Otherwise, just increment the iterator to move on */
        else
            ++t;
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Ground::render( void )
{
    /*  Create the iterator */
    std::vector<SDL_Rect>::iterator t;

    /*  Go through all the tiles and render them */
    for( t = mTiles.begin(); t != mTiles.end(); ++t )
    {
        mGroundTexture->render( t->x, t->y, t->w, t->h );
    }

    /*  Change the render color to that of the dirt's */
    SDL_SetRenderDrawColor( gRenderer, mColor.r, mColor.g, mColor.b, 255 );

    /*  This rect fills the rest of the bottom of the screen */
    SDL_Rect dRect = { 0, bHeight + mGroundTexture->get_height(),
        gWidth, bHeight - mGroundTexture->get_height() };

    /*  Fill the rect */
    SDL_RenderFillRect( gRenderer, &dRect );

}
