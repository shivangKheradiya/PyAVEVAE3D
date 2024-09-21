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