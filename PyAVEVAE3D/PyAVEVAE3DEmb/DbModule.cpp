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

ACDF::DBElementCollection^ DbModule::CollectAllForElement(System::String^ elmName) {
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

ACDF::TypeFilter^ DbModule::TypeFilter(System::String^ elementTypes) {
    array<System::String^>^ elmTypes = elementTypes->Split(' ');
    array<DbElementType^>^ dbElmTypes = gcnew array<DbElementType^>(elmTypes->Length);

    int i = 0;
    for each (System::String^ elementType in elmTypes)
    {
        dbElmTypes[i] = DbElementType::GetElementType(elementType);
        i++;
    }
    return gcnew ACDF::TypeFilter(dbElmTypes);
}

array<ACDF::DBElementCollection^>^ DbModule::CollectAllTypesFor(System::String^ scopeElementNames, ACDF::TypeFilter^ typeFilter) {
    array<System::String^>^ elmsName = scopeElementNames->Split(' ');
    array<ACDF::DBElementCollection^>^ colls = gcnew array<ACDF::DBElementCollection^>(elmsName->Length);
    
    int i = 0;
    for each (System::String ^ elmName in elmsName)
    {
        colls[i] = DbModule::CollectAllTypeWithFilter(elmName, typeFilter);
        i++;
    }

    return colls;
}