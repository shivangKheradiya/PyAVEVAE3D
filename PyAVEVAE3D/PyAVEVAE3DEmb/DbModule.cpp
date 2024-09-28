#include "DbModule.h"
using namespace Aveva::Core::Database;
using namespace System;

array<System::String^>^ DbModule::attributes() {
    array<DbAttribute^>^ atts = CurrentElement::Element->GetAttributes();
    array<System::String^>^ attributeNames = gcnew array<System::String^>(atts->Length);
    int i = 0;
    for each (DbAttribute ^ att in atts)
    {
        attributeNames[i] = att->Name;
        i++;
    }
    return attributeNames;
}

ACDF::DBElementCollection^ DbModule::CollectAllFor(System::String^ elmName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName));
}

ACDF::DBElementCollection^ DbModule::CollectAllTypeFor(System::String^ elmName, System::String^ elmType) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::TypeFilter(DbElementType::GetElementType(elmType)));
}

ACDF::DBElementCollection^ DbModule::CollectAllTypeWithUnsetAttFor(System::String^ elmName, System::String^ attributName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::AttributeUnsetFilter(DbAttribute::GetDbAttribute(attributName)));
}

ACDF::DBElementCollection^ DbModule::CollectAllTypeWithAttRefFor(System::String^ elmName, System::String^ attributName, System::String^ attRefElmName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::AttributeRefFilter(DbAttribute::GetDbAttribute(attributName), DbElement::GetElement(attRefElmName)));
}

ACDF::DBElementCollection^ DbModule::CollectAllTypeWithFilter(System::String^ elmName, ACDF::BaseFilter^ baseFilter) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), baseFilter);
}

ACDF::AndFilter^ DbModule::AndFilter() {
    return gcnew ACDF::AndFilter();
}

ACDF::OrFilter^ DbModule::OrFilter() {
    return gcnew ACDF::OrFilter();
}

ACDF::TypeFilter^ DbModule::TypeFilter() {
    return gcnew ACDF::TypeFilter();
}

void DbModule::AddBaseFilterInOrFilter(ACDF::OrFilter^ orFilter, ACDF::BaseFilter^ baseFilter) {
    orFilter->Add(baseFilter);
}

void DbModule::AddBaseFilterInAndFilter(ACDF::AndFilter^ andFilter, ACDF::BaseFilter^ baseFilter) {
    andFilter->Add(baseFilter);
}

void DbModule::AddElmTypeInTypeFilter(ACDF::TypeFilter^ typeFilter, System::String^ elementTypeName ) {
    Aveva::Core::Database::DbElementType^ elementType = DbElementType::GetElementType(elementTypeName);
    typeFilter->Add(elementType);
}