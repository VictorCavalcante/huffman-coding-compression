/*
 * auxiliary_functions.c
 *  Created on: May 30, 2015
 */
#include <string.h>
#include <stdio.h>
#define H_MAX 13

int is_bigendian(){
	int i = 1;
	return ( (*(char*)&i) == 0 );
}

short reverseShort(short s) {
    unsigned char c1, c2;
    if(is_bigendian()){
        return s;
    } else {
        c1 = s & 255;
        c2 = (s >> 8) & 255;
        return (c1 << 8) + c2;
    }
}

void setHeaderPlaceholder(FILE *pFile){
	unsigned short mask = 0;
	fwrite(&mask, sizeof(mask), 1, pFile);
}

void writeTrashAndTreeSize(FILE *pFile, int trashSize, int treeSize){
	fseek(pFile, 0, SEEK_SET);
	unsigned short mask = (trashSize << 13) | treeSize;
	mask = reverseShort(mask); //Check if littleEndian or bigEndian and formatting accordingly
	fwrite(&mask, sizeof(mask), 1, pFile);
}

int getTrashSize(FILE *pFile){
	fseek(pFile, 0, SEEK_SET);
	unsigned char trashSize = fgetc(pFile);
	return trashSize >> 5;
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
