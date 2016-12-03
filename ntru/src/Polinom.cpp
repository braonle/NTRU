#include "Polinom.h"

Polinom::Polinom()
{
}

Polinom::~Polinom()
{
}

SignedByteResiduePolinom::SignedByteResiduePolinom(int size)
{
	coefs = new vector<SignedByteResidue>(size, SignedByteResidue(0, 253));
	this->size = size;
}

SignedByteResiduePolinom::SignedByteResiduePolinom(vector<SignedByteResidue>& v)
{
	size = v.size();
	*coefs = v;
	mod = v[0].getMod();
}

SignedByteResiduePolinom::SignedByteResiduePolinom(vector<SignedByteResidue>* v)
{
	size = v->size();
	coefs = v;
	mod = (*v)[0].getMod();
}

SignedByteResiduePolinom::SignedByteResiduePolinom(unsigned char _mod, int size)
{
	this->size = size;
	mod = _mod;
	coefs = new vector<SignedByteResidue>(size, SignedByteResidue(0, _mod));
}

SignedByteResiduePolinom::SignedByteResiduePolinom(const SignedByteResiduePolinom &arg)
{
	coefs = new vector<SignedByteResidue>(*arg.coefs);
	mod = arg.mod;
	size = arg.size;
}

SignedByteResiduePolinom::~SignedByteResiduePolinom()
{
	delete coefs;
}

void SignedByteResiduePolinom::changeMod(unsigned char arg)
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i].changeMod(arg);
	mod = arg;
}

SignedByteResiduePolinom & SignedByteResiduePolinom::add(const SignedByteResiduePolinom &arg)
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i] += (*(arg.coefs))[i];
	return *this;
}

SignedByteResiduePolinom & SignedByteResiduePolinom::subtract(const SignedByteResiduePolinom &arg)
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i] -= (*(arg.coefs))[i];
	return *this;
}

SignedByteResiduePolinom & SignedByteResiduePolinom::multiple(const SignedByteResiduePolinom &arg)
{
	SignedByteResidue temp(0, mod);
	vector<SignedByteResidue> *tmp = new vector<SignedByteResidue>(size, SignedByteResidue(0, mod));
	for (int k = 0; k < size; ++k)
	{
		for (int i = 0; i <= k; ++i)
			(*tmp)[getRevIndex(k)] += (*coefs)[getRevIndex(i)] * (*(arg.coefs))[getRevIndex(k - i)];

		for (int i = k + 1; i < size; ++i)
			(*tmp)[getRevIndex(k)] += (*coefs)[getRevIndex(i)] * (*(arg.coefs))[getRevIndex(size - i + k)];
	}
	delete coefs;
	coefs = tmp;
	return *this;
}

SignedByteResiduePolinom & SignedByteResiduePolinom::multiple(const SignedByteResidue &arg)
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i] *= arg;
	return *this;
}

SignedByteResiduePolinom & SignedByteResiduePolinom::devide(const SignedByteResidue &arg)
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i] /= arg;
	return *this;
}

SignedByteResidue & SignedByteResiduePolinom::operator[](unsigned int n)
{
	if (n >= size)
		throw -1;
	return (*coefs)[n];
}

SignedByteResiduePolinom & SignedByteResiduePolinom::operator=(SignedByteResiduePolinom &arg)
{
	delete coefs;
	size = arg.size;
	mod = arg.mod;
	coefs = arg.coefs;
	arg.coefs = nullptr;
	return *this;
}

void SignedByteResiduePolinom::clean()
{
	for (int i = 0; i < size; ++i)
		(*coefs)[i] = 0;
}

int SignedByteResiduePolinom::getMainIndex() const
{
	for (int i = 0; i < size; ++i)
		if (!(*coefs)[i].isZero())
			return i;
	return -1;
}

SignedByteResidue & SignedByteResiduePolinom::getFreeCoef()
{
	return (*coefs)[size - 1];
}

