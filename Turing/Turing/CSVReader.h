#pragma once
#include <string>
#include "..\..\BioNet.h"
#include <iostream>
using std::string;
using std::cin;
using std::cout;

class CSVReader
{
public:
	CSVReader();
	~CSVReader();
	void readFile(BioNet &file, const string & fname = "");

private:
	string filename;
};

