#pragma once
#include <Windows.h>
#include <vcclr.h>
#include "typecast.h"
#include <vector>
#include <cmath>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif