/*******************************************************************************
 *  hud.cpp
 *
 *  This file defines the methods used by the HUD class, which displays the
 *  Heads Up Display (i.e., the score counter).
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
Hud::Hud( void )
{
    /*  Set position */
    mPos.x = mPos.y = 0;

    /*  Set dimensions */
    mWidth = mHeight = 0;

    /*  Set scores to zero */
    mOldScore = mNewScore = 0;

    /*  Null the pointers */
    mTextureObject = NULL;
    mShadow = NULL;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Hud::~Hud( void )
{
    /*  Free the texture */
    free_textures();

    /*  Reset other attributes */
    mPos.x = mPos.y = 0;
    mWidth = mHeight = 0;
}



/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
 *  Free the texture objects
*/
void Hud::free_textures( void )
{
    /*  Free the main texture object */
    if( mTextureObject != NULL )
    {
        delete mTextureObject;
        mTextureObject = NULL;
    }

    /*  Free the drop shadow */
    if( mShadow != NULL )
    {
        delete mShadow;
        mShadow = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                 CREATE TEXTURE
--------------------------------------------------------------------------------
*/
bool Hud::create_textures( void )
{
    /*  Free the texture if it exists */
    free_textures();

    /*  Create the score string */
    char scoreStr[ 8 ];
    snprintf( scoreStr, 8, "%02d", mNewScore );

    /*  Create texture objects */
    mTextureObject = new Texture();
    mShadow = new Texture();

    /*  Load the string texture */
    if( ! mTextureObject->create_texture_from_string( gFont, scoreStr,
                colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create HUD texture!\n");
        return( false );
    }

    /*  Load the shadow */
    if( ! mShadow->create_texture_from_string( gFont, scoreStr,
                colors[ COLOR_BLACK ] ) )
    {
        printf("ERROR:  Could not create HUD shadow texture!\n");
        return( false );
    }

    /*  Init dimensions */
    mWidth = mTextureObject->get_width();
    mHeight = mTextureObject->get_height();

    return( true );
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  START EVERYTHING UP
 *  
 *  ...really, just loads the texture and calls the layout method.
*/
bool Hud::init( void )
{
    /*  Create textures */
    if( ! create_textures() )
        return( false );

    /*  Layout */
    layout();

    return( true );
}



/*
--------------------------------------------------------------------------------
                               SET / GET POSITION
--------------------------------------------------------------------------------
*/
void Hud::set_position( int x, int y )
{
    mPos.x = x;
    mPos.y = y;
}

int Hud::get_pos_x( void )
{
    return( mPos.x );
}

int Hud::get_pos_y( void )
{
    return( mPos.y );
}



/*
--------------------------------------------------------------------------------
                              SET / GET DIMENSIONS
--------------------------------------------------------------------------------
*/
void Hud::set_width( int width )
{
    mWidth = width;
}


void Hud::set_height( int height )
{
    mHeight = height;
}


int Hud::get_width( void )
{
    return( mWidth );
}

int Hud::get_height( void )
{
    return( mHeight );
}



/*
--------------------------------------------------------------------------------
                                SET / GET SCORE
--------------------------------------------------------------------------------
*/
void Hud::score( void )
{
    /*  Increment the score */
    mNewScore = mOldScore + 1;

    /*  If this new version is higher than the high score, make it the high */
    if( mNewScore > gHighScore )
        gHighScore = mNewScore;

}

void Hud::set_score( int score )
{
    /*  Save the score in the oldScore variable */
    mOldScore = mNewScore;

    /*  Make the new score whatever was given */
    mNewScore = score;

    if( score > gHighScore )
        gHighScore = score;
}

int Hud::get_score( void )
{
    return( mNewScore );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
*/
void Hud::layout( void )
{
    /*  X pos:  Middle of the screen */
    mPos.x = ( gWidth - mWidth ) / 2;

    /*  Y pos:  Middle of the bottom section */
    mPos.y = bHeight + ( ( (gHeight - bHeight) - mHeight ) / 2 );
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Hud::update( void )
{
    /*  Update the scores and textures */
    if( mNewScore > mOldScore )
    {
        mOldScore = mNewScore;
        create_textures();
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Hud::render( void )
{
    /*  Render the drop shadow */
    mShadow->render( mPos.x + 4, mPos.y + 4, mWidth, mHeight );

    /*  Render the main text */
    mTextureObject->render( mPos.x, mPos.y, mWidth, mHeight );
}
