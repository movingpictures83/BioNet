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
class FileNotExistException : public Exception {
public:
	/**
	Declares FileNotExistException constructor that inherits from BioNet::Exception
	Takes Exception message as parameter

	*/
	FileNotExistException(string message) : Exception(message) {}
};