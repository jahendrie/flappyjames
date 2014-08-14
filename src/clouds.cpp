/*******************************************************************************
 *  clouds.cpp
 *
 *  This defines the Clouds class.  The class creates, updates and renders the
 *  clouds that scroll by in the background.
 *
 *  The reason we use a vector of separate textures rather than a bunch of clips
 *  of the same texture is that we want some clouds to be more transparent than
 *  others, and you can't alter the alpha of a cloud without altering its base
 *  texture; thus, unique textures are necessary.
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
Clouds::Clouds( void )
{
    mTextureObject = NULL;
    mClouds.clear();
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Clouds::~Clouds( void )
{
    free_textures();
    mClouds.clear();
}


/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
*/
void Clouds::free_textures( void )
{
    /*  Free the base texture */
    if( mTextureObject != NULL )
    {
        delete mTextureObject;
        mTextureObject = NULL;
    }

    /*  Go through the list and free the individual textures */
    std::vector<CloudStruct>::iterator c;
    for( c = mClouds.begin(); c != mClouds.end(); ++c )
    {
        SDL_DestroyTexture( c->texture );
        c->texture = NULL;
    }
}


/*
--------------------------------------------------------------------------------
                                 INITIALIZATION
--------------------------------------------------------------------------------
*/
bool Clouds::init( void )
{
    /*  Create and load the base cloud texture */
    mTextureObject = new Texture();
    if( ! mTextureObject->create_texture_from_file( "data/gfx/clouds.png" ))
    {
        printf("ERROR:  Could not create clouds texture\n");
        return( false );
    }

    /*  Set default position of base texture */
    mTextureObject->set_position( 0, 0 );

    /*  Init clips */
    for( int i = 0; i < TOTAL_CLOUDS; ++i )
    {
        mClips[ i ].x = 0;
        mClips[ i ].y = i * mTextureObject->get_width();
        mClips[ i ].w = mTextureObject->get_width();
        mClips[ i ].h = mTextureObject->get_width();
    }


    return( true );
}



/*
--------------------------------------------------------------------------------
                                   ADD CLOUD
--------------------------------------------------------------------------------
 *  Add a cloud.  Each cloud has its own copy of the appropriate clip of the
 *  base clouds texture.
*/
void Clouds::add_cloud( void )
{
    /*  Create the cloud struct */
    CloudStruct cloud;

    /*  Set the cloud struct's 'rect' */
    cloud.x = gWidth;
    cloud.y = ( rand() % ( bHeight - 50 ) );
    cloud.w = mTextureObject->get_width();
    cloud.h = mTextureObject->get_width();

    /*  Create a blank texture for the cloud */
    cloud.texture = SDL_CreateTexture( gRenderer, gPixelFormat,
            SDL_TEXTUREACCESS_TARGET,
            cloud.w, cloud.h );

    /*  Switch the texture's blend mode */
    SDL_SetTextureBlendMode( cloud.texture, SDL_BLENDMODE_BLEND );

    /*  Switch the rendering target */
    SDL_SetRenderTarget( gRenderer, cloud.texture );

    /*  Clear the cloud's texture */
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderClear( gRenderer );

    /*  Copy the cloud texture to the new target texture */
    mTextureObject->render( 0, 0, cloud.w, cloud.h, &mClips[ rand() % 3 ] );

    /*  Switch the rendering target back */
    SDL_SetRenderTarget( gRenderer, NULL );

    /*  Mod the cloud texture's alpha */
    SDL_SetTextureAlphaMod( cloud.texture, ( rand() % 191 ) + 64 );

    /*  If it's night time, modulate the cloud's color */
    if( currentTimeOfDay == TIME_NIGHT )
    {
        SDL_SetTextureColorMod( cloud.texture,
                colors[ COLOR_NIGHT_SKY ].r,
                colors[ COLOR_NIGHT_SKY ].g/2,
                colors[ COLOR_NIGHT_SKY ].b );
    }

    /*  Push it onto the vector */
    mClouds.push_back( cloud );
}


/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Clouds::update( void )
{
    /*  Create an iterator for our vector doodad */
    std::vector<CloudStruct>::iterator c;
    
    /*  Erase dead clouds */
    for( c = mClouds.begin(); c != mClouds.end(); )
    {
        /*  If the cloud has gone too far left */
        if( c->x < -( c->w ) )
        {
            /*  Take care of the texture */
            SDL_DestroyTexture( c->texture );
            c->texture = NULL;

            /*  Take care of everything else */
            mClouds.erase( c );
        }

        /*  Otherwise, move the cloud left */
        else
        {
            if( gMoveSpeed > 0 )
                --c->x;

            /*  Increment to next CloudStruct instance */
            ++c;
        }
    }

    /*  1 in 1000 chance of spawning a new cloud */
    if( rand() % 1000 == 0 && gMoveSpeed > 0 )
        add_cloud();
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Clouds::render( void )
{
    /*  Create an iterator */
    std::vector<CloudStruct>::iterator c;

    /*  Go through the clouds vector, rendering each one */
    for( c = mClouds.begin(); c != mClouds.end(); ++c )
    {
        SDL_Rect dRect = { c->x, c->y, c->w, c->h };
        SDL_RenderCopy( gRenderer, c->texture, NULL, &dRect );
    }
}
