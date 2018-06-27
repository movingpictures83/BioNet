#pragma once


#include <exception>
#include "../../BioNetException.h"
using std::exception;

#include <string>
using std::string;
//#include "BioNetException.h"

//using BioNetException::BioNetException;

class FileNotExistException : public BioNetException {
public:
	FileNotExistException(string message) : BioNetException(message) {}
};

class IncorrectFileFormatException : public BioNetException {
public:
	IncorrectFileFormatException(string message) : BioNetException(message) {}
};

class DataInvalidFormatException : public BioNetException {
public:
	DataInvalidFormatException(string message) : BioNetException(message) {}
};
