#include "common.h"
#include "FileHandler.h"

int keylen(KeyType *keytype){
	int len=0;
	for (int i=0;i<keytype->numAttrs; i++) {
		len += keytype->attrLen[i];
	}
	return len;
}

class Index{
public:
	TreeNode *root;
	char rootAddress[16];
	KeyType keytype;
	int payloadlen;

	Index(char* indexName, KeyType *keytype, int payloadlen){
		FileHandler *fHandler = new FileHandler(indexName);
		this->keytype.numAttrs = keytype->numAttrs;
		for (int i=0; i < keytype->numAttrs;i++) {
			this->keytype.attrTypes[i] = keytype->attrTypes[i];
			this->keytype.attrLen[i] = keytype->attrLen[i];
		}
		this->payloadlen = payloadlen;
	}

	//returns -1 if first value is smaller
	int compare(char *received_key, char *received_nodeKey) {
		char *key = received_key, *nodeKey = received_nodeKey;
		for (int i=0; i < keytype.numAttrs; i++){
			switch(keytype.attrTypes[i]) {
			case intType:
				if ( (int)(*key) > (int)(*nodeKey) )
					return 1;
				else if ( (int)(*key) < (int)(*nodeKey) )
					return -1;
				break;

			case stringType:
				int result = strncmp (key, nodeKey, keytype.attrLen[i]);
				if (result != 0 )
						return result;
				break;
			}
			key = key + keytype.attrLen[i];
			nodeKey = nodeKey + keytype.attrLen[i];
		}
		return 0;
	}


	Index(char* indexName){
		root = (TreeNode *)strtoul(rootAddress,NULL,10);
	}
	int insert(char key[], char payload[]){

		if(root == 0)
		{
			addFirstElement(key,payload);
			return 0;
		}
		TreeNode * current = root;
		char *nodekey;
		TreeNode *accessPath[MAX_TREE_HEIGHT];
		int height = 0, i;
		while(current != 0)
		{
			accessPath[height++]=current;
			for (i = 0 ; i<current->numkeys ; i++ )
			{
				nodekey = &(current->keys[keylen(&keytype)*i]);
				int isLesser = compare(nodekey,key);
				if ( isLesser != -1)
				{
					break;
				}
			}

			if (current->flag == 'c')
				handleLeaf(key, payload, &current, i, accessPath,height);
			else
				handleNonLeaf(&current, i);
		}
		return 0;
	}
	int addFirstElement(byte *key,byte *payload)
	{
		root = new TreeNode();
		sprintf(rootAddress,"%u",(unsigned int)root);
		root->numkeys = 1;
		strncpy(root->keys, key, keylen(&keytype));
		root->flag = 'c';
		strncpy(root->payload, payload, payloadlen);
        return 0;
	}
	int handleNonLeaf(TreeNode **rcvd_node, int position) {
		TreeNode *node=*rcvd_node;
		*rcvd_node = (TreeNode *)strtoul(&(node->children[position*16]),NULL,10);
		return 0;
	}

