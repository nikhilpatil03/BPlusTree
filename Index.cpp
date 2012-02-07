#include<common.h>


class Index{
	TreeNode *root;
	KeyType keytype;
	int payloadlen;
	Index(char* indexName, KeyType *keytype, int payloadlen){
		this->keytype = new(*keytype);
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
		TreeNode accessPath[MAX_TREE_HEIGHT];
		int height = 0, i;
		while(current != 0)
		{

			accessPath[height++]=current;
			for (i = 0 ; i<current->numkeys ; i++ )
			{
				nodekey = current->keys[keylen(ktype)*i];
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
		root->keys[0] = key;
		root->flag = 'c';
		root->payload[0] = payload;
        root->keys[keylen*1] = 0;
        return 0;
	}
	int handleNonLeaf(TreeNode *node, int position) {
		node = (TreeNode *)strtoul(node->children[position*8],NULL,10);
		return 0;
	}

	int handleLeaf(char key[], char payload[], TreeNode *node, int position, TreeNode *accessPath) {
		return 0;
	}

	int lookup(char key[], char payload[]){
		return 0;
	}
};

int keylen(KeyType *keytype){
	return sizeof(keytype->attrLen)+sizeof(keytype->attrTypes)+sizeof(keytype->numAttrs);
}

int compare(char *key, char *nodeKey) {
	return 0;
}
