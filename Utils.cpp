/*
 * Utils.cpp
 *
 *  Created on: 08-Feb-2012
 *      Author: sandeep
 */

#include "Utils.h"
#include "common.h"

Utils::Utils() {
	// TODO Auto-generated constructor stub

}
unsigned char* Utils::getBytesForUnsignedInt(unsigned int input)
{
	union{
		unsigned char bytes[sizeof(input)];
		unsigned int in;
	} u;
	u.in = input;
	return u.bytes;
}

char* Utils::getBytesForInt(int input)
{
	union{
		char bytes[sizeof(input)];
		int in;
	} u;
	u.in = input;
	return u.bytes;
}

char* Utils::getBytesForKeyType(KeyType input)
{
	char *bytes;
	bytes = (char *)malloc(sizeof(input));
	strncpy(bytes,getBytesForInt(input.numAttrs),sizeof(int));
	int offset = sizeof(int);
	for (int i = 0 ; i < input.numAttrs ; i++)
	{
		strncpy(&bytes[offset],getBytesForInt(input.attrLen[i]),sizeof(int));
		offset = offset + sizeof(int);
		strncpy(&bytes[offset],getBytesForInt(input.attrTypes[i]),sizeof(int));
		offset = offset + sizeof(int);
	}
	return bytes;
}
KeyType  Utils::getKeyTypeForBytes(char * input)
{
	KeyType key;
	key.numAttrs = getIntForBytes(input);
	int offset = sizeof(int);
	for(int i = 0 ; i < key.numAttrs ; i++)
	{
		key.attrLen[i] = getIntForBytes(&input[offset]);
		offset = offset + sizeof(int);
		key.attrTypes[i] = (attrType)getIntForBytes(&input[offset]);
		offset = offset + sizeof(int);
	}
	return key;
}

unsigned int Utils::getUnsignedIntForBytes(unsigned char bytes[4]){
	union{
			unsigned char bytes[sizeof(unsigned int)];
			unsigned int in;
		} u;
		for ( int i = 0 ; i < sizeof(unsigned int) ; i ++)
			u.bytes[i]=bytes[i];
		return u.in;
}

int Utils::getIntForBytes(char bytes[4]){
	union{
			char bytes[sizeof(int)];
			int in;
		} u;
		for ( int i = 0 ; i < sizeof(int) ; i ++)
			u.bytes[i]=bytes[i];
		return u.in;
}



int Utils::copyBytes(char *destination , unsigned char * source , int number){
	for (int i = 0 ; i<number ; i++)
		destination[i] = source [i];
	return 0;
}

int Utils::copyBytes(char *destination , char * source , int number){
	for (int i = 0 ; i<number ; i++)
		destination[i] = source [i];
	return 0;
}



int Utils::copyBytes(unsigned char *destination , char * source , int number){
	for (int i = 0 ; i<number ; i++)
		destination[i] = source [i];
	return 0;
}


int Utils::copyBytes(unsigned char *destination , unsigned char * source , int number){
	for (int i = 0 ; i<number ; i++)
		destination[i] = source [i];
	return 0;
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

