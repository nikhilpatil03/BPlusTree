/*
 * TreeNode.cpp
 *
 *  Created on: 06-Feb-2012
 *      Author: nikhil
 */
#include<common.h>

class TreeNode {
	int numkeys;
	byte keys[];
	byte myaddr[8];
	union {
		byte *children[8];
		byte payload[8][];
	};
	char flag;

	TreeNode()
	{
		sprintf(myaddr,"%u",this);
	}
}
