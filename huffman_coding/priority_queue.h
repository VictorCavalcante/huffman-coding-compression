/*
 * priority_queue.h
 *  Created on: May 30, 2015
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

/**
 * Struct of a node containing both a value, a priority and a pointer
 * that points to the next node on the priority queue
 */
typedef struct node Node;

/**
 * Struct of a queue containing a pointer that points to the
 * very first node of the priority queue
 */
typedef struct queue Queue;

/**
 * Allocates queue, sets its property @first as NULL and
 * returns a pointer to the newly allocated Queue.
 */
Queue* createQueue();

/**
 * Check if the queue is empty
 * returns true of false.
 */
int isEmpty(Queue* queue);

/**
 * Allocates node and sets its priority and value,
 * then inserts the new node in the queue according to its priority in ASCENDING order.
 */
Queue* enqueue(Queue* priorityQueue, int item, int priority);

/**
 * Free first element of the queue (Element with the lowest priority),
 * and then returns its value.
 * If the queue is empty, returns -1
 */
int dequeue(Queue* queue);

/**
 * Prints every element of the queue in order.
 */
void printPriorityQueue(Queue* queue);

/**
 * Free every element of the queue.
 */
void freePriorityQueue(Queue* queue);


#endif /* PRIORITY_QUEUE_H_ */
