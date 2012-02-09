/*
 * FileHandler.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "FileHandler.h"
#include "common.h"

FileHandler::FileHandler(char *inputFileName) {
	fio.open(inputFileName, ios::out | ios::binary);
	if(!fio) {
		printf("File opening failed.");
		exit(1);
	}
	fio.close();
	fio.open(inputFileName, ios::out | ios::in | ios::binary);
}


FileHandler::FileHandler(char *inputFileName,char open) {
	fio.open(inputFileName, ios::out | ios::in | ios::binary);
	if(!fio) {
		printf("File opening failed.");
		exit(1);
	}

}




int FileHandler::readBlock(long long int offset, byte *data) {

	fio.seekp(0,ios::end);
		if (offset*BLOCK_SIZE + BLOCK_SIZE > fio.tellp()) {
			printf("Error: Reading beyond the file.");
			return 0;
		}
		fio.seekg(offset*BLOCK_SIZE,ios::beg);
		fio.read((char *)data, BLOCK_SIZE);
		return 1;
	}


int FileHandler::writeBlock(long long int offset, byte *data) {

	fio.seekp(0,ios::end);
			if (offset > (fio.tellp()+1)) {
				printf("Error: Offset > fileSize, causing to create holes in the file.");
				return 0;
			}

			fio.seekp(offset*BLOCK_SIZE,ios::beg);
			fio.write((char *)data, BLOCK_SIZE);
			return 0;

}

int FileHandler::writeBlock(byte *data) {
			fio.seekp(0,ios::end);
			fio.write((char *)data, BLOCK_SIZE);
			return 0;
}

int FileHandler::getSize() {
	fio.seekg(0,ios::end);
	return (long long int)((fio.tellg()+1)/BLOCK_SIZE);
}

FileHandler::~FileHandler() {
	printf("Writing Index File!");
	fio.close();
}

