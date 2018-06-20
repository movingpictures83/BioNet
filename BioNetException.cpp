#include "BioNetException.h"
// exception::what

BioNetException::BioNetException(std::string m)
{
	message = "[BIONET EXCEPTION] " + m;
}

const char* BioNetException::what() const throw()
{
	return message.c_str();
}

BioNetException::~BioNetException() {
}


//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
