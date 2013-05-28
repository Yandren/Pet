#ifndef TIMER_H
#define	TIMER_H

#include "glew\include\GL\glew.h"
#include "glfw\include\GL\glfw.h"

class CTimer
{
    private:

    int startTicks, pausedTicks;
    bool paused, started;

    public:

    CTimer();
    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();
};

#endif	/* TIMER_H */

