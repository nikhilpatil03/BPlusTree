/*
 * TreeNode.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "TreeNode.h"


TreeNode::TreeNode() {
	// TODO Auto-generated constructor stub
	utils = new Utils();
}


int TreeNode::addData(KeyType keytype,char *key, int payloadlen,char *payload,int position){
//	if(numkeys ==0)
//	{
//		utils->copyBytes(&(data[(position)*keylen(&keytype)]),key, keylen(&keytype));
//		utils->copyBytes(&(data[DATA_SIZE-(position+1)*payloadlen-1]),payload,payloadlen);
//		return 0;
//	}
	for(int j = numkeys-1; j >= (position); j--) {
		utils->copyBytes(&(data[(j+1)*keylen(&keytype)]), &(data[j*keylen(&keytype)]),keylen(&keytype));
	}
	utils->copyBytes(&(data[(position)*keylen(&keytype)]),key, keylen(&keytype));

	for(int j = (DATA_SIZE-numkeys*payloadlen); j < (DATA_SIZE-position*payloadlen); j+=payloadlen) {
			utils->copyBytes(&(data[j-payloadlen]), &(data[j]),payloadlen);
	}
	utils->copyBytes(&(data[DATA_SIZE-(position+1)*payloadlen]),payload,payloadlen);
	return 0;
}

int TreeNode::getKey(KeyType keytype,char *key,int position){
	int keystart = 0;
	utils->copyBytes(key,&(data[keystart+(position*keylen(&keytype))]),keylen(&keytype));
	return 0;
}

int TreeNode::getPayload(int payloadlen,char *payload,int position){
	int payloadstart = DATA_SIZE;
	utils->copyBytes(payload,&(data[payloadstart-((position+1)*payloadlen)]),payloadlen);
	return 0;
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub
}

