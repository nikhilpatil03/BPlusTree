/*
 * FileHandler.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "FileHandler.h"
#include "common.h"

FileHandler::FileHandler(char *inputFileName) {
//	fstream fio;
	fio.open(inputFileName, ios::out | ios::binary);		//pass mode as iso:: in | ios::out | ios::binary
	if(!fio) {
		printf("File opening failed.");
		exit(1);
	}
	fio.close();
//	strcpy(this->fileName, inputFileName);
	fio.open(inputFileName, ios::out | ios::in | ios::binary);
}



int FileHandler::readBlock(int offset, byte *data) {
//		if (offset % BLOCK_SIZE != 0) {
//			printf("Offset is not aligned to block boundaries.");
//			return 1;
//		}
//	fstream fio;
//	fio.open(fileName, ios::out | ios::in | ios::binary);

	fio.seekp(0,ios::end);
		if (offset*BLOCK_SIZE + BLOCK_SIZE > fio.tellp()) {
			printf("Error: Reading beyond the file.");
			return 0;
		}
		fio.seekg(offset*BLOCK_SIZE,ios::beg);
		fio.read((char *)data, BLOCK_SIZE);
//		fio.close();
		return 1;
	}


int FileHandler::writeBlock(int offset, byte *data) {
//		if (offset % BLOCK_SIZE != 0) {
//				printf("Offset is not aligned to block boundaries.");
//				return 1;
//			}

//		ofstream fio;
//		fio.open(fileName, ios::out | ios::binary);

		fio.seekp(0,ios::end);
			if (offset > (fio.tellp()+1)) {
				printf("Error: Offset > fileSize, causing to create holes in the file.");
				return 0;
			}

			fio.seekp(offset*BLOCK_SIZE,ios::beg);
			fio.write((char *)data, BLOCK_SIZE);
//			fio.close();
			return 0;

}

int FileHandler::writeBlock(byte *data) {
//	fstream fio;
//		fio.open(fileName, ios::out | ios::in | ios::binary);
			fio.seekp(0,ios::end);
			fio.write((char *)data, BLOCK_SIZE);
//			fio.close();
			return 0;
}

int FileHandler::getSize() {
//	fstream fio;
//		fio.open(fileName, ios::out | ios::in | ios::binary);
	fio.seekg(0,ios::end);
//	fio.close();
	return ((fio.tellg()+1)/BLOCK_SIZE);
}

FileHandler::~FileHandler() {
	fio.close();
}