	int handleLeaf(byte key[], byte payload[], TreeNode **rcvd_node, int position, TreeNode *accessPath[],int height) {
		TreeNode *node=*rcvd_node;
		for(int j = node->numkeys-1; j >= position; j--) {
			strncpy(&(node->keys[(j+1)*keylen(&keytype)]), &(node->keys[j*keylen(&keytype)]),keylen(&keytype));
		}
		strncpy(&(node->keys[position*keylen(&keytype)]),key, keylen(&keytype));
		node->numkeys = node->numkeys + 1;

		if(splitNecessary(node->numkeys,node->flag))
		{
			TreeNode *newLeaf = new TreeNode();
			int n_by_two = (node->numkeys)/2;
			for(int i = n_by_two; i< node->numkeys ; i++)
			{
				strncpy(&(newLeaf->keys[(i-n_by_two)*keylen(&keytype)]),&(node->keys[(i)*keylen(&keytype)]),keylen(&keytype));
				strncpy(&(newLeaf->payload[(i-n_by_two)*payloadlen]),&(node->payload[(i)*payloadlen]),payloadlen);
			}
			newLeaf->flag = 'c';
			newLeaf->numkeys = n_by_two;
			node->numkeys = n_by_two;
			TreeNode* parent = 0;
			for(int i = 0 ; i < height ; i++)
				if(accessPath[i]==node)
					parent = accessPath[i-1];
			char* nextKey =(char *) malloc(keylen(&keytype));

			strncpy(nextKey,newLeaf->keys,keylen(&keytype));
			insertIntoParent(node,nextKey,newLeaf,parent,height,accessPath);
		}
		*rcvd_node=0;
		return 0;
	}
	int insertIntoParent(TreeNode *left,byte key[],TreeNode *right,TreeNode *parent,int height,TreeNode *accessPath[]){
		if(root == left)
		{
			TreeNode *newRoot = new TreeNode();
			newRoot->numkeys = 1;
			strncpy(&(newRoot->keys[0]),key,keylen(&keytype));
			sprintf(&(newRoot->children[0]),"%u",(unsigned int)left);
			sprintf(&(newRoot->children[16]),"%u",(unsigned int)right);
			root = newRoot;
			return 0;
		}
		int i;
		char *nodekey;
		for (i = 0 ; i < parent->numkeys ; i++ )
		{
			nodekey = &(parent->keys[keylen(&keytype)*i]);
			int isLesser = compare(nodekey,key);
			if ( isLesser != -1)
			{
				break;
			}
		}
		for(int j = parent->numkeys-1; j >= i; j--) {
			strncpy(&(parent->keys[(j+1)*keylen(&keytype)]), &(parent->keys[j*keylen(&keytype)]),keylen(&keytype));
			strncpy(&(parent->children[(j+1)*16]), &(parent->children[j*16]),16);
		}
		strncpy(&(parent->keys[i*keylen(&keytype)]),key, keylen(&keytype));
		strncpy(&(parent->children[i*16]),key,16);
		parent->numkeys = parent->numkeys +1;
		if(splitNecessary(parent->numkeys,'n'))
		{
			TreeNode *newNonLeaf = new TreeNode();
			int n_by_two = (parent->numkeys)/2;
			for(int i = n_by_two+1; i< parent->numkeys ; i++)
			{
				strncpy( &(newNonLeaf->keys[(i-n_by_two)*keylen(&keytype)]),&(parent->keys[(i)*keylen(&keytype)]),keylen(&keytype));
				strncpy(&(newNonLeaf->payload[(i-n_by_two)*16]),&(parent->children[(i)*16]), payloadlen);
			}
			newNonLeaf->flag = 'n';
			newNonLeaf->numkeys = n_by_two-1;
			parent->numkeys = n_by_two;
			TreeNode* grandParent = 0;
			for(int i = 0 ; i < height ; i++)
				if(accessPath[i]==parent)
					grandParent = accessPath[i-1];
			char* nextKey =(char *) malloc(keylen(&keytype));
			strncpy(nextKey,&(parent->keys[n_by_two]),keylen(&keytype));
			insertIntoParent(parent,nextKey,newNonLeaf,grandParent,height,accessPath);
		}
		return 0;
	}
	int splitNecessary(int numkeys,char type){
		int allowedKeys;
		if(type == 'c')
			allowedKeys = (BLOCK_SIZE)/((keylen(&keytype)+payloadlen)+16);
		else
			allowedKeys = (BLOCK_SIZE)/((keylen(&keytype)+16)+16);
		if(numkeys > allowedKeys)
			return 1;
		return 0;
	}
	int lookup(char key[], char payload[]){
		return 0;
	}
};

int main(){
	KeyType keyType;
	keyType.numAttrs=1;
	keyType.attrTypes[0]=stringType;
	keyType.attrLen[0]=sizeof(int);

	class Index *index = new Index("test.txt",&keyType,8);
//	char * one;
//	char * two;
//	char * three;
//	char * four;
//	char * five;
//	char * six;
//	char * seven;
//	char * eight;
//	sprintf(one,"%d",1);
//	sprintf(two,"%d",2);
//	sprintf(three,"%d",3);
//	sprintf(four,"%d",4);
//	sprintf(five,"%d",5);
//	sprintf(six,"%d",6);
//	sprintf(seven,"%d",7);
//	sprintf(eight,"%d",8);

	index->insert("2","2");
	index->insert("3","3");
	index->insert("1","1");
	index->insert("5","5");
	index->insert("33","33");
	index->insert("23","23");
	index->insert("7","7");

}
