/*
 * main.c
 *  Created on: May 30, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "auxiliary_functions.h"
#define MAX_LINE 400
#define MAX_TOTAL 400

int main(){
	FILE *pFile;
	Queue* occurrenceQueue = createQueue();
	char strAux[MAX_LINE];
	char file_text[MAX_TOTAL] = "";

	//Open File
	pFile = fopen("test.txt", "r");
	if(pFile == NULL){
		printf("Error opening file");
		exit(0);
	}

	//Save entire text file content into string: file_text
	while(fgets(strAux, 100, pFile) != NULL){
		strcat(file_text, strAux);
	}
	removeLineBreakOfString(file_text);

	//Generating Ocurrence priority queue
	occurrenceQueue = generateCharacterOcurrenceQueue(occurrenceQueue, file_text);

	//Merging Queue into a tree
	Node *huffmanTree = mergeQueueIntoHuffmanTree(occurrenceQueue);

	//Print huffman tree in preOrder
	printQueueTreePreOrder(huffmanTree);

	//Free & close
	freePriorityQueue(occurrenceQueue);
	fclose(pFile);
	return 0;
}
