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
	FileHandler(char *fileName,char);
	~FileHandler() ;
	int readBlock(long long int offset, byte *data) ;
	int writeBlock(long long int offset, byte *data) ;
	int writeBlock(byte *data) ;
	int getSize();
};
