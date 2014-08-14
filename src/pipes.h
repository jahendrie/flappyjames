/*******************************************************************************
 *  pipes.h
 *
 *  This is the header file for the Pipes class, defined in pipes.cpp.
 *
*******************************************************************************/
#ifndef CLASS_PIPES_H
#define CLASS_PIPES_H


/*  Information that each pair of pipes needs */
struct PipeStruct
{
    SDL_Rect topPipe;       //  General rect for the top pipe
    SDL_Rect bottomPipe;    //  General rect for the bottom pipe

    bool scored;            //  Has this pipe been scored on?
};


/*
 *  The Pipes class
 */
class Pipes
{
    public:
        /*  Constructor */
        Pipes( void );

        /*  Destructor */
        ~Pipes( void );

        /*  Free a texture */
        void free_texture( Texture *texture );

        /*  Free all textures */
        void free_textures( void );

        /*  Init everything */
        bool init( void );

        /*  Add a pair of pipes */
        void add_pipes( void );

        /*  Update */
        void update( void );

        /*  Score */
        void score( void );

        /*  Render */
        void render( void );

        /*  Draw colliders */
        void draw_colliders( void );

        /*  Return a set of simple colliders */
        std::vector<SDL_Rect> get_colliders( void );

    private:
        /*  The top of our pipe texture */
        Texture *mPipeTop;

        /*  The body of the pipe texture */
        Texture *mPipeBody;

        /*  Vector of pipes */
        std::vector<PipeStruct> mPipes;

        /*  Pipe ticks */
        int mAddTicks;
        int mAddDelay;
};

#endif
