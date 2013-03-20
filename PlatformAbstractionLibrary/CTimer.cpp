#include "CTimer.h"

CTimer::CTimer():startTicks(0),pausedTicks(0), paused(false), started(false)
{}

void CTimer::start()
{
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
}

void CTimer::stop()
{
    started = false;
    paused = false;
}

void CTimer::pause()
{
    if( started && !paused )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void CTimer::unpause()
{
    if( paused)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int CTimer::get_ticks()
{
    if( started)
    {
        if( paused) return pausedTicks;
        else return SDL_GetTicks() - startTicks;
    }
    return 0;
}

bool CTimer::is_started()
{
    return started;
}

bool CTimer::is_paused()
{
    return paused;
}