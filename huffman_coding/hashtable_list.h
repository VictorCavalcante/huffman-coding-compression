/*
 * hashtable_list.h
 *  Created on: Jun 3, 2015
 */

#ifndef HASHTABLE_LIST_H_
#define HASHTABLE_LIST_H_

typedef struct h_node H_node;
typedef struct hashtable Hashtable;

/**
 * Creates a HashTable by allocating space for the array of pointers
 * and assigning each pointer to NULL.
 * @return 		Pointer to the newly created HashTable
 */
Hashtable* createHashTable();

/**
 * Divides the int correspondent of the key's ASCII code by the maximum size of the HashTable,
 * therefore returning a number inside the range between 0 and the HashTable's size.
 * @param key 	Char letter
 * @return 		Integer inside the range of [0, H_MAX]
 */
int hashGenerator(char key);

/*
 * Inserts/allocates a new value into the hashTable and updates its ocurrence accordingly.
 * If the key already exists, its 'occurrence' is increased by 1.
 * @param ht 		The HashTable
 * @param keyLetter The letter used as a key in the hashGenerator() function.
 */
void put_occurrence(Hashtable* ht, char keyLetter);

/*
 * Inserts/allocates a new value into the hashTable. Allows same keys for different values.
 * @param ht 		The HashTable
 * @param binary	A string containing the new binary representation of given key
 * @param keyLetter The letter used as a key in the hashGenerator() function.
 */
void put(Hashtable* ht, char *binary, char keyLetter);

/*
 * Gets the new binary representation (value) of given key stored in a HashTable.
 * @param ht 		The HashTable
 * @param keyLetter The letter used as a key.
 * @return 			Value of given key.
 */
char* get(Hashtable* ht, char keyLetter);

/*
 * Prints the complete HashTable with its pointers and values.
 * @param ht 	The HashTable
 */
void printHashTable(Hashtable *ht);

/*
 * Frees HashTable completly
 * @param ht 	The HashTable
 */
void freeHashTable(Hashtable *ht);

/**
 * Recursive function that iterates the huffman tree in pre-order concatenating 0 every time it moves
 * the pointer to the left and 1 when it moves to the right. When the pointer reaches the traversal '*'
 * it then pushes the string containing the 0's and 1's and node value into a hashtable, generating a
 * dictionary of characters and correspondent binary representation.
 * @param node 		First node (root) of a huffman tree
 * @param path		Binary code representing the path taken to reach a key leaf (Set empty string as default)
 * @param direction The direction to take in order to find the key leaf (Set empty string as default)
 * @param ht		The HashTable
 */
void create_binary_dictionary_hashtable(Q_node* node, char *path, char *direction, Hashtable* ht);

/**
 * Iterates through a 'occurrence' hashTable containing a key (letter) and its value (frequency)
 * saving every value and key into a Min-Priority Queue (ascending order) using its frequency as priority.
 * @param queue 			The Priority Queue
 * @param occurrenceHash 	The 'occurrence' HashTable
 * @return 					Min-priority Queue with frequency of occurence of given characters.
 */
Queue* generateCharacterOcurrenceQueue(Queue* queue, Hashtable *occurrenceHash);


#endif /* HASHTABLE_LIST_H_ */
