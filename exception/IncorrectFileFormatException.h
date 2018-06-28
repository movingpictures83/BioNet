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
class IncorrectFileFormatException : public Exception {
public:
	/**
	Declares IncorrectFileFormatException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	IncorrectFileFormatException(string message) : Exception(message) {}
};