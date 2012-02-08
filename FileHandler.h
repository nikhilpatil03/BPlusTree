#include <iostream>
#include <fstream>

typedef char byte;
using namespace std;

class FileHandler {
private:
	char fileName[50];
	fstream fio;

public:
	FileHandler(char *fileName);
	~FileHandler() ;
	int readBlock(int offset, byte *data) ;
	int writeBlock(int offset, byte *data) ;
	int writeBlock(byte *data) ;
	int getSize();
};
