/*******************************************************************************
 *  stars.cpp
 *
 *  This file defines the Stars class, which creates and renders the stars in
 *  the sky (assuming it's night).
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
Stars::Stars( void )
{
    /*  For every pixel in the visible sky */
    for( int x = 0; x < gWidth; ++x )
    {
        for( int y = 0; y < bHeight; ++y )
        {
            /*  Approx. 1/1000 chance of adding a star to that position */
            if( rand() % 1000 == 0 )
            {
                add_star( x, y );
            }
        }
    }
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Stars::~Stars( void )
{
    mStars.clear();
}



/*
--------------------------------------------------------------------------------
                                    ADD STAR
--------------------------------------------------------------------------------
 *  Add a star to the mStars vector
*/
void Stars::add_star( int x, int y )
{
    /*  Create an instance of our struct */
    struct StarStruct star;

    /*  Set the star's position */
    star.x = x;
    star.y = y;

    /*  1/10 chance of being a random choice */
    if( rand() % 10 == 0 )
        star.color = colors[ rand() % COLOR_TAN ];

    /*  Otherwise, guaranteed white */
    else
        star.color = colors[ COLOR_WHITE ];


    /*  Add this to the stars vector */
    mStars.push_back( star );
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Render all of the stars
*/
void Stars::render( void )
{
    /*  Create the star struct iterator */
    std::vector<StarStruct>::iterator s;

    /*  Go through all of our stars, rendering them */
    for( s = mStars.begin(); s != mStars.end(); ++s )
    {
        /*  Change the render color to the star's color */
        SDL_SetRenderDrawColor( gRenderer,
                s->color.r,
                s->color.g,
                s->color.b, 255 );

        /*  Draw the point */
        SDL_RenderDrawPoint( gRenderer, s->x, s->y );
    }
}
