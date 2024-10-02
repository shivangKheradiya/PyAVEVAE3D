#pragma once
#include <Windows.h>
#include <vcclr.h>
#include <vector>
#include <cmath>
#include <string>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif