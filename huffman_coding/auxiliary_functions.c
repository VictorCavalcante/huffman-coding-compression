/*
 * auxiliary_functions.c
 *  Created on: May 30, 2015
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define H_MAX 30

void checkOpeningFileError(FILE *pFile){
	if(pFile == NULL){
		printf("Error opening file");
		exit(0);
	}
}

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

int getFileHeaderTrashSize(FILE *pFile){
	fseek(pFile, 0, SEEK_SET);
	unsigned char trashSize = fgetc(pFile);
	return trashSize >> 5;
}

int getFileHeaderTreeSize(FILE *pFile){
	fseek(pFile, 0, SEEK_SET);
	unsigned short treeSize;
	fread(&treeSize, sizeof(treeSize), 1, pFile);
	treeSize = reverseShort(treeSize); //Check if littleEndian or bigEndian and formatting accordingly
	return (treeSize | 57344) ^ 57344; // fill first 3 bits with 111 then sets it to 000
}

void removeLineBreakOfString(char* newStr){
	if ((strlen(newStr) > 0) && (newStr[strlen(newStr) - 1] == '\n')){
		newStr[strlen(newStr) - 1] = '\0';
	}
}

void formatFileExtensionToHuff(char* outputName, char* fileName){
	strncat(outputName, fileName, strlen(fileName) - 3);
	strcat(outputName, "huff");
}

void formatFileExtensionToText(char* outputName, char* fileName){
	strncat(outputName, fileName, strlen(fileName) - 4);
	strcat(outputName, "txt");
}

long getLastBytePosition(FILE* pFile){
	long currPos = ftell(pFile);
	fseek(pFile, 0, SEEK_END);
	long finalPos = ftell(pFile);
	fseek(pFile, currPos, SEEK_SET);

	return finalPos;
}

unsigned char setBit(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask | c;
}

int isBitISet(unsigned char c, int i){
	unsigned char mask = 1 << i;
	return mask & c;
}
