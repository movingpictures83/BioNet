#pragma once


#include <string>
using std::string;


class FileHandler {
protected:  // Accessible in Reader and classes that inherit from Reader
	string extension;

public:
	string getDefaultExt()
	{
		return extension;
	}
};

//FileHandler::extension = "default";
