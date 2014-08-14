/*******************************************************************************
 *  face.h
 *
 *  This is the header file for the Face class, defined in face.cpp.
 *
*******************************************************************************/
#ifndef CLASS_FACE_H
#define CLASS_FACE_H

/*
 *  The Face class
 */
class Face
{
    public:
        /*  Constructor */
        Face( void );

        /*  Destructor */
        ~Face( void );

        /*  Init with the default face texture */
        bool init( void );

        /*  Set texture object */
        bool set_texture_object( Texture *texture );

        /*  Free texture object */
        void free_texture_object( Texture *texture );

        /*  Free all textures */
        void free_textures( void );

        /*  Set / get position */
        void set_default_position( int x, int y );
        void set_position( int x, int y );
        int get_default_pos_x( void );
        int get_default_pos_y( void );
        int get_pos_x( void );
        int get_pos_y( void );

        /*  Set / get dimensions */
        void set_dimensions( int width, int height );
        void set_width( int width );
        void set_height( int height );
        int get_width( void );
        int get_height( void );
        int get_texture_width( void );
        int get_texture_height( void );

        /*  Get / set living status */
        void live( void );
        bool is_alive( void );

        /*  Set / get current scale */
        void set_scale( int scale );
        int get_scale( void );

        /*  Handle events */
        void events( SDL_Event &e );

        /*  Flap the face */
        void flap( void );

        /*  Set / get lift */
        void set_lift( int lift );
        int get_lift( void );

        /*  Set / get flapped status */
        void set_flapped( bool flapped );
        bool get_flapped( void );

        /*  Kill the face */
        void kill( void );

        /*  Update */
        void update( void );

        /*  Scale colliders */
        void scale_colliders( int scale );

        /*  Get colliders */
        std::vector<Collider> get_colliders( void );

        /*  Render */
        void render( void );

        /*  Draw the colliders */
        void draw_colliders( void );

    private:
        /*  The texture object used for the face */
        Texture *mTextureObject;

        /*  Position */
        SDL_Point mPos;
        SDL_Point mDefaultPos;

        /*  Dimensions */
        int mWidth;
        int mHeight;
        int mDefaultWidth;
        int mDefaultHeight;

        /*  Current scale */
        int mScale;

        /*  How this object interacts with 'gravity' */
        int mLift;
        int mLiftTicks;
        int mTerminalVelocity;

        /*  Have we flapped recently? */
        bool mFlapped;

        /*  Is the player alive? */
        bool mAlive;

        /*  Which way the face is tilted */
        double mTilt;

        /*  Colliders for the FACE */
        std::vector<Collider> mColliders;
};

#endif
