/*
 * main.c
 *  Created on: May 30, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "hashtable_list.h"
#include "auxiliary_functions.h"
#define MAX_LINE 400
#define MAX_TOTAL 400
#define MAX_BIN_PATH 100

int main(){
	FILE *pFile;
	Queue* occurrenceQueue = createQueue();
	char strAux[MAX_LINE];
	char file_text[MAX_TOTAL] = "";
	char binaryPath[MAX_BIN_PATH] = "";
	char pathDirection[5] = "";

// STEP ONE - Open File > Save text > Genereate Queue > Generate Tree ====================
	// Open File
	pFile = fopen("test.txt", "r");
	if(pFile == NULL){
		printf("Error opening file");
		exit(0);
	}

	// Save entire text file content into string: file_text
	while(fgets(strAux, 100, pFile) != NULL){
		strcat(file_text, strAux);
	}
	removeLineBreakOfString(file_text);

	// Generating Ocurrence priority queue
	occurrenceQueue = generateCharacterOcurrenceQueue(occurrenceQueue, file_text);

	// Merging Queue into a tree
	Q_node *huffmanTree = mergeQueueIntoHuffmanTree(occurrenceQueue); //====================

	// Generating hash with binary dictionary
	Hashtable* dictionary = createHashTable();
	create_binary_dictionary_hashtable(huffmanTree, binaryPath, pathDirection, dictionary);
	printHashTable(dictionary);

	//Free & close
	freePriorityQueue(occurrenceQueue);
	freeHashTable(dictionary);
	fclose(pFile);
	return 0;
}
