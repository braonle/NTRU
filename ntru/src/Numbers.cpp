#include "Numbers.h"



SignedByteResidue::SignedByteResidue(long long n, unsigned char _mod)
{
	mod = _mod;
	this->n = align(n);
}


SignedByteResidue::~SignedByteResidue() { }

char SignedByteResidue::changeMod(unsigned char _mod)
{
	mod = _mod;
	n = align(n);
	return n;
}

char SignedByteResidue::getByMod(unsigned char _mod)
{
	unsigned char tmp = mod;
	mod = _mod;
	char temp = align(n);
	mod = tmp;
	return temp;
}

SignedByteResidue SignedByteResidue::getReverse() const
{
	SignedByteResidue x(0, mod), y(0, mod);
	int c = gcd(n, mod, x, y);
	if (abs(c) != 1)
	{
		//cout << "Does not exist";
		throw 1;
	}
	return (c < 0) ? x * SignedByteResidue(-1, mod) : x;
}

SignedByteResidue SignedByteResidue::operator+(const SignedByteResidue &arg) const
{
	return SignedByteResidue((int)n + arg.n, mod);
}

SignedByteResidue & SignedByteResidue::operator+=(const SignedByteResidue &arg)
{
	n = align((int)n + arg.n);
	return *this;
}

SignedByteResidue SignedByteResidue::operator-(const SignedByteResidue &arg) const
{
	return SignedByteResidue((int)n - arg.n, mod);
}

SignedByteResidue & SignedByteResidue::operator-=(const SignedByteResidue &arg)
{
	n = align((int)n - arg.n);
	return *this;
}

SignedByteResidue SignedByteResidue::operator*(const SignedByteResidue &arg) const
{
	return SignedByteResidue((int)n * arg.n, mod);
}

SignedByteResidue & SignedByteResidue::operator*=(const SignedByteResidue &arg)
{
	n = align((int)n * arg.n);
	return *this;
}

SignedByteResidue SignedByteResidue::operator/(const SignedByteResidue &arg) const
{
	return SignedByteResidue(*this) * arg.getReverse();
}

SignedByteResidue & SignedByteResidue::operator/=(const SignedByteResidue &arg)
{
	SignedByteResidue tmp(0, mod);
	SignedByteResidue temp(*this);
	tmp = arg.getReverse();
	temp *= tmp.getValue();
	n = temp.getValue();
	return *this;
}

SignedByteResidue & SignedByteResidue::operator=(long long arg)
{
	n = align(arg);
	return *this;
}

bool SignedByteResidue::isZero() const
{
	return !n;
}

char SignedByteResidue::getValue() const
{
	return n;
}

unsigned char SignedByteResidue::getMod() const
{
	return mod;
}

char SignedByteResidue::align(long long n)
{
	n %= mod;
	n = (n < 0) ? n + mod : n;
	n = (n <= mod / 2) ? n : n - mod;
	return n;
}

ostream & operator<<(ostream & in, const SignedByteResidue num)
{
	in << (int)num.getValue() << " mod " << (unsigned int)num.getMod();
	return in;
}

int gcd(int a, int b, SignedByteResidue &x, SignedByteResidue &y)
{
	if (!a)
	{
		x = 0;
		y = 1;
		return b;
	}
	SignedByteResidue x1(0, x.getMod()), y1(0, x.getMod());
	char d = gcd(b % a, a, x1, y1);
	x = y1 - SignedByteResidue(b / a, x.getMod()) * x1;
	y = x1;
	return d;
}
