/*******************************************************************************
 *  render.cpp
 *
 *  This file defines the functions that handle the rendering for the program,
 *  either directly or by calling the rendering methods of various classes.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif



void render_intro( void )
{
    /*  Have all the objects render their things */
    gClouds->render();
    gBuildings->render();
    gBushes->render();
    gFace->render();
    gGround->render();

    /*  Intro text drop shadow */
    gIntroTextShadow->set_position(
            ( ( gWidth - gIntroTextShadow->get_width() ) / 2 ) + 4,
            ( bHeight + ( gIntroTextShadow->get_height() / 2 ) ) + 4 );

    /*  Now render the intro text */
    gIntroText->set_position(
        ( gWidth - gIntroText->get_width() ) / 2,
        bHeight + ( gIntroText->get_height() / 2 ) );

    /*  Render the 'A Button' texture if appropriate */
    if( SDL_NumJoysticks() > 0 )
    {
        gAButton->render(
                gIntroText->get_pos_x() + (gIntroText->get_width() / 2.5f ),
                gIntroText->get_pos_y() + ( gIntroText->get_height()/4 ),
                gAButton->get_width(), gAButton->get_height() );
    }

    /*  Render the main intro text to the screen */
    gIntroTextShadow->render_self();
    gIntroText->render_self();

    /*  Create a rect to draw on the screen */
    SDL_Rect bRect;

    /*  Set dimensions and position of the box */
    bRect.w = gWidth/2;
    bRect.h = gHeight/3;
    bRect.x = ( gWidth - bRect.w ) / 2;
    bRect.y = gHeight / 20;

    /*  Draw the box */
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 192 );
    SDL_RenderFillRect( gRenderer, &bRect );

    /*  Now position our credits text */
    gCreditsText1->set_position(
            bRect.x + ( ( bRect.w - gCreditsText1->get_width() ) / 2 ),
            bRect.y + gCreditsText1->get_height() );

    gCreditsText2->set_position(
            bRect.x + ( ( bRect.w - gCreditsText2->get_width() ) / 2 ),
            bRect.y + gCreditsText2->get_height() * 3 );

    gCreditsText3->set_position(
            bRect.x + ( ( bRect.w - gCreditsText3->get_width() ) / 2 ),
            bRect.y + gCreditsText3->get_height() * 5 );

    /*  Render the credits text */
    gCreditsText1->render_self();
    gCreditsText2->render_self();
    gCreditsText3->render_self();

}


void render_main( void )
{
    /*  Have the objects render their things */
    if( currentTimeOfDay == TIME_NIGHT )
        gStars->render();
    gClouds->render();
    gBuildings->render();
    gBushes->render();
    gFace->render();
    gPipes->render();
    gGround->render();
    gHud->render();
    gMenu->render();

}

void render( void )
{
    /*  Pick the color for the sky */
    SDL_Color c;
    if( currentTimeOfDay == TIME_DAY )
        c = colors[ COLOR_SKY_BLUE ];
    else if( currentTimeOfDay == TIME_NIGHT )
        c = colors[ COLOR_NIGHT_SKY ];

    /*  Change the rendering color to the sky color and clear the renderer */
    SDL_SetRenderDrawColor( gRenderer, c.r, c.g, c.b, c.a );
    SDL_RenderClear( gRenderer );

    /*  Move on to the proper rendering function depending on the screen */
    switch( currentScreen )
    {
        case SCREEN_MAIN:
            render_main();
            break;
        case SCREEN_INTRO:
            render_main();
            render_intro();
            break;
    }
}
