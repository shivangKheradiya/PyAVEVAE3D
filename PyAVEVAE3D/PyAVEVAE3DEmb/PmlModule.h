#include "AllHeader.h"

namespace acuc = Aveva::Core::Utilities::CommandLine;
using namespace acuc;
using namespace System::Collections;

#pragma once
class PmlModule
{
public:
	bool RunInPdms(System::String^ command);
	bool Run(System::String^ command);
	bool GetPmlBool(System::String^ variableName);
	double GetPmlReal(System::String^ variableName);
	System::String^ GetPmlString(System::String^ variableName);
	Hashtable^ GetPmlArray(System::String^ variableName);
private:
};