unsigned char SignedByteResiduePolinom::getMod() const
{
	return mod;
}

char * SignedByteResiduePolinom::getChar() const
{
	char* res = new char[size];
	for (int i = 0; i < size; ++i)
		res[i] = (*coefs)[i].getValue();
	return res;
}

int SignedByteResiduePolinom::getSize() const
{
	return size;
}

SignedByteResiduePolinom* SignedByteResiduePolinom::getResidue(SignedByteResiduePolinom &arg, SignedByteResiduePolinom **dev)
{
	if (getMainIndex() > arg.getMainIndex())
		return this;
	vector<SignedByteResidue> *_tmp = new vector<SignedByteResidue>(size, SignedByteResidue(0, mod));
	SignedByteResiduePolinom* res = new SignedByteResiduePolinom(_tmp);
	SignedByteResiduePolinom tmp0(new vector<SignedByteResidue>(*_tmp));
	SignedByteResiduePolinom* tmp = new SignedByteResiduePolinom(*this);
	
	for (int temp, main_in_1, main_in_2; (temp = ((main_in_2 = arg.getMainIndex()) - (main_in_1 = tmp->getMainIndex()))) >= 0 && main_in_1 != -1; )
	{
		if (main_in_2 == -1)
		{
			delete res;
			delete tmp;
			throw 1;
		}

		try
		{
			tmp0[getRevIndex(temp)] = (*tmp)[main_in_1] / arg[main_in_2];
		}
		catch (int e)
		{
			delete res;
			delete tmp;
			throw e;
		}
		(*res)[getRevIndex(temp)] = tmp0[getRevIndex(temp)];

		tmp0.multiple(arg);
		tmp->subtract(tmp0);
		
		tmp0.clean();
	}
	if (dev)
		*dev = res;
	else
		delete res;

	return tmp;
}

SignedByteResiduePolinom* SignedByteResiduePolinom::getResidueModByThis(SignedByteResiduePolinom **dev)
{
	//SignedByteResiduePolinom &arg = *this;
	int temp, main_in_1, main_in_2;
	main_in_2 = getMainIndex();
	
	if (isZero())
	{
		*dev = nullptr;
		return new SignedByteResiduePolinom(this->getMod());
	}

	vector<SignedByteResidue> *_tmp = new vector<SignedByteResidue>(size, SignedByteResidue(0, mod));
	SignedByteResiduePolinom* res = new SignedByteResiduePolinom(_tmp);
	SignedByteResiduePolinom tmp0(new vector<SignedByteResidue>(*_tmp));
	SignedByteResiduePolinom* tmp = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));
	//Чтобы не вычитать единицу после умножения (полученную переходом из старшего разряда)


	temp = getRevIndex(main_in_2) - 1;
	if (main_in_2 == -1 || temp == -1)
	{
		delete res;
		delete tmp;
		throw 1;
	}

	try
	{
		tmp0[temp] = SignedByteResidue(1, getMod()) / (*this)[main_in_2];
	}
	catch (int e)
	{
		delete res;
		delete tmp;
		throw e;
	}
	//tmp0[temp] = SignedByteResidue(1, getMod()) / (*this)[main_in_2];
	(*res)[temp] = tmp0[temp];

	tmp0.multiple(*this);
	tmp->subtract(tmp0);

	tmp0.clean();



	for (; (temp = (main_in_2 - (main_in_1 = tmp->getMainIndex()))) >= 0 && main_in_1 != -1; )
	{
		if (main_in_2 == -1)
		{
			delete res;
			delete tmp;
			throw 1;
		}

		try
		{
			tmp0[getRevIndex(temp)] = (*tmp)[main_in_1] / (*this)[main_in_2];
		}
		catch (int e)
		{
			delete res;
			delete tmp;
			throw e;
		}
		
		(*res)[getRevIndex(temp)] = tmp0[getRevIndex(temp)];

		tmp0.multiple(*this);
		tmp->subtract(tmp0);

		tmp0.clean();
	}
	if (dev)
		*dev = res;
	else
		delete res;

	return tmp;
}

