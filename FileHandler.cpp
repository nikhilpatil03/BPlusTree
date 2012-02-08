/*
 * FileHandler.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "FileHandler.h"
#include "common.h"

FileHandler::FileHandler(char *fileName) {
 fio.open(fileName, ios:: in | ios::out | ios::binary);		//pass mode as iso:: in | ios::out | ios::binary
	if(!fio) {
		printf("File opening failed.");
	}
}



int FileHandler::readBlock(int offset, byte *data) {
if (offset % BLOCK_SIZE != 0) {
			printf("Offset is not aligned to block boundaries.");
			return 1;
		}
		fio.seekp(0,ios::end);
		if (offset + BLOCK_SIZE > fio.tellp()) {
			printf("Error: Reading beyond the file.");
			return 0;
		}
		fio.seekg(offset,ios::beg);
		fio.read((char *)data, BLOCK_SIZE);
		return 1;
	}


int FileHandler::writeBlock(int offset, byte *data) {
	if (offset % BLOCK_SIZE != 0) {
				printf("Offset is not aligned to block boundaries.");
				return 1;
			}

			fio.seekp(0,ios::end);
			if (offset > fio.tellp()+1) {
				printf("Error: Offset > fileSize, causing to create holes in the file.");
				return 0;
			}

			fio.seekp(offset,ios::beg);
			fio.write((char *)data, BLOCK_SIZE);
			return 0;
}

FileHandler::~FileHandler() {
	fio.close();
}

