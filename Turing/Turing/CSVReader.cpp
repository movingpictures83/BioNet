#include "stdafx.h"
#include "CSVReader.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ios;
using std::stringstream;


CSVReader::CSVReader(const string &fname)
{
	this->_filename = fname;
}


CSVReader::~CSVReader()
{
}

vector <string> CSVReader::split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}
void CSVReader::readFile(BioNet &file, const string & fname)
{
	//string filename;
	ifstream inputFile(_filename, ios::in);
	string line;
	vector <string> labels ;
	getline(inputFile, line);
	labels = split(line, ',');

	while (!getline(inputFile,line))
	{

	}

}