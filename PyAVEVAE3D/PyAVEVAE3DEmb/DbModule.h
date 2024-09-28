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
	ACDF::DBElementCollection^ CollectAllFor(System::String^ elmName);
	ACDF::DBElementCollection^ CollectAllTypeFor(System::String^ elmName, System::String^ elmType);
	ACDF::DBElementCollection^ CollectAllTypeWithUnsetAttFor(System::String^ elmName, System::String^ attributName);
	ACDF::DBElementCollection^ CollectAllTypeWithAttRefFor(System::String^ elmName, System::String^ attributName, System::String^ attributValue);
	ACDF::AndFilter^ AndFilter();
	static void AddBaseFilterInAndFilter(ACDF::AndFilter^ andFilter, ACDF::BaseFilter^ baseFilter);
	ACDF::OrFilter^ OrFilter();
	static void AddBaseFilterInOrFilter(ACDF::OrFilter^ andFilter, ACDF::BaseFilter^ baseFilter);
	void AddElmTypeInTypeFilter(ACDF::TypeFilter^ typeFilter, System::String^ elementTypeName);
	ACDF::TypeFilter^ TypeFilter();
	ACDF::DBElementCollection^ CollectAllTypeWithFilter(System::String^ elmName, ACDF::BaseFilter^ baseFilter);
};