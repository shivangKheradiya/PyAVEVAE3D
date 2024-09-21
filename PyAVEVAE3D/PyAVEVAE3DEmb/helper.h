#include "AllHeader.h"

using namespace System;
using namespace System::Runtime::InteropServices;

#pragma once
static public ref class typecast
{
public:
	static char* StringToCharP(System::String^ str);
	static String^ CharPToString(const char* str);
	static PyObject* PyUnicode_FromStr(char* charPtr);
private:
};

