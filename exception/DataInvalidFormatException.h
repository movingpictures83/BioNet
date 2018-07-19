#pragma once

#include <exception>
#include "Exception.h"
using std::exception;
using namespace BioNet;

#include <string>
using std::string;

/**
 * Exception for when read or used data has invalid format.
 */
class DataInvalidFormatException : public Exception {
public:
	/**
	 * Declares DataInvalidFormatException constructor that inherits from BioNet::Exception
	 * Takes Exception message as parameter	
	 * @param message Exception message
	 */
	DataInvalidFormatException(string message) : Exception(message) {}
};
