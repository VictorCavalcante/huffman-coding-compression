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

// STEP ONE - Open File > Save text > Genereate Queue > Generate Tree > Create Binary Dictionary ======
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
	fclose(pFile);
	// Generating Ocurrence priority queue
	occurrenceQueue = generateCharacterOcurrenceQueue(occurrenceQueue, file_text);

	// Merging Queue into a tree
	Q_node *huffmanTree = mergeQueueIntoHuffmanTree(occurrenceQueue); //====================

	// Generating hash with binary dictionary
	Hashtable* dictionary = createHashTable();
	create_binary_dictionary_hashtable(huffmanTree, binaryPath, pathDirection, dictionary);

// STEP TWO - ====================
	/*FILE *outFile;
	char unChar[8] = "This is";

	outFile = fopen("outTest.huff", "w+b");
	if(outFile == NULL){
		printf("Error writing file");
		exit(0);
	}
	fwrite(unChar, sizeof(unChar), 1, outFile);
	fclose(outFile);*/

	FILE *tFile = fopen("test.txt", "r");
	Queue *binaryTrans = createQueue();
	char currChar, currBin[100];
	int i;
	if(tFile == NULL){
		printf("Error opening file");
		exit(0);
	}
	while((currChar = fgetc(tFile)) != EOF) {
		strcpy(currBin, get(dictionary, currChar));
		for(i = 0; i < strlen(currBin); i++){
			enqueue(binaryTrans, currBin[i]);
		}
		if(getQueueLength(binaryTrans) >= 8){
			//todo dequeue 8 times while creating binary (setBit foo), then write it on the new .huff file
			for(i = 0; i < 8; i++){
				printf("%c", dequeueAndFree(binaryTrans));
			}
			printf("\n");
		}
	}
	if(strlen(currBin) > 0){
		//todo get trash size here
	}
	freePriorityQueue(binaryTrans);
	fclose(tFile);

	//Free & close
	freePriorityQueue(occurrenceQueue);
	freeHashTable(dictionary);

	return 0;
}
