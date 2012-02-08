/*
 * Utils.h
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "common.h"

class Utils {
public:
	Utils();
	virtual ~Utils();
	unsigned int getUnsignedIntForBytes(unsigned char bytes[4]);
	int getIntForBytes(char bytes[4]);
	unsigned char* getBytesForUnsignedInt(unsigned int input);
	KeyType getKeyTypeForBytes(char* );
	char * getBytesForKeyType(KeyType k);
	char * getBytesForInt(int input);
	int copyBytes(char *,unsigned char *,int);
	int copyBytes(unsigned char *,unsigned char *,int);
	int copyBytes(unsigned char *, char *,int);
	int copyBytes(char *, char *,int);
};

#endif /* UTILS_H_ */
