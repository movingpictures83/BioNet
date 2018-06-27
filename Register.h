#pragma once
#include "BioAdjFactory.h"

#include <string>
#include <functional>
using std::string;
using std::function;

struct Register
{
	// name="B"  checkType= address of B::checkType
	string keyword;
	Register(string name, Adj * (*func)())
	{
		keyword = name;
		BioAdjFactory::RegisterType(name, func);
	}
};