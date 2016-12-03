#include <iostream>
#include "generator.h"
#include "NTRULib.h"
#include "Numbers.h"


using namespace std;

int main()
{
	int type = 251;
	int size = type * 8;

	unsigned char *data, *res;
	char *en_text, *tmp = nullptr;
	generator<SignedByteResidue> gen(size);

	data = gen.genData(size / 8);
	void* dec = sessionDecInit(type);
	void* en = sessionEncInit(type, tmp = getPublicKey(dec));

	en_text = encrypt(data, en);

	res = decrypt(en_text, dec);

	sessionEncClose(en);
	sessionDecClose(dec);

	for (int i = 0; i < type; ++i)
		if (data[i] != res[i])
		{
			cout << "Error " << i << endl;
			break;
		}

	cout << "ok" << endl;
	delete[] data;
	delete[] en_text;
	delete[] res;
	delete[] tmp;

	return 0;
}
