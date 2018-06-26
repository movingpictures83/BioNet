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

#include "../../Reader.h"
#include "../../Writer.h"

class CSVReader : public Reader, public Writer
{
public:
	CSVReader(/*const string &filename,*/string p="") : Reader(/*filename,*/p), Writer(/*filename,*/ p) {}
	~CSVReader();
	string getDefaultExt() { return "csv"; }
//private:
	//string _filename;
private :
	vector<string> split(const string &s, char delim);

	template <typename T>
	void doRead(BioNet<T> &file, const string & fname);

	template <typename T>
	void doWrite(BioNet<T> &file, const string & fname) {};

};

