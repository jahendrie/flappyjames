/*******************************************************************************
 *  files.h
 *
 *  This is the header for the Files class, defined in files.cpp.
 *
*******************************************************************************/
#ifndef CLASS_FILES_H
#define CLASS_FILES_H


/*  Hold all of the data we want to read / write */
struct DataStruct
{
    int highScore;
};


/*
 *  The Files class
 */
class Files
{
    public:
        /*  Constructor */
        Files( void );

        /*  Destructor */
        ~Files( void );

        /*  Open a file for reading or writing */
        bool open_file( const char *path, const char *mode );

        /*  Read / write score */
        bool read_score( void );
        bool write_score( void );

        /*  Get the path values */
        const char* get_data_path();
        const char* get_prefs_path();

    private:
        /*  The location of our prefs file */
        std::string mPrefsPath;

        /*  The location of our binary data file */
        std::string mDataPath;

        /*  File pointer */
        FILE *mFile;
};

#endif
