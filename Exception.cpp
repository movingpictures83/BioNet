#include "Exception.h"
using namespace BioNet;

Exception::Exception(const std::string &m)
{
	message = "[BIONET EXCEPTION] " + m;
}

const char* Exception::what() const throw()
{
	return message.c_str();
}

Exception::~Exception() {
}


//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
