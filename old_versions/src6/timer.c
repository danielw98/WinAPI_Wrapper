#include "timer.h"

void wwTimer_Init(wwTimer *timer)
{
    QueryPerformanceFrequency(&timer->frequency);
}
void wwTimer_Start(wwTimer *timer)
{
    QueryPerformanceCounter(&timer->startTime);
}
int wwTimer_End(wwTimer *timer)
{
    QueryPerformanceCounter(&timer->stopTime);
    LONGLONG timeDiff = timer->stopTime.QuadPart - timer->startTime.QuadPart;
    double milliseconds = (double) timeDiff * 1000.0 / (double) timer->frequency.QuadPart;
    return (int) milliseconds;
}
void wwTimer_Delay(int milliseconds)
{
    Sleep(milliseconds);
}