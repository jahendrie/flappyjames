/*******************************************************************************
 *  hud.h
 *
 *  This is the header file for the HUD class, defined in hud.cpp.
 *
*******************************************************************************/
#ifndef CLASS_HUD_H
#define CLASS_HUD_H

/*
 *  The HUD class
 */
class Hud
{
    public:
        /*  Constructor */
        Hud( void );

        /*  Destructor */
        ~Hud( void );

        /*  Free our texture */
        void free_textures( void );

        /*  Create the texture */
        bool create_textures( void );

        /*  Init the hud */
        bool init( void );

        /*  Set / get position */
        void set_position( int x, int y );
        int get_pos_x( void );
        int get_pos_y( void );

        /*  Set / get dimensions */
        void set_width( int width );
        void set_height( int height );
        int get_width( void );
        int get_height( void );

        /*  Set / get score */
        void score( void );
        void set_score( int score );
        int get_score( void );

        /*  Layout - does the setting for you!  How convenient */
        void layout( void );

        /*  Update the display */
        void update( void );

        /*  Render the HUD */
        void render( void );

    private:
        /*  Position */
        SDL_Point mPos;

        /*  Dimensions */
        int mWidth;
        int mHeight;

        /*  The texture object pointer */
        Texture *mTextureObject;
        Texture *mShadow;

        /*  Keeps track of the scores */
        int mOldScore;
        int mNewScore;
};

#endif
