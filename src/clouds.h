/*******************************************************************************
 *  clouds.h
 *
 *  This is the header file for the Clouds class, defined in clouds.cpp.
 *
*******************************************************************************/
#ifndef CLASS_CLOUDS_H
#define CLASS_CLOUDS_H


/*  Information that our cloud needs */
struct CloudStruct
{
    SDL_Texture *texture;       //  Texture pointer for this cloud

    int x;                      //  X coordinate
    int y;                      //  Y coordinate
    int w;                      //  Width
    int h;                      //  Height
};


/*  The different types of cloud */
enum CloudsEnum
{
    CLOUD_MEDIUM,       //  Top cloud
    CLOUD_SMALL,        //  Middle cloud
    CLOUD_BIG,          //  Bottom cloud
    TOTAL_CLOUDS
};


/*
 *  The Clouds class
 */
class Clouds
{
    public:
        /*  Constructor */
        Clouds( void );

        /*  Destructor */
        ~Clouds( void );

        /*  Free textures */
        void free_textures( void );

        /*  Init */
        bool init( void );

        /*  Add a cloud */
        void add_cloud( void );

        /*  Update */
        void update( void );

        /*  Render */
        void render( void );

    private:
        /*  vector with our cloud structs */
        std::vector<CloudStruct> mClouds;

        /*  Base clouds texture */
        Texture *mTextureObject;

        /*  Clips for our cloud texture */
        SDL_Rect mClips[ TOTAL_CLOUDS ];
};

#endif
