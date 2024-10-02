#include "AvevaWraperClassDefinations.h"

using namespace Aveva::Core::Database;
using namespace System;

array<System::String^>^ DbClass::attributes() {
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

ACDF::DBElementCollection^ DbClass::CollectAllForElement(System::String^ elmName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName));
}

ACDF::DBElementCollection^ DbClass::CollectAllTypeFor(System::String^ elmName, System::String^ elmType) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::TypeFilter(DbElementType::GetElementType(elmType)));
}

ACDF::DBElementCollection^ DbClass::CollectAllTypeWithUnsetAttFor(System::String^ elmName, System::String^ attributName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::AttributeUnsetFilter(DbAttribute::GetDbAttribute(attributName)));
}

ACDF::DBElementCollection^ DbClass::CollectAllTypeWithAttRefFor(System::String^ elmName, System::String^ attributName, System::String^ attRefElmName) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), gcnew ACDF::AttributeRefFilter(DbAttribute::GetDbAttribute(attributName), DbElement::GetElement(attRefElmName)));
}

ACDF::DBElementCollection^ DbClass::CollectAllTypeWithFilter(System::String^ elmName, ACDF::BaseFilter^ baseFilter) {
    return gcnew ACDF::DBElementCollection(DbElement::GetElement(elmName), baseFilter);
}

ACDF::TypeFilter^ DbClass::TypeFilter(System::String^ elementTypes) {
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

array<ACDF::DBElementCollection^>^ DbClass::CollectAllTypesFor(System::String^ scopeElementNames, ACDF::TypeFilter^ typeFilter) {
    array<System::String^>^ elmsName = scopeElementNames->Split(' ');
    array<ACDF::DBElementCollection^>^ colls = gcnew array<ACDF::DBElementCollection^>(elmsName->Length);
    
    int i = 0;
    for each (System::String ^ elmName in elmsName)
    {
        colls[i] = DbClass::CollectAllTypeWithFilter(elmName, typeFilter);
        i++;
    }

    return colls;
}

void DbClass::SetStringAttribute(System::String^ elmName, System::String^ attName, System::String^ attValue) {
    DbElement^ elm = DbElement::GetElement(elmName);
    DbAttribute^ att = DbAttribute::GetDbAttribute(attName);
    elm->SetAttribute(att, attValue);
}

void DbClass::SetBoolAttribute(System::String^ elmName, System::String^ attName, bool attValue) {
    DbElement^ elm = DbElement::GetElement(elmName);
    DbAttribute^ att = DbAttribute::GetDbAttribute(attName);
    elm->SetAttribute(att, attValue);
}

void DbClass::SetRealAttribute(System::String^ elmName, System::String^ attName, double attValue) {
    DbElement^ elm = DbElement::GetElement(elmName);
    DbAttribute^ att = DbAttribute::GetDbAttribute(attName);
    try
    {
        elm->SetAttribute(att, attValue);
    }
    catch (System::Exception^ ex)
    {
        Console::WriteLine("Attribute : " + attName + " can't assign double value :" + attValue);
        elm->SetAttribute(att, (int)attValue);
        Console::WriteLine("Attribute : " + attName + " assigned int value :" + attValue);
    }
    catch (...)
    {
        Console::WriteLine("Attribute : "+ attName + " can't assign value :" + attValue);
    }
}