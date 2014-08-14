/*******************************************************************************
 *  prototypes.h
 *
 *  This file declares all of the global functions used throughout the program.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*  Initializes everything, primarily SDL stuff - defined in init.cpp */
extern bool init( void );

/*  Load all of the media - defined in load.cpp */
extern bool load_media( void );

/*  Load global objects */
extern bool load_objects( void );

/*  Close out everything and quit SDL - defined in close.cpp */
extern void close( void );

/*  Delete all of the custom 'global objects' - defined in close.cpp */
extern void kill_objects( void );

/*  Handle all events - events.cpp */
extern void events( SDL_Event &e );

/*  Update everything - update.cpp */
extern void update( void );

/*  Render everything - render.cpp */
extern void render( void );

//  Check for collisions between colliders and a rect - defined in collision.cpp
extern bool check_collision_colliders_box( std::vector<Collider> &c,
        SDL_Rect &r);

/*  Check for collisions between two rects - defined in collision.cpp */
extern bool check_collision_box( SDL_Rect &rectA, SDL_Rect &rectB );

/*  Reset the game */
extern void reset( void );

/*  Toggle fullscreen on / off */
extern void toggle_fullscreen( void );

/*  Toggle the sound effects or music - defined in sounds.cpp */
extern void toggle_music( void );
extern void toggle_sounds( void );

/*  Check args - defined in args.cpp */
extern int check_args( int argc, char *argv[] );
