/******************************************************************************

Pepe Gallardo

gcc -O3 -std=c99 BinarySearch.c timer.c

gcc (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 5.2.0

Rec: 0.001141 1.140591
Iter: 0.001157 1.157179

******************************************************************************/

int binarySearchRec(int len, int xs[len], int e) {
    int searchRec(int left, int right) {
        if(left>right)
            return -1;
        else {
            int center = (left+right)/2;
            if(xs[center] == e)
                return center;
            else if(xs[center] < e)
                return searchRec(center+1, right);
            else
                return searchRec(left, center-1);            
        }
    }
    return searchRec(0, len-1);
}

int binarySearchIter(int len, int xs[len], int e) {
    int left = 0;
    int right = len-1;
    while(left<=right) {
        int center = (left+right)/2;
        if(xs[center] == e)
            return center;
        else if(xs[center] < e)
            left = center+1;
        else
            right = center-1;        
    }
    return -1;
}


#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

int cmp(const void *p1, const void *p2) {
    int v1 = *((int*)p1);
    int v2 = *((int*)p2);
    if (v1>v2) 
        return  1;
    else if (v1<v2) 
        return -1;
    else    
        return 0;
}

double test(int seed, int len) {
    int xs[len];
    srand(seed);
    for(int i=0; i<len; i++)
        xs[i] = rand();
    qsort (xs, sizeof(xs)/sizeof(*xs), sizeof(*xs), cmp);
    TimerP t = newTimer();
    TimerStart(t);
    
    int probes = len/10;
    
    for(int i=0; i<probes; i++)
        //binarySearchRec(len, xs, rand());
        binarySearchIter(len, xs, rand());

    TimerStop(t);
    double time = TimerGetElapsed(t);
    freeTimer(&t);

    return time;        
}

int main() {
    double times = 0.0;
    int tests = 1000;
    int len = 100000;

    for(int i=0; i<tests; i++)
        times += test(i, len);
    double avgTime = times / tests;
    printf("%f %f\n", avgTime, times);
}

