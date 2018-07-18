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
	/**
	 * GMLHandler constructor.
	 *
	 * Creates the object and sets extension as "gml".
	 */
	GMLHandler() { extension = "gml"; }

	/** 
	 * Reads a GML file into a Net<T> object.
	 * 
	 * Goes line by line reading the nodes and creating them in the Net<T> object,
	 * then reads the edges and sets them in the appropriate nodes in the Net<T>.
	 * Checks for wrong source or target nodes and for valid numbers. (No negatives)
	 *
	 * @param b Reference to the Net<T> object
	 * @param fname File path of the GML file
	 * @return No return value
	 */
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
			unsigned int tempsource;
			unsigned int temptarget;
			T tempweight;
			do {
				if (0 == temp.compare("edge"))
				{
					infile >> temp >> temp >> temp;

					try
					{
						tempsource = stoi(temp);

						infile >> temp >> temp;

						temptarget = stoi(temp);

						infile >> temp >> temp;

						tempweight = stof(temp);
					}
					catch (DataInvalidFormatException ex)
					{
						cerr << ex.what() << endl;
						exit(1);
					}
					b.setEdge(tempsource, temptarget, tempweight);

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

	/**
	 *  Writes a GML file from a Net<T> object.
	 * 
	 *	Writes line by line reading the nodes in the Net<T> object, then writes the
	 *	the edges tied to the nodes in the Net<T>. Creates the GML file it it doesn't
	 *	exist.
	 *
	 *	@param net Reference to the Net<T> object
	 *	@param fname File path of the GML file
	 *	@return No return value
	 */
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
			unsigned int netsize = net.size();

			// start of file
			outfile << "graph [" << "\n";

			// nodes
			for (int i = 0; i < netsize; i++) {
				outfile << "node [" << "\n";
				outfile << "id " << i << "\n";
				outfile << "label " << "\"" << net.getNode(i) << "\"" << "\n";
				outfile << "]" << "\n";
			}

			// edges
			for (int x = 0; x < netsize; x++) {
				for (int y = 0; y < netsize; y++) {
					T edgeweight = net.getEdge(x, y);
					if(edgeweight){
						outfile << "edge [" << "\n";
						outfile << "source " << x << "\n";
						outfile << "target " << y << "\n";
						outfile << "weight " << edgeweight << "\n";
						outfile << "]" << "\n";
					}
				}
			}

			// end of file
			outfile << "]" << endl;
			outfile.close();
		}
		catch(Exception ex){
			cerr << ex.what() << endl;
			exit(1);
		}
	};
//	GMLHandler(string p = "") : Reader(p), Writer(p) {};
//	~GMLHandler();
//	string getDefaultExt() { return ".gml"; }
};

