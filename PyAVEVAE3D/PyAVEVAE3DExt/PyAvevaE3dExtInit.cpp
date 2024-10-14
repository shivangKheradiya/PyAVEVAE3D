#include "AllHeader.h"
#include "AvevaWraperClassDefinations.h"

using namespace System;
using namespace Aveva::Core::Database;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;

typedef struct {
    PyObject_HEAD
        PmlClass* cpp_PmlClassInstance;
} PyPmlClass;

typedef struct {
    PyObject_HEAD
        DbClass* cpp_DbClassInstance;
} PyDbClass;

typedef struct {
    PyObject_HEAD
        CommonClass* cpp_CommonClassInstance;
} PyCommonClass;

static PyObject* PyRunInPdms(PyPmlClass* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlClassInstance->RunInPdms(typecast::CharPToString(commandChar)));
}

static PyObject* PyRun(PyPmlClass* self, PyObject* args) {
    const char* commandChar;
    if (!PyArg_Parse(args, "s", &commandChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlClassInstance->Run(typecast::CharPToString(commandChar)));
}

static PyObject* PyGetPmlBool(PyPmlClass* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyBool_FromLong(self->cpp_PmlClassInstance->GetPmlBool(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlReal(PyPmlClass* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyFloat_FromDouble((double)self->cpp_PmlClassInstance->GetPmlReal(typecast::CharPToString(varNameChar)));
}

static PyObject* PyGetPmlString(PyPmlClass* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_PmlClassInstance->GetPmlString(typecast::CharPToString(varNameChar))));
}

static PyObject* PyGetPmlArray(PyPmlClass* self, PyObject* args) {
    const char* varNameChar;
    if (!PyArg_Parse(args, "s", &varNameChar)) {
        Py_RETURN_NONE;
    }

    Hashtable^ tbl = self->cpp_PmlClassInstance->GetPmlArray(typecast::CharPToString(varNameChar));
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

static PyMethodDef PyPmlClassMethods[] = {
    {"RunInPdms", (PyCFunction)PyRunInPdms, METH_O, "Runs the PML Command in PDMS Console"},
    {"Run", (PyCFunction)PyRun, METH_O, "Runs the PML Command in .Net Environment"},
    {"GetPmlString", (PyCFunction)PyGetPmlString, METH_O, "Retuns the Value of the PML Variable as String"},
    {"GetPmlReal", (PyCFunction)PyGetPmlReal, METH_O, "Retuns the Value of the PML Variable as Long"},
    {"GetPmlBool", (PyCFunction)PyGetPmlBool, METH_O, "Retuns the Value of the PML Variable as Bool"},
    {"GetPmlArray", (PyCFunction)PyGetPmlArray, METH_O, "Retuns the Value of the PML Variable as Array"},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject PyPmlClassType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3dext.pml",
    sizeof(PmlClass),   
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    "Module to Interact with PML Commandline Channel",
    0,
    0,
    0,
    0,
    0,
    0,
    PyPmlClassMethods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyType_GenericNew,
};

static PyObject* PyAttributes(PyDbClass* self) {
    try
    {
        return typecast::StringArrayToPyList(self->cpp_DbClassInstance->attributes());
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PyCollectAllForElement(PyDbClass* self, PyObject* elementName) {
    try
    {
        const char* elementNameChar;
        if (!PyArg_Parse(elementName, "s", &elementNameChar)) {
            Py_RETURN_NONE;
        }

        return typecast::StringArrayToPyList(typecast::GetArrayFromCollection(self->cpp_DbClassInstance->CollectAllForElement(typecast::CharPToString(elementNameChar))));
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PyCollectAllFor(PyDbClass* self, PyObject* args) {
    try
    {
        const char* elementTypes;
        const char* elementScope;
        if (!PyArg_ParseTuple(args, "ss", &elementTypes, &elementScope)) {
            Py_RETURN_NONE;
        }

        TypeFilter^ typeFilter = self->cpp_DbClassInstance->TypeFilter(typecast::CharPToString(elementTypes));

        return typecast::StringArrayToPyList(typecast::GetArrayFromArrayCollection(self->cpp_DbClassInstance->CollectAllTypesFor(typecast::CharPToString(elementScope), typeFilter)));
    }
    catch (...)
    {
        Console::WriteLine("Unable to fatch attributes");
    }
    Py_RETURN_NONE;
}

static PyObject* PySetStringAttribute(PyDbClass* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    const char* attValue;

    if (!PyArg_ParseTuple(args, "sss", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }
    self->cpp_DbClassInstance->SetStringAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), typecast::CharPToString(attValue));
    Py_RETURN_NONE;
}

static PyObject* PySetRealAttribute(PyDbClass* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    int attValue;

    if (!PyArg_ParseTuple(args, "ssi", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }
    self->cpp_DbClassInstance->SetRealAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), attValue);
    Py_RETURN_NONE;
}

static PyObject* PySetBoolAttribute(PyDbClass* self, PyObject* args) {
    const char* elementName;
    const char* attName;
    int attValue;

    if (!PyArg_ParseTuple(args, "ssi", &elementName, &attName, &attValue)) {
        Py_RETURN_NONE;
    }

    bool boolValue = (attValue != 0);

    self->cpp_DbClassInstance->SetBoolAttribute(typecast::CharPToString(elementName), typecast::CharPToString(attName), boolValue);
    Py_RETURN_NONE;
}

static PyMethodDef PyDbClassMethods[] = {
    {"attributes", (PyCFunction)PyAttributes, METH_NOARGS, "Returns Attributes on current elements."},
    {"collectAllForElement", (PyCFunction)PyCollectAllForElement, METH_O, "Returns Collection as List for Element"},
    {"collectAllFor", (PyCFunction)PyCollectAllFor, METH_VARARGS, "Returns Collection as List for Element"},
    {"SetStringAttribute", (PyCFunction)PySetStringAttribute, METH_VARARGS, "Sets String Attribute for Element"},
    {"SetRealAttribute", (PyCFunction)PySetRealAttribute, METH_VARARGS, "Sets Real Attribute for Element"},
    {"SetBoolAttribute", (PyCFunction)PySetBoolAttribute, METH_VARARGS, "Sets Bool Attribute for Element"},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject PyDbClassType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3dext.db",
    sizeof(DbClass),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    "Module to interact with Dabacon DB",
    0,
    0,
    0,
    0,
    0,
    0,
    PyDbClassMethods,       
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyType_GenericNew,
};

static PyObject* PyMdb(PyCommonClass* self) {
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_CommonClassInstance->mdb()));
}

static PyObject* PySaveWork(PyCommonClass* self) {
    self->cpp_CommonClassInstance->SaveWork();
    Py_RETURN_NONE;
}

static PyObject* PyGetWork(PyCommonClass* self) {
    self->cpp_CommonClassInstance->GetWork();
    Py_RETURN_NONE;
}

static PyMethodDef PyCommonClassMethods[] = {
    {"mdb", (PyCFunction)PyMdb, METH_VARARGS, "MDB Name"},
    {"savework", (PyCFunction)PySaveWork, METH_VARARGS, "Savework Command"},
    {"getwork", (PyCFunction)PyGetWork, METH_VARARGS, "Getwork Command"},
    {NULL, NULL, 0, NULL}
};

static PyObject* PyCommonModule_getce(PyCommonClass* self, void* closure) {
    return PyUnicode_FromString(typecast::StringToCharP(self->cpp_CommonClassInstance->getce()));
}

static int PyCommonModule_setce(PyCommonClass* self, PyObject* value, void* closure) {
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The CE Element must be a string.");
        return -1;
    }
    self->cpp_CommonClassInstance->setce(typecast::CharPToString(PyUnicode_AsUTF8(value)));
    return 0;
}

static PyGetSetDef PyCommonModule_getsetters[] = {
    {"ce", (getter)PyCommonModule_getce, (setter)PyCommonModule_setce, "ce", "Get & Set CE"},
    {NULL}
};

static PyTypeObject PyCommonModuleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyavevae3dext.common",
    sizeof(CommonClass),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    "Module to Interact with PML Commandline Channel",
    0,
    0,
    0,
    0,
    0,
    0,
    PyCommonClassMethods,
    0,
    PyCommonModule_getsetters,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    PyType_GenericNew,
};

static PyMethodDef pyavevae3dext_methods[] = {
    { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef pyavevae3dext_module = {
    PyModuleDef_HEAD_INIT,
    "pyavevae3dext",
    "Provides the functionality to Access AVEVA E3D From Python",
    -1,
    pyavevae3dext_methods
};

PyMODINIT_FUNC PyInit_pyavevae3dext(void) {

    PyObject* m;

    m = PyModule_Create(&pyavevae3dext_module);
    if (m == NULL)
        return nullptr;

    if (PyType_Ready(&PyPmlClassType) < 0)
        return NULL;
    Py_INCREF(&PyPmlClassType);
    PyModule_AddObject(m, "PML", (PyObject*)&PyPmlClassType);

    if (PyType_Ready(&PyDbClassType) < 0)
        return NULL;
    Py_INCREF(&PyDbClassType);
    PyModule_AddObject(m, "DB", (PyObject*)&PyDbClassType);

    if (PyType_Ready(&PyCommonModuleType) < 0)
        return NULL;
    Py_INCREF(&PyCommonModuleType);
    PyModule_AddObject(m, "COMMON", (PyObject*)&PyCommonModuleType);
    
    Console::WriteLine("pyavevae3dext init successfully.");
    return m;
}