#include "AllHeader.h"
#include "PyAvevaE3dEmbModule.h"
#include "PmlModule.h"
#include "DbModule.h"

using namespace System;
using namespace Aveva::Core::Database;
using namespace System::Runtime::InteropServices;

typedef struct {
    PyObject_HEAD
        PmlModule* cpp_obj;
} PyPmlModule;

typedef struct {
    PyObject_HEAD
        DbModule* cpp_obj;
} PyDbModule;

static PyObject* PyRunInPdms(PyPmlModule* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_obj->RunInPdms(typecast::CharPToString(commandChar)));
}

static PyObject* PyRun(PyPmlModule* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_obj->Run(typecast::CharPToString(commandChar)));
}

static PyObject* PyGetPmlBool(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_obj->GetPmlBool(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlReal(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyFloat_FromDouble((double)self->cpp_obj->GetPmlReal(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlString(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_obj->GetPmlString(typecast::CharPToString(varNameChar))));
}

static PyMethodDef PmlMethods[] = {
    {"RunInPdms", (PyCFunction)PyRunInPdms, METH_O, "Runs the PML Command in PDMS Console"},
    {"Run", (PyCFunction)PyRun, METH_O, "Runs the PML Command in .Net Environment"},
    {"GetPmlString", (PyCFunction)PyGetPmlString, METH_O, "Retuns the Value of the PML Variable as String"},
    {"GetPmlReal", (PyCFunction)PyGetPmlReal, METH_O, "Retuns the Value of the PML Variable as Long"},
    {"GetPmlBool", (PyCFunction)PyGetPmlBool, METH_O, "Retuns the Value of the PML Variable as Bool"},
    {nullptr, nullptr, 0, nullptr}
};

static PyTypeObject PyPmlModuleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3demb.pml",               /* tp_name */
    sizeof(PmlModule),                 /* tp_basicsize */
    0,                                 /* tp_itemsize */
    0,                                 /* tp_dealloc */
    0,                                 /* tp_print */
    0,                                 /* tp_getattr */
    0,                                 /* tp_setattr */
    0,                                 /* tp_as_async */
    0,                                 /* tp_repr */
    0,                                 /* tp_as_number */
    0,                                 /* tp_as_sequence */
    0,                                 /* tp_as_mapping */
    0,                                 /* tp_hash */
    0,                                 /* tp_call */
    0,                                 /* tp_str */
    0,                                 /* tp_getattro */
    0,                                 /* tp_setattro */
    0,                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "Module to Interact with PML Commandline Channel",               /* tp_doc */
    0,                                 /* tp_traverse */
    0,                                 /* tp_clear */
    0,                                 /* tp_richcompare */
    0,                                 /* tp_weaklistoffset */
    0,                                 /* tp_iter */
    0,                                 /* tp_iternext */
    PmlMethods,                        /* tp_methods */
    0,                                 /* tp_members */
    0,                                 /* tp_getset */
    0,                                 /* tp_base */
    0,                                 /* tp_dict */
    0,                                 /* tp_descr_get */
    0,                                 /* tp_descr_set */
    0,                                 /* tp_dictoffset */
    0,                                 /* tp_init */
    0,                                 /* tp_alloc */
    PyType_GenericNew,                 /* tp_new */
};

// DB class type
static PyTypeObject PyDbModuleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3demb.db",                /* tp_name */
    sizeof(DbModule),                  /* tp_basicsize */
    0,                                 /* tp_itemsize */
    0,                                 /* tp_dealloc */
    0,                                 /* tp_print */
    0,                                 /* tp_getattr */
    0,                                 /* tp_setattr */
    0,                                 /* tp_as_async */
    0,                                 /* tp_repr */
    0,                                 /* tp_as_number */
    0,                                 /* tp_as_sequence */
    0,                                 /* tp_as_mapping */
    0,                                 /* tp_hash */
    0,                                 /* tp_call */
    0,                                 /* tp_str */
    0,                                 /* tp_getattro */
    0,                                 /* tp_setattro */
    0,                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "Module to interact with Dabacon DB",                 /* tp_doc */
    0,                                 /* tp_traverse */
    0,                                 /* tp_clear */
    0,                                 /* tp_richcompare */
    0,                                 /* tp_weaklistoffset */
    0,                                 /* tp_iter */
    0,                                 /* tp_iternext */
    0, //DbMethods,                         /* tp_methods */
    0,                                 /* tp_members */
    0,                                 /* tp_getset */
    0,                                 /* tp_base */
    0,                                 /* tp_dict */
    0,                                 /* tp_descr_get */
    0,                                 /* tp_descr_set */
    0,                                 /* tp_dictoffset */
    0,                                 /* tp_init */
    0,                                 /* tp_alloc */
    PyType_GenericNew,                 /* tp_new */
};

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

PyObject* attributes(PyObject* /* unused module reference */) {
    try
    {
        PyObject* pyList = PyList_New(CurrentElement::Element->GetAttributes()->Length);
        int i = 0;
        for each (DbAttribute^ att in CurrentElement::Element->GetAttributes())
        {
            PyObject* attName = PyUnicode_FromString((char*)(void*)Marshal::StringToHGlobalAnsi(att->Name));
            PyList_SetItem(pyList, i, attName);
            i++;
        }
        return pyList;
    }
    catch (...)
    {
        Console::WriteLine("Unable to gather attributes");
    }
    Py_RETURN_NONE;
}

static PyMethodDef pyavevae3demb_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
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
    {"attributes", (PyCFunction)attributes, METH_NOARGS, nullptr},
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

    PyObject* m;

    m = PyModule_Create(&pyavevae3demb_module);
    if (m == NULL)
        return nullptr;

    // Initialize PML class
    if (PyType_Ready(&PyPmlModuleType) < 0)
        return NULL;
    Py_INCREF(&PyPmlModuleType);
    PyModule_AddObject(m, "PML", (PyObject*)&PyPmlModuleType);

    // Initialize DB class
    if (PyType_Ready(&PyDbModuleType) < 0)
        return NULL;
    Py_INCREF(&PyDbModuleType);
    PyModule_AddObject(m, "DB", (PyObject*)&PyDbModuleType);

    PyObject* db_module_def = PyModule_Create(&db_Module);
    if (!db_module_def) {
        Py_DECREF(m);
        return nullptr;
    }
    
    PyObject* pml_module_def = PyModule_Create(&pml_Module);
    if (!pml_module_def) {
        Py_DECREF(m);
        return nullptr;
    }
    
    PyModule_AddObject(m, "db", db_module_def);
    PyModule_AddObject(m, "pml", pml_module_def);
    
    Console::WriteLine("pyavevae3demb init successfully.");
    return m;

    // PyObject* pyavevae3demb_module_def = PyModule_Create(&pyavevae3demb_module);
    // if (!pyavevae3demb_module_def) {
    //     return nullptr;
    // }
    // 
    // PyObject* db_module_def = PyModule_Create(&db_Module);
    // if (!db_module_def) {
    //     Py_DECREF(pyavevae3demb_module_def);
    //     return nullptr;
    // }
    // 
    // PyObject* pml_module_def = PyModule_Create(&pml_Module);
    // if (!pml_module_def) {
    //     Py_DECREF(pyavevae3demb_module_def);
    //     return nullptr;
    // }
    // 
    // PyModule_AddObject(pyavevae3demb_module_def, "db", db_module_def);
    // PyModule_AddObject(pyavevae3demb_module_def, "pml", pml_module_def);
    // 
    // Console::WriteLine("pyavevae3demb init successfully.");
    // return pyavevae3demb_module_def;
}