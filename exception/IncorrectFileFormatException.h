#pragma once

#include <exception>
#include "Exception.h"
using namespace BioNet;

#include <string>
using std::string;

///Incorrect file format exceptions
/**
* Exception for when a file is not the correct format when trying to access it.
*/
class IncorrectFileFormatException : public Exception {
public:
	/**
	 * Declares IncorrectFileFormatException constructor that inherits from BioNet::Exception
	 * @param message Exception message
	 */
	IncorrectFileFormatException(string message) : Exception(message) {}
};