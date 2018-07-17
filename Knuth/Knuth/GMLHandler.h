#pragma once


#include <string>
#include <fstream>
#include "Net.h"
#include "Reader.h"
#include "Writer.h"
#include "FileHandler.h"
#include "List.h"
#include <vector>
#include "FileNotExistException.h"
#include "IncorrectFileFormatException.h"
#include "DataInvalidFormatException.h"
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::fixed;
using std::endl;
using std::vector;

struct GMLNode {
	unsigned int id;
	string label;
};


class GMLHandler : public BioNet::FileHandler
{
private:

public:
	GMLHandler() { extension = "gml"; }
	template <typename T>
	static void doRead(Net<T>& b, const string& fname){	
		ifstream infile;
		vector<GMLNode> nodes;
		nodes.reserve(20);
		try {
			infile.open(fname);
			if (infile.fail())
				throw FileNotExistException("File does not exist");		
		}
		catch (FileNotExistException ex) {

			cerr << ex.what() << endl;
			exit(1);
		}

		GMLNode node;

		try {
			string temp;
			do {
				infile >> temp;
				if (0 == temp.compare("node"))
				{
					infile >> temp >> temp >> temp;
					// temp has ID value now
					try
					{
						node.id = stoi(temp);
					}
					catch (DataInvalidFormatException ex)
					{
						cerr << ex.what() << endl;
						exit(1);
					}
					infile >> temp >> temp;
					node.label = temp.substr(1, temp.length() - 2);
					nodes.push_back(node);
				}
				else  if (0 == temp.compare("edge"))
				{
					break;
				}
				else continue;
			} while (!infile.eof());

			b.resize(nodes.size());
			for (size_t i = 0; i < nodes.size(); i++)
			{
				b.setNode(nodes[i].id, nodes[i].label);
			}

			// temporary vars for reading data
			unsigned int tempSource;
			unsigned int tempTarget;
			T tempWeight;
			do {
				if (0 == temp.compare("edge"))
				{
					infile >> temp >> temp >> temp;

					try
					{
						tempSource = stoi(temp);

						infile >> temp >> temp;

						tempTarget = stoi(temp);

						infile >> temp >> temp;

						tempWeight = stof(temp);
					}
					catch (DataInvalidFormatException ex)
					{
						cerr << ex.what() << endl;
						exit(1);
					}
					b.setEdge(tempSource, tempTarget, tempWeight);

				}
				else
				{
					infile >> temp;
					continue;
				}
			} while (!infile.eof());

		}
		catch (IncorrectFileFormatException ex)
		{
			cerr << ex.what() << endl;
			exit(1);

		}
	}
	template <typename T>
	static void doWrite(Net<T>& net, const string& fname) {
		ofstream outfile;
		try {
			outfile.open(fname);
			if (outfile.fail())
				throw FileNotExistException("File does not exist");
		}
		catch (FileNotExistException ex) {

			cout << ex.what() << endl;
			exit(1);
		}

		try {
			// start of file
			outfile << "graph [" << "\n";

			// nodes
			unsigned int netSize = net.size();
			for (int i = 0; i < netSize; i++) {
				outfile << "node [" << "\n";
				outfile << "id " << i << "\n";
				outfile << "label " << "\"" << net.getNode(i) << "\"" << "\n";
				outfile << "]" << "\n";
			}

			// edges
			for (int x = 0; x < netSize; x++) {
				for (int y = 0; y < netSize; y++) {
					T edgeWeight = net.getEdge(x, y);
					if(edgeWeight){
						outfile << "edge [" << "\n";
						outfile << "source " << x << "\n";
						outfile << "target " << y << "\n";
						outfile << "weight " << edgeWeight << "\n";
						outfile << "]" << "\n";
					}
				}
			}

			// end of file
			outfile << "]" << endl;
			outfile.close();
		}
		catch(Exception ex){
			cout << ex.what() << endl;
			exit(1);
		}
	};
//	GMLHandler(string p = "") : Reader(p), Writer(p) {};
//	~GMLHandler();
//	string getDefaultExt() { return ".gml"; }
};

