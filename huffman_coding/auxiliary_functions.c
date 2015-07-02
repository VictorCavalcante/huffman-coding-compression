/*
 * auxiliary_functions.c
 *  Created on: May 30, 2015
 */
#include <string.h>
#include <stdio.h>
#define H_MAX 13

void setHeaderPlaceholder(FILE *pFile){
	unsigned char mask = 0;
	fwrite(&mask, sizeof(unsigned char), 1, pFile);
	fwrite(&mask, sizeof(unsigned char), 1, pFile);
}

void writeTrashAndTreeSize(FILE *pFile, int trashSize, int treeSize){
	//fseek(pFile, 0, SEEK_SET);
	//unsigned short mask = 0;
	//fwrite(&mask, sizeof(unsigned short), 1, pFile);
	printf("trash size: %d\ntree size: %d", trashSize, treeSize);
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
