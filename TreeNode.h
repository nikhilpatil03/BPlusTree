/*
 * TreeNode.h
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#ifndef TREENODE_H_
#define TREENODE_H_
#include "common.h"

class TreeNode {
public:
	int numkeys;
	byte data[BLOCK_SIZE - 7];
	byte keys[1000];
	byte myaddr[8];
	Utils *utils;
	union {
		unsigned char children[64];
		byte payload[64];
	};
	char flag;
	int addData(KeyType keytype,char key[], int payloadlen,char payload[]);
	int getKey(KeyType keytype,char key[], int position);
	int readData(int position,KeyType keytype,char key[], int payloadlen,char payload[]);
	int getPayload(int payloadlen,char *payload,int position);

};
#endif /* TREENODE_H_ */
