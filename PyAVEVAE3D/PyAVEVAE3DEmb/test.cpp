#include <Windows.h>
#include <cmath>
#include <vcclr.h>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

using namespace System;
using namespace Aveva::Core::Database;
using namespace System::Runtime::InteropServices;

const double e = 2.7182818284590452353602874713527;

double sinh_impl(double x) {
    return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl(double x) {
    return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double tanh_impl(double x) {
    return sinh_impl(x) / cosh_impl(x);
}

PyObject* tanh_impl(PyObject* /* unused module reference */, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    double tanh_x = sinh_impl(x) / cosh_impl(x);
    return PyFloat_FromDouble(tanh_x);
}

PyObject* mdb(PyObject* /* unused module reference */) {
    //Console::WriteLine("Current MDB: " + MDB::CurrentMDB->Name);
    return PyUnicode_FromString((char*)(void*)Marshal::StringToHGlobalAnsi(MDB::CurrentMDB->Name));
    //Py_RETURN_NONE;
}

PyObject* set_ce(PyObject* /* unused module reference */, PyObject* o) {
    Console::WriteLine("Set Method started");
    const char* elementName = 0;
        //PyBytes_AsString(o);
    if (!PyArg_Parse(o, "s", &elementName)) {
        //Py_DECREF(o);
        Py_RETURN_NONE;
    }
    String^ elementFlnn = gcnew String(elementName);
    try
    {
        CurrentElement::Element = DbElement::GetElement(elementFlnn->ToString());
    }
    catch (...)
    {
        Console::WriteLine("Unable to goto Element Name : " + elementFlnn);
    }
    //Py_DECREF(o);
    Py_RETURN_NONE;
}

PyObject* get_ce(PyObject* /* unused module reference */) {
    try
    {
        return PyUnicode_FromString( (char*)(void*) Marshal::StringToHGlobalAnsi( CurrentElement::Element->EvaluateString( DbExpression::Parse("flnn") ) ) );
    }
    catch (...)
    {
        Console::WriteLine("Unable to find current element.");
    }
    Py_RETURN_NONE;
}

static PyMethodDef pyavevae3demb_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    { "fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr },
    { "mdb", (PyCFunction)mdb, METH_NOARGS , nullptr },
    { "get_ce", (PyCFunction)get_ce, METH_NOARGS , nullptr },
    { "set_ce", (PyCFunction)set_ce, METH_O , nullptr },
    // Terminate the array with an object containing nulls
    { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef pyavevae3demb_module = {
    PyModuleDef_HEAD_INIT,
    "pyavevae3demb",                        // Module name to use with Python import statements
    "Provides the functionality to Access AVEVA E3D From Python",  // Module description
    -1,
    pyavevae3demb_methods                   // Structure that defines the methods of the module
};

static PyObject* hello_world(PyObject* self, PyObject* args) {
    return PyUnicode_FromString("Hi, World!");
}

static PyMethodDef pml_Module_Methods[] = {
    {"hello", hello_world, METH_NOARGS, ""},
    {nullptr, nullptr, 0, nullptr}
};

static PyMethodDef db_Module_Methods[] = {
    {"hello", hello_world, METH_NOARGS, ""},
    {nullptr, nullptr, 0, nullptr}
};

static PyModuleDef db_Module = {
    PyModuleDef_HEAD_INIT,
    "db",
    "To interact with the database.",
    -1,
    db_Module_Methods
};

static PyModuleDef pml_Module = {
    PyModuleDef_HEAD_INIT,
    "pml",
    "To interact with pml commandline",
    -1,
    pml_Module_Methods
};

PyMODINIT_FUNC PyInit_pyavevae3demb(void) {
    PyObject* pyavevae3demb_module_def = PyModule_Create(&pyavevae3demb_module);
    if (!pyavevae3demb_module_def) {
        return nullptr;
    }

    PyObject* db_module_def = PyModule_Create(&db_Module);
    if (!db_module_def) {
        Py_DECREF(pyavevae3demb_module_def);
        return nullptr;
    }

    PyObject* pml_module_def = PyModule_Create(&pml_Module);
    if (!pml_module_def) {
        Py_DECREF(pyavevae3demb_module_def);
        return nullptr;
    }

    PyModule_AddObject(pyavevae3demb_module_def, "db", db_module_def);
    PyModule_AddObject(pyavevae3demb_module_def, "pml", pml_module_def);

    Console::WriteLine("pyavevae3demb init successfully.");
    return pyavevae3demb_module_def;
}