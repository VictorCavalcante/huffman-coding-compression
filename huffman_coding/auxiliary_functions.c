/*
 * auxiliary_functions.c
 *  Created on: May 30, 2015
 */
#include <string.h>
#include <stdio.h>
#define H_MAX 13

void setHeaderPlaceholder(FILE *pfile){
	unsigned char mask = 0;
	fwrite(&mask, sizeof(unsigned char), 1, pfile);
	fwrite(&mask, sizeof(unsigned char), 1, pfile);
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
