#pragma once


#include <exception>
using std::exception;

#include <string>
using std::string;

class TerminalException : public exception {
private:
	string msg;
public:
	TerminalException(string message) : msg(message) {}
	const char* what() const {
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
