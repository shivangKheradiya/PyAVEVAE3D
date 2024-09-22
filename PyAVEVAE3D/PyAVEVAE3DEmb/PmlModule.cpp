#include "PmlModule.h"

namespace acuc = Aveva::Core::Utilities::CommandLine;
using namespace acuc;

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

System::Double^ PmlModule::GetPmlReal(System::String^ variableName) {
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