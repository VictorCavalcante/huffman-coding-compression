/*
 * wrapper_functions.h
 *
 *  Created on: Jul 5, 2015
 *      Author: victor
 */

#ifndef WRAPPER_FUNCTIONS_H_
#define WRAPPER_FUNCTIONS_H_

/**
 * Opens the file to retrieve data, generates the occurrence hashTable, then uses it to generate
 * the priority queue, then merge the priority queue into a huffman tree.
 * @return 		The huffman tree
 */
Q_tree* createHuffmanTree();

/**
 * Generates 'binary-dictionary' HashTable using the huffman tree to access the keys and correpondents
 * 'binary-paths'.
 * @param huffmanTree 	The huffman tree
 * @return 				The 'dictionary' HashTable
 */
Hashtable* createBinaryDicitionary(Q_tree *huffmanTree);

/**
 * Opens file for binary translation & .huff file to write compressed binary data, then sets the header
 * placeholder, writes the tree inside the header after the placeholder, and creates the translation queue.
 * After that, it reads character by character, translating them and writing its binary correspondent
 * on file, then writes the trash-size and tree-size on the file header.
 * @param huffmanTree 	The huffman tree
 * @param dictionary	The 'dictionary' HashTable
 */
void writeOnCompressedFile(Q_tree *huffmanTree, Hashtable* dictionary);

/**
 * Opens compressed file for binary translation, gets the data written on the header, generates the pre-ordered tree,
 * then reads, translates and writes on the new .huff file.
 */
void readAndDecompressFile();

#endif /* WRAPPER_FUNCTIONS_H_ */
