#pragma once

#include "Polinom.h"
#include "generator.h"
#include "Parameters.h"
#include "BitStream.h"

class Encryption
{
	PolType* h;
	Parameters* p;
	generator<SignedByteResidue> gen;
public:
	Encryption(Parameters*, PolType*);

	PolType* encryptPol(PolType*);
	char* encrypt(unsigned char*);
	~Encryption();

	Encryption(Parameters*, char*);
};

