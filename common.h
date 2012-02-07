#include <stdlib.h>
#include <string.h>
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

class TreeNode {
public:
	int numkeys;
	byte keys[];
	byte myaddr[8];
	union {
		byte children[];
		byte payload[];
	};
	char flag;

//	TreeNode()
//	{
//		sprintf(myaddr,"%u",this);
//	}
};

//TreeNode :: TreeNode(TreeNode &node) {
//	numkeys = node.numkeys;
//	strcpy(keys, node.keys, numkeys * );
//	flag = node.flag;
//}