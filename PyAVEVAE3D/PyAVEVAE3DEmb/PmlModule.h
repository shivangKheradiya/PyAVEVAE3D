#include "AllHeader.h"

namespace acuc = Aveva::Core::Utilities::CommandLine;
using namespace acuc;

#pragma once
class PmlModule
{
public:
	bool RunInPdms(System::String^ command);
	bool Run(System::String^ command);
	bool GetPmlBool(System::String^ variableName);
	System::Double^ GetPmlReal(System::String^ variableName);
	System::String^ GetPmlString(System::String^ variableName);
private:
};

