/*******************************************************************************
 *  pipes.cpp
 *
 *  This file defines the methods used by the Pipes class, which creates,
 *  updates and renders the pairs of pipes that the player 'flaps' through while
 *  playing the game.
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
Pipes::Pipes( void )
{
    /*  The different parts of the pipe */
    mPipeTop = NULL;
    mPipeBody = NULL;

    /*  Pipes are added every so often at predetermined times */
    mAddTicks = 0;

    /*  ...but they don't start getting added until after an initial delay */
    mAddDelay = 0;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Pipes::~Pipes( void )
{
    /*  Get rid of all the evidence */
    free_textures();

    /*  Clear the pipes vector... just in case */
    mPipes.clear();
}



/*
--------------------------------------------------------------------------------
                                  FREE TEXTURE
--------------------------------------------------------------------------------
 *  Frees a given texture
*/
void Pipes::free_texture( Texture *texture )
{
    if( texture != NULL )
    {
        delete texture;
        texture = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                 FREE TEXTURES
--------------------------------------------------------------------------------
 *  Frees all textures in the class
*/
void Pipes::free_textures( void )
{
    free_texture( mPipeTop );
    free_texture( mPipeBody );
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Create and load the textures
*/
bool Pipes::init( void )
{
    /*  This is the 'top' / 'bottom' of the pipe */
    mPipeTop = new Texture();
    if( ! mPipeTop->create_texture_from_file( "data/gfx/pipe-top.png" ) )
    {
        printf("ERROR:  Could not load pipe top texture\n");
        return( false );
    }

    /*  This is the main body of the pipe */
    mPipeBody = new Texture();
    if( ! mPipeBody->create_texture_from_file( "data/gfx/pipe-body.png" ) )
    {
        printf("ERROR:  Could not load pipe body texture\n");
        return( false );
    }


    return( true );
}


/*
--------------------------------------------------------------------------------
                                   ADD PIPES
--------------------------------------------------------------------------------
 *  Adds a pair of pipes
*/
void Pipes::add_pipes( void )
{
    /*  Create a new instance of a pair of pipes */
    PipeStruct pipes;

    /*
     *  The distance between the pipes changes depending on whether the screen
     *  is 1080p or 720p.
     */
    int scaleDistance = 0;
    if( gScale == 4 )           //  720
        scaleDistance = 120;
    else if( gScale == 3 )      //  1080
        scaleDistance = 150;

    /*  The distance between the top and bottom pipes */
    int pipeDistance = ( rand() % 20 ) + scaleDistance;

    /*  Top pipe starts out all the way to the right, at the top */
    pipes.topPipe.x = gWidth;
    pipes.topPipe.y = 0;
    pipes.topPipe.w = mPipeTop->get_width();

    /*  Semi-randomly generated height */
    pipes.topPipe.h = ( rand() % 200 ) + 200;

    /*  Set position of bottom pipe according to top pipe and distance */
    pipes.bottomPipe.x = gWidth;
    pipes.bottomPipe.y = pipes.topPipe.h + pipeDistance;
    pipes.bottomPipe.h = bHeight - pipes.bottomPipe.y;
    pipes.bottomPipe.w = mPipeTop->get_width();

    /*  Set the 'scored' bool to false */
    pipes.scored = false;

    /*  Push it onto pipes vector */
    mPipes.push_back( pipes );

}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Updates the pipes, corrects lift, etc.
*/
void Pipes::update( void )
{
    /*  Check for, and clear, dead pipes */
    std::vector<PipeStruct>::iterator p;
    for( p = mPipes.begin(); p != mPipes.end(); )
    {
        /*  If the pipe is too far left, erase it */
        if( (p->topPipe.x + p->topPipe.w) < 0 )
            mPipes.erase( p );
        else
            ++p;
    }


    /*  Move the pipes to the left and check if the player scored */
    for( p = mPipes.begin(); p != mPipes.end(); ++p )
    {
        /*  Move both parts of the pipe to the left */
        p->topPipe.x -= gMoveSpeed;
        p->bottomPipe.x -= gMoveSpeed;

        /*  If the pipe hasn't been 'score on' yet */
        if( ! p->scored )
        {
            /*  Check the player's position against the pipe's */
            int pipeMid = p->topPipe.x + ( p->topPipe.w / 2 );
            int faceMid = gFace->get_pos_x() + ( gFace->get_width() / 2 );

            /*  If the face is in the right position */
            if( faceMid > pipeMid )
            {
                p->scored = true;
                score();
            }
        }
    }


    /*  Wait a couple of seconds before adding any pipes at all */
    if( mAddDelay < 120 )
        ++mAddDelay;
    else
    {
        /*  After that, ever two seconds (approx.), add a pair of pipes */
        if( mAddTicks == 120 )
        {
            add_pipes();
            mAddTicks = 0;
        }
        else
            ++mAddTicks;
    }

}



/*
--------------------------------------------------------------------------------
                                     SCORE
--------------------------------------------------------------------------------
 *  This method is called when the player scores
*/
void Pipes::score( void )
{
    Mix_PlayChannel( -1, gScore, 0 );

    gHud->score();
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  Renders our pipes
*/
void Pipes::render( void )
{
    /*  Create the iterator and go through the pipes vector */
    std::vector<PipeStruct>::iterator p;
    for( p = mPipes.begin(); p != mPipes.end(); ++p )
    {
        /*  Top pipe, bottom section */
        mPipeTop->render_ex(
                p->topPipe.x,
                p->topPipe.h - mPipeTop->get_height(),
                mPipeTop->get_width(),
                mPipeTop->get_height(),
                0, SDL_FLIP_VERTICAL );

        /*  Top pipe, body section */
        mPipeBody->render_ex(
                p->topPipe.x +
                ( (mPipeTop->get_width() - mPipeBody->get_width()) / 2 ) - 1,

                0,
                mPipeBody->get_width(),
                p->topPipe.h - mPipeTop->get_height(), 0 );


        /*  Bottom pipe, top section */
        mPipeTop->render_ex(
                p->bottomPipe.x,
                p->bottomPipe.y,
                mPipeTop->get_width(),
                mPipeTop->get_height(), 0 );

        /*  Bottom pipe, body section */
        mPipeBody->render_ex(
                p->bottomPipe.x + 
                ( ( mPipeTop->get_width() - mPipeBody->get_width() ) / 2 ) - 1,

                p->bottomPipe.y + mPipeTop->get_height(),
                mPipeBody->get_width(),
                p->bottomPipe.h - mPipeTop->get_height(), 0 );
    }

}


/*
--------------------------------------------------------------------------------
                                 GET COLLIDERS
--------------------------------------------------------------------------------
 *  Returns a set of simple SDL_Rect colliders
*/
std::vector<SDL_Rect> Pipes::get_colliders( void )
{
    /*  Create the colliders vector */
    std::vector<SDL_Rect> simpleColliders;

    /*  Get the pipe body width and pipe top height here */
    int pbWidth = mPipeBody->get_width();
    int ptWidth = mPipeTop->get_width();
    int ptHeight = mPipeTop->get_height();

    std::vector<PipeStruct>::iterator it;
    for( it = mPipes.begin(); it != mPipes.end(); ++it )
    {
        /*  Top pipe body */
        SDL_Rect tpb = { it->topPipe.x + ( (ptWidth - pbWidth) / 2 ),
            it->topPipe.y, pbWidth, it->topPipe.h - ptHeight };

        /*  Top pipe 'top' */
        SDL_Rect tpt = { it->topPipe.x, it->topPipe.y +
            (it->topPipe.h - ptHeight), ptWidth, ptHeight };

        /*  Bottom pipe top */
        SDL_Rect bpt = { it->bottomPipe.x, it->bottomPipe.y, ptWidth, ptHeight};

        /*  Bottom pipe body */
        SDL_Rect bpb = { it->bottomPipe.x + ( (ptWidth - pbWidth) /2 ),
            it->bottomPipe.y + ptHeight, pbWidth,
            it->bottomPipe.h - ptHeight };


        /*  Push all of these rects onto the new colliders vector */
        simpleColliders.push_back( tpb );
        simpleColliders.push_back( tpt );
        simpleColliders.push_back( bpt );
        simpleColliders.push_back( bpb );
    }


    /*  Return the colliders */
    return( simpleColliders );
}


/*
--------------------------------------------------------------------------------
                                 DRAW COLLIDERS
--------------------------------------------------------------------------------
 *  Here for testing purposes
*/
void Pipes::draw_colliders( void )
{
    /*  Get the colliders */
    std::vector<SDL_Rect> colliders = get_colliders();

    /*  Create our iterator and go through the colliders vector */
    std::vector<SDL_Rect>::iterator it;
    for( it = colliders.begin(); it != colliders.end(); ++it )
    {
        /*  Create the rect */
        SDL_Rect dRect = *it;

        /*  Change the draw color */
        SDL_SetRenderDrawColor( gRenderer, 255, 0, 255, 127 );

        /*  Fill the rect */
        SDL_RenderFillRect( gRenderer, &dRect );
    }
}
