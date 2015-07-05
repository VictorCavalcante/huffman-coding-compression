/*
 * wrapper_functions.h
 *
 *  Created on: Jul 5, 2015
 *      Author: victor
 */

#ifndef WRAPPER_FUNCTIONS_H_
#define WRAPPER_FUNCTIONS_H_

//Open File > Genereate Occurrence-Hash > Genereate Queue > Generate Tree
Q_tree* createHuffmanTree();

//Create Binary Dictionary
Hashtable* createBinaryDicitionary(Q_tree *huffmanTree);

//Open file (trslte & .huff) > Create trslte queue > Trslte c-by-c > Write on file
void writeOnCompressedFile(Q_tree *huffmanTree, Hashtable* dictionary);

//Get Header Data: Trash size, Tree size, Tree string > Generate tree > Read file, translate & write
void readAndDecompressFile(Q_tree *huffmanTree);

#endif /* WRAPPER_FUNCTIONS_H_ */
