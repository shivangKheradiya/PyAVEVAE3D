#include "CommonModule.h"

using namespace Aveva::Core::Database;
using namespace System;

System::String^ CommonModule::mdb() {
    return MDB::CurrentMDB->Name;
}

void CommonModule::SaveWork() {
    MDB::CurrentMDB->SaveWork("Savework By Python");
}

void CommonModule::GetWork() {
    MDB::CurrentMDB->GetWork();
}

System::String^ CommonModule::getce() {
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

void CommonModule::setce(System::String^ elementName) {
    try
    {
        CurrentElement::Element = DbElement::GetElement((elementName)->ToString());
    }
    catch (...)
    {
        Console::WriteLine("Unable to goto Element Name : " + elementName);
    }
}