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
#define MAX_BIN_PATH 100

int main(){
	FILE *inFile;

	char auxChar;
	char binaryPath[MAX_BIN_PATH] = "";
	char pathDirection[5] = "";

// STEP ONE - Open File > Genereate Occurrence-Hash > Genereate Queue > Generate Tree > Create Binary Dictionary ======
	// Open File
	inFile = fopen("test.txt", "r");
	if(inFile == NULL){
		printf("Error opening file");
		exit(0);
	}

	// Genereate Occurrence Hashtable
	Hashtable *occurrenceHash = createHashTable();
	while((auxChar = fgetc(inFile)) != EOF){
		put_occurrence(occurrenceHash, auxChar);
	}
	fclose(inFile);

	// Generating priority queue
	Queue* occurrenceQueue = createQueue();
	occurrenceQueue = generateCharacterOcurrenceQueue(occurrenceQueue, occurrenceHash);
	free(occurrenceHash);

	// Merging Queue into a tree
	Q_node *huffmanTree = mergeQueueIntoHuffmanTree(occurrenceQueue);

	// Generating hash with binary dictionary
	Hashtable* dictionary = createHashTable();
	create_binary_dictionary_hashtable(huffmanTree, binaryPath, pathDirection, dictionary);

// STEP TWO - Open file (trslte & .huff) > Create trslte queue > Trslte c-by-c > Write on file
	//Opening file for binary translation
	//todo Use fseek instead of opening the file again
	FILE *tslFile = fopen("test.txt", "r");
	if(tslFile == NULL){
		printf("Error opening file");
		exit(0);
	}

	//Creating new .huff file to write compressed binary data
	FILE *headerFile = fopen("outTest.huff", "a+");
	if(headerFile == NULL){
		printf("Error writing file");
		exit(0);
	}

	//Setting Header placeholder
	setHeaderPlaceholder(headerFile);

	//Writting tree (pre-order)
	writeTreeOnFile(headerFile, huffmanTree);

	fclose(headerFile);

	FILE *outFile = fopen("outTest.huff", "ab+");
	if(outFile == NULL){
		printf("Error writing file");
		exit(0);
	}

	//Creating translation queue
	Queue *binaryTrans = createQueue();
	char currChar, currBin[MAX_BIN_PATH];
	unsigned char mask;
	int i;
	// Reading character by character, translating them and then writing its binary correspondent on .huff
	while((currChar = fgetc(tslFile)) != EOF) {
		strcpy(currBin, get(dictionary, currChar));
		for(i = 0; i < strlen(currBin); i++){
			enqueue(binaryTrans, currBin[i]);
		}
		while(getQueueLength(binaryTrans) >= 8){
			mask = 0 << 8;
			for(i = 7; i >= 0; i--){
				if(dequeueAndFree(binaryTrans) == '1'){
					mask = setBit(mask, i);
				}
			}
			fwrite(&mask, sizeof(unsigned char), 1, outFile);
		}
	}

	//todo get trash size here
	// Reading remaining characters and writing their binary correspondent
	if(getQueueLength(binaryTrans) > 0){
		int binQueueSize = getQueueLength(binaryTrans), j = 7;
		mask = 0 << 8;
		for(i = 0; i < binQueueSize; i++){
			if(dequeueAndFree(binaryTrans) == '1'){
				mask = setBit(mask, j);
			}
			j--;
		}
		fwrite(&mask, sizeof(unsigned char), 1, outFile);
	}

	//Free & close
	fclose(tslFile);
	fclose(outFile);
	freePriorityQueue(binaryTrans);
	freePriorityQueue(occurrenceQueue);
	freeHashTable(dictionary);

	return 0;
}
