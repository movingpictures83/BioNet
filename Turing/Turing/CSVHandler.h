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
#include "FileNotExistException.h"
#include "DataInvalidFormatException.h"
#include "FileHandler.h"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::stringstream;
using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::stod;
using BioNet::Net;
using BioNet::Exception;
using BioNet::FileHandler;



class CSVHandler: public FileHandler
{
public:
	/// Method to read the files and populates a bionet
	/**
	@param bionet Reference to a **Net** object.
	@param fname  File name to read from.
	*/
	template <typename T>
	static void doRead(Net<T> &bionet, const string & fname)
	{
		//string filename;
		ifstream inputFile(fname/*_filename*/, ios::in);
		try {
			if (inputFile.fail())
				throw FileNotExistException("Unable to open given file");
		}
		catch(FileNotExistException e){
			cout << e.what() << endl;
			exit(1);
		}
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
		for (unsigned int col = 1; col < cols; col++)
		{
			bionet.setNode(col - 1, col_Values[col]);
		}
		vector <string> row_line;
		unsigned int row_count = 0;
		char * rowVal = 0;
			while (!inputFile.eof())
			{
				getline(inputFile, line);
				if (line == "")
					continue;
				rowVal = split2(line, ',', cols - 1);

				//Moving through every row, and setting the col value.
				for (unsigned int i = 1; i < cols; i++)
				{
					bionet.setEdge(row_count, i - 1, (T)stod(&rowVal[i]));
				}
				row_count++;
			}
			/// Make sure the memory gets deallocated
			free(rowVal);
	}

	template <typename T>
	/// Writes the BioNet to a file
	/**
	@param bionet Reference to a **Net** object.
	@param fname  File name to output to.
	*/
	static void doWrite(Net<T> &bionet, const string & fname)
	{
		try {
			ofstream outpuFile(fname, ios::out);
			if (!bionet)
				throw DataInvalidFormatException("Bionet doesn't contain any data");
		}
		catch (DataInvalidFormatException e) {
			cout << e.what() << endl;
			exit(1);
		}

		unsigned int rows = bionet.size();
		unsigned int row = 0;
		unsigned int col = 0;
		//looping throgh columns like a matrix
		while (row < rows)
		{
				if (row == 0)
				{
					//setting the nodes names
					for (unsigned int col = 0; col < bionet.size(); col++)
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
					for (unsigned int col = 0; col < bionet.size(); col++)
					{
						if (col == 0)
							outpuFile << bionet.getNode(col);
						else
							outpuFile << "," << bionet.getEdge(row - 1, col - 1);
					}
					outpuFile << "\n";

				}
				row++;
		}	
	}

//private:
	//string _filename;
private :
	static vector<string> split(const string &s, char delim);
	static char * split2(const string &s, char delim, int sizeB);
};

