/*******************************************************************************
 *  face.cpp
 *
 *  This defines the Face class, which creates, updates and renders the face.
 *  The face is controlled by the player by this class's events method.
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
Face::Face( void )
{
    /*  Init texture object to null */
    mTextureObject = NULL;

    /*  Init position */
    mPos.x = mPos.y = 0;
    mDefaultPos.x = mDefaultPos.y = 0;

    /*  Init dimensions */
    mWidth = mHeight = 0;
    mDefaultWidth = mDefaultHeight = 0;

    /*  Init scale */
    mScale = 1;

    /*  Init velocity */
    mLift = 0;
    mLiftTicks = 0;
    mTerminalVelocity = 16;

    /*  Have we already flapped up? */
    mFlapped = false;

    /*  Is the player alive */
    mAlive = true;

    /*  Which way the face is tilted */
    mTilt = 0;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Face::~Face( void )
{
    /*  Free the texture object */
    free_textures();
}



/*
--------------------------------------------------------------------------------
                                      INIT
--------------------------------------------------------------------------------
 *  Initialize with default face texture
*/
bool Face::init( void )
{
    /*  Set the default face texture */
    mTextureObject = new Texture();
    if( ! mTextureObject->create_texture_from_file( "data/gfx/face1.png", true))
    {
        printf("ERROR:  Could not load face texture\n");
        return( false );
    }

    /*  Get the default dimensions */
    mDefaultWidth = mTextureObject->get_width();
    mDefaultHeight = mTextureObject->get_height();

    return( true );
}



/*
--------------------------------------------------------------------------------
                               SET TEXTURE OBJECT
--------------------------------------------------------------------------------
 *  Sets the main texture object to whichever texture object pointer was given
*/
bool Face::set_texture_object( Texture *texture )
{
    mTextureObject = texture;

    if( mTextureObject == NULL )
    {
        printf("ERROR:  Texture object is null\n");
        return( false );
    }

    return( true );
}



