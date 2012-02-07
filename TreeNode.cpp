/*
 * TreeNode.cpp
 *
 *  Created on: 06-Feb-2012
 *      Author: nikhil
 */
#include<common.h>

class TreeNode {
public:
	int numkeys;
	byte keys[];
	byte myaddr[8];
	union {
		byte children[];
		byte payload[];
	};
	char flag;

//	TreeNode()
//	{
//		sprintf(myaddr,"%u",this);
//	}
};
