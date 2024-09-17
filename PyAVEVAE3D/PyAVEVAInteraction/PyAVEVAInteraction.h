#include <Windows.h>
#include <exception>
#include <cstdio>
#include <cstring>
#include <vcclr.h>

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
			System::Double LaunchVenvCmd(System::String^ venv_exe_path);
		[PMLNetCallable()]
			System::String^ GetString(System::String^ message);
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
	};
}
