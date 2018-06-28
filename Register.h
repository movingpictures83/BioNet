#pragma once
#include "BioAdjFactory.h"

#include <string>
#include <functional>
using std::string;
using std::function;

namespace BioNet {
	struct Register {
		// name="B"  checkType= address of B::checkType
		string keyword;
		Register(string name, GenericAdj * (*func)())
		{
			keyword = name;
			BioAdjFactory::RegisterType(name, func);
		}
	};
}