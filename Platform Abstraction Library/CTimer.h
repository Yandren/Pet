#ifndef __TIMER_H
#define	__TIMER_H

class CTimer
{
    private:

    float startTicks, pausedTicks;
    bool paused, started;

    public:

    CTimer();
    void start();
    void stop();
    void pause();
    void unpause();

    float get_ticks();

    bool is_started();
    bool is_paused();
};

#endif	/* TIMER_H */

