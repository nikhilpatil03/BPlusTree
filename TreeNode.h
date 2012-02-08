/*
 * TreeNode.h
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#ifndef TREENODE_H_
#define TREENODE_H_
#include "common.h"
#include "Utils.h"
class TreeNode {
public:
	int numkeys;
	byte data[BLOCK_SIZE - NODE_HEADER_LENGTH];
//	byte keys[1000];
	byte myaddr[NODE_OFFSET_SIZE];
	Utils *utils;
//	union {
//		unsigned char children[64];
//		byte payload[64];
//	};
	char flag;
	TreeNode();
	~TreeNode();
	int addData(KeyType keytype,char key[], int payloadlen,char payload[],int position);
	int getKey(KeyType keytype,char key[], int position);
	int readData(int position,KeyType keytype,char key[], int payloadlen,char payload[]);
	int getPayload(int payloadlen,char *payload,int position);

};
#endif /* TREENODE_H_ */
