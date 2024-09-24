#include <Windows.h>
#include <exception>
#include <cstdio>
#include <cstring>
#include <vcclr.h>
#include "typecast.h"

#pragma once
using namespace System;
using namespace Aveva::Core::PMLNet;
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
			void RunInSysPy();
		[PMLNetCallable()]
			void LaunchVenvCmddd();
		[PMLNetCallable()]
			void RunInVenvPy(System::String^ venv_exe_path, System::String^ filePath);
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
