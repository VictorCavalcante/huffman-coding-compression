/*
 * auxiliary_functions.h
 *  Created on: May 30, 2015
 */

#ifndef AUXILIARY_FUNCTIONS_H_
#define AUXILIARY_FUNCTIONS_H_

void checkOpeningFileError(FILE *pFile);

int is_bigendian();

short reverseShort(short s);

void setHeaderPlaceholder(FILE *pFile);

void writeTrashAndTreeSize(FILE *pFile, int trashSize, int treeSize);

int getFileHeaderTrashSize(FILE *pFile);

int getFileHeaderTreeSize(FILE *pFile);

/**
 * Removes line breack character '\n' from the end of the string
 */
void removeLineBreakOfString(char* newStr);


long getLastBytePosition(FILE* pFile);

/**
 * Creates a mask empty buffer then sets a bit on its #i position.
 * Then using the OR arithmetic operation between given buffer and mask, sets
 * the bit '1' on the #i position of given buffer, then returns it.
 */
unsigned char setBit(unsigned char c, int i);

int isBitISet(unsigned char c, int i);

#endif /* AUXILIARY_FUNCTIONS_H_ */
