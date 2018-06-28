#include "stdafx.h"
#include "CSVHandler.h"
#include <fstream>
#include <sstream>
#include "../../exception/Exception.h"

using std::ifstream;
using std::ios;
using std::stringstream;


vector <string> CSVHandler::split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}

