#pragma once
#include "BioAdjFactory.h"

#include <string>
#include <functional>
using std::string;
using std::function;

struct Register
{
	// name="B"  checkType= address of B::checkType
	Register(string name, function<Adj*(void)> func)
	{
		BioAdjFactory::RegisterType(name, func);
	}
};