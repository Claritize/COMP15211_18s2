#ifndef QUEUE_H
#define QUEUE_H
 
#define MAXQ 6
 
typedef struct { 
   int nitems;
   int head;
   int tail;
   int items[MAXQ];
} Queue;
 
// initialise a Queue
void initQueue(Queue *q);
// insert a new item at the tail of the Queue
void  enterQueue(Queue *, int);
// remove/return the item at the head of the Queue
int   leaveQueue(Queue *);
// return the number of items currently in the Queue
int   lengthQueue(Queue);
// display the contents of the Queue
void showQueue(Queue);
 
#endif