#include <string>

namespace ACDF = Aveva::Core::Database::Filters;
using namespace System;
using namespace System::Collections;
using namespace ACDF;

#pragma once
class DbModule
{
public:
	array<System::String^> ^attributes();
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