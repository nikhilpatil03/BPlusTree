#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MaxAttrs 16
#define MAX_TREE_HEIGHT 16
#define BLOCK_SIZE 100
#define NODE_OFFSET_SIZE 8
#define NODE_HEADER_LENGTH (NODE_OFFSET_SIZE+1+4)
#define DATA_SIZE BLOCK_SIZE-NODE_HEADER_LENGTH
 
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

int keylen(KeyType *keytype);

#endif
