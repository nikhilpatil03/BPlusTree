/*
 * FileHandler.h
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_


class FileHandler {
	FILE * filePointer;
public:
	FileHandler(char *fileName);
	virtual ~FileHandler();
	int readBlock(int offset, byte *data);
	int writeBlock(int offset, byte *data);
	int close();
};

#endif /* FILEHANDLER_H_ */
