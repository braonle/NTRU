#pragma once

class Parameters
{
public:
	Parameters();
	virtual ~Parameters();

	virtual int get_df() = 0;
	virtual int get_dg() = 0;
	virtual int get_dr() = 0;
	virtual int get_p() = 0;
	virtual int get_q() = 0;
	virtual int get_N() = 0;
};

class Parameters503 : public Parameters
{
public:
	Parameters503();
	virtual int get_df();
	virtual int get_dg();
	virtual int get_dr();
	virtual int get_p();
	virtual int get_q();
	virtual int get_N();
	virtual ~Parameters503();
};

class Parameters167 : public Parameters
{
public:
	Parameters167();
	virtual int get_df();
	virtual int get_dg();
	virtual int get_dr();
	virtual int get_p();
	virtual int get_q();
	virtual int get_N();
	virtual ~Parameters167();
};

class Parameters251 : public Parameters
{
public:
	Parameters251();
	virtual int get_df();
	virtual int get_dg();
	virtual int get_dr();
	virtual int get_p();
	virtual int get_q();
	virtual int get_N();
	virtual ~Parameters251();
};

class TestPar : public Parameters
{
public:
	TestPar();
	virtual int get_df();
	virtual int get_dg();
	virtual int get_dr();
	virtual int get_p();
	virtual int get_q();
	virtual int get_N();
	virtual ~TestPar();
};