/*******************************************************************************
 *  ground.h
 *
 *  This is the header file for the Ground class, defined in ground.cpp.
 *
*******************************************************************************/
#ifndef CLASS_GROUND_H
#define CLASS_GROUND_H

class Ground
{
    public:
        /*  Constructor */
        Ground( void );

        /*  Destructor */
        ~Ground( void );

        /*  Free the texture */
        void free_texture( void );

        /*  Initialization */
        bool init( void );

        /*  Update */
        void update( void );

        /*  Render */
        void render( void );

    private:
        /*  Our ground tiles */
        std::vector<SDL_Rect> mTiles;

        /*  The texture we're using */
        Texture *mGroundTexture;

        /*  Color of the ground underneath texture */
        SDL_Color mColor;
};

#endif
