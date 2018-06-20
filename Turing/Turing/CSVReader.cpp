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

void CSVReader::readFile(BioNet &bionet, const string & fname)
{
	//string filename;
	ifstream inputFile(_filename, ios::in);
	string line;
	vector <string> col_Values;
	getline(inputFile, line);
	col_Values = split(line, ',');
	int cols = 0;
	//vector<vector<string>> v(row, vector<string>(col));
	cols = (col_Values.size()) - 1;
	//bionet.resize(col);
	for (int col = 1; col < cols; col++)
	{
		bionet.setNode(col - 1, col_Values[col]);
	}
	vector <string> row_line;
	int row_count = 0;
	int row_perCol = 0;
	while (!inputFile.eof)
	{
		getline(inputFile, line);
		col_Values = split(line, ',');
		row_perCol = col_Values.size();
		//Verify each row has the same column numbers
		//Moving through every row, and setting the col value.
		for (int i = 1; i < cols; i++)
		{
			bionet.setEdge(row_count, i, stof(col_Values[i]));
		}
		row_count++;
	}

}