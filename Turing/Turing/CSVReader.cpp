#include "stdafx.h"
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include "..\..\BioNetException.h"

using std::ifstream;
using std::ios;
using std::stringstream;


vector <string> CSVReader::split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}

