#pragma once

#include <iostream>

#define abs(A) ((A < 0) ? -1 * A : A)

using namespace std;

class SignedByteResidue
{
	unsigned char mod;
	char n;
public:
	SignedByteResidue(long long _n = 0, unsigned char _mod = 253);
	~SignedByteResidue();
	
	char changeMod(unsigned char _mod);
	char getByMod(unsigned char _mod);

	SignedByteResidue getReverse() const;
	SignedByteResidue operator+(const SignedByteResidue&) const;
	SignedByteResidue& operator+=(const SignedByteResidue&);
	SignedByteResidue operator-(const SignedByteResidue&) const;
	SignedByteResidue& operator-=(const SignedByteResidue&);
	SignedByteResidue operator*(const SignedByteResidue&) const;
	SignedByteResidue& operator*=(const SignedByteResidue&);
	SignedByteResidue operator/(const SignedByteResidue&) const;
	SignedByteResidue& operator/=(const SignedByteResidue&);
	SignedByteResidue& operator=(long long);
	bool isZero() const;
	char getValue() const;
	unsigned char getMod() const;
	void print() const;

private:
	char align(long long);
};

int gcd(int, int, SignedByteResidue&, SignedByteResidue&);
ostream& operator<<(ostream& in, const SignedByteResidue);

