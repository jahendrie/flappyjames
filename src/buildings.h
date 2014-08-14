/*******************************************************************************
 *  buildings.h
 *
 *  Header file for the Buildings class defined in buildings.cpp.
 *
*******************************************************************************/
#ifndef CLASS_BUILDINGS_H
#define CLASS_BUILDINGS_H

/*  Holds information about a given building */
struct BuildingStruct
{
    SDL_Rect clip;      //  Clip of the texture to render

    int x;              //  X position
    int y;              //  Y position
    int w;              //  Width
    int h;              //  Height
};


/*  The different types of buildings (clips of the texture) */
enum BuildingsEnum
{
    TOP_BUILDINGS,
    MIDDLE_BUILDINGS,
    BOTTOM_BUILDINGS,
    TOTAL_BUILDINGS
};


/*
 *  The Buildings class
 */
class Buildings
{
    public:
        /*  Constructor */
        Buildings( void );

        /*  Destructor */
        ~Buildings( void );

        /*  Initialize the buildings */
        bool init( void );

        /*  Layout */
        void layout( void );

        /*  Add a building */
        void add_building( int x, int y );

        /*  Update */
        void update( void );

        /*  Render */
        void render( void );

    private:
        /*  Holds our buildings */
        std::vector<BuildingStruct> mBuildings;

        /*  Base textures */
        Texture *mBuildingTextures[ TOTAL_TIMES ];

        /*  Clips for the textures */
        SDL_Rect mClips[ TOTAL_BUILDINGS ];

        /*  Scale of the buildings */
        int mScale;

};

#endif
