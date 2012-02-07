#include <stdlib.h>
#define MaxAttrs 16
#define MAX_TREE_HEIGHT 16

typedef char byte;

enum attrType {
	intType,
	stringType
};

struct KeyType {
	int numAttrs;
	attrType attrTypes[MaxAttrs];
	int attrLen[MaxAttrs];
};

