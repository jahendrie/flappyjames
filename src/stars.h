/*******************************************************************************
 *  stars.h
 *
 *  This is the header for the Stars class, defined in stars.cpp.
 *
*******************************************************************************/
#ifndef CLASS_STARS_H
#define CLASS_STARS_H

/*  Information our stars need */
struct StarStruct
{
    int x;                  //  X position
    int y;                  //  Y position

    SDL_Color color;        //  This star's color
};



/*
 *  The Stars class
 */
class Stars
{
    public:
        /*  Constructor */
        Stars( void );
        
        /*  Destructor */
        ~Stars( void );

        /*  Add a star to the starfield */
        void add_star( int x, int y );

        /*  Render the stars */
        void render( void );


    private:
        /*  This holds our stars */
        std::vector<StarStruct> mStars;
};

#endif
