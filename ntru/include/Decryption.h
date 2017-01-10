#pragma once

#include "Polinom.h"
#include "Parameters.h"
#include "generator.h"
#include "BitStream.h"

class Decryption
{
	Parameters* p;
	generator<SignedByteResidue> gen;
	PolType* f;
	PolType* fp;
	PolType* h;
public:
	Decryption(Parameters*);
	PolType* getOpenKeyPol();
	PolType* decryptPol(PolType*);
	unsigned char* decrypt(char*, unsigned char*);
	~Decryption();
	char* getOpenKey();
};

