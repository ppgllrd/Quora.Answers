/******************************************************************************

Pepe Gallardo

gcc -O3 -std=c99 BinaryTree.c timer.c

gcc (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 5.2.0

Rec     3.972642
Iter    4.966925
Rec2    2.363191
Iter2   2.509771

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include <stdbool.h>

typedef struct Node* Tree;

struct Node {
    int val;
    Tree left;
    Tree right;
};

Tree mkTree(int depth) {
    Tree aux(int depth, int left, int right) {
        if(depth<=0)
            return NULL;
        else {    
            int middle = (left+right) / 2;
            Tree node = (Tree) malloc(sizeof(struct Node));
            node->val = middle;
            node->left = aux(depth-1, left, middle-1);
            node->right = aux(depth-1, middle+1, right);
            return  node;
        }        
    }
    return aux(depth, 0, pow(2,depth)-2);
}

int sumTreeRec(Tree t) {
    return (t==NULL) ? 0 
                     : t->val + sumTreeRec(t->left) + sumTreeRec(t->right);    
}

int sumTreeRec2(Tree t) {
    int aux(Tree t, int ac) {
        return (t==NULL) ? ac
                         : aux(t->right, aux(t->left, ac+t->val));
    }
    return aux(t, 0); 
}

int sumTreeIter(Tree t, int depth) {
    Tree stack[depth+1];
    int top = -1;
    inline void push(Tree x) { stack[++top] = x; }
    inline Tree pop() { return stack[top--]; }
    inline bool stackEmpty() { return top<0; }

    int s = 0;
    push(t);
    while(!stackEmpty()) {
        Tree t = pop();
        if(t != NULL) {
            s += t->val;
            push(t->right);
            push(t->left);
        }
    }
    return s;
}

int sumTreeIter2(Tree t, int depth) {
    Tree stack[depth+1];
    int top = -1;
    inline void push(Tree x) { stack[++top] = x; }
    inline Tree pop() { return stack[top--]; }
    inline bool stackEmpty() { return top<0; }

    int s = 0;
    push(t);
    while(!stackEmpty()) {
        Tree t = pop();
        while(t != NULL) {
            s += t->val;
            push(t->right);
            t = t->left;
        }
    }
    return s;
}


#include "timer.h"

int main() {
    int depth = 13;
    Tree tree = mkTree(depth);
    TimerP t = newTimer();

    int repeats = 100000;   
    int s0=0, s1=0, s2=0, s3=0;

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s0 += sumTreeRec(tree);
    TimerStop(t);
    double t0 = TimerGetElapsed(t);

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s1 += sumTreeIter(tree, depth);
    TimerStop(t);
    double t1 = TimerGetElapsed(t);

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s2 += sumTreeRec2(tree);
    TimerStop(t);
    double t2 = TimerGetElapsed(t);

    TimerReset(t);
    TimerStart(t);
    for(int i=0; i<repeats; i++)
        s3 += sumTreeIter2(tree, depth);
    TimerStop(t);
    double t3 = TimerGetElapsed(t);

    printf("%d %d %d %d\n",s0,s1,s2,s3);

    printf("Rec\t%f\nIter\t%f\nRec2\t%f\nIter2\t%f\n", t0, t1, t2, t3);
    freeTimer(&t);

}