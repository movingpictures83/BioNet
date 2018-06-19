#include "stdafx.h"
#include "CSVReader.h"


CSVReader::CSVReader()
{
}


CSVReader::~CSVReader()
{
}

void CSVReader::readFile(BioNet &file, const string & fname)
{
	string filename;
	if (fname == "")
	{
		cout << "Please enter the filename:";
	}
	else
	{
		filename = fname;
	}
	
cin >>filename

}