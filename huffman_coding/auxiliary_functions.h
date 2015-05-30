/*
 * auxiliary_functions.h
 *  Created on: May 30, 2015
 */

#ifndef AUXILIARY_FUNCTIONS_H_
#define AUXILIARY_FUNCTIONS_H_

/**
 * Sorts the given string, then calculates the frequency of ocurrence of
 * each different character on given string. Later, pushes each different
 * character into a priority queue using its frequency as priority.
 * Returns the newly created queue containing every character
 * and its frequency of occurence on each node.
 */
Queue* generateCharacterOcurrenceQueue(Queue* queue, char *fullText);

/**
 * Removes line breack character '\n' from the end of the string
 */
void removeLineBreakOfString(char* newStr);

#endif /* AUXILIARY_FUNCTIONS_H_ */
