#include <stdlib.h>
#include <string.h>
#define MaxAttrs 16
#define MAX_TREE_HEIGHT 16
#define BLOCK_SIZE 16
 
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

class TreeNode {
public:
	int numkeys;
	byte keys[1000];
	byte myaddr[8];
	union {
		byte children[64];
		byte payload[64];
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