/*
--------------------------------------------------------------------------------
                              FREE TEXTURE OBJECT
--------------------------------------------------------------------------------
 *  Free a given texture object
*/
void Face::free_texture_object( Texture *texture )
{
    /*  If the given texture isn't null, free its memory and null the pointer */
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
 *  Free all texture objects in this class
*/
void Face::free_textures( void )
{
    /*  Free our main texture object */
    free_texture_object( mTextureObject );
}



/*
--------------------------------------------------------------------------------
                               SET / GET POSITION
--------------------------------------------------------------------------------
*/
void Face::set_default_position( int x, int y )
{
    mDefaultPos.x = x;
    mDefaultPos.y = y;
}

void Face::set_position( int x, int y )
{
    mPos.x = x;
    mPos.y = y;

    mTextureObject->set_position( x, y );
}


int Face::get_default_pos_x( void )
{
    return( mDefaultPos.x );
}

int Face::get_default_pos_y( void )
{
    return( mDefaultPos.y );
}

int Face::get_pos_x( void )
{
    return( mPos.x );
}

int Face::get_pos_y( void )
{
    return( mPos.y );
}


/*
--------------------------------------------------------------------------------
                              SET / GET DIMENSIONS
--------------------------------------------------------------------------------
*/
void Face::set_dimensions( int width, int height )
{
    mWidth = width;
    mHeight = height;

    mTextureObject->set_width( width );
    mTextureObject->set_height( height );
}

void Face::set_width( int width )
{
    mWidth = width;
    mTextureObject->set_width( width );
}

void Face::set_height( int height )
{
    mHeight = height;
    mTextureObject->set_height( height );
}

int Face::get_width( void )
{
    return( mWidth );
}

int Face::get_height( void )
{
    return( mHeight );
}

int Face::get_texture_width( void )
{
    return( mTextureObject->get_width() );
}

int Face::get_texture_height( void )
{
    return( mTextureObject->get_height() );
}



/*
--------------------------------------------------------------------------------
                                SET / GET SCALE
--------------------------------------------------------------------------------
*/
void Face::set_scale( int scale )
{
    /*  Set the scale */
    if( scale > 0 )
        mScale = scale;

    /*  Scale the texture and face */
    set_dimensions( mDefaultWidth / mScale, mDefaultHeight / mScale );
}


int Face::get_scale( void )
{
    return( mScale );
}



/*
--------------------------------------------------------------------------------
                            SET / GET LIVING STATUS
--------------------------------------------------------------------------------
*/
void Face::live( void )
{
    mAlive = true;
}


bool Face::is_alive( void )
{
    return( mAlive );
}



/*
--------------------------------------------------------------------------------
                                     EVENTS
--------------------------------------------------------------------------------
 *  Handle events
*/
void Face::events( SDL_Event &e )
{
    /*  If a key is held down and the player hasn't already flapped */
    if( e.type == SDL_KEYDOWN && ! mFlapped )
    {
        /*  Spacebar flaps */
        if( e.key.keysym.sym == SDLK_SPACE )
        {
            /*  Normally, we flap */
            if( mAlive )
                flap();

            /*  If the player is dead and the head has fallen, reset */
            else if( mPos.y == ( bHeight - mHeight ) )
                reset();

        }
    }

    /*  When the release the spacebar, make it so they can flap again */
    else if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_SPACE:
                mFlapped = false;
                break;
        }
    }

    /*  Same as the space bar above, but any mouse button */
    if( e.type == SDL_MOUSEBUTTONDOWN && ! mFlapped )
    {
        /*  Normally, we flap */
        if( mAlive )
            flap();

        /*  If the player is dead and the head has fallen, reset */
        else if( mPos.y == ( bHeight - mHeight ) )
            reset();
    }

    /*  When they release the mouse button, allow them to flap again */
    else if( e.type == SDL_MOUSEBUTTONUP )
    {
        mFlapped = false;
    }



    /*  Same as the mouse stuff above */
    if( e.type == SDL_JOYBUTTONDOWN && ! mFlapped )
    {
        /*  Normally, we flap */
        if( mAlive )
            flap();

        /*  If the player is dead and the head has fallen, reset */
        else if( mPos.y == ( bHeight - mHeight ) )
            reset();

    }

    else if( e.type == SDL_JOYBUTTONUP )
        mFlapped = false;
}



/*
--------------------------------------------------------------------------------
                                      FLAP
--------------------------------------------------------------------------------
 *  FLAP THE FACE
*/
void Face::flap( void )
{
    /*  Adjust the lift */
    if( mLift < 0 )
        mLift -= 5;
    else
        mLift = -5;

    /*  Set flapped to 'true' */
    mFlapped = true;

    /*  Play the flap sound effect */
    Mix_PlayChannel( -1, gFlap, 0 );
}



/*
--------------------------------------------------------------------------------
                                      KILL
--------------------------------------------------------------------------------
 *  KILL THE FACE
*/
void Face::kill( void )
{
    /*  Make the face dead */
    mAlive = false;

    /*  Play the 'punch' sound effect */
    Mix_PlayChannel( -1, gFaceKilled, 0 );

    /*  Set the global movement speed to zero */
    gMoveSpeed = 0;

    /*  Set the lift to whatever gravity is */
    mLift = GRAVITY;

    /*  Start the drop-down menu */
    gMenu->start();
}



/*
--------------------------------------------------------------------------------
                                     UPDATE
--------------------------------------------------------------------------------
 *  Update the face (tilt, gravity, etc.)
*/
void Face::update( void )
{
    /*
     *  Adjust lift:  We don't adjust the lift every tick, since that's too
     *  fast.  We delay each adjustment by a tick and then adjust the lift.
     */

    /*  Tick up the liftTicks counter if we're under max */
    if( mLiftTicks < 2 )
        ++mLiftTicks;

    /*  Otherwise, adjust the lift */
    else
    {
        if( mLift < mTerminalVelocity )
            mLift += GRAVITY;

        mLiftTicks = 0;
    }

    /*  Correct the lift if it's going too high */
    if( mLift < -(mTerminalVelocity) )
        mLift = -(mTerminalVelocity);

    /*  Or if we've reached 'terminal velocity' */
    else if( mLift > mTerminalVelocity )
        mLift = mTerminalVelocity;

    /*  Adjust position */
    mPos.y += mLift;

    /*  Correct position if we're too low */
    if( mPos.y + mHeight > bHeight )
    {
        mPos.y = bHeight - mHeight;

        /*  Also, kill the player */
        if( mAlive )
            kill();
    }

    /*  Correct the position if we're too high */
    if( mPos.y < 0 )
    {
        mPos.y = 0;
        mLift = 0;
    }

    /*  Adjust tilt */
    if( mTilt < mLift )
        mTilt += 2;
    else if( mTilt > mLift )
        mTilt -= 2;
}



