#include "typecast.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Aveva::Core::Database;
using namespace System::Collections;

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

array<System::String^>^ typecast::GetArrayFromCollection(ACDF::DBElementCollection^ cs_collection) {
	return typecast::GetListFromDBElementCollection(cs_collection)->ToArray();
}

System::Collections::Generic::List<System::String^>^ typecast::GetListFromDBElementCollection(ACDF::DBElementCollection^ cs_collection) {

	System::Collections::Generic::List<System::String^>^ collection = gcnew System::Collections::Generic::List<System::String^>();

	for each (DbElement ^ elm in cs_collection)
	{
		collection->Add(elm->GetAsString(DbAttributeInstance::FLNN));
	}

	return collection;
}

array<System::String^>^ typecast::GetArrayFromArrayCollection(array<ACDF::DBElementCollection^>^ colls) {
	System::Collections::Generic::List<System::String^>^ collection = gcnew System::Collections::Generic::List<System::String^>();
	
	for each (ACDF::DBElementCollection ^ elmColl in colls)
	{
		collection->AddRange(typecast::GetListFromDBElementCollection(elmColl));
	}
	
	return collection->ToArray();
}