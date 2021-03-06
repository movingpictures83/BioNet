#pragma once

#include <exception>
#include "Exception.h"
using namespace BioNet;

#include <string>
using std::string;

/// Invalid data format exception
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
