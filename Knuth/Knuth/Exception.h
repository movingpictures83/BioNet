#pragma once


#include <exception>
using std::exception;

#include <string>
using std::string;
//#include "BioNetException.h"

//using BioNetException::BioNetException;

class TerminalException : public exception {
private:
	string msg;
public:
	TerminalException(string message) : msg(message) {}
	const char* getMsg() const {
		return msg.c_str();
	}
};

class FileNotExistException : public TerminalException {
public:
	FileNotExistException(string message) : TerminalException(message) {}
};

class IncorrectFileFormatException : public TerminalException {
public:
	IncorrectFileFormatException(string message) : TerminalException(message) {}
};

class DataInvalidFormatException : public TerminalException {
public:
	DataInvalidFormatException(string message) : TerminalException(message) {}
};
