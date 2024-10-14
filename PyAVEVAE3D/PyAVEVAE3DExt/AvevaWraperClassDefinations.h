#pragma once
#include "AllHeader.h"
#include "typecast.h"

namespace acuc = Aveva::Core::Utilities::CommandLine;
namespace ACDF = Aveva::Core::Database::Filters;

using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;
using namespace ACDF;
using namespace acuc;

#pragma once
class DbClass
{
public:
	array<System::String^>^ attributes();
	ACDF::DBElementCollection^ CollectAllForElement(System::String^ elmName);
	ACDF::DBElementCollection^ CollectAllTypeFor(System::String^ elmName, System::String^ elmType);
	ACDF::DBElementCollection^ CollectAllTypeWithUnsetAttFor(System::String^ elmName, System::String^ attributName);
	ACDF::DBElementCollection^ CollectAllTypeWithAttRefFor(System::String^ elmName, System::String^ attributName, System::String^ attributValue);
	ACDF::TypeFilter^ TypeFilter(System::String^ elementTypes);
	ACDF::DBElementCollection^ CollectAllTypeWithFilter(System::String^ elmName, ACDF::BaseFilter^ baseFilter);
	array<ACDF::DBElementCollection^>^ CollectAllTypesFor(System::String^ scopeElementNames, ACDF::TypeFilter^ typeFilter);
	void SetStringAttribute(System::String^ elmName, System::String^ attName, System::String^ attValue);
	void SetRealAttribute(System::String^ elmName, System::String^ attName, double attValue);
	void SetBoolAttribute(System::String^ elmName, System::String^ attName, bool attValue);
};

class PmlClass
{
public:
	bool RunInPdms(System::String^ command);
	bool Run(System::String^ command);
	bool GetPmlBool(System::String^ variableName);
	double GetPmlReal(System::String^ variableName);
	System::String^ GetPmlString(System::String^ variableName);
	Hashtable^ GetPmlArray(System::String^ variableName);
private:
};

class CommonClass
{
public:
	System::String^ mdb();
	void SaveWork();
	void GetWork();
	System::String^ getce();
	void setce(System::String^ elementName);
};

static public ref class typecast
{
public:
	static char* StringToCharP(System::String^ str);
	static String^ CharPToString(const char* str);
	static PyObject* PyUnicode_FromStr(char* charPtr);
	static PyObject* StringArrayToPyList(array<System::String^>^ stringArray);
	static array<System::String^>^ GetArrayFromCollection(ACDF::DBElementCollection^ collection);
	static System::Collections::Generic::List<System::String^>^ GetListFromDBElementCollection(ACDF::DBElementCollection^ cs_collection);
	static array<System::String^>^ GetArrayFromArrayCollection(array<ACDF::DBElementCollection^>^ colls);
private:
};