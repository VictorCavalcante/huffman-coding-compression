/*
 * priority_queue.c
 *  Created on: May 15, 2015
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char value;
	int priority;
	struct node *nextNode;
}Node;

typedef struct queue{
	Node *first;
}Queue;

Queue* createQueue(){
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	return queue;
}

int isEmpty(Queue* queue){
	return (queue->first == NULL);
}

Queue* enqueue(Queue* priorityQueue, char item, int priority){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->priority = priority;
	newNode->value = item;
	//insert front
	if(isEmpty(priorityQueue) || priorityQueue->first->priority > priority){
		newNode->nextNode = priorityQueue->first;
		priorityQueue->first = newNode;
	} else {
		Node *current = priorityQueue->first;
		//insert end or mid
		while(current->nextNode != NULL && current->nextNode->priority < priority){
			current = current->nextNode;
		}
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
	}
	return priorityQueue;
}

int dequeue(Queue* queue){
	if(!isEmpty(queue)){
		int dequeued = queue->first->value;
		Node *current = queue->first;
		queue->first = queue->first->nextNode;
		free(current);
		return dequeued;
	}
	return -1;
}

void printPriorityQueue(Queue* queue){
	Node *current = queue->first;
	while(current != NULL){
		if(current->value == '\n'){
			printf("\\n | %d\n", current->priority);
		} else {
			printf("%c | %d\n", current->value, current->priority);
		}
		current = current->nextNode;
	}
}

void freePriorityQueue(Queue* queue){
	Node *current;
	while(queue->first != NULL){
		current = queue->first;
		queue->first = queue->first->nextNode;
		free(current);
	}
}


