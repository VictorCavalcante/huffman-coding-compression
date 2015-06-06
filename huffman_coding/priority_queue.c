/*
 * priority_queue.c
 *  Created on: May 15, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_list.h"
#define MAX_BIN_PATH 100

typedef struct q_node{
	char value;
	int priority;
	struct q_node *nextNode;
	struct q_node *left;
	struct q_node *right;
}Q_node;

typedef struct queue{
	Q_node *first;
}Queue;

Queue* createQueue(){
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	return queue;
}

int queueIsEmpty(Queue* queue){
	return (queue->first == NULL);
}

Queue* insertNodeOnQueue(Queue* priorityQueue, Q_node* newNode){
	//insert front
	if(queueIsEmpty(priorityQueue) || priorityQueue->first->priority > newNode->priority){
		newNode->nextNode = priorityQueue->first;
		priorityQueue->first = newNode;
	} else {
		Q_node *current = priorityQueue->first;
		//insert end or mid
		while(current->nextNode != NULL && current->nextNode->priority < newNode->priority){
			current = current->nextNode;
		}
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
	}
	return priorityQueue;
}

Q_node* createQueueNode(char item, int priority){
	Q_node *newNode = (Q_node*)malloc(sizeof(Q_node));
	newNode->priority = priority;
	newNode->value = item;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Queue* enqueue(Queue* priorityQueue, char item, int priority){
	Q_node *newNode = createQueueNode(item, priority);
	return insertNodeOnQueue(priorityQueue, newNode);
}

Q_node* dequeue(Queue* queue){
	if(!queueIsEmpty(queue)){
		Q_node *current = queue->first;
		queue->first = queue->first->nextNode;
		current->nextNode = NULL;
		return current;
	}
	return NULL;
}

void printPriorityQueue(Queue* queue){
	Q_node *current = queue->first;
	while(current != NULL){
		if(current->value == '\n'){
			printf("\\n | %d\n", current->priority);
		} else {
			printf("%c | %d\n", current->value, current->priority);
		}
		current = current->nextNode;
	}
}

void printQueueTreePreOrder(Q_node* node){
	if(node != NULL){
		printf("%c ", node->value);
		printQueueTreePreOrder(node->left);
		printQueueTreePreOrder(node->right);
	}
}

void freePriorityQueue(Queue* queue){
	Q_node *current;
	while(queue->first != NULL){
		current = queue->first;
		queue->first = queue->first->nextNode;
		free(current);
	}
}

int getQueueLength(Queue* queue){
	Q_node *current = queue->first;
	int count = 0;
	while(current != NULL){
		current = current->nextNode;
		count++;
	}
	return count;
}

Q_node* mergeQueueIntoHuffmanTree(Queue* queue){
	Q_node *firstNode, *secondNode, *newNode;
	int sum;

	while(getQueueLength(queue) > 1){
		firstNode = dequeue(queue);
		secondNode = dequeue(queue);
		sum = firstNode->priority + secondNode->priority;

		newNode = createQueueNode('*', sum);
		queue = insertNodeOnQueue(queue, newNode);
		newNode->left = firstNode;
		newNode->right = secondNode;
	}
	return newNode;
}

void create_binary_dictionary_hashtable(Q_node* node, char *path, char *direction, Hashtable* ht){
	char pathTurn[MAX_BIN_PATH];
	if(strcmp(direction, "left") == 0){
			strcat(path, "0");
	} else if (strcmp(direction, "right") == 0){
		strcat(path, "1");
	}
	strcpy(pathTurn, path);

	if(node->value == '*'){
		create_binary_dictionary_hashtable(node->left, path, "left", ht);
		create_binary_dictionary_hashtable(node->right, pathTurn, "right", ht);
	} else {
		put(ht, path, node->value);
	}
}
