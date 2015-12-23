/*
 * timer.h
 *
 * Author: Pepe Gallardo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <unistd.h>

typedef struct timeval Clock;

typedef enum {
    STOPPED = 0, TIMER_RUNNING = 1, PAUSED = 2
} TimerStatus;

typedef struct {
    Clock beginTime;
    /* time at which the timer was started */
    double elapsedTime;
    /* time elapsed since last start */
    TimerStatus status; /* status of the timer */
} Timer;

typedef Timer *TimerP;

TimerP newTimer();

void freeTimer(TimerP *timerPP);

void TimerReset(TimerP timerP);

void TimerStart(TimerP timerP);

void TimerPause(TimerP timerP);

void TimerStop(TimerP timerP);

double TimerGetElapsed(TimerP timerP);

#endif /* TIMER_H_ */
