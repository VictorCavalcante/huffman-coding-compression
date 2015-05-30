/*
 * main.c
 *  Created on: May 30, 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "auxiliary_functions.h"

int main(){
	FILE *pFile;
	Queue* ocurrenceQueue = createQueue();
	char strAux[100];
	char file_text[250] = "";

	//Open File
	pFile = fopen("test.txt", "r");
	if(pFile == NULL){
		printf("Error opening file");
		exit(0);
	}

	//Save entire text file content into string: file_text
	while(fgets(strAux, 100, pFile) != NULL){
		strcat(file_text, strAux);
	}
	removeLineBreakOfString(file_text);

	//Generating Ocurrence priority queue
	ocurrenceQueue = generateCharacterOcurrenceQueue(ocurrenceQueue, file_text);

	//Free & close
	freePriorityQueue(ocurrenceQueue);
	fclose(pFile);

	return 0;
}
