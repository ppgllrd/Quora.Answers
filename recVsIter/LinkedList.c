/******************************************************************************

Pepe Gallardo

gcc -O3 -std=c99 LinkedList.c timer.c

gcc (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 5.2.0

Rec     7.735338
TailRec 7.726792
Iter    7.744590

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node* List;

struct Node {
    int val;
    List next;
};

List mkList(int max) {   
    List aux(int val) {
        if(val >= max)
            return NULL;
        else {    
            List node = (List) malloc(sizeof(struct Node));
            node->val = val;
            node->next = aux(val+1);
            return node;
        }        
    }
    return aux(0);
}

int sumListRec(List xs) {
    return (xs == NULL) ? 0 
                        : xs->val + sumListRec(xs->next);    
}

int sumListTailRec(List xs) {
    int aux(List xs, int ac) {
        return (xs == NULL) ? ac
                            : aux(xs->next, ac + xs->val); 
    }
    return aux(xs, 0);
}

int sumListIter(List xs) {
    int s = 0;
    while(xs != NULL) {
        s += xs->val;
        xs = xs->next;
    }
    return s;
}
/*
Rec     7.529280
TailRec 7.539118
Iter    7.510432
*/

#include "timer.h"

int main() {
    TimerP t = newTimer();
    List xs = mkList(pow(2,15));
    
    int repeats = 100000;
    
    int s0=0, s1=0, s2=0;

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s0 += sumListRec(xs);
    TimerStop(t);
    double t0 = TimerGetElapsed(t);
    
    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s1 += sumListTailRec(xs);
    TimerStop(t);
    double t1 = TimerGetElapsed(t);

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s2 += sumListIter(xs);
    TimerStop(t);
    double t2 = TimerGetElapsed(t);

    printf("Rec\t%f\nTailRec\t%f\nIter\t%f\n", t0, t1, t2);
    freeTimer(&t);
}