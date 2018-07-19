#pragma once

#include <exception>
#include "Exception.h"
using namespace BioNet;

#include <string>
using std::string;

/// File create exception
/**
 * Exception for when a file could not be created.
 */
class FileCreationFailedException : public Exception {
public:
	/**
	 * Declares FileCreationFailedException constructor that inherits from BioNet::Exception
	 * @param message Exception message
	 */
	FileCreationFailedException(string message) : Exception(message) {}
};