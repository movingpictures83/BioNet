#pragma once

#include <exception>
#include "Exception.h"
using std::exception;
using namespace BioNet;

#include <string>
using std::string;

/**
Inherits from BioNet::Exception

*/
class NoMemoryAllocatedException : public Exception {
public:
	/**
	Declares NoMemoryAllocatedException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	NoMemoryAllocatedException(string message) : Exception(message) {}
};