/*******************************************************************************
 *  files.cpp
 *
 *  This file defines the methods used by the Files class, which reads from and
 *  writes to specific files.
 *
*******************************************************************************/
#ifndef UTIL_H
#include "util.h"
#endif


/*
--------------------------------------------------------------------------------
                                  CONSTRUCTOR
--------------------------------------------------------------------------------
*/
Files::Files( void )
{
    /*  Assign our file paths */
    mPrefsPath = "data/prefs.cfg";
    mDataPath = "data/fj.dat";

    /*  Null our the file pointer */
    mFile = NULL;
}


/*
--------------------------------------------------------------------------------
                                   DESTRUCTOR
--------------------------------------------------------------------------------
*/
Files::~Files( void )
{
    if( mFile != NULL )
    {
        fclose( mFile );
        mFile = NULL;
    }
}



/*
--------------------------------------------------------------------------------
                                   OPEN FILE
--------------------------------------------------------------------------------
 *  Generic file-opening method
*/
bool Files::open_file( const char *path, const char *mode )
{
    /*  Open the file */
    mFile = fopen( path, mode );
    if( mFile == NULL )
        return( false );

    /*  If it opened, report success */
    return( true );
}




/*
--------------------------------------------------------------------------------
                                   READ SCORE
--------------------------------------------------------------------------------
*/
bool Files::read_score( void )
{
    /*  Open the data file for reading */
    if( ! open_file( mDataPath.c_str(), "r" ) )
    {
        printf("WARNING:  Could not read from data file '%s' \n",
                mDataPath.c_str() );
        return( false );
    }

    /*  Create a data stuct instance and copy data to it */
    DataStruct data;
    fread( &data, sizeof( struct DataStruct ), 1, mFile );

    /*  The the high score to whatever was saved */
    gHighScore = data.highScore;

    /*  Close and null out the file */
    fclose( mFile );
    mFile = NULL;


    return( true );
}



/*
--------------------------------------------------------------------------------
                                  WRITE SCORE
--------------------------------------------------------------------------------
*/
bool Files::write_score( void )
{
    /*  Open the data file for writing */
    if( ! open_file( mDataPath.c_str(), "w" ) )
    {
        printf("WARNING:  Could not open data file '%s' for writing\n",
                mDataPath.c_str() );
        return( false );
    }

    /*  Create and fill a datastruct instance with the high score */
    DataStruct data = { gHighScore };

    /*  Write the high score to the data file */
    fwrite( &data, sizeof( struct DataStruct ), 1, mFile );

    /*  Close and null out the pointer */
    fclose( mFile );
    mFile = NULL;

    return( true );
}



/*
--------------------------------------------------------------------------------
                                GET FILES PATHS
--------------------------------------------------------------------------------
*/
const char* Files::get_data_path( void )
{
    return( mDataPath.c_str() );
}


const char* Files::get_prefs_path( void )
{
    return( mPrefsPath.c_str() );
}
