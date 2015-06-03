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

void put(Hashtable* ht, char *binary, char keyLetter);

char get(Hashtable* ht, char keyLetter);

void printHashTable(Hashtable *ht);

void freeHashTable(Hashtable *ht);

#endif /* HASHTABLE_LIST_H_ */
