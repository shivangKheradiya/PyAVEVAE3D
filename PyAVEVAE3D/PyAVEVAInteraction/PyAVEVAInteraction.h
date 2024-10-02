#include <Windows.h>
#include <exception>
#include <cstdio>
#include <cstring>
#include <vcclr.h>
#include "typecast.h"

#pragma once
using namespace System;
using namespace Aveva::Core::PMLNet;
using namespace System::Runtime::InteropServices;
using namespace std;

namespace PyAVEVAInteraction {

	[PMLNetCallable()]
	public ref class PyAVEVAInteractionObj
	{
	public:
		[PMLNetCallable()]
			PyAVEVAInteractionObj();
		[PMLNetCallable()]
			void StartVenvPy(System::String^ venv_exe_path);
		[PMLNetCallable()]
			void StartSysPy();
		[PMLNetCallable()]
			void RunPyFile(System::String^ filePath);
		[PMLNetCallable()]
			void RunPyCode(System::String^ PythonCode);
		[PMLNetCallable()]
			void StopPy();
		[PMLNetCallable()]
			void Assign(PyAVEVAInteractionObj that);
		[PMLNetCallable()]
			~PyAVEVAInteractionObj();
		void RunPythonFile(const char* filePath);
		PyConfig* pyConfig;
		PyStatus* pyStatus;
		[PMLNetCallable()]
			bool isEnvOpen;
	};
}

static public ref class typecast
{
public:
	static char* StringToCharP(System::String^ str);
	static String^ CharPToString(const char* str);
	static PyObject* PyUnicode_FromStr(char* charPtr);
};
