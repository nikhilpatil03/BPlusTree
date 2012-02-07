#include "common.h"

int keylen(KeyType *keytype){
	int len=0;
	for (int i=0;i<keytype->numAttrs; i++) {
		len += keytype->attrLen[i];
	}
	return len;
}

int compare(char *key, char *nodeKey) {
	return 0;
}


class Index{
	TreeNode *root;
	KeyType keytype;
	int payloadlen;
	Index(char* indexName, KeyType *keytype, int payloadlen){
		this->keytype.numAttrs = keytype->numAttrs;
		for (int i=0; i < keytype->numAttrs;i++) {
			this->keytype.attrTypes[i] = keytype->attrTypes[i];
			this->keytype.attrLen[i] = keytype->attrLen[i];
		}
		this->payloadlen = payloadlen;
	}
	Index(char* indexName){

	}
	int insert(char key[], char payload[]){

		if(root == 0)
		{
			addFirstElement(key,payload);
			return 0;
		}
		TreeNode * current = root;
		char *nodekey;
		KeyType *ktype = & keytype;
		TreeNode *accessPath[MAX_TREE_HEIGHT];
		int height = 0, i;
		while(current != 0)
		{

			accessPath[height++]=current;
			for (i = 0 ; i<current->numkeys ; i++ )
			{
				nodekey = &(current->keys[keylen(ktype)*i]);
				int isLesser = compare(key,nodekey);
				if ( isLesser != 1)
				{
					break;
				}
				if(i == current->numkeys-1)
					i++;
			}

			if (current->flag == 'c')
				handleLeaf(key, payload, current, i, accessPath);
			else
				handleNonLeaf(current, i);
		}
		return 0;
	}
	int addFirstElement(byte *key,byte *payload)
	{
		root = new TreeNode();
		root->numkeys = 1;
		strncpy(root->keys, key, keylen(&keytype));

		root->flag = 'c';
		strncpy(root->payload, payload, payloadlen);
//        root->keys[keylen*1] = 0;
        return 0;
	}
	int handleNonLeaf(TreeNode *node, int position) {
		node = (TreeNode *)strtoul(&(node->children[position*8]),NULL,10);
		return 0;
	}

	int handleLeaf(char key[], char payload[], TreeNode *node, int position, TreeNode *accessPath[]) {
		return 0;
	}

	int lookup(char key[], char payload[]){
		return 0;
	}
};

int main(){
	KeyType keyType;
	keyType.numAttrs=1;
	keyType.attrTypes[0]=intType;
	keyType.attrLen[0]=sizeof(intType);

	Index *index = new Index("test.txt",&keyType,8);
}
