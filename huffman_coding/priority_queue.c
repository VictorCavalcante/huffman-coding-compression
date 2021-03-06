/*
 * priority_queue.c
 *  Created on: May 15, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary_functions.h"

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

typedef struct q_tree{
	int treeSize;
	Q_node *first;
}Q_tree;

Queue* createQueue(){
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	return queue;
}

Q_tree* createQueueTree(){
	Q_tree* tree = (Q_tree*)malloc(sizeof(Q_tree));
	tree->first = NULL;
	tree->treeSize = 0;
	return tree;
}

int queueIsEmpty(Queue* queue){
	return (queue->first == NULL);
}

Queue* insertNodeOnPriorityQueue(Queue* priorityQueue, Q_node* newNode){
	//insert front
	if(queueIsEmpty(priorityQueue) || priorityQueue->first->priority >= newNode->priority){
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

Queue* insertNodeOnQueue(Queue* queue, Q_node* newNode){
	//insert front
	if(queueIsEmpty(queue)){
		newNode->nextNode = queue->first;
		queue->first = newNode;
	} else {//insert end
		Q_node *current = queue->first;
		while(current->nextNode != NULL){
			current = current->nextNode;
		}
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
	}
	return queue;
}

Q_node* createQueueNode(char item, int priority){
	Q_node *newNode = (Q_node*)malloc(sizeof(Q_node));
	newNode->priority = priority;
	newNode->value = item;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Queue* PQ_enqueue(Queue* priorityQueue, char item, int priority){
	Q_node *newNode = createQueueNode(item, priority);
	return insertNodeOnPriorityQueue(priorityQueue, newNode);
}

Queue* enqueue(Queue* queue, char item){
	Q_node *newNode = createQueueNode(item, 0);
	return insertNodeOnQueue(queue, newNode);
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

char dequeueAndFree(Queue* queue){
	if(!queueIsEmpty(queue)){
		Q_node *current = queue->first;
		char dequeuedValue;
		dequeuedValue = current->value;
		queue->first = queue->first->nextNode;
		free(current);
		return dequeuedValue;
	}
	return -1;
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
		printf("%c - %d\n", node->value, node->priority);
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

void freeQueueTree(Q_node* first){
	if(first != NULL){
		freeQueueTree(first->left);
		freeQueueTree(first->right);
		free(first);
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

Q_tree* mergeQueueIntoHuffmanTree(Queue* queue){
	Q_node *firstNode, *secondNode, *newNode;
	Q_tree *huffmanTree = createQueueTree();
	int sum;

	while(getQueueLength(queue) > 1){
		firstNode = dequeue(queue);
		secondNode = dequeue(queue);
		sum = firstNode->priority + secondNode->priority;

		newNode = createQueueNode('*', sum);
		queue = insertNodeOnPriorityQueue(queue, newNode);
		newNode->left = firstNode;
		newNode->right = secondNode;
	}
	huffmanTree->first = newNode;
	return huffmanTree;
}

void writeTreeOnFile(FILE *pfile, Q_node *node, Q_tree *tree){
	if(node != NULL){
		tree->treeSize++;
		fputc(node->value, pfile);
		writeTreeOnFile(pfile, node->left, tree);
		writeTreeOnFile(pfile, node->right, tree);
	}
}

void readTraslateWrite(FILE *pFile, Q_node *huffmanTree, int trashSize, char* fileName){
	FILE *endFile = fopen(fileName, "w");
	checkOpeningFileError(endFile);

	long finalPos = getLastBytePosition(pFile);
	unsigned char outChar;
	int i, custom_right_most_byte_limit = 0;
	Q_node *current = huffmanTree;

	while(!feof(pFile)){
		fread(&outChar, 1, 1, pFile);
		//If current byte is the last one on file
		if(ftell(pFile) == finalPos){
			fread(&outChar, 1, 1, pFile);
			custom_right_most_byte_limit = trashSize;
		}

		//Read and write until bit in the "custom_right_most_byte_limit" position
		for(i = 7; i >= custom_right_most_byte_limit; i--){
			// 1 => right
			if(current->value == '*' && isBitISet(outChar, i)){
				current = current->right;
			}// 0 <= left
			else {
				current = current->left;
			}
			//Upon reaching a leaf, write corresponding character to file
			if(current->value != '*'){
				fwrite(&current->value, sizeof(current->value), 1, endFile);
				current = huffmanTree; //back to top
			}
		}
	}
	fclose(endFile);
}

Q_node* build_tree_from_queue(Q_node *tree, Queue *queue){
	char dequeueValue = dequeueAndFree(queue);
	if(dequeueValue == '*'){
		tree = createQueueNode(dequeueValue, 0);

		tree->left = build_tree_from_queue(tree->left, queue);
		tree->right = build_tree_from_queue(tree->right, queue);
	} else {
		tree = createQueueNode(dequeueValue, 0);
	}
	return tree;
}

Q_node* enqueue_pre_order_tree(FILE *pFile, int treeSize){
	int n;
	Queue *queue = createQueue();
	for(n = 0; n < treeSize; n++){
		enqueue(queue, fgetc(pFile));
	}

	Q_node *newTree = NULL;
	newTree = build_tree_from_queue(newTree, queue);
	return newTree;
}

/*======== Getters ========*/

Q_node* getTreeRootNode(Q_tree* tree){
	return tree->first;
}

int getTreeSize(Q_tree* tree){
	return tree->treeSize;
}

Q_node* getQueueNodeLeft(Q_node* node){
	return node->left;
}

Q_node* getQueueNodeRight(Q_node* node){
	return node->right;
}

char getQueueNodeValue(Q_node* node){
	return node->value;
}
