/*******************************************************************************
 *  bushes.h
 *
 *  Header file for the Bushes class defined in bushes.cpp.
 *
*******************************************************************************/
#ifndef CLASS_BUSHES_H
#define CLASS_BUSHES_H


/*  Hold information about a given bush */
struct BushStruct
{
    int x;              //  X pos
    int y;              //  Y pos
    int w;              //  Width
    int h;              //  Height
    SDL_Rect clip;      //  Which part of the texture to render
};


/*  The different types of bush (clips of the texture) */
enum BushesEnum
{
    TOP_BUSH,
    MIDDLE_BUSH,
    BOTTOM_BUSH,
    TOTAL_BUSHES
};



/*
 *  The Bushes class
 */
class Bushes
{
    public:
        /*  Constructor */
        Bushes( void );

        /*  Destructor */
        ~Bushes( void );

        /*  Free textures */
        void free_textures( void );

        /*  Init */
        bool init( void );

        /*  Layout */
        void layout( void );

        /*  Add a bush */
        void add_bush( int x, int y );

        /*  Update ze bushes */
        void update( void );

        /*  Render ze bushes */
        void render( void );

    private:
        /*  Vector to hold our bushes */
        std::vector<BushStruct> mBushes;

        /*  Initial bush textures */
        Texture *mBushTextures[ TOTAL_TIMES ];

        /*  How big do we want the bush to be? */
        int mScale;

        /*  Clips for the bush textures */
        SDL_Rect mClips[ TOTAL_BUSHES ];
};


#endif
