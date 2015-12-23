/*
 * timer.c
 *
 * Author: Pepe Gallardo
 */

#include "timer.h"
#include <stdlib.h>

#define GetTimeFunction(timerP)   {  gettimeofday(&timerP, NULL); }

TimerP newTimer() {
    TimerP timerP = (TimerP) malloc(sizeof(Timer));
    TimerReset(timerP);
    return timerP;
}

void freeTimer(TimerP *timerPP) {
    free(*timerPP);
    (*timerPP) = NULL;
}

double TimeDifference(Clock end, Clock start) {
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    return ((seconds) + (double) useconds / 1E6);
}

/*
 *  Resets a timer, i.e., stops it if it was running and
 * sets the elapsed time to 0.
 *
 */
void TimerReset(TimerP timerP) {
    timerP->status = STOPPED;
    timerP->elapsedTime = 0.0;
}

/*
 *  Starts the timer. If it was stopped, the elapsed time
 * is reset to 0. Otherwise (it was paused) the elapsed time
 * is retained.
 *
 */
void TimerStart(TimerP timerP) {
    if(timerP->status == STOPPED)
        timerP->elapsedTime = 0.0;
    timerP->status = TIMER_RUNNING;
    GetTimeFunction(timerP->beginTime);
}

/*
 *  Pauses a timer. Any further call to GetElapsedTime will
 * return the total time measured since it was started. The
 * timer can be further resumed by calling StartTimer.
 *
 */
void TimerPause(TimerP timerP) {
    Clock timeNow;

    GetTimeFunction(timeNow);
    timerP->elapsedTime += TimeDifference(timeNow, timerP->beginTime);
    timerP->status = PAUSED;
}

/*
 *  Stops a timer. This function is similar to PauseTimer,
 * with the difference that the timer cannot be resumed.
 *
 */
void TimerStop(TimerP timerP) {
    Clock timeNow;

    GetTimeFunction(timeNow);
    timerP->elapsedTime += TimeDifference(timeNow, timerP->beginTime);
    timerP->status = STOPPED;
}

/*
 *  Gets the elapsed time. This function works in any status
 * of the timer but notice that this function requires some
 * time and, if the timer is running, the final measure will
 * include it.
 *
 */
double TimerGetElapsed(TimerP timerP) {
    if(timerP->status == TIMER_RUNNING) {
        Clock timeNow;

        GetTimeFunction(timeNow);
        return (timerP->elapsedTime + TimeDifference(timeNow, timerP->beginTime));
    }

    return timerP->elapsedTime;
}
