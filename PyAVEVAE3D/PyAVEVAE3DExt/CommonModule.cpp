#include "AvevaWraperClassDefinations.h"

using namespace Aveva::Core::Database;
using namespace System;

System::String^ CommonClass::mdb() {
    return MDB::CurrentMDB->Name;
}

void CommonClass::SaveWork() {
    MDB::CurrentMDB->SaveWork("Savework By Python");
}

void CommonClass::GetWork() {
    MDB::CurrentMDB->GetWork();
}

System::String^ CommonClass::getce() {
    try
    {
        return CurrentElement::Element->EvaluateString(DbExpression::Parse("flnn"));
    }
    catch (...)
    {
        Console::WriteLine("Unable to find current element.");
    }
    return String::Empty;
}

void CommonClass::setce(System::String^ elementName) {
    try
    {
        CurrentElement::Element = DbElement::GetElement((elementName)->ToString());
    }
    catch (...)
    {
        Console::WriteLine("Unable to goto Element Name : " + elementName);
    }
}