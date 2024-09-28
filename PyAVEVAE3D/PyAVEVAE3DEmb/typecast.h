#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

namespace ACDF = Aveva::Core::Database::Filters;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;
using namespace ACDF;

#pragma once
static public ref class typecast
{
public:
	static char* StringToCharP(System::String^ str);
	static String^ CharPToString(const char* str);
	static PyObject* PyUnicode_FromStr(char* charPtr);
	static PyObject* StringArrayToPyList(array<System::String^>^ stringArray);
	static array<System::String^>^ GetArrayFromCollection(ACDF::DBElementCollection^ collection);
private:
};

