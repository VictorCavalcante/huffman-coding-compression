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
	struct node *left;
	struct node *right;
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

Queue* insertNodeOnQueue(Queue* priorityQueue, Node* newNode){
	//insert front
	if(isEmpty(priorityQueue) || priorityQueue->first->priority > newNode->priority){
		newNode->nextNode = priorityQueue->first;
		priorityQueue->first = newNode;
	} else {
		Node *current = priorityQueue->first;
		//insert end or mid
		while(current->nextNode != NULL && current->nextNode->priority < newNode->priority){
			current = current->nextNode;
		}
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
	}
	return priorityQueue;
}

Node* createQueueNode(char item, int priority){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->priority = priority;
	newNode->value = item;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Queue* enqueue(Queue* priorityQueue, char item, int priority){
	Node *newNode = createQueueNode(item, priority);
	return insertNodeOnQueue(priorityQueue, newNode);
}

Node* dequeue(Queue* queue){
	if(!isEmpty(queue)){
		Node *current = queue->first;
		queue->first = queue->first->nextNode;
		current->nextNode = NULL;
		return current;
	}
	return NULL;
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

void printQueueTreePreOrder(Node* node){
	if(node != NULL){
		printf("%c ", node->value);
		printQueueTreePreOrder(node->left);
		printQueueTreePreOrder(node->right);
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

int getQueueLength(Queue* queue){
	Node *current = queue->first;
	int count = 0;
	while(current != NULL){
		current = current->nextNode;
		count++;
	}
	return count;
}

Node* mergeQueueIntoHuffmanTree(Queue* queue){
	Node *firstNode, *secondNode, *newNode;
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
