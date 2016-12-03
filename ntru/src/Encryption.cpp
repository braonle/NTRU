#include "Encryption.h"
#include <iostream>

Encryption::Encryption(Parameters *_p, PolType* _h) : p(_p), h(_h), gen(p->get_N())
{
}

PolType * Encryption::encryptPol(PolType * data)
{
	PolType *r = new PolType(gen.generate(p->get_dr(), p->get_dr() - 1, p->get_q()));
	r->multiple(SignedByteResidue(p->get_p(), p->get_q()));
	r->multiple(*h);
	r->add(*data);

	return r;
}

char * Encryption::encrypt(unsigned char *data)
{
	PolType *pols[8];
	BitStreamIn st(data, p->get_N());
	char *data_out = nullptr;

	//������������ ���������
	for (int i = 0; i < 8; ++i)
	{
		vector<SignedByteResidue> *v = new vector<SignedByteResidue>(p->get_N(), SignedByteResidue(0, p->get_p()));
		for (int j = 0; j < p->get_N(); ++j)
			(*v)[j] = st.getNextBit();
		pols[i] = new PolType(v);
		//data_in[i] = nullptr;
	}

	try
	{
		//����������
		for (int i = 0; i < 8; ++i)
		{
			PolType *tmp;
			*(pols[i]) = *(tmp = encryptPol(pols[i]));
			delete tmp;
		}

		//������������ �����������
		data_out = new char[p->get_N() * 8];
		for (int i = 0; i < p->get_N() * 8; ++i)
			data_out[i] = (*(pols[i / p->get_N()]))[i % p->get_N()].getValue();
		
		for (int i = 0; i < 8; ++i)
			delete pols[i];

		return data_out;
	}
	catch (int)
	{
		for (int i = 0; i < 8; ++i)
			delete pols[i];
		delete data_out;
		return nullptr;
	}
}

Encryption::~Encryption()
{
	delete p;
	delete h;
}

Encryption::Encryption(Parameters *p, char *data) : gen(p->get_N())
{
	this->p = p;
	vector<SignedByteResidue> *v = new vector<SignedByteResidue>(p->get_N(), SignedByteResidue(0, p->get_q()));
	for (int i = 0; i < p->get_N(); ++i)
		(*v)[i] = data[i];
	h = new PolType(v);
}
