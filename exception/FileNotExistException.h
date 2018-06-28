#pragma once

#include <exception>
#include "Exception.h"
using std::exception;
using namespace BioNet;

#include <string>
using std::string;

/**
Declares FileNotExistException constructor that inherits from BioNet::Exception

*/
class FileNotExistException : public Exception {
public:
	/**
	Inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	FileNotExistException(string message) : Exception(message) {}
};