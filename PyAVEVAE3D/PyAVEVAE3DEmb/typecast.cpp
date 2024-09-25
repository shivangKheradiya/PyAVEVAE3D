#include "typecast.h"

using namespace System;
using namespace System::Runtime::InteropServices;

char* typecast::StringToCharP(System::String^ str) {
	return (char*)(void*)Marshal::StringToHGlobalAnsi(str);
}
String^ typecast::CharPToString(const char* str) {
	return (gcnew String(str));
}

PyObject* typecast::PyUnicode_FromStr(char* charPtr) {
	return PyUnicode_FromString(charPtr);
}

PyObject* typecast::StringArrayToPyList(array<System::String^>^ stringArray) {
	PyObject* pyList = PyList_New(stringArray->Length);
	
	int i = 0;
	for each (String^ value in stringArray)
	{
		PyObject* attName = PyUnicode_FromString(typecast::StringToCharP(value));
		PyList_SetItem(pyList, i, attName);
		i++;
	}
	return pyList;
}