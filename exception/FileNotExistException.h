#pragma once

#include <exception>
#include "Exception.h"
using std::exception;
using namespace BioNet;

#include <string>
using std::string;

/**
 * Exception for when a file does not exist when trying to access it.
 */
class FileNotExistException : public Exception {
public:
	/**
	 * Declares FileNotExistException constructor that inherits from BioNet::Exception
	 * @param message Exception message
	 */
	FileNotExistException(string message) : Exception(message) {}
};