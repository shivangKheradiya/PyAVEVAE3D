#include "PmlModule.h"

namespace acuc = Aveva::Core::Utilities::CommandLine;
using namespace acuc;
using namespace System;
using namespace Aveva::Core::PMLNet;

bool PmlModule::RunInPdms(System::String^ command) {
    try
    {
        acuc::Command^ cmd = acuc::Command::CreateCommand(command);
        return cmd->RunInPdms();
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::RunInPdms method");
    }
    return false;
}

bool PmlModule::Run(System::String^ command) {
    try
    {
        acuc::Command^ cmd = acuc::Command::CreateCommand(command);
        return cmd->Run();
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::Run method");
    }
    return false;
}

System::String^ PmlModule::GetPmlString(System::String^ variableName) {
    try
    {
        acuc::Command^ cmd = acuc::Command::CreateCommand("");
        return cmd->GetPMLVariableString(variableName->ToUpper());
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::GetPmlString method");
    }
    return System::String::Empty;
}

bool PmlModule::GetPmlBool(System::String^ variableName) {
    try
    {
        acuc::Command^ cmd = acuc::Command::CreateCommand("");
        return cmd->GetPMLVariableBoolean(variableName->ToUpper());
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::GetPmlBool method");
    }
}

Hashtable^ PmlModule::GetPmlArray(System::String^ variableName) {
    try
    {
        PMLNetAny^ PmlObject = PMLNetAny::createInstance("DATABRIDGE", gcnew array < System::Object^>{}, 0, true);
        System::Object^ pmlArrayObject = gcnew Hashtable();
        PmlObject->invokeMethod("getArray", gcnew array < System::Object^>{ variableName }, 1, pmlArrayObject , true, true);
        return safe_cast<Hashtable^>(pmlArrayObject);
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::GetPmlArray method");
    }
}

double PmlModule::GetPmlReal(System::String^ variableName) {
    try
    {
        acuc::Command^ cmd = acuc::Command::CreateCommand("");
        return cmd->GetPMLVariableReal(variableName->ToUpper());
    }
    catch (...)
    {
        Console::Write("Something went wrong in PmlModule::GetPmlReal method");
    }
}