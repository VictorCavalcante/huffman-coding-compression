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

// COMPRESS
	Q_tree *huffmanTree = createHuffmanTree();
	Hashtable* dictionary = createBinaryDicitionary(huffmanTree);
	writeOnCompressedFile(huffmanTree, dictionary);

// DECOMPRESS //todo: it doesn't need to pass huffmanTree as attr (make function to generate tree)
	readAndDecompressFile(huffmanTree);

//FREE
	//todo: free the huffmanTree
	//freeHashTable(dictionary);

	return 0;
}
