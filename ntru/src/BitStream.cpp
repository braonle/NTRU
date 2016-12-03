#include "BitStream.h"

BitStreamIn::BitStreamIn(unsigned char *data, int num)
{
	this->data = data;
	num_of_bytes = num;
}

BitStreamIn::~BitStreamIn()
{
}

char BitStreamIn::getNextBit()
{
	if (bit_count >= num_of_bytes * 8)
		throw 5;
	int tmp = bit_count;
	return BiteField(data[tmp / 8])[bit_count++];
}

BiteField::BiteField(unsigned char c)
{
	b.c = c;
	Byte tmp;
	tmp.c = (unsigned char)1;
	if (tmp.bite_field.b0)
	{
		f = &BiteField::getBiteBE;
		g = &BiteField::setBiteBE;
	}
	else
	{
		f = &BiteField::getBiteLE;
		g = &BiteField::setBiteLE;
	}
}

BiteField::~BiteField() {}

char BiteField::operator[](unsigned char i)
{
	return (this->*f)(i);
}

void BiteField::setBite(unsigned char i, unsigned char c)
{
	(this->*g)(i, c);
}

unsigned char BiteField::getByte()
{
	return b.c;
}

char BiteField::getBiteBE(unsigned char i)
{
	i %= 8;
	i = 7 - i;
	return getField(i);
}

char BiteField::getBiteLE(unsigned char i)
{
	i %= 8;
	return getField(i);
}

char BiteField::getField(unsigned char i)
{
	switch (i)
	{
	case 0:
		return b.bite_field.b0;
	case 1:
		return b.bite_field.b1;
	case 2:
		return b.bite_field.b2;
	case 3:
		return b.bite_field.b3;
	case 4:
		return b.bite_field.b4;
	case 5:
		return b.bite_field.b5;
	case 6:
		return b.bite_field.b6;
	case 7:
		return b.bite_field.b7;
	default:
		return 0;
	}
}

void BiteField::setBiteLE(unsigned char i, unsigned char c)
{
	i %= 8;
	setField(i, c);
}

void BiteField::setBiteBE(unsigned char i, unsigned char c)
{
	i %= 8;
	i = 7 - i;
	setField(i, c);
}

void BiteField::setField(unsigned char i, unsigned char c)
{
	switch (i)
	{
	case 0:
		b.bite_field.b0 = c;
		break;
	case 1:
		b.bite_field.b1 = c;
		break;
	case 2:
		b.bite_field.b2 = c;
		break;
	case 3:
		b.bite_field.b3 = c;
		break;
	case 4:
		b.bite_field.b4 = c;
		break;
	case 5:
		b.bite_field.b5 = c;
		break;
	case 6:
		b.bite_field.b6 = c;
		break;
	case 7:
		b.bite_field.b7 = c;
	}
}

ByteStreamOut::ByteStreamOut(char **data, int num_bytes, int num_blocks)
{
	this->data = data;
	num_of_bytes_in_block = num_bytes;
	num_of_blocks = num_blocks;
}

ByteStreamOut::~ByteStreamOut()
{
}

unsigned char ByteStreamOut::getNextByte()
{
	if (bit_count >= num_of_bytes_in_block * num_of_blocks)
		throw 5;
	
	BiteField b(0);

	for (int i = 0; i < 8; ++i)
	{
		int tmp = bit_count++;
		b.setBite(i, data[tmp / num_of_bytes_in_block][tmp % num_of_bytes_in_block]);
	}
	return b.getByte();
}