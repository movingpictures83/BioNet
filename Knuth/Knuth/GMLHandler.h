#pragma once


#include <string>
#include <fstream>
#include "Net.h"
#include "Reader.h"
#include "Writer.h"
#include "File.h"
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
template <typename T>
struct GMLEdge {
	unsigned int source;
	unsigned int target;
	T weight;
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
		}
		catch (FileNotExistException ex) {

			cout << ex.what() << endl;
			exit(1);
		}

		GMLNode node;
		GMLEdge<T> edge;

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
						cout << ex.what() << endl;
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

			for (size_t i = 0; i < nodes.size(); i++)
			{
				b.resize(nodes.size());
				b.setNode(nodes[i].id, nodes[i].label);
			}

			do {
				if (0 == temp.compare("edge"))
				{
					infile >> temp >> temp >> temp;

					try
					{
						edge.source = stoi(temp);

						infile >> temp >> temp;

						edge.target = stoi(temp);

						infile >> temp >> temp;

						edge.weight = stof(temp);
					}
					catch (DataInvalidFormatException ex)
					{
						cout << ex.what() << endl;
						exit(1);
					}
					b.setEdge(edge.source, edge.target, edge.weight);

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
			cout << ex.what() << endl;
			exit(1);

		}
	}
	template <typename T>
	static void doWrite(Net<T>&, const string& fname) {
		return;
	};
//	GMLHandler(string p = "") : Reader(p), Writer(p) {};
//	~GMLHandler();
//	string getDefaultExt() { return ".gml"; }
};

