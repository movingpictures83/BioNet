#pragma once
#include "AdjFactory.h"
#include <string>
#include <functional>
using std::string;
using std::function;

namespace BioNet {
	/// A struct to register the adj type from the factory map.
	/**
	Registers the adj type from the factory map.
	*/
	struct Register {
		// name="B"  checkType= address of B::checkType
		string keyword;
		/**
		Constructor that registers function with AdjFactory's mFactoryMap

		@param name - unique string identifier for the function being provided for the map.
		@param func - unique function for constructing desired underlying type.
		*/

		Register(const string name, GenericAdj * (*func)())
		{
			keyword = name;
			AdjFactory::getInstance()->RegisterType(name, func);
		}
	};
}