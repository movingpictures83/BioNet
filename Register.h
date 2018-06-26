#pragma once
#include "BioAdjFactory.h"

#include <string>
#include <functional>
using std::string;
using std::function;

struct Register
{
	// name="B"  checkType= address of B::checkType
	Register(string name, Adj * (*func)())
	{
		BioAdjFactory::RegisterType(name, func);
	}
};