#include "stdafx.h"
#include "CSVHandler.h"
#include "../../exception/Exception.h"


vector <string> CSVHandler::split(const string &s, char delim) {
	vector<string> result;
	char * str_s = (char *)s.c_str();
	char* pch = NULL;
	char * next_token = NULL;
	pch = strtok_s(str_s, ",", &next_token);
	
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok_s(NULL, ",", &next_token);
	}
	return result;
}

