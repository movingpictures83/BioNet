#pragma once
#include <string>

namespace BioNet {
	/**
	* Implements GenericAdj class
	*
	*/
	class GenericAdj {
		/**
		* Return the name of the tyepe T used by derived class Adj<T>
		* i.e Adj<int> gets "int".
		* 
		*/ 
		virtual const std::string getKeyword() const = 0;
	};
}