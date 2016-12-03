#include "NTRULib.h"
#include "Encryption.h"
#include "Decryption.h"
#include <iostream>

void * sessionDecInit(int n)
{
	switch (n)
	{
	case 503:
		return new Decryption(new Parameters503());
	case 251:
		return new Decryption(new Parameters251());
	case 167:
		return new Decryption(new Parameters167());
	default:
		return nullptr;
	}
}

char * encrypt(unsigned char *data, void* obj)
{
	return ((Encryption*)obj)->encrypt(data);
}

char * getPublicKey(void* obj)
{
	return ((Decryption*)obj)->getOpenKey();
}

unsigned char * decrypt(char *data, void *obj)
{
	return ((Decryption*)obj)->decrypt(data);
}

void sessionEncClose(void *obj)
{
	delete (Encryption*)obj;
}

void sessionDecClose(void *obj)
{
	delete (Decryption*)obj;
}

void * sessionEncInit(int n, char *h)
{
	switch (n)
	{
	case 503:
		return new Encryption(new Parameters503(), h);
	case 251:
		return new Encryption(new Parameters251(), h);
	case 167:
		return new Encryption(new Parameters167(), h);
	default:
		return nullptr;
	}
}

void ptrdel(void* ptr)
{
    delete[] (char*) ptr;
}