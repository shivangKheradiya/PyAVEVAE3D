#include <Windows.h>
#include <cmath>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

using namespace System;
using namespace Aveva::Core::Database;

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

PyObject* current_MDB(PyObject* /* unused module reference */) {
    Console::WriteLine("Current MDB: " + MDB::CurrentMDB->Name);
    Py_RETURN_NONE;
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

static PyMethodDef pyavevae3demb_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    { "fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr },
    { "current_MDB", (PyCFunction)current_MDB, METH_NOARGS , nullptr },
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

PyMODINIT_FUNC PyInit_pyavevae3demb(void) {
    Console::WriteLine("pyavevae3demb init successfully.");
    return PyModule_Create(&pyavevae3demb_module);
}