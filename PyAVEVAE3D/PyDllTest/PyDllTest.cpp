#include "pch.h"

using namespace System;
using namespace PyAVEVAInteraction;

int main(array<System::String ^> ^args)
{
    PyAVEVAInteractionObj obj;
    obj.RunInVenvPy("C:\\Program Files (x86)\\AVEVA\\Everything3D2.10\\skDlls\\pyEnv\\Scripts\\python.exe", "C:\\db\\test.py");
    return 0;
}
