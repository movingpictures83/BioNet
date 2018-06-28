#pragma once

#include <exception>
#include "Exception.h"
using std::exception;
using namespace BioNet;

#include <string>
using std::string;

/**
Declares DataInvalidFormatException constructor that inherits from BioNet::Exception

*/
class DataInvalidFormatException : public Exception {
public:
	/**
	Inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	DataInvalidFormatException(string message) : Exception(message) {}
};
