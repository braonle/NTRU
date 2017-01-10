#include "Decryption.h"

Decryption::Decryption(Parameters *_p) : p(_p), gen(p->get_N())
{
	PolType *g = nullptr;
	PolType *fq = nullptr;
	PolType *tmp = nullptr;

	g = new PolType(gen.generate(p->get_dg(), p->get_dg(), p->get_q()));

	for (; ;)
	{
		try
		{
			f = new PolType(gen.generate(p->get_df(), p->get_df() - 1, p->get_q()));
			
			fq = f->getReverse();

			tmp = new PolType(*f);
			tmp->changeMod(p->get_p());
			fp = tmp->getReverse();
		}
		catch (int i)
		{
			delete f;
			delete fq;
			delete fp;
			delete tmp;
			continue;
		}
		break;
	}
	
	h = new PolType(fq->multiple(*g));
	delete g;
	delete fq;
	delete tmp;
}

PolType * Decryption::getOpenKeyPol()
{
	return h;
}

PolType * Decryption::decryptPol(PolType * c)
{
	PolType *tmp = new PolType(*f);
	tmp->multiple(*c);
	
	tmp->changeMod(p->get_p());
	tmp->multiple(*fp);
	
	return tmp;
}

unsigned char * Decryption::decrypt(char *data, unsigned char *data_out)
{
	PolType *pols[8];
	char *data_in[8];
	
	//Формирование полинома
	for (int i = 0; i < 8; ++i)
	{
		vector<SignedByteResidue> *v = new vector<SignedByteResidue>(p->get_N(), SignedByteResidue(0, p->get_q()));
		for (int j = 0; j < p->get_N(); ++j)
			(*v)[j] = data[i * p->get_N() + j];
		pols[i] = new PolType(v);
		data_in[i] = nullptr;
	}

	try
	{
		//Расшифровка
		for (int i = 0; i < 8; ++i)
		{
			PolType *tmp;
			*(pols[i]) = *(tmp = decryptPol(pols[i]));
			delete tmp;
		}

		for (int i = 0; i < 8; ++i)
			data_in[i] = pols[i]->getChar();

		ByteStreamOut st_out(data_in, p->get_N(), 8);
		for (int i = 0; i < p->get_N(); ++i)
			data_out[i] = st_out.getNextByte();
		
		for (int i = 0; i < 8; ++i)
		{
			delete pols[i];
			delete[] data_in[i];
		}
		return data_out;
	}
	catch (int)
	{
		for (int i = 0; i < 8; ++i)
		{
			delete pols[i];
			delete[] data_in[i];
		}
		return nullptr;
	}
}

Decryption::~Decryption()
{
	delete p;
	delete h;
	delete f;
	delete fp;
}

char * Decryption::getOpenKey()
{
	return h->getChar();
}
