/*
 * auxiliary_functions.h
 *  Created on: May 30, 2015
 */

#ifndef AUXILIARY_FUNCTIONS_H_
#define AUXILIARY_FUNCTIONS_H_

/**
 * Checks weather the File opening was successful.
 * @param pFile		Pointer to the openend file
 */
void checkOpeningFileError(FILE *pFile);

/**
 * Determine endianness of your machine (little endian or big endian)
 * Little and big endian are two ways of storing multibyte data-types (int, float, etc).
 * In little endian machines: the last byte of a binary representation is stored first. 1 = 00000001 00000000
 * In big endian machines: the first byte of a binary representation is stored first. 1 = 00000000 00000001
 * @return		True(1) for big endian, false(0) for little endian
 */
int is_bigendian();

/**
 * Converts a short (data-type) little endian binary representation into its big endian representation,
 * only if dealing with a little endian machine.
 * @param s		Short value to be converted
 * @return		The value of a 'short' in its its big endian representation
 */
short reverseShort(short s);

/**
 * Writes an empty placeholder the size of a short (2 bytes) at the beggining of the file,
 * enabling the user to later configure the header by overriding the empty template.
 * @param pFile		Pointer to the file
 */
void setHeaderPlaceholder(FILE *pFile);

/**
 * Sets the file pointer to the beggining of the file, then writes the trash size (on the first 3 bits)
 * and the tree size (from the 4th bit to the 16th bit) taking up the first 2 bytes of the file (header).
 * @param pFile		Pointer to the file
 * @param trashSize	Size of the trash
 * @param treeSize 	Size of the tree
 */
void writeTrashAndTreeSize(FILE *pFile, int trashSize, int treeSize);

/**
 * Reads the first byte of a file, then shifts 5 bits to the right, therefore returning the only first 3 bits
 * that cointains the trash size.
 * @param pFile 	Pointer to the file
 * @return			Trash size
 */
int getFileHeaderTrashSize(FILE *pFile);

/**
 * Reads the first 2 bytes of a file, then using bitwise operations sets the first 3 bits to 0 to ignore the
 * trash size therefore returning only the tree.
 * @param pFile 	Pointer to the file
 * @return			Tree size
 */
int getFileHeaderTreeSize(FILE *pFile);

/**
 * Removes line breack character '\n' from the end of the string
 * @param newStr	String to be trimmed.
 */
void removeLineBreakOfString(char* newStr);

/*
 * Moves the file pointer to the last position in the file to get the last byte's position,
 * than moves it back to its previous place.
 * @param pFile		Pointer to the file
 * @return 			The position of the last byte in the file
 */
long getLastBytePosition(FILE* pFile);

/**
 * Creates a mask empty buffer then sets a bit on its N position.
 * Then using bitwise operations, sets '1' in the Nth position of given buffer.
 * @param c 	A character holding the expected binary
 * @param i 	The Nth position in which the bit is to be set
 * @return  	The char representation with a bit set on the Nth position
 */
unsigned char setBit(unsigned char c, int i);

/**
 * Checks weather the bit in the Nth postion of given byte is set to 1.
 * @param c 	A character holding the expected binary
 * @param i 	The Nth position in which to check if the bit is set
 * @return  	True(1) if bit is set, False(0) if not.
 */
int isBitISet(unsigned char c, int i);


#endif /* AUXILIARY_FUNCTIONS_H_ */
