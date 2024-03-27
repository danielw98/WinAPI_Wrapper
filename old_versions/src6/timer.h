#ifndef _TIMER_H_
#define _TIMER_H_
#include <windows.h>

typedef struct wwTimer
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    LARGE_INTEGER stopTime;
}wwTimer;

void wwTimer_Init(wwTimer *timer);
void wwTimer_Start(wwTimer *timer);
int wwTimer_End(wwTimer *timer);
void wwTimer_Delay(int milliseconds);
#endif /* _TIMER_H_ */