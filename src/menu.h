/*******************************************************************************
 *  menu.h
 *
 *  This is the header file for the Menu class, defined in menu.cpp.
 *
*******************************************************************************/
#ifndef CLASS_MENU_H
#define CLASS_MENU_H

/*  The menu text label textures */
enum menuTextEnum
{
    YOUR_SCORE_LABEL,
    YOUR_SCORE,
    BEST_SCORE_LABEL,
    BEST_SCORE,
    PRESS_SPACE,
    TOTAL_MENU_TEXT_TEXTURES
};



/*
 *  The Menu class
 */
class Menu
{
    public:
        /*  Constructor */
        Menu( void );

        /*  Destructor */
        ~Menu( void );

        /*  Free a given texture */
        void free_texture( Texture *texture );

        /*  Free all of the textures */
        void free_textures( void );

        /*  Initialize all of the textures */
        bool init( void );

        /*  Layout the menu */
        void layout( void );

        /*  Is the menu present? */
        bool is_present( void );

        /*  Is the menu finished moving? */
        bool is_static( void );

        /*  Start the menu dropdown animation */
        void start( int direction = 1 );

        /*  Update the score textures */
        bool update_scores( void );

        /*  Update the animation */
        void update( void );

        /*  Render the menu screen dealie */
        void render( void );


    private:
        /*  Bools */
        bool mPresent;
        bool mStatic;

        /*  Textures */
        SDL_Texture *mTarget;
        Texture *mTextures[ TOTAL_MENU_TEXT_TEXTURES ];

        /*  Positions */
        SDL_Point mPos;

        /*  Dimensions */
        int mWidth;
        int mHeight;

        /*  Distance we need to travel */
        int mDistance;

        /*  Direction in which we travel:  -1 is up, 1 is down */
        int mDirection;
};

#endif
