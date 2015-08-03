/*
 * hashtable_list.c
 *  Created on: May 17, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#define MAX_BIN_PATH 100
#define H_MAX 30
#define BNRY_SIZE 100

typedef struct h_node{
	char binary[BNRY_SIZE];
	char keyLetter;
	int occurrence;
	struct h_node* nextElement;
}H_node;

typedef struct hashtable{
	H_node *table[H_MAX];
}Hashtable;

Hashtable* createHashTable(){
	Hashtable* newTable = malloc(sizeof(Hashtable));
	int i;
	for(i = 0; i < H_MAX; i++){
		newTable->table[i] = NULL;
	}
	return newTable;
}

int hashGenerator(char key){
	return key % H_MAX;
}

void put_occurrence(Hashtable* ht, char keyLetter){
	int h = hashGenerator(keyLetter);
	H_node *current = ht->table[h];
	//Search for update
	while(current != NULL){
		if(current->keyLetter == keyLetter){ //Update
			current->occurrence++;
			break;
		 }
		current = current->nextElement;
	}
	//Insert front
	if(current == NULL){
		H_node* newElement = (H_node*)malloc(sizeof(H_node));
		newElement->keyLetter = keyLetter;
		newElement->occurrence = 1;
		newElement->nextElement = ht->table[h];
		ht->table[h] = newElement;
	}
}

void put(Hashtable* ht, char *binary, char keyLetter){
	int h = hashGenerator(keyLetter);
	H_node* newElement = (H_node*)malloc(sizeof(H_node));
	strcpy(newElement->binary, binary);
	newElement->keyLetter = keyLetter;
	newElement->nextElement = ht->table[h];
	ht->table[h] = newElement;
}

char* get(Hashtable* ht, char keyLetter){
	int h = hashGenerator(keyLetter);
	H_node* current = ht->table[h];
	while(current != NULL && current->keyLetter != keyLetter){
		current = current->nextElement;
	}
	if(current == NULL){
		return "not found";
	} else {
		return current->binary;
	}
}

void printHashTable(Hashtable *ht){
    int i;
    H_node *current;
    for(i = 0; i < H_MAX; i++){
		printf("\n[%d.]--", i);
		current = ht->table[i];
		while(current != NULL){
			printf("%c|%s -> ", current->keyLetter, current->binary);
			current = current->nextElement;
		}
    }
}

void freeHashTable(Hashtable *ht){
    int i;
    H_node *current, *previous;
    for(i = 0; i < H_MAX; i++){
		current = ht->table[i];
		while(current != NULL){
			previous = current;
			current = current->nextElement;
			free(previous);
		}
    }
}

void create_binary_dictionary_hashtable(Q_node* node, char *path, char *direction, Hashtable* ht){
	char pathTurn[MAX_BIN_PATH];
	if(strcmp(direction, "left") == 0){
		strcat(path, "0");
	} else if (strcmp(direction, "right") == 0){
		strcat(path, "1");
	}
	strcpy(pathTurn, path);

	if(getQueueNodeValue(node) == '*'){
		create_binary_dictionary_hashtable(getQueueNodeLeft(node), path, "left", ht);
		create_binary_dictionary_hashtable(getQueueNodeRight(node), pathTurn, "right", ht);
	} else {
		put(ht, path, getQueueNodeValue(node));
	}
}

Queue* generateCharacterOcurrenceQueue(Queue* queue, Hashtable *occurrenceHash){
	int i;
	H_node *current;
	for(i = 0; i < H_MAX; i++){
		current = occurrenceHash->table[i];
		while(current != NULL){
			queue = PQ_enqueue(queue, current->keyLetter, current->occurrence);
			current = current->nextElement;
		}
	}
	return queue;
}
