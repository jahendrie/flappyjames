/*******************************************************************************
 *  timer.h
 *
 *  This is the header for the Timer class, defined in timer.cpp.
 *
*******************************************************************************/
#ifndef CLASS_TIMER_H
#define CLASS_TIMER_H


/*
 *  The Timer class
 */
class Timer
{
    public:
        /*  Constructor */
        Timer( void );
        
        /*  Destructor */
        ~Timer( void );

        /*  Start / stop the timer */
        void start( void );
        void stop( void );

        /*  Toggle the timer paused / unpaused */
        void toggle( void );

        /*  Get the ticks */
        Uint32 get_ticks( void );

        /*  Check the timer's status */
        bool is_started( void );
        bool is_paused( void );

    private:
        /*  The global ticks when the timer started */
        Uint32 mTicksStart;

        /*  The ticks when the timer is paused */
        Uint32 mTicksPaused;

        /*  The timer's status */
        bool mStarted;
        bool mPaused;
};

#endif
