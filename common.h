#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MaxAttrs 16
#define MAX_TREE_HEIGHT 16
#define BLOCK_SIZE 100
#define NODE_OFFSET_SIZE 8
#define NODE_HEADER_LENGTH 7
 
typedef char byte;

enum attrType  {
	intType,
	stringType
};

struct KeyType {
	int numAttrs;
	attrType attrTypes[MaxAttrs];
	int attrLen[MaxAttrs];
};


