/*
 * hashtable_list.h
 *  Created on: Jun 3, 2015
 */

#ifndef HASHTABLE_LIST_H_
#define HASHTABLE_LIST_H_

typedef struct h_node H_node;

typedef struct hashtable Hashtable;

Hashtable* createHashTable();

int hashGenerator(char key);

void put_occurrence(Hashtable* ht, char keyLetter);

void put(Hashtable* ht, char *binary, char keyLetter);

char* get(Hashtable* ht, char keyLetter);

void printHashTable(Hashtable *ht);

void freeHashTable(Hashtable *ht);

/**
 * Receives a tree as first parameter then iterates the tree in pre-order
 * concatenating 0 everytime it moves the pointer to the left and 1 when it moves the pointer
 * to the right, when the pointer reaches the traversal '*' it then pushes the string containing
 * the 0's and 1's and node value into a hashtable, generating a dictionary of characters and
 * correspondent binary representation.
 */
void create_binary_dictionary_hashtable(Q_node* node, char *path, char *direction, Hashtable* ht);

/**
 * Sorts the given string, then calculates the frequency of ocurrence of
 * each different character on given string. Later, pushes each different
 * character into a priority queue using its frequency as priority.
 * Returns the newly created queue containing every character
 * and its frequency of occurence on each node.
 */
Queue* generateCharacterOcurrenceQueue(Queue* queue, Hashtable *occurrenceHash);

#endif /* HASHTABLE_LIST_H_ */
