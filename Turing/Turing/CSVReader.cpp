#include "stdafx.h"
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include "..\..\BioNetException.h"

using std::ifstream;
using std::ios;
using std::stringstream;


/*CSVReader::CSVReader(const string &fname)
{
	this->_filename = fname;
}*/


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

void CSVReader::readFile(BioNet &bionet, const string & fname)
{
	//string filename;
	ifstream inputFile(fname/*_filename*/, ios::in);
	if (inputFile.fail())
		throw BioNetException("Unable to open given file");

	string line;
	vector <string> col_Values;
	getline(inputFile, line);
	col_Values = split(line, ',');
	auto cols = col_Values.size();
	bionet.resize(cols-1);
	for (int col = 1; col < cols; col++)
	{
		bionet.setNode(col - 1, col_Values[col]);
	}
	vector <string> row_line;
	int row_count = 0;
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		if (line == "")
			continue;
		col_Values = split(line, ',');
		auto row_perCol = col_Values.size();
		//Verify each row has the same column numbers
		if(row_perCol != cols)
		{
			string error = "Invalid column width for row " + std::to_string(row_count) + "Expected: " + std::to_string(cols)
				+ " columns recieved: " + std::to_string(row_perCol);
			throw BioNetException(error);
		}
		
		//Moving through every row, and setting the col value.
		for (int i = 1; i < cols; i++)
		{
			bionet.setEdge(row_count, i-1, stof(col_Values[i]));
		}
		row_count++;
	}

}