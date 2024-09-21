#include "pch.h"
#include "PyAVEVAInteraction.h"
#include "PythonConsole.h"
#include "cstdio"

using namespace PyAVEVAInteraction;
using namespace std;
using namespace System::Runtime::InteropServices;
using namespace PythonEmbeddedApp;

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

void PyAVEVAInteractionObj::RunInVenvPy(System::String^ venv_exe_path, System::String^ filePath) {
	try
	{
		PyConfig pyConfig;
		PyStatus pyStatus;
		//const wchar_t* wch_venv_exe_path = L"C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe";
		pin_ptr<const wchar_t> wch_venv_exe_path = PtrToStringChars(venv_exe_path);
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

		const char* ch_py_file_path = (char*)(void*)Marshal::StringToHGlobalAnsi(filePath);
		Console::WriteLine("Python Execution From .Py File At " + filePath->ToString());
			//C:\\db\\test.py");
		//const char* pythonFilePath = "C:\\db\\test.py";
		PyAVEVAInteractionObj::RunPythonFile(ch_py_file_path);

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

void PyAVEVAInteractionObj::StartVenvPy(System::String^ venv_exe_path) {
	try
	{
		PyConfig pyConfig;
		PyStatus pyStatus;
		PyAVEVAInteractionObj::pyConfig = &pyConfig;
		PyAVEVAInteractionObj::pyStatus = &pyStatus;
		//const wchar_t* wch_venv_exe_path = L"C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe";
		pin_ptr<const wchar_t> wch_venv_exe_path = PtrToStringChars(venv_exe_path);
		//auto wch_venv_exe_path = L"C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe";

		PyConfig_InitIsolatedConfig(PyAVEVAInteractionObj::pyConfig);
		PyConfig_SetString(PyAVEVAInteractionObj::pyConfig, &PyAVEVAInteractionObj::pyConfig->executable, wch_venv_exe_path);

		PyAVEVAInteractionObj::pyStatus = &Py_InitializeFromConfig(PyAVEVAInteractionObj::pyConfig);
		if (PyStatus_Exception(*PyAVEVAInteractionObj::pyStatus)) {
			goto exception;
		}

		//if (PyStatus_Exception(pyStatus)) {
		//	Py_ExitStatusException(pyStatus);
		//}

		PyConfig_Clear(PyAVEVAInteractionObj::pyConfig);
		Console::WriteLine("Python Virtual Environment Started Successfuly.");
		return;
	exception:
		PyConfig_Clear(PyAVEVAInteractionObj::pyConfig);
		if (PyStatus_IsExit(*PyAVEVAInteractionObj::pyStatus))
		{
			Console::WriteLine("ExitCode :" + PyAVEVAInteractionObj::pyStatus->exitcode);
		}
		Console::WriteLine("Exception in StartVenvPy");
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void PyAVEVAInteractionObj::RunPyFileInVenv(System::String^ filePath) {
	try
	{
		PyAVEVAInteractionObj::RunPythonFile(typecast::StringToCharP(filePath));
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in RunPyFileInVenv");
	}
}

void PyAVEVAInteractionObj::RunPyCodeInVenv(System::String^ PythonCode) {
	try
	{
		PyObject* sys = PyImport_ImportModule("sys");
		PyObject* stringIO = PyImport_ImportModule("io");
		PyObject* pyOutput = PyObject_CallMethod(stringIO, "StringIO", nullptr);

		// Redirect Python stdout and stderr to StringIO
		PyObject_SetAttrString(sys, "stdout", pyOutput);
		PyObject_SetAttrString(sys, "stderr", pyOutput);

		if (PyRun_SimpleString(typecast::StringToCharP(PythonCode)) != 0) {
			// Handle any errors
			PyErr_Print();
		}

		PyObject* output = PyObject_CallMethod(pyOutput, "getvalue", nullptr);
		const char* outputStr = PyUnicode_AsUTF8(output);
		Py_XDECREF(output);
		Py_XDECREF(pyOutput);
		Py_XDECREF(sys);
		Py_XDECREF(stringIO);
		Console::WriteLine(typecast::CharPToString(outputStr));
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in RunPyCodeInVenv");
	}
}

void PyAVEVAInteractionObj::StopVenvPy() {
	try
	{
		Py_Finalize();
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in StopVenvPy");
	}
}

void PyAVEVAInteractionObj::EmbadeJupyter(){
	try
	{
		Form1^ fm1 = gcnew Form1();
		fm1->Show();
		// //std::string pythonExePath = unmanagedEnvPath + "\\Scripts\\python.exe";
		// 
		// // Allocate a new console for the new process
		// AllocConsole();
		// 
		// // Prepare the command to run the Python script in IPython
		// const char* command = "\"C:\\Program Files(x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe\" \"C:\\db\\ipython_shell.py\"";
		// 
		// // Set up process information structures
		// STARTUPINFOA si;
		// PROCESS_INFORMATION pi;
		// ZeroMemory(&si, sizeof(si));
		// si.cb = sizeof(si);
		// si.dwFlags = STARTF_USESTDHANDLES;
		// si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		// si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		// si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		// 
		// // Create the process
		// if (!CreateProcessA(
		// 	NULL,                         // No module name (use command line)
		// 	const_cast<char*>(command), // Command line
		// 	NULL,                         // Process handle not inheritable
		// 	NULL,                         // Thread handle not inheritable
		// 	TRUE,                         // Set handle inheritance to TRUE
		// 	0,                            // No creation flags
		// 	NULL,                         // Use parent's environment block
		// 	NULL,                         // Use parent's starting directory 
		// 	&si,                          // Pointer to STARTUPINFO structure
		// 	&pi)                          // Pointer to PROCESS_INFORMATION structure
		// 	) {
		// 	Console::WriteLine("Failed to create process.");
		// 	return;
		// }
		// 
		// // Wait until the new process exits
		// WaitForSingleObject(pi.hProcess, INFINITE);
		// 
		// // Clean up
		// CloseHandle(pi.hProcess);
		// CloseHandle(pi.hThread);


		// FreeConsole();
		// if (AllocConsole()) {
		// 	FILE* new_stdout;
		// 	FILE* new_stderr;
		// 
		// 	if (freopen_s(&new_stdout, "CONOUT$", "w", stdout) != 0) {
		// 		Console::WriteLine("Failed to redirect stdout.");
		// 	}
		// 
		// 	if (freopen_s(&new_stderr, "CONOUT$", "w", stderr) != 0) {
		// 		Console::WriteLine("Failed to redirect stderr.");
		// 	}
		// 
		// 	// Start an interactive Python shell
		// 	PyRun_InteractiveLoop(stdin, "<stdin>");
		// }



		// FreeConsole();
		// 
		// if (AllocConsole()) {
		// 	FILE* new_stdout;
		// 	FILE* new_stdin;
		// 	FILE* new_stderr;
		// 
		// 	freopen_s(&new_stdout, "CONOUT$", "w", stdout);
		// 	freopen_s(&new_stdin, "CONIN$", "r", stdin);
		// 	freopen_s(&new_stderr, "CONOUT$", "w", stderr);
		// 
		// 	Console::Write("Hii Python is working\n");
		// 
		// 	// Redirect standard output and input to the new console
		// 	//freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		// 	//freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
		// 	//freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
		// 
		// 	//std::cout << "Console successfully created for current process." << std::endl;
		// }
		// else {
		// 	//std::cerr << "Failed to create a new console." << std::endl;
		// }

		//PythonConsole pythonConsole;
		//
		//// Create a new console window
		//pythonConsole.createConsole();
		//
		//// Run embedded Python code
		//pythonConsole.runEmbeddedPython();
		//
		//PyRun_SimpleString("import sys");
		//PyRun_SimpleString("import os");
		//
		//// Set the path to include the directory where ipykernel is installed
		//PyRun_SimpleString("sys.path.append(os.path.dirname(sys.executable))");
		//
		//// Import the necessary modules for Jupyter kernel
		//PyRun_SimpleString("import ipykernel");
		//PyRun_SimpleString("from IPython import embed_kernel");
		//
		//// Start the IPython kernel within the embedded interpreter
		//PyRun_SimpleString("embed_kernel()");
		//PyAVEVAInteractionObj::RunPyCodeInVenv("from IPython import embed_kernel\nembed_kernel()\n");
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in RunPyCodeInVenv");
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