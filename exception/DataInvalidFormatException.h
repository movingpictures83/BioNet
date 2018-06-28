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
class DataInvalidFormatException : public Exception {
public:
	/**
	Declares DataInvalidFormatException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter	

	*/
	DataInvalidFormatException(string message) : Exception(message) {}
};
