/*
 * main.c
 *  Created on: May 30, 2015
 */
#include <stdio.h>
#include "priority_queue.h"
#include "hashtable_list.h"
#include "auxiliary_functions.h"
#include "wrapper_functions.h"

int main(){
	int entry;
	char fileName[20];
	printf( "			|-------- HUFFMAN CODING --------|\n"
			"			|================================|\n"
			"			|	1. Compress      =><=    |\n"
			"			|	2. Decompress    <==>    |\n"
			"			|================================|\n\n"
			"Enter your choice: ");
	scanf("%d", &entry);
	switch(entry){
		case 1:
			printf("::: Ready to compress file...\n"
					"Enter file name: ");
			scanf("%s", fileName);
			// COMPRESS ================================================
			Q_tree *huffmanTree = createHuffmanTree(fileName);
			Hashtable* dictionary = createBinaryDicitionary(huffmanTree);
			writeOnCompressedFile(huffmanTree, dictionary, fileName);
			//FREE
			freeQueueTree(getTreeRootNode(huffmanTree));
			freeHashTable(dictionary);
			break;
		case 2:
			printf("\n::: Ready to decompress file...\n"
					"Enter file name: ");
			scanf("%s", fileName);
			// DECOMPRESS ==============================================
			readAndDecompressFile(fileName);
			break;
	}

	return 0;
}
