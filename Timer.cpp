#include "defines.h"
#include "Timer.h"


int Timer::Delta() 
{
  return l_ticks - s_ticks;
}

void Timer::Start() 
{
  s_ticks = SDL_GetTicks();
}

Timer::Timer() 
{
  return;
}

Timer::~Timer()
{
  return;
}

