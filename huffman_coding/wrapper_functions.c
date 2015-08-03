/*
 * wrapper_functions.c
 *
 *  Created on: Jul 5, 2015
 *      Author: victor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "hashtable_list.h"
#include "auxiliary_functions.h"
#define MAX_BIN_PATH 100
#define DIR_SIZE 5

Q_tree* createHuffmanTree(char *fileName){
	char auxChar;
	// Open File
	FILE *inFile;
	inFile = fopen(fileName, "r");
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

	return huffmanTree;
}

Hashtable* createBinaryDicitionary(Q_tree *huffmanTree){
	// Generating hash with binary dictionary
	char binaryPath[MAX_BIN_PATH] = "";
	char pathDirection[DIR_SIZE] = "";
	Hashtable* dictionary = createHashTable();
	create_binary_dictionary_hashtable(getTreeRootNode(huffmanTree), binaryPath, pathDirection, dictionary);
	return dictionary;
}

void writeOnCompressedFile(Q_tree *huffmanTree, Hashtable* dictionary, char *fileName){
	//Opening file for binary translation
		FILE *tslFile = fopen(fileName, "r");
		checkOpeningFileError(tslFile);

		//Creating new .huff file to write compressed binary data
		char outputName[20] = "";
		formatFileExtensionToHuff(outputName, fileName);
		FILE *outFile = fopen(outputName, "w+b");
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
				mask = 0;
				for(i = 7; i >= 0; i--){
					if(dequeueAndFree(binaryTrans) == '1'){
						mask = setBit(mask, i);
					}
				}
				fwrite(&mask, sizeof(mask), 1, outFile);
			}
		}

		// Reading remaining characters and writing their binary correspondent
		int trashSize = 0;
		if(getQueueLength(binaryTrans) > 0){
			int binQueueSize = getQueueLength(binaryTrans), j = 7;
			trashSize = 8 - binQueueSize;
			mask = 0;
			for(i = 0; i < binQueueSize; i++){
				if(dequeueAndFree(binaryTrans) == '1'){
					mask = setBit(mask, j);
				}
				j--;
			}
			//Writting last byte of the file (+ trash)
			fwrite(&mask, sizeof(mask), 1, outFile);
		}
		
		//Writting Trash Size and Tree Size on file header
		writeTrashAndTreeSize(outFile, trashSize, getTreeSize(huffmanTree));

		//FREE & CLOSE
		fclose(tslFile);
		fclose(outFile);
		freePriorityQueue(binaryTrans);
		printf("\n=><= COMPRESSED FILE: %s\n", outputName);
}

void readAndDecompressFile(char* fileName){
	//Opening file for binary translation
	char outputName[20] = "[1]";
	formatFileExtensionToText(outputName, fileName);
	FILE *huffFile = fopen(fileName, "r");
	checkOpeningFileError(huffFile);

	//Getting header data
	int trashSize = getFileHeaderTrashSize(huffFile),
		treeSize = getFileHeaderTreeSize(huffFile);

	//Generate tree
	Q_node *huffmanTree = enqueue_pre_order_tree(huffFile, treeSize);

	//Reading, translating, writing
	readTraslateWrite(huffFile, huffmanTree, trashSize, outputName);

	//FREE & CLOSE
	fclose(huffFile);
	printf("\n<==> DECOMPRESSED FILE: %s\n", outputName);
}
