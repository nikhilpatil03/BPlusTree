#include "common.h"

int displayBPLus(TreeNode *root, KeyType *keytype) {
	TreeNode *queue[1000];
	int queue_count = 2, queue_processed = 0;
	TreeNode *temp, temp2;
	queue[0] = root;
	queue[1] = &temp2;

	while(queue_processed < queue_count) {
		temp = queue[queue_processed++];
		if (temp == &temp2) {
			printf("********next level done**********");
			continue;
		}
		//add pointers to queue
		for (int i=0;i<root->numkeys; i++) {
			queue[queue_count++]=(TreeNode *)root->children[8*i];
			printf(" %d ",root->keys[keylen(keytype)*i]);
		}
		queue[queue_count++]= &temp2;
		printf("---------Next node done---------");
	}
	return 0;
}
