#include "AllHeader.h"
#include <string>

using namespace System;
#pragma once
class CommonModule
{
//private:
//	std::string ce;
public:
	//CommonModule(const std::string& ce) : ce(ce) {}
	System::String^ mdb();
	void SaveWork();
	void GetWork();
	System::String^ getce();
	void setce(System::String^ elementName);
};

