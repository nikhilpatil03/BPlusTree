#include "common.h"
#include "FileHandler.h"
#include "Utils.h"

int keylen(KeyType *keytype){
	int len=0;
	for (int i=0;i<keytype->numAttrs; i++) {
		len += keytype->attrLen[i];
	}
	return len;
}

class Index{
public:
	FileHandler *fHandler;
	TreeNode *root;
	unsigned char *rootAddress;
	KeyType keytype;
	int payloadlen;
	class Utils *utils;
	char *header;
	int node_address_size;

	Index(char* indexName, KeyType *keytype, int payloadlen){
		utils = new Utils();
		node_address_size = sizeof(unsigned int);
		fHandler = new FileHandler(indexName);
		this->keytype.numAttrs = keytype->numAttrs;
		for (int i=0; i < keytype->numAttrs;i++) {
			this->keytype.attrTypes[i] = keytype->attrTypes[i];
			this->keytype.attrLen[i] = keytype->attrLen[i];
		}
		this->payloadlen = payloadlen;
		header = (char *)malloc(BLOCK_SIZE);
		strncpy(&header[node_address_size],utils->getBytesForInt(payloadlen),sizeof(int));
		strncpy(&header[node_address_size+sizeof(payloadlen)],utils->getBytesForKeyType(this->keytype),sizeof(keytype));
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
		fHandler = new FileHandler(indexName);
		header = (char *)malloc(BLOCK_SIZE);
		fHandler->readBlock(0,header);
		utils = new Utils();
		utils->copyBytes(rootAddress,header,node_address_size);
		root = (TreeNode *)utils->getUnsignedIntForBytes(rootAddress);
		payloadlen= utils->getIntForBytes(&header[node_address_size]);
		keytype = utils->getKeyTypeForBytes(&header[node_address_size+sizeof(payloadlen)]);
	}

	int loadNode(TreeNode **here,char *offset){

		fHandler->readBlock(utils->getIntForBytes(offset),)
	}

	int insert(char key[], char payload[]){
		if(root == 0)
		{
			addFirstElement(key,payload);
			return 0;
		}
		TreeNode * current = root;
		char *nodekey;
		char accessPath[MAX_TREE_HEIGHT][NODE_OFFSET_SIZE];
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
	int storeNode(TreeNode *node, int offset){
		char *block = (char *)malloc(BLOCK_SIZE);
		int position = 0;
		strncpy(&block[position],utils->getBytesForInt(offset),sizeof(offset));
		position += sizeof(offset);
		block[position]=node->flag;
		position += 1;
		strncpy(&block[position],utils->getBytesForInt(node->numkeys),sizeof(node->numkeys));
		position += sizeof(node->numkeys);




	}

	int addFirstElement(byte *key,byte *payload)
	{
		root = new TreeNode();
		rootAddress = utils->getBytesForUnsignedInt((unsigned int)root);
		utils->copyBytes(header,rootAddress,node_address_size);
		fHandler->writeBlock(0,header);
		root->numkeys = 1;
		strncpy(root->keys, key, keylen(&keytype));
		root->flag = 'c';
		strncpy(root->payload, payload, payloadlen);
		storeNode(root,2);
        return 0;
	}
	int handleNonLeaf(TreeNode **rcvd_node, int position) {
		TreeNode *node=*rcvd_node;
		unsigned char *nextNodeAddress;
		nextNodeAddress = (unsigned char *)malloc(node_address_size);
		utils->copyBytes(nextNodeAddress,&(node->children[position*node_address_size]),node_address_size);
		*rcvd_node = (TreeNode *)utils->getUnsignedIntForBytes(nextNodeAddress);
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
			utils->copyBytes(&(newRoot->children[0]),utils->getBytesForUnsignedInt((unsigned int)left),node_address_size);
			utils->copyBytes(&(newRoot->children[node_address_size]),utils->getBytesForUnsignedInt((unsigned int)right),node_address_size);
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
			utils->copyBytes(&(parent->children[(j+1)*node_address_size]), &(parent->children[j*node_address_size]),node_address_size);
		}
		strncpy(&(parent->keys[i*keylen(&keytype)]),key, keylen(&keytype));
		utils->copyBytes(&(parent->children[i*node_address_size]),utils->getBytesForUnsignedInt((unsigned int)right),node_address_size);
		parent->numkeys = parent->numkeys +1;
		if(splitNecessary(parent->numkeys,'n'))
		{
			TreeNode *newNonLeaf = new TreeNode();
			int n_by_two = (parent->numkeys)/2;
			for(int i = n_by_two+1; i< parent->numkeys ; i++)
			{
				strncpy( &(newNonLeaf->keys[(i-n_by_two)*keylen(&keytype)]),&(parent->keys[(i)*keylen(&keytype)]),keylen(&keytype));
				utils->copyBytes(&(newNonLeaf->children[(i-n_by_two)*node_address_size]),&(parent->children[(i)*node_address_size]),node_address_size);
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
		if(root == 0) {
			printf("BPlus Tree empty.");
			return 1;
		}
		TreeNode * current = root;
		char *nodekey;
		int i, isLesser;
		while(current != 0) {
			for (i = 0 ; i<current->numkeys ; i++ ) {
				nodekey = &(current->keys[keylen(&keytype)*i]);
				isLesser = compare(nodekey,key);
				if ( isLesser != -1) {
					break;
				}
			}

			if (current->flag == 'c') {
				if (isLesser != 0)	//key not found
					return 1;

				//key found, copy payload
				strncpy(payload, &(current->payload[payloadlen *i]),payloadlen);
				return 0;
			}
			else
				handleNonLeaf(&current, i);
		}
		return 1;
	}
};

int main(){
	KeyType keyType;
	keyType.numAttrs=1;
	keyType.attrTypes[0]=stringType;
	keyType.attrLen[0]=sizeof(int);

	class Index *index = new Index("test.txt",&keyType,8);

	index->insert("2","2");
	index->insert("3","3");
	index->insert("1","1");
	index->insert("5","5");
	index->insert("33","33");
	index->insert("23","23");
	index->insert("7","7");

}
