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
class FileCreationFailedException : public Exception {
public:
	/**
	Declares FileCreationFailedException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	FileCreationFailedException(string message) : Exception(message) {}
};