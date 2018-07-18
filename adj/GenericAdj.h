#pragma once
#include <string>

namespace BioNet {
	class GenericAdj {
		virtual const std::string getKeyword() const = 0;
	};
}