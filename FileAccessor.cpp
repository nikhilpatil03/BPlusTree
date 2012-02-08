#include <iostream>
#include <fstream>

#define BLOCK_SIZE 50

typedef char byte;

using namespace std;

class FileAccessor {
private:
	 fstream fio;

public:
	 FileAccessor(char *indexName) {
		 fio.open(indexName, ios:: in | ios::out | ios::binary);		//pass mode as iso:: in | ios::out | ios::binary
			if(!fio) {
				printf("File opening failed.");
			}
	 }

	 ~FileAccessor() {
		 fio.close();
	 }

	int readBlock(int offset, byte *data) {
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

	int writeBlock(int offset, byte *data) {
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
};
