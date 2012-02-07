/*
 * FileHandler.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "FileHandler.h"
#include <common.h>

FileHandler::FileHandler(char *fileName) {
	// A constructor to create and/or open file named "fileName" for reading or writing depending on mode.
			filePointer = fopen(fileName, "a+");
			if (!filePointer) {
				printf("Failed to open file %s",fileName);
			}

}

int FileHandler::readBlock(int offset, byte *data) {
		if (offset % BLOCK_SIZE != 0) {
			printf("Offset is not aligned to block boundaries.");
			return 1;
		}

		return (fread(data, 1, BLOCK_SIZE, filePointer) == BLOCK_SIZE);
	}

	int FileHandler::writeBlock(int offset, byte *data) {
		if (offset % BLOCK_SIZE != 0) {
			printf("Offset is not aligned to block boundaries.");
						return 1;
		}

		return (fwrite(data, 1, BLOCK_SIZE, filePointer) == BLOCK_SIZE);
	}

	int FileHandler::close() {
		return fclose(filePointer);
	}



FileHandler::~FileHandler() {
	// TODO Auto-generated destructor stub
}

