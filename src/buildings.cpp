/*******************************************************************************
 *  buildings.cpp
 *
 *  This file defines the Buildings class, which is responsible for the
 *  creation, movement and display of the buildings in the background.
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
Buildings::Buildings( void )
{
    /*  Null out the textures */
    mBuildingTextures[ TIME_DAY ] = NULL;
    mBuildingTextures[ TIME_NIGHT ] = NULL;

    /*  Set the scale to twice normal size */
    mScale = 2;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Buildings::~Buildings( void )
{
    /*  Clear the vector */
    mBuildings.clear();
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
*/
bool Buildings::init( void )
{
    /*  Init the day buildings texture */
    mBuildingTextures[ TIME_DAY ] = new Texture();
    if( ! mBuildingTextures[ TIME_DAY ]->create_texture_from_file(
                "data/gfx/buildings-day.png"))
    {
        printf("ERROR:  Could not init buildings (day) texture\n");
        return( false );
    }


    /*  Init the night buildings texture */
    mBuildingTextures[ TIME_NIGHT ] = new Texture();
    if( ! mBuildingTextures[ TIME_NIGHT ]->create_texture_from_file(
                "data/gfx/buildings-night.png" ))
    {
        printf("ERROR:  Could not init buildings (night) texture\n");
        return( false );
    }


    /*  Init the clips */
    for( int i = 0; i < TOTAL_BUILDINGS; ++i )
    {
        mClips[ i ].x = 0;
        mClips[ i ].y = i * 64;
        mClips[ i ].w = 128;
        mClips[ i ].h = 64;
    }


    /*  Lay out the buildings */
    layout();


    return( true );
}



/*
--------------------------------------------------------------------------------
                                     LAYOUT
--------------------------------------------------------------------------------
*/
void Buildings::layout( void )
{
    /*  Create a whole damn row of building */
    for( int i = 0; i < (gWidth / ( 128 * mScale ) ) + 1; ++i )
    {
        add_building( i * ( 128 * mScale ), bHeight - ( 64 * mScale) );
    }
}



/*
--------------------------------------------------------------------------------
                                  ADD BUILDING
--------------------------------------------------------------------------------
*/
void Buildings::add_building( int x, int y )
{
    /*  Create a BuildingStruct instance */
    struct BuildingStruct building;

    /*  Set the texture, clip and position of the building */
    building.clip = mClips[ rand() % 3 ];
    building.x = x;
    building.y = y;
    building.w = 128 * mScale;
    building.h = 64 * mScale;

    /*  Stick it on the vector */
    mBuildings.push_back( building );
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
*/
void Buildings::update( void )
{
    /*  Create our iterator */
    std::vector<BuildingStruct>::iterator b;

    /*  Go through the vector; erase dead buildings, update the rest */
    for( b = mBuildings.begin(); b != mBuildings.end(); )
    {
        /*  If it's too far left, erase it and add a new one */
        if( b->x < -( b->w * mScale ) )
        {
            /*  Erase from vector */
            mBuildings.erase( b );

            /*  1/3 chance of adding a new building */
            if( rand() % 3 > 0 )
                add_building( gWidth, bHeight - ( 64 * mScale ) );
        }

        /*  If it isn't too far left, update it */
        else
        {
            /*  Move it to the left */
            if( gMoveSpeed > 0 )
                --b->x;

            /*  Increment iterator to move on to the next building */
            ++b;
        }
    }
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
*/
void Buildings::render( void )
{
    /*  Iterator */
    std::vector<BuildingStruct>::iterator b;

    /*  Go through the vector and render every building */
    for( b = mBuildings.begin(); b != mBuildings.end(); ++b )
    {
        mBuildingTextures[ currentTimeOfDay ]->render(
                b->x, b->y, b->w, b->h, &b->clip );
    }
}
