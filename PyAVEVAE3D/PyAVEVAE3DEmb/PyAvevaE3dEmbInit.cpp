#include "AllHeader.h"
#include "PmlModule.h"
#include "DbModule.h"
#include "CommonModule.h"

using namespace System;
using namespace Aveva::Core::Database;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;

typedef struct {
    PyObject_HEAD
        PmlModule* cpp_PmlModuleObj;
} PyPmlModule;

typedef struct {
    PyObject_HEAD
        DbModule* cpp_DbModuleObj;
} PyDbModule;

typedef struct {
    PyObject_HEAD
        CommonModule* cpp_CommonModuleObj;
} PyCommonModule;

static PyObject* PyRunInPdms(PyPmlModule* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlModuleObj->RunInPdms(typecast::CharPToString(commandChar)));
}

static PyObject* PyRun(PyPmlModule* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlModuleObj->Run(typecast::CharPToString(commandChar)));
}

static PyObject* PyGetPmlBool(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlModuleObj->GetPmlBool(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlReal(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyFloat_FromDouble((double)self->cpp_PmlModuleObj->GetPmlReal(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlString(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_PmlModuleObj->GetPmlString(typecast::CharPToString(varNameChar))));
}

static PyObject* PyGetPmlArray(PyPmlModule* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }

    Hashtable^ tbl = self->cpp_PmlModuleObj->GetPmlArray(typecast::CharPToString(varNameChar));
    PyObject* pyList = PyList_New(tbl->Count);
    int i = 0;

    for each (DictionaryEntry^ dataElm in tbl)
    {
        PyObject* attName = PyUnicode_FromString(typecast::StringToCharP(dataElm->Value->ToString()));
        PyList_SetItem(pyList, i, attName);
        i++;
    }
    return pyList;
}

static PyMethodDef PyPmlMethods[] = {
    {"RunInPdms", (PyCFunction)PyRunInPdms, METH_O, "Runs the PML Command in PDMS Console"},
    {"Run", (PyCFunction)PyRun, METH_O, "Runs the PML Command in .Net Environment"},
    {"GetPmlString", (PyCFunction)PyGetPmlString, METH_O, "Retuns the Value of the PML Variable as String"},
    {"GetPmlReal", (PyCFunction)PyGetPmlReal, METH_O, "Retuns the Value of the PML Variable as Long"},
    {"GetPmlBool", (PyCFunction)PyGetPmlBool, METH_O, "Retuns the Value of the PML Variable as Bool"},
    {"GetPmlArray", (PyCFunction)PyGetPmlArray, METH_O, "Retuns the Value of the PML Variable as Array"},
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
    PyPmlMethods,                        /* tp_methods */
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

static PyObject* PyAttributes(PyDbModule* self) {
    try
    {
        return typecast::StringArrayToPyList(self->cpp_DbModuleObj->attributes());
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PyCollectAllForElement(PyDbModule* self, PyObject* elementName) {
    try
    {
        const char* elementNameChar;
        if (!PyArg_Parse(elementName, "s", &elementNameChar)) {
            Py_RETURN_NONE;
        }

        return typecast::StringArrayToPyList(typecast::GetArrayFromCollection(self->cpp_DbModuleObj->CollectAllForElement(typecast::CharPToString(elementNameChar))));
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PyCollectAllFor(PyDbModule* self, PyObject* args) {
    try
    {
        const char* elementTypes;
        const char* elementScope;
        if (!PyArg_ParseTuple(args, "ss", &elementTypes, &elementScope)) {
            Py_RETURN_NONE;
        }

        TypeFilter^ typeFilter = self->cpp_DbModuleObj->TypeFilter(typecast::CharPToString(elementTypes));

        return typecast::StringArrayToPyList(typecast::GetArrayFromArrayCollection(self->cpp_DbModuleObj->CollectAllTypesFor(typecast::CharPToString(elementScope), typeFilter)));
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PySetStringAttribute(PyDbModule* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    const char* attValue;

    if (!PyArg_ParseTuple(args, "sss", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }
    self->cpp_DbModuleObj->SetStringAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), typecast::CharPToString(attValue));
    Py_RETURN_NONE;
}

static PyObject* PySetRealAttribute(PyDbModule* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    int attValue;

    if (!PyArg_ParseTuple(args, "ssi", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }
    self->cpp_DbModuleObj->SetRealAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), attValue);
    Py_RETURN_NONE;
}

static PyObject* PySetBoolAttribute(PyDbModule* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    int attValue;

    if (!PyArg_ParseTuple(args, "ssi", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }

    bool boolValue = (attValue != 0);

    self->cpp_DbModuleObj->SetBoolAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), boolValue);
    Py_RETURN_NONE;
}

static PyMethodDef PyDbMethods[] = {
    {"attributes", (PyCFunction)PyAttributes, METH_NOARGS, "Returns Attributes on current elements."},
    {"collectAllForElement", (PyCFunction)PyCollectAllForElement, METH_O, "Returns Collection as List for Element"},
    {"collectAllFor", (PyCFunction)PyCollectAllFor, METH_VARARGS, "Returns Collection as List for Element"},
    {"SetStringAttribute", (PyCFunction)PySetStringAttribute, METH_VARARGS, "Sets String Attribute for Element"},
    {"SetRealAttribute", (PyCFunction)PySetRealAttribute, METH_VARARGS, "Sets Real Attribute for Element"},
    {"SetBoolAttribute", (PyCFunction)PySetBoolAttribute, METH_VARARGS, "Sets Bool Attribute for Element"},
    {nullptr, nullptr, 0, nullptr}
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
    PyDbMethods,                         /* tp_methods */
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

static PyObject* PyMdb(PyCommonModule* self) {
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_CommonModuleObj->mdb()));
}

static PyObject* PySaveWork(PyCommonModule* self) {
    self->cpp_CommonModuleObj->SaveWork();
    Py_RETURN_NONE;
}

static PyObject* PyGetWork(PyCommonModule* self) {
    self->cpp_CommonModuleObj->GetWork();
    Py_RETURN_NONE;
}

static PyMethodDef PyCommonMethods[] = {
    {"mdb", (PyCFunction)PyMdb, METH_VARARGS, "MDB Name"},
    {"savework", (PyCFunction)PySaveWork, METH_VARARGS, "Savework Command"},
    {"getwork", (PyCFunction)PyGetWork, METH_VARARGS, "Getwork Command"},
    {nullptr, nullptr, 0, nullptr}
};

static PyObject* PyCommonModule_getce(PyCommonModule* self, void* closure) {
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_CommonModuleObj->getce()));
}

static int PyCommonModule_setce(PyCommonModule* self, PyObject* value, void* closure) {
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The CE Element must be a string.");
        return -1;
    }
    self->cpp_CommonModuleObj->setce(typecast::CharPToString(PyUnicode_AsUTF8(value)));
    return 0;
}

static PyGetSetDef PyCommonModule_getsetters[] = {
    {"ce", (getter)PyCommonModule_getce, (setter)PyCommonModule_setce, "ce", "Get & Set CE"},
    {nullptr}  /* Sentinel */
};

static PyTypeObject PyCommonModuleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3demb.common",            /* tp_name */
    sizeof(CommonModule),              /* tp_basicsize */
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
    PyCommonMethods,                   /* tp_methods */
    0,                                 /* tp_members */
    PyCommonModule_getsetters,                                 /* tp_getset */
    0,                                 /* tp_base */
    0,                                 /* tp_dict */
    0,                                 /* tp_descr_get */
    0,                                 /* tp_descr_set */
    0,                                 /* tp_dictoffset */
    0,                                 /* tp_init */
    0,                                 /* tp_alloc */
    PyType_GenericNew,                 /* tp_new */
};

static PyMethodDef pyavevae3demb_methods[] = {
    // Module specific Methods Can be added here
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

    // Initialize Common class
    if (PyType_Ready(&PyCommonModuleType) < 0)
        return NULL;
    Py_INCREF(&PyCommonModuleType);
    PyModule_AddObject(m, "COMMON", (PyObject*)&PyCommonModuleType);
    
    Console::WriteLine("pyavevae3demb init successfully.");
    return m;
}