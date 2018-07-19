#include "stdafx.h"
#include "CSVHandler.h"
#include "../../exception/Exception.h"


vector <string> CSVHandler::split(const string &s, const char delim) {
	vector<string> result;
	char * str_s = (char *)s.c_str();
	char* pch = NULL;
	char * next_token = NULL;
	pch = strtok_s(str_s, &delim, &next_token);
	
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok_s(NULL, ",", &next_token);
	}
	return result;
}


char ** CSVHandler::split2(const string &s, const char delim, const int rows, const int colsize)
{
	char ** result = (char **)malloc(rows*sizeof(char *));
	if (0 == result)
		return 0;
	for (int i = 0; i < rows; i++)
	{
		result[i] = (char *)malloc(colsize);
		if (0 == result[i])
			return 0;
		memset((void *)result[i], 0, colsize);
	}
	char * str_s = (char *)s.c_str();
	char* pch = NULL;
	char * next_token = NULL;
	pch = strtok_s(str_s, &delim, &next_token);
	if (0 == pch) return 0;
	pch = strtok_s(NULL, &delim, &next_token);
	
	int i = 0;
	while (pch != NULL)
	{
		memcpy((void *)result[i++], pch, strlen(pch));
		pch = strtok_s(NULL, &delim, &next_token);
	}

	return result;
}
