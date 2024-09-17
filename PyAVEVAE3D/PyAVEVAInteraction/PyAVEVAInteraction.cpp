#include "pch.h"
#include "PyAVEVAInteraction.h"

using namespace PyAVEVAInteraction;
using namespace std;

PyAVEVAInteractionObj::PyAVEVAInteractionObj() {}

System::Double PyAVEVAInteractionObj::LaunchVenvCmd(String^ venv_exe_path) {
	//Py_Initialize();
	//
	//// Check if Python interpreter was initialized successfully
	//if (!Py_IsInitialized()) {
	//	Console::WriteLine("Python initialization failed!");
	//	return 1;
	//}
	//
	//// Execute a Python script
	//PyRun_SimpleString("import sys\n"
	//	"print('Hello from Python!')\n"
	//	"print('Python version:', sys.version)\n"
	//	"import os\nprint(os.__file__)");
	//
	//// Finalize Python interpreter
	//Py_Finalize();

	Console::WriteLine(venv_exe_path);
	return 0;
	//	pin_ptr<const wchar_t> wch_venv_exe_path = PtrToStringChars(venv_exe_path);
	//	PyConfig pyConfig;
	//	PyStatus pyStatus;
	//
	//	PyConfig_InitIsolatedConfig(&pyConfig);
	//	PyConfig_SetString(&pyConfig, &pyConfig.executable, wch_venv_exe_path);
	//	pyStatus = Py_InitializeFromConfig(&pyConfig);
	//	PyConfig_Clear(&pyConfig);
	//	if (PyStatus_Exception(pyStatus)) {
	//		goto exception;
	//	}
	//
	//	return Py_RunMain();
	//exception:
	//	if (PyStatus_IsExit(pyStatus))
	//	{
	//		return pyStatus.exitcode;
	//	}
}

PyAVEVAInteractionObj::~PyAVEVAInteractionObj() {}

void PyAVEVAInteractionObj::RunInSysPy() {
	try
	{
		//PyObject* main_module = PyImport_AddModule("__main__");
		//PyObject* main_dict = PyModule_GetDict(main_module);
		Py_Initialize();

		// Check if Python interpreter was initialized successfully
		if (!Py_IsInitialized()) {
			Console::WriteLine("Python initialization failed!");
		}

		Console::WriteLine("Python Execution From C++");
		// Execute a Python script
		PyRun_SimpleString(//"import sys\n"
			"print('Hello from Python!')\n"
			//"print('Python version:', sys.version)\n"
			//"import os\nprint(os.__file__)"
		);

		Console::WriteLine("Python Execution From .Py File At C:\\db\\test.py");
		const char* pythonFilePath = "C:\\db\\test.py";
		PyAVEVAInteractionObj::RunPythonFile(pythonFilePath);
	
		// Finalize Python interpreter
		Py_Finalize();

		Console::WriteLine("Python script executed successfully.");
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void PyAVEVAInteractionObj::LaunchVenvCmddd() {
	try
	{
		wchar_t* program = Py_DecodeLocale("C:\Program Files (x86)\AVEVA\Everything3D2.10\des.exe", NULL);
		if (program == NULL) {
			fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
			exit(1);
		}

		Py_SetProgramName(program);  /* optional but recommended */
		Py_Initialize();
		PyRun_SimpleString("from time import time,ctime\n"
			"print('Today is', ctime(time()))\n");
		if (Py_FinalizeEx() < 0) {
			exit(120);
		}
		PyMem_RawFree(program);
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void PyAVEVAInteractionObj::RunInVenvPy() {
	try
	{
		PyConfig pyConfig;
		PyStatus pyStatus;
		const wchar_t* wch_venv_exe_path = L"C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe";
		//pin_ptr<const wchar_t> wch_venv_exe_path = PtrToStringChars(venv_exe_path);
		//auto wch_venv_exe_path = L"C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe";

		PyConfig_InitIsolatedConfig(&pyConfig);
		PyConfig_SetString(&pyConfig, &pyConfig.executable, wch_venv_exe_path);

		pyStatus = Py_InitializeFromConfig(&pyConfig);
		if (PyStatus_Exception(pyStatus)) {
			goto exception;
		}

		//if (PyStatus_Exception(pyStatus)) {
		//	Py_ExitStatusException(pyStatus);
		//}

		PyConfig_Clear(&pyConfig);
		
		Console::WriteLine("Python Execution From .Py File At C:\\db\\test.py");
		const char* pythonFilePath = "C:\\db\\test.py";
		PyAVEVAInteractionObj::RunPythonFile(pythonFilePath);

		// Finalize Python interpreter
		Py_Finalize();
		
		Console::WriteLine("Python script executed successfully.");
		return;
		//Console::WriteLine("Py_RunMain() Returned: " + Py_RunMain());
	exception:
		PyConfig_Clear(&pyConfig);
		if (PyStatus_IsExit(pyStatus))
		{
			Console::WriteLine("ExitCode :" + pyStatus.exitcode);
		}
		Console::WriteLine("Exception in RunInVenvPy");
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void  PyAVEVAInteractionObj::Assign(PyAVEVAInteractionObj that) {}

System::String^ PyAVEVAInteractionObj::GetString(System::String^ message) {
	Console::WriteLine(message);
	return message;
}

void  PyAVEVAInteractionObj::RunPythonFile(const char* filePath) {
	PyObject* obj = Py_BuildValue("s", filePath);
	FILE* fd = _Py_fopen_obj(obj, "r");
	//PyObject* pResult = PyRun_File(fd, filePath, Py_file_input);
	PyRun_SimpleFile(fd, filePath);
	//PyObject* PyFileObject = PyFile_FromString("test.py", "r");
	//PyRun_SimpleFileEx(PyFile_AsFile(PyFileObject), "test.py", 1);
}