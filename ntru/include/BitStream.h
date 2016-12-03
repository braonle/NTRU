#pragma once

struct Bits
{
	unsigned b0 : 1;
	unsigned b1 : 1;
	unsigned b2 : 1;
	unsigned b3 : 1;
	unsigned b4 : 1;
	unsigned b5 : 1;
	unsigned b6 : 1;
	unsigned b7 : 1;
};

union Byte
{
	Bits bite_field;
	unsigned char c;
};

class BiteField
{
	Byte b;
	//char (*f)(unsigned char);

	char (BiteField::*f)(unsigned char);
	void (BiteField::*g)(unsigned char, unsigned char);
public:
	BiteField(unsigned char);
	~BiteField();

	char operator[](unsigned char);
	void setBite(unsigned char, unsigned char);
	unsigned char getByte();

private:
	char getBiteBE(unsigned char);
	char getBiteLE(unsigned char);
	char getField(unsigned char);
	void setBiteLE(unsigned char, unsigned char);
	void setBiteBE(unsigned char, unsigned char);
	void setField(unsigned char, unsigned char);
};

class BitStreamIn
{
	unsigned char *data;
	int num_of_bytes;
	int bit_count = 0;
public:
	BitStreamIn(unsigned char *, int);
	~BitStreamIn();

	char getNextBit();
};

class ByteStreamOut
{
	char **data;
	int num_of_bytes_in_block;
	int num_of_blocks;
	int bit_count = 0;
public:
	ByteStreamOut(char**, int, int);
	~ByteStreamOut();

	unsigned char getNextByte();
};