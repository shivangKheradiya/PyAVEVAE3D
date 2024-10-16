#include "pch.h"
#include "PyAVEVAInteraction.h"
#include "cstdio"

using namespace std;
using namespace System::Runtime::InteropServices;
using namespace PyAVEVAInteraction;

PyAVEVAInteractionObj::PyAVEVAInteractionObj() {
	PyAVEVAInteractionObj::isEnvOpen = false;
}

PyAVEVAInteractionObj::~PyAVEVAInteractionObj() {}

void PyAVEVAInteractionObj::StartVenvPy(System::String^ venv_exe_path) {

	if (PyAVEVAInteractionObj::isEnvOpen)
	{
		Console::WriteLine("Python Environment is Already Running.");
		return;
	}

	try
	{
		PyConfig pyConfig;
		PyStatus pyStatus;
		PyAVEVAInteractionObj::pyConfig = &pyConfig;
		PyAVEVAInteractionObj::pyStatus = &pyStatus;
		pin_ptr<const wchar_t> wch_venv_exe_path = PtrToStringChars(venv_exe_path);

		PyConfig_InitIsolatedConfig(PyAVEVAInteractionObj::pyConfig);
		PyConfig_SetString(PyAVEVAInteractionObj::pyConfig, &PyAVEVAInteractionObj::pyConfig->executable, wch_venv_exe_path);

		PyAVEVAInteractionObj::pyStatus = &Py_InitializeFromConfig(PyAVEVAInteractionObj::pyConfig);
		if (PyStatus_Exception(*PyAVEVAInteractionObj::pyStatus)) {
			goto exception;
		}

		PyConfig_Clear(PyAVEVAInteractionObj::pyConfig);
		Console::WriteLine("Python Virtual Environment Started Successfuly.");
		PyAVEVAInteractionObj::isEnvOpen = true;
		return;
	exception:
		PyConfig_Clear(PyAVEVAInteractionObj::pyConfig);
		if (PyStatus_IsExit(*PyAVEVAInteractionObj::pyStatus))
		{
			Console::WriteLine("ExitCode :" + PyAVEVAInteractionObj::pyStatus->exitcode);
		}
		Console::WriteLine("Exception in StartVenvPy");
	}
	catch (System::Exception^ ex)
	{
		Console::WriteLine("Managed exception: " + ex->Message);
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void PyAVEVAInteractionObj::StartSysPy() {

	if ( PyAVEVAInteractionObj::isEnvOpen )
	{
		Console::WriteLine("Python Environment is Already Running.");
		return;
	}

	try
	{
		Py_Initialize();
		if (!Py_IsInitialized()) {
			Console::WriteLine("Python initialization failed!");
		}
		else
		{
			PyAVEVAInteractionObj::isEnvOpen = true;
			Console::WriteLine("System Leval Python initialized.");
		}
	}
	catch (System::Exception^ ex)
	{
		Console::WriteLine("Managed exception: " + ex->Message);
	}
	catch (...)
	{
		Console::WriteLine("exception something went wrong");
	}
}

void PyAVEVAInteractionObj::RunPyFile(System::String^ filePath) {
	if (!PyAVEVAInteractionObj::isEnvOpen)
	{
		Console::WriteLine("Python Environment is not running to run the file " + filePath);
		return;
	}

	try
	{
		PyAVEVAInteractionObj::RunPythonFile(typecast::StringToCharP(filePath));
	}
	catch (System::Exception^ ex)
	{
		Console::WriteLine("Managed exception: " + ex->Message);
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in RunPyFileInVenv");
	}
}

void PyAVEVAInteractionObj::RunPyCode(System::String^ PythonCode) {
	if (!PyAVEVAInteractionObj::isEnvOpen)
	{
		Console::WriteLine("Python Environment is not running to run the code " + PythonCode);
		return;
	}

	try
	{
		PyObject* sys = PyImport_ImportModule("sys");
		PyObject* stringIO = PyImport_ImportModule("io");
		PyObject* pyOutput = PyObject_CallMethod(stringIO, "StringIO", nullptr);

		PyObject_SetAttrString(sys, "stdout", pyOutput);
		PyObject_SetAttrString(sys, "stderr", pyOutput);

		if (PyRun_SimpleString(typecast::StringToCharP(PythonCode)) != 0) {
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
	catch (System::Exception^ ex)
	{
		Console::WriteLine("Managed exception: " + ex->Message);
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in RunPyCodeInVenv");
	}
}

void PyAVEVAInteractionObj::StopPy() {
	if (!PyAVEVAInteractionObj::isEnvOpen)
	{
		Console::WriteLine("Python Environment is not Running.");
		return;
	}

	try
	{
		Py_Finalize();
		PyAVEVAInteractionObj::isEnvOpen = false;
		Console::WriteLine("Python Environment is Closed.");
	}
	catch (System::Exception^ ex)
	{
		Console::WriteLine("Managed exception: " + ex->Message);
	}
	catch (...)
	{
		Console::WriteLine("Something went wrong in StopVenvPy");
	}
}

void  PyAVEVAInteractionObj::Assign(PyAVEVAInteractionObj that) {}

void  PyAVEVAInteractionObj::RunPythonFile(const char* filePath) {

	PyObject* obj = Py_BuildValue("s", filePath);
	FILE* fd = _Py_fopen_obj(obj, "r");

	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* stringIO = PyImport_ImportModule("io");
	PyObject* pyOutput = PyObject_CallMethod(stringIO, "StringIO", nullptr);

	PyObject_SetAttrString(sys, "stdout", pyOutput);
	PyObject_SetAttrString(sys, "stderr", pyOutput);

	if (PyRun_SimpleFile(fd, filePath) != 0) {
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