#include "NTRULib.h"
#include "Encryption.h"
#include "Decryption.h"
#include <iostream>
#include <ctime>

int sessionDecInit(int n)
{
	switch (n)
	{
	case 503:
		return (int)new Decryption(new Parameters503());
	case 251:
		return (int)new Decryption(new Parameters251());
	case 167:
		return (int)new Decryption(new Parameters167());
	default:
		return 0;
	}
}

static int getNumOfParts(int data_size, int obj)
{
	int size = ((Encryption*)obj)->size();
        int tmp = data_size / size;
        if (size * tmp < data_size - )
		++tmp;
	return tmp;
}

int getEncSize(int data_size, int obj)
{
	return ((Encryption*)obj)->size() *  getNumOfParts(data_size, obj) * 8;
}

void encrypt(char* in, int in_size, char* out, int obj)
{
	srand(time(NULL));
	int size = ((Encryption*)obj)->size();

	//Для последнего куска, чтобы посолить его и пихнуть количество значащих символов в последнем блоке
	char* tmp = new char[size];
	int i = 0;

	//Добавить xor
	for (; i < in_size - size; i += size)
	{
		if (!((Encryption*)obj)->encrypt((unsigned char*)&(in[i]), &(out[i * 8])))
			throw -50;
	}
	
	int j, temp = in_size % size;
	memcpy(tmp, &(in[i]), temp);
	for (j = temp; j < size - 2; ++j)
		tmp[j] = (char)rand();
	
	//В конец добавляется записанное в обратном порядке двухбайтовое число, означающее количество значащих байтов в последнем блоке
	(unsigned char)tmp[j++] = temp % 256;
	temp /= 256;
	(unsigned char)tmp[j] = temp;
 	((Encryption*)obj)->encrypt(tmp, out[i * 8]);
	delete[] tmp;
}

char * getPublicKey(int obj)
{
	return ((Decryption*)obj)->getOpenKey();
}

int decrypt(char* in, int in_size, char* out, int obj)
{
	int size = ((Encryption*)obj)->size();
	int max_out_size = in_size / 8;

	//Добавить xor
	for (int i = 0; i < max_out_size; i += size)
		((Decryption*)obj)->decrypt(&(in[i * 8]), (unsigned char*)&(out[i]));
	int tmp = in[in_size - 1] * 256 + in[in_size - 2];
	return max_out_size - size + tmp;
}

void sessionEncClose(int obj)
{
	delete (Encryption*)obj;
}

void sessionDecClose(int obj)
{
	delete (Decryption*)obj;
}

int  sessionEncInit(int n, char *h)
{
	switch (n)
	{
	case 503:
		return (int)new Encryption(new Parameters503(), h);
	case 251:
		return (int)new Encryption(new Parameters251(), h);
	case 167:
		return (int)new Encryption(new Parameters167(), h);
	default:
		return 0;
	}
}

void ptrdel(char *ptr)
{
    delete[] ptr;
}
