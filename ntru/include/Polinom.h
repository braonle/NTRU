#pragma once

#include "Numbers.h"
#include <vector>

using namespace std;

class Polinom
{
public:
	Polinom();
	~Polinom();
};

class SignedByteResiduePolinom : public Polinom
{
	vector<SignedByteResidue> *coefs = nullptr;
	unsigned char mod = 253;
	//const int size = 503;
	int size;
public:
	SignedByteResiduePolinom(int size);
	SignedByteResiduePolinom(vector<SignedByteResidue> &);
	SignedByteResiduePolinom(vector<SignedByteResidue> *);
	SignedByteResiduePolinom(unsigned char, int size);
	SignedByteResiduePolinom(const SignedByteResiduePolinom&);
	~SignedByteResiduePolinom();

	void changeMod(unsigned char);
	SignedByteResiduePolinom& add(const SignedByteResiduePolinom&);
	SignedByteResiduePolinom& subtract(const SignedByteResiduePolinom&);
	SignedByteResiduePolinom& multiple(const SignedByteResiduePolinom&);
	SignedByteResiduePolinom& multiple(const SignedByteResidue&);
	SignedByteResiduePolinom& devide(const SignedByteResidue&);

	SignedByteResidue& operator[](unsigned int);
	SignedByteResiduePolinom& operator=(SignedByteResiduePolinom&);

	void clean();

	int getMainIndex() const;
	SignedByteResidue& getFreeCoef();
	unsigned char getMod() const;
	char* getChar() const;
	int getSize() const;
	SignedByteResiduePolinom* getResidue(SignedByteResiduePolinom&, SignedByteResiduePolinom ** = nullptr);
	SignedByteResiduePolinom* getResidueModByThis(SignedByteResiduePolinom ** = nullptr);
	SignedByteResiduePolinom* getReverse();
	bool isZero() const;
	bool isConst() const;

	friend ostream& operator<<(ostream& in, const SignedByteResiduePolinom&);

private:
	unsigned int getRevIndex(unsigned int) const;
};

SignedByteResiduePolinom* gcd(SignedByteResiduePolinom *, SignedByteResiduePolinom *,\
	SignedByteResiduePolinom **, SignedByteResiduePolinom **);

using PolType = SignedByteResiduePolinom;