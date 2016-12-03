#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename Num>
class generator
{
	int n;
public:

	generator(int n)
	{
		srand(time(nullptr));
		this->n = n;
	}

	vector<Num>* generate(int num_of_1, int num_of_neg_1, unsigned char mod)
	{
		vector<Num>* tmp = new vector<Num>(n, Num(0, mod));
		int temp;
		for (int i = 0; i < num_of_1;)
		{
			if ((*tmp)[temp = random(n)].isZero())
			{
				(*tmp)[temp] = 1;
				++i;
			}
		}

		for (int i = 0; i < num_of_neg_1;)
		{
			if ((*tmp)[temp = random(n)].isZero())
			{
				(*tmp)[temp] = -1;
				++i;
			}
		}
		return tmp;
	}

	vector<Num>* genTest(unsigned char mod, int start = 0)
	{
		vector<Num> *tmp = new vector<Num>(n, Num(0, mod));
		for (int i = start; i < n; ++i)
			(*tmp)[i] = random(mod);
		return tmp;
	}

	unsigned char* genData(int m)
	{
		unsigned char *res = new unsigned char[m];
		for (int i = 0; i < m; ++i)
			res[i] = random(256);
		return res;
	}

	~generator()
	{
	}

private:
	int random(unsigned int mod)
	{
		return rand() % mod;
	}
};

