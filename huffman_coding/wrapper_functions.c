/*
 * wrapper_functions.c
 *
 *  Created on: Jul 5, 2015
 *      Author: victor
 */
#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "hashtable_list.h"
#include "auxiliary_functions.h"
#define MAX_BIN_PATH 100

Q_tree* createHuffmanTree(){
	char auxChar;
	// Open File
	FILE *inFile;
	inFile = fopen("test.txt", "r");
	checkOpeningFileError(inFile);

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
	Q_tree *huffmanTree = mergeQueueIntoHuffmanTree(occurrenceQueue);

	//FREE
	//todo: find a way to free the queue before returning it
	//freePriorityQueue(occurrenceQueue);

	return huffmanTree;
}

Hashtable* createBinaryDicitionary(Q_tree *huffmanTree){
	// Generating hash with binary dictionary
	char binaryPath[MAX_BIN_PATH] = "";
	char pathDirection[5] = "";
	Hashtable* dictionary = createHashTable();
	create_binary_dictionary_hashtable(getTreeRootNode(huffmanTree), binaryPath, pathDirection, dictionary);
	return dictionary;
}

void writeOnCompressedFile(Q_tree *huffmanTree, Hashtable* dictionary){
	//Opening file for binary translation
		FILE *tslFile = fopen("test.txt", "r");
		checkOpeningFileError(tslFile);

		//Creating new .huff file to write compressed binary data
		FILE *outFile = fopen("outTest.huff", "w+b");
		checkOpeningFileError(outFile);

		//Setting Header placeholder
		setHeaderPlaceholder(outFile);

		//Writting tree (pre-order)
		writeTreeOnFile(outFile, getTreeRootNode(huffmanTree), huffmanTree);

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
			int trashSize = 8 - getQueueLength(binaryTrans);
			int binQueueSize = getQueueLength(binaryTrans), j = 7;
			mask = 0 << 8;
			for(i = 0; i < binQueueSize; i++){
				if(dequeueAndFree(binaryTrans) == '1'){
					mask = setBit(mask, j);
				}
				j--;
			}
			writeTrashAndTreeSize(outFile, trashSize, getTreeSize(huffmanTree));
		}


		//FREE & CLOSE
		fclose(tslFile);
		fclose(outFile);
		freePriorityQueue(binaryTrans);
		printf("\nCOMRPESSED! ><");
}

void readAndDecompressFile(Q_tree *huffmanTree){
	//Opening file for binary translation
	FILE *huffFile = fopen("outTest.huff", "r");
	checkOpeningFileError(huffFile);

	//Getting header data
	int trashSize = getFileHeaderTrashSize(huffFile),
		treeSize = getFileHeaderTreeSize(huffFile);
	int n;
	printf("Trash size: %d\n", trashSize);
	printf("Tree size: %d\n", treeSize);
	printf("Tree: ");
	for(n = 0; n < treeSize; n++){
		printf("%c", fgetc(huffFile));
	}

	//Generate tree
	// ?

	//Reading, translating, writing
	readTraslateWrite(huffFile, huffmanTree);

	//FREE & CLOSE
	fclose(huffFile);
	printf("\nDECOMRPESSED! <>");
}