/*
--------------------------------------------------------------------------------
                                SCALE COLLIDERS
--------------------------------------------------------------------------------
 *  This function scales the colliders to match the face's own scale; the number
 *  of colliders is scaled, as are the dimensions and positions of each collider
 *  retained
*/
void Face::scale_colliders( int scale )
{
    /*
     *  Here we create a new, temporary collider rects vector to store the data
     *  from the texture object's own corresponding colliders.
     */
    std::vector<Collider> tColliders = mTextureObject->get_pixel_colliders();

    /*
     *  Go through the face object's vector of colliders, scaling the
     *  corresponding temporary (local) texture colliders to match the face's
     *  scale, including relative collider rect location, the positions and the
     *  dimensions.
     */
    mColliders.clear();

    for( unsigned int c = 0; c < tColliders.size(); c += scale )
    {
        Collider collider;
        collider.x = (tColliders[ c ].x / scale);
        collider.y = c/scale;
        collider.w = tColliders[ c ].w / scale;
        collider.h = 1;

        mColliders.push_back( collider );
    }
}


/*
--------------------------------------------------------------------------------
                                 GET COLLIDERS
--------------------------------------------------------------------------------
 *  Return a corrected copy of the colliders vector
*/
std::vector<Collider> Face::get_colliders( void )
{
    /*  New colliders vector */
    std::vector<Collider> colliders = mColliders;

    /*  Correct the X and Y positions */
    std::vector<Collider>::iterator it;
    for( it = colliders.begin(); it != colliders.end(); ++it )
    {
        it->x += mPos.x;
        it->y += mPos.y;
    }

    /*  Return the new vector */
    return( colliders );
}



/*
--------------------------------------------------------------------------------
                                     RENDER
--------------------------------------------------------------------------------
 *  RENDER THE FACE!!!!
*/
void Face::render( void )
{
    mTextureObject->render_ex( mPos.x, mPos.y, mWidth, mHeight, mTilt );
}



/*
--------------------------------------------------------------------------------
                                 DRAW COLLIDERS
--------------------------------------------------------------------------------
 *  Here for testing purposes
*/
void Face::draw_colliders( void )
{
    /*  Get a corrected vector of colliders */
    std::vector<Collider>colliders = get_colliders();

    /*  DRAW ALL ZE COLLIDERS */
    std::vector<Collider>::iterator it;
    for( it = colliders.begin(); it != colliders.end(); ++it )
    {
        /*  Create the rect */
        SDL_Rect dRect = { it->x, it->y, it->w, it->h };

        /*  Set the draw color */
        SDL_SetRenderDrawColor( gRenderer, 255, 0, 255, 127 );

        /*  Fill the rect */
        SDL_RenderFillRect( gRenderer, &dRect );
    }
}



/*
--------------------------------------------------------------------------------
                                 SET / GET LIFT
--------------------------------------------------------------------------------
 *  Set or get the current lift of the face
*/
void Face::set_lift( int lift )
{
    mLift = lift;
}


int Face::get_lift( void )
{
    return( mLift );
}



/*
--------------------------------------------------------------------------------
                            SET / GET FLAPPED STATUS
--------------------------------------------------------------------------------
*/
void Face::set_flapped( bool flapped )
{
    mFlapped = flapped;
}


bool Face::get_flapped( void )
{
    return( mFlapped );
}