SignedByteResiduePolinom * SignedByteResiduePolinom::getReverse()
{
	SignedByteResiduePolinom *x, *c = nullptr, *x1, *y1, *temp, *tmp, *t = nullptr;
	vector<SignedByteResidue> *_tmp = new vector<SignedByteResidue>(size, SignedByteResidue(0, mod));
	x = new SignedByteResiduePolinom(_tmp);
	x1 = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));
	y1 = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));
	//temp = new SignedByteResiduePolinom(mod);
	//tmp = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));
	//c = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));

	try
	{
		//_CrtMemState s1, s2, s3;
		//_CrtMemCheckpoint(&s1);
		
		c = gcd(t = getResidueModByThis(&tmp), this, &x1, &y1);
		delete t;

		/*_CrtMemCheckpoint(&s2);
		if (_CrtMemDifference(&s3, &s1, &s2))
			_CrtMemDumpStatistics(&s3);*/
		
	}
	catch (int e)
	{
		delete x;
		delete x1;
		delete y1;
		delete tmp;
		delete c;
		delete t;
		throw e;
	}
	
	if (!c->isConst())
	{
		//cout << "Does not exist";
		delete x;
		delete x1;
		delete y1;
		delete tmp;
		delete c;
		throw 2;
	}

 	temp = new SignedByteResiduePolinom(*x1);
	temp->multiple(*tmp);
	y1->subtract(*temp);

	*x = *y1;

	x->devide(c->getFreeCoef());
	delete x1;
	delete y1;
	delete tmp;
	delete temp;
	delete c;

	return x;
}

bool SignedByteResiduePolinom::isZero() const
{
	for (int i = 0; i < size; ++i)
		if (!(*coefs)[i].isZero())
			return false;
	return true;
}

bool SignedByteResiduePolinom::isConst() const
{
	if (getMainIndex() < size - 1)
		return false;
	return true;
}

unsigned int SignedByteResiduePolinom::getRevIndex(unsigned int i) const
{
	return size - 1 - i;
	//return i;
}

SignedByteResiduePolinom* gcd(SignedByteResiduePolinom *a, SignedByteResiduePolinom *b, \
	SignedByteResiduePolinom **x, SignedByteResiduePolinom **y)
{
	if (a->isZero())
	{
		(*x)->getFreeCoef() = 0;
		(*y)->getFreeCoef() = 1;
		return new SignedByteResiduePolinom(*b);
	}

	SignedByteResiduePolinom *x1, *y1;
	vector<SignedByteResidue> *_tmp = new vector<SignedByteResidue>(a->getSize(), SignedByteResidue(0, a->getMod()));
	x1 = new SignedByteResiduePolinom(_tmp);
	y1 = new SignedByteResiduePolinom(new vector<SignedByteResidue>(*_tmp));
	SignedByteResiduePolinom *tmp = nullptr, *temp = nullptr;
	SignedByteResiduePolinom* d = nullptr;
	
	try
	{

		temp = b->getResidue(*a, &tmp);

		d = gcd(temp, a, &x1, &y1);
	}
	catch (int e)
	{
		delete temp;
		delete d;
		delete x1;
		delete y1;
		delete tmp;
		throw e;
	}
	delete temp;
	
	temp = new SignedByteResiduePolinom(*x1);
	temp->multiple(*tmp);
	y1->subtract(*temp);
	
	**x = *y1;
	**y = *x1;
	
	delete temp;
	delete tmp;
	delete x1;
	delete y1;

	return d;
}

ostream & operator<<(ostream & in, const SignedByteResiduePolinom &arg)
{
	for (int i = 0; i < arg.size; ++i)
		cout << (int)(*arg.coefs)[i].getValue() << " ";
	cout << "mod " << (unsigned int)arg.mod;
	return in;
}
