#pragma once
#include <string>
#include "..\..\BioNet.h"
#include <iostream>
#include <ios>
#include <vector>
using std::string;
using std::cin;
using std::cout;
using std::vector;



class CSVReader
{
public:
	CSVReader(const string &filename);
	~CSVReader();
	void readFile(BioNet &file, const string & fname = "");

private:
	string _filename;
private :
	vector<string> split(const string &s, char delim);
};

