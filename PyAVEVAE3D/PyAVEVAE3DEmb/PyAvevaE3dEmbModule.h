#include "AllHeader.h"

#pragma once
static public ref class PyAvevaE3dEmbModule
{
public:
	static PyObject* mdb(PyObject* /* unused module reference */);
	static PyObject* get_ce(PyObject* /* unused module reference */);
	static PyObject* set_ce(PyObject* /* unused module reference */, PyObject* o);
private:
};

