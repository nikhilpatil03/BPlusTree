#include <stdio.h>

class FileRW {

	private FILE * filePointer;

	FileRW(char *fileName, char *mode) {
		// A constructor to create and/or open file named "fileName" for reading or writing depending on mode.
		filePointer = fopen(filename, mode);
		if (!filePointer) {
			cout << "Failed to open file " << fileName; //status to be return????
		}
	}

	int readBlock(int offset, byte *data) {
		if (offset % BLOCKSIZE != 0) {
			cout << "Offset is not aligned to block boundaries."
			return FAILURE;
		}

		return (fread(data, 1, BLOCKSIZE, filepointer) == BLOCKSIZE);
	}

	int writeBlock(int offset, byte *data) {
		if (offset % BLOCKSIZE != 0) {
			cout << "Offset is not aligned to block boundaries."
			return FAILURE;
		}

		return (fwrite(data, 1, BLOCKSIZE, filepointer) == BLOCKSIZE);
	}

	int close() {
		return filePointer.fclose();		//check return value of fclose
	}
}

//freed can read directly into structure
