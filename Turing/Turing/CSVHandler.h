#pragma once
#include <string>
#include "Net.h"
#include <iostream>
#include <ios>
#include <vector>
#include "Reader.h"
#include "Writer.h"
#include <fstream>
#include <sstream>
#include "Exception.h"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::stringstream;
using std::string;
using std::cin;
using std::cout;
using std::vector;
using BioNet::Net;
using BioNet::Exception;



class CSVHandler
{
public:
	///Method to read the files and populates a bionet
	template <typename T>
	static void doRead(Net<T> &bionet, const string & fname)
	{
		//string filename;
		ifstream inputFile(fname/*_filename*/, ios::in);
		if (inputFile.fail())
			throw Exception("Unable to open given file");
		string line;
		//vector <string> col_Values;
		vector<string> col_Values;
		getline(inputFile, line);
		// calculate the number of commas
		// of the first line (header)
		// then for this number generate the format string for scanf 
		// and replace the split line by line for a scanf
		col_Values = split(line, ',');
		auto cols = col_Values.size();
		bionet.resize((int)cols - 1);
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
			if (row_perCol != cols)
			{
				string error = "Invalid column width for row " + std::to_string(row_count) + "Expected: " + std::to_string(cols)
					+ " columns recieved: " + std::to_string(row_perCol);
				throw Exception(error);
			}

			//Moving through every row, and setting the col value.
			for (int i = 1; i < cols; i++)
			{
				bionet.setEdge(row_count, i - 1, (T)stod(col_Values[i]));
			}
			row_count++;
		}
	}

	template <typename T>
	static void doWrite(Net<T> &bionet, const string & fname)
	{
		ofstream outpuFile(fname, ios::out);
		if(!bionet)
			throw Exception("Bionet doesn't contain any data");

		int rows = bionet.size();
		int row = 0;
		int col = 0;
		//looping throgh columns like a matrix
		while (row < rows)
		{
			if (row == 0)
			{
				//setting the nodes names
				for (int col = 0; col < bionet.size(); col++)
				{
					if (col == 0)
						outpuFile << "\"\"";
					else
					{
						outpuFile << "," << bionet.getNode(col - 1);
					}
				}
				
			}
			else
			{ //setting the edges values 
				for (int col = 0; col < bionet.size(); col++)
				{
				if(col == 0)
					outpuFile << bionet.getNode(col);
				else				
					outpuFile << "," << bionet.getEdge(row - 1,col - 1);	
				}
				outpuFile << "\n";

			}
			row++;
		}	
	}

	static string getDefaultExt() { return "csv"; }
//private:
	//string _filename;
private :
	static vector<string> split(const string &s, char delim);
};

