/*******************************************************************************
 *  update.cpp
 *
 *  This file defines the functions used to update everything in the game,
 *  either directly or by calling update methods of objects.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  UPDATE INTRO
--------------------------------------------------------------------------------
 *  Update everything relevant to the intro screen
*/
void update_intro( void )
{
    /*  Make the objects update themselves */
    gFace->update();
    gGround->update();
    gClouds->update();
    gBuildings->update();
    gBushes->update();

    /*  If the face is too low, flap it */
    if( gFace->get_lift() == 5 )
        gFace->flap();

    /*  Correct the face */
    if( gFace->get_pos_y() < gFace->get_default_pos_y() )
        gFace->set_position( gFace->get_pos_x(), gFace->get_default_pos_y() );
}




/*
--------------------------------------------------------------------------------
                                  UPDATE MAIN
--------------------------------------------------------------------------------
 *  Update everything relevant to the main screen
*/
void update_main( void )
{
    /*  Make the objects update themselves */
    gFace->update();
    gPipes->update();
    gGround->update();
    gHud->update();
    gMenu->update();
    gClouds->update();
    gBuildings->update();
    gBushes->update();



    /*  COLLISION CHECKING */
    if( gFace->is_alive() )
    {
        /*  Get the pipe colliders */
        std::vector<SDL_Rect> pc = gPipes->get_colliders();

        /*  Check for relatively simple collisions */
        std::vector<SDL_Rect>::iterator it;
        for( it = pc.begin(); it != pc.end(); ++it )
        {
            SDL_Rect pBox = { gFace->get_pos_x(), gFace->get_pos_y(),
                gFace->get_width(), gFace->get_height() };

            /*  Check for box collision */
            if( check_collision_box( pBox, *it ) )
            {
                /*  Get the player colliders */
                std::vector<Collider> pColliders = gFace->get_colliders();

                /*  Check for collider collisions */
                if( check_collision_colliders_box( pColliders, *it ) )
                {
                    gFace->kill();
                }
            }
        }
    }
}


/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Master update function; updates different parts of the game depending on
 *  which screen is active
*/
void update( void )
{
    switch( currentScreen )
    {
        case SCREEN_MAIN:
            update_main();
            break;
        case SCREEN_INTRO:
            update_intro();
            break;
    }
}
