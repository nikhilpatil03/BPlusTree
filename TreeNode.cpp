/*
 * TreeNode.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "TreeNode.h"

namespace std {

TreeNode::TreeNode() {
	// TODO Auto-generated constructor stub
	utils = new Utils();
}


int TreeNode::addData(KeyType keytype,char *key, int payloadlen,char *payload){

}

int TreeNode::getKey(KeyType keytype,char *key,int position){
	int keystart = NODE_HEADER_LENGTH;
	strncpy(key,&(data[keystart+(position*keylen(&keytype))]),keylen(&keytype));
	return 0;
}

int TreeNode::getPayload(int payloadlen,char *payload,int position){
	int payloadstart = BLOCK_SIZE;
	strncpy(payload,&(data[payloadstart-((position+1)*payloadlen)]),payloadlen);
	return 0;
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
