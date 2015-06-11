/*
 * auxiliary_functions.c
 *  Created on: May 30, 2015
 */
#include <string.h>
#include "priority_queue.h"

Queue* generateCharacterOcurrenceQueue(Queue* queue, char *fullText){
	int i, j, eventCount = 1;
	char aux;
	//Sorting fullText string
	for(i = 0; i < strlen(fullText); i++){
		for(j = i; j < strlen(fullText); j++){
			if(fullText[i] > fullText[j]){
				aux = fullText[i];
				fullText[i] = fullText[j];
				fullText[j] = aux;
			}
		}
	}
	//Counting ocurrencies & enqueuing characters
	char prev = fullText[0];
	for(i = 1; i <= strlen(fullText); i++){
		if(fullText[i] == prev && fullText[i] != '\0'){
			eventCount++;
		} else {
			queue = PQ_enqueue(queue, prev, eventCount);
			eventCount = 1;
			prev = fullText[i];
		}
	}
	return queue;
}

void removeLineBreakOfString(char* newStr){
	if ((strlen(newStr) > 0) && (newStr[strlen(newStr) - 1] == '\n')){
		newStr[strlen(newStr) - 1] = '\0';
	}
}

unsigned char setBit(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask | c;
}
