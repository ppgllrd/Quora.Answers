/******************************************************************************

Pepe Gallardo

gcc -O3 -std=c99 QuickSort.c timer.c

gcc (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 5.2.0

Rec: 0.008844 8.843624
Iter: 0.008750 8.750375

******************************************************************************/


void quickSortRec(int len, int xs[len]) {
    void swap(int p1, int p2) {
        int aux = xs[p1];
        xs[p1] = xs[p2];
        xs[p2] = aux;
    }
    
    int partition(int left, int right) {
        int center = (left+right)/2;
        int pivot = xs[center];
        swap(center, right);
        int p = left;
        for(int i=left; i<right; i++) {
            if(xs[i]<=pivot) {
                swap(i,p);
                p++;
            }    
        }
        swap(p, right);
        return p;
    }
    
    void sortRec(int left, int right) {
        if(left<right) {
            int posPivot = partition(left, right);
            sortRec(left, posPivot-1);
            sortRec(posPivot+1, right);
        }
    }
    
    sortRec(0, len-1);
}

#include <stdbool.h>

void quickSortIter(int len, int xs[len]) {
    void swap(int p1, int p2) {
        int aux = xs[p1];
        xs[p1] = xs[p2];
        xs[p2] = aux;
    }
    
    int partition(int left, int right) {
        int center = (left+right)/2;
        int pivot = xs[center];
        swap(center, right);
        int p = left;
        for(int i=left; i<right; i++) {
            if(xs[i]<=pivot) {
                swap(i,p);
                p++;
            }    
        }
        swap(p, right);
        return p;
    }
    
    int stack[2*len];
    int top = -1;
    inline void push(int x) { stack[++top] = x; }
    inline int pop() { return stack[top--]; }
    inline bool stackEmpty() { return top<0; }
    
    void sortIter() {
        int left = 0;
        int right = len-1;
        push(left);
        push(right);
        while(!stackEmpty()) {
            right = pop();
            left = pop();
            if(left<right) {
                int posPivot = partition(left, right);
                push(left);
                push(posPivot-1);
                push(posPivot+1);
                push(right);
            }
        }
    }
        
    sortIter();
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
    //qsort (xs, sizeof(xs)/sizeof(*xs), sizeof(*xs), cmp);
    TimerP t = newTimer();
    TimerStart(t);
    quickSortRec(len, xs);
    //quickSortIter(len, xs);
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

