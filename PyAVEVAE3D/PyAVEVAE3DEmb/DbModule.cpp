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