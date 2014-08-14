/*******************************************************************************
 *  menu.cpp
 *
 *  This file defines the Menu class, which creates, updates and renders the
 *  dropdown menu that appears when the player dies.
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
Menu::Menu( void )
{
    /*  Is it present?  Is it static? */
    mPresent = false;
    mStatic = false;

    /*  Init position and dimensions */
    mPos.x = mPos.y = 0;
    mWidth = mHeight = 0;

    /*  Init distance and direction */
    mDistance = 0;
    mDirection = 0;

    /*  Null all of the class's textures */
    for( int i = 0; i < TOTAL_MENU_TEXT_TEXTURES; ++i )
    {
        mTextures[ i ] = NULL;
    }

    /*  Null the rendering target texture */
    mTarget = NULL;
}



/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Menu::~Menu( void )
{
    free_textures();
}



/*
--------------------------------------------------------------------------------
                                 FREE A TEXTURE
--------------------------------------------------------------------------------
 *  Free a given texture
*/
void Menu::free_texture( Texture *texture )
{
    if( texture != NULL )
    {
        delete texture;
        texture = NULL;
    }
}


/*
--------------------------------------------------------------------------------
                               FREE ALL TEXTURES
--------------------------------------------------------------------------------
 *  Free all of our textures
*/
void Menu::free_textures( void )
{
    /*  Free all of the text textures */
    for( int i = 0; i < TOTAL_MENU_TEXT_TEXTURES; ++i )
    {
        free_texture( mTextures[ i ] );
    }

    /*  Free the rendering target texture */
    if( mTarget != NULL )
    {
        SDL_DestroyTexture( mTarget );
        mTarget = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
*/
bool Menu::init( void )
{
    /*  Create all of the texture objects */
    for( int i = 0; i < TOTAL_MENU_TEXT_TEXTURES; ++i )
    {
        mTextures[ i ] = new Texture();
    }

    /*  Create the score textures */
    if( ! update_scores() )
    {
        printf("ERROR:  Could not create score textures\n");
        return( false );
    }

    /*  Current score label */
    if( ! mTextures[ YOUR_SCORE_LABEL ]->create_texture_from_string( gFontSmall,
                "Current score", colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create current score label texture\n");
        return( false );
    }

    /*  High score label */
    if( ! mTextures[ BEST_SCORE_LABEL ]->create_texture_from_string( gFontSmall,
                "Best score", colors[ COLOR_WHITE ] ) )
    {
        printf("ERROR:  Could not create best score label texture\n");
        return( false );
    }

    /*  "press space" label */
    if( ! mTextures[ PRESS_SPACE ]->create_texture_from_string( gFontSmall,
                "Press space to restart or 'Q' to quit", colors[ COLOR_WHITE ]))
    {
        printf("ERROR:  Could not create 'press space' text texture\n");
        return( false );
    }

    /*  Set initial dimensions */
    mWidth = mTextures[ PRESS_SPACE ]->get_width() + 100;
    mHeight = mTextures[ YOUR_SCORE ]->get_height() * 4;

    /*  Set initial position */
    mPos.x = ( gWidth - mWidth ) / 2;
    mPos.y = -mHeight;

    /*  Create target texture */
    mTarget = SDL_CreateTexture( gRenderer, gPixelFormat,
            SDL_TEXTUREACCESS_TARGET, mWidth, mHeight );

    /*  Set target texture blend mode */
    SDL_SetTextureBlendMode( mTarget, SDL_BLENDMODE_BLEND );

    /*  Lay everything out */
    layout();


    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
 *  Layout relative positions
*/
void Menu::layout( void )
{
    /*  Your score */
    mTextures[ YOUR_SCORE_LABEL ]->set_position( mWidth / 20, mHeight / 10 );

    mTextures[ YOUR_SCORE ]->set_position(
            mTextures[ YOUR_SCORE_LABEL ]->get_pos_x(), mHeight / 5 );


    /*  Best score */
    mTextures[ BEST_SCORE_LABEL ]->set_position(
            mWidth -  mTextures[ BEST_SCORE_LABEL ]->get_width() - (mWidth/20),
            mHeight / 10 );

    mTextures[ BEST_SCORE ]->set_position(
            mTextures[ BEST_SCORE_LABEL ]->get_pos_x(), mHeight/5 );


    /*  "Press space", etc. */
    mTextures[ PRESS_SPACE ]->set_position(
            mWidth -  mTextures[ PRESS_SPACE ]->get_width() - (mWidth/20),
            ( mHeight / 2 ) + ( mTextures[ PRESS_SPACE ]->get_height() * 2) );
}



/*
--------------------------------------------------------------------------------
                                   IS PRESENT
--------------------------------------------------------------------------------
*/
bool Menu::is_present( void )
{
    return( mPresent );
}



/*
--------------------------------------------------------------------------------
                                   IS STATIC
--------------------------------------------------------------------------------
*/
bool Menu::is_static( void )
{
    return( mStatic );
}



/*
--------------------------------------------------------------------------------
                                     START
--------------------------------------------------------------------------------
 *  Get the dropdown menu started
*/
void Menu::start( int direction )
{
    /*  Set the direction to whatever was given */
    mDirection = direction;

    /*  If it's going down, have it stop about halfway down the screen */
    if( direction > 0 )
        mDistance = ( ( gHeight - mHeight ) / 2 ) - ( mPos.y / 2 );

    else
        mDistance = ( ( gHeight - mHeight ) / 2 );

    /*  Make it present and not static */
    mPresent = true;
    mStatic = false;

    /*  Update the score textures before they get rendered */
    update_scores();
}



/*
--------------------------------------------------------------------------------
                                 UPDATE SCORES
--------------------------------------------------------------------------------
 *  Update the score textures
*/
bool Menu::update_scores( void )
{
    /*  Character array to hold our string */
    char scoreStr[ 8 ];

    /*  Create current score texture */
    snprintf( scoreStr, 8, "%02d", gHud->get_score() );
    if( ! mTextures[ YOUR_SCORE ]->create_texture_from_string( gFont, scoreStr,
                colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create current score text texture\n");
        return( false );
    }


    /*  Create high score texture */
    snprintf( scoreStr, 8, "%02d", gHighScore );
    if( ! mTextures[ BEST_SCORE ]->create_texture_from_string( gFont, scoreStr,
                colors[ COLOR_WHITE ] ))
    {
        printf("ERROR:  Could not create high score text texture\n");
        return( false );
    }


    return( true );
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Menu::update( void )
{
    /*  If the menu is allowed to move */
    if( ! mStatic )
    {
        /*  Speed of the menu movement ( N * 60 pixels per second ) */
        int speed = 32;

        /*  If we have some distance to go */
        if( mDistance > 0 )
        {
            /*  Move 'speed' pixels in 'mDirection' direction */
            mPos.y += speed * mDirection;

            /*  Decrease the distance to move */
            mDistance -= speed;
        }

        /*  If we're done moving */
        else
        {
            mStatic = true;
        }

    }

}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Menu::render( void )
{
    if( mPresent )
    {
        /*  Change render targets */
        SDL_SetRenderTarget( gRenderer, mTarget );

        /*  Render clear the background of the target texture */
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 192 );
        SDL_RenderClear( gRenderer );
        
        /*  Now, render all of the text elements to the target texture */
        for( int i = 0; i < TOTAL_MENU_TEXT_TEXTURES; ++i )
        {
            mTextures[ i ]->render_self();
        }

        /*  Draw some lines to the target texture */
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

        /*  Top line */
        SDL_RenderDrawLine( gRenderer,
                10, 10, mWidth - 10, 10 );

        /*  Right line */
        SDL_RenderDrawLine( gRenderer,
                mWidth - 10, 10, mWidth - 10, mHeight - 10 );

        /*  Bottom line */
        SDL_RenderDrawLine( gRenderer,
                mWidth - 10, mHeight - 10, 10, mHeight - 10 );

        /*  Left line */
        SDL_RenderDrawLine( gRenderer,
                10, mHeight - 10, 10, 10 );

        /*  Switch render target back to default */
        SDL_SetRenderTarget( gRenderer, NULL );

        /*  Draw the texture to the screen */
        SDL_Rect dRect = { mPos.x, mPos.y, mWidth, mHeight };
        SDL_RenderCopy( gRenderer, mTarget, NULL, &dRect );
    }

}
