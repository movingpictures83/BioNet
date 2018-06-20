#pragma once
#include <iostream>       // std::cout
#include <exception>      // std::exception
class BioNetException : public std::exception
{
private:
	std::string message;
public:
	BioNetException(std::string m);
	const char * what() const throw();
	~BioNetException();
};

