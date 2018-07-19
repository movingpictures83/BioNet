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
class NoDataExistsException : public Exception {
public:
	/**
	Declares NoDataexistsException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	NoDataExistsException(string message) : Exception(message) {}
};