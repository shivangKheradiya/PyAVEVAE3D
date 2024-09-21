#include "PyAvevaE3dEmbModule.h"

using namespace Aveva::Core::Database;

PyObject* PyAvevaE3dEmbModule::mdb(PyObject* /* unused module reference */) {
    return typecast::PyUnicode_FromStr(typecast::StringToCharP(MDB::CurrentMDB->Name));
}

PyObject* PyAvevaE3dEmbModule::get_ce(PyObject* /* unused module reference */) {
    try
    {
        return typecast::PyUnicode_FromStr(typecast::StringToCharP(CurrentElement::Element->EvaluateString(DbExpression::Parse("flnn"))));
    }
    catch (...)
    {
        Console::WriteLine("Unable to find current element.");
    }
    Py_RETURN_NONE;
}

PyObject* PyAvevaE3dEmbModule::set_ce(PyObject* /* unused module reference */, PyObject* o) {
    const char* elementName = 0;
    //PyBytes_AsString(o);
    if (!PyArg_Parse(o, "s", &elementName)) {
        //Py_DECREF(o);
        Py_RETURN_NONE;
    }

    String^ elementFlnn = typecast::CharPToString(elementName);
    try
    {
        CurrentElement::Element = DbElement::GetElement((elementFlnn)->ToString());
    }
    catch (...)
    {
        Console::WriteLine("Unable to goto Element Name : " + elementFlnn);
    }
    //Py_DECREF(o);
    Py_RETURN_NONE;
}