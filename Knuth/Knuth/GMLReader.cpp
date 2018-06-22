#include "stdafx.h"
#include "GMLReader.h"
#include <algorithm>
#include "Exception.h"
#include <iostream>
using std::cout;

//GMLReader::GMLReader(string filename) {
//	nodes.reserve(20);
//	infile.open(filename, ios::in);
//
//}

GMLHandler::~GMLHandler() {};

void GMLHandler::readFile(BioNet& b, string& fname) {
	nodes.reserve(20);

	// check if path
	string filename = "";
	size_t found = fname.find("/") + fname.find("\\");
	if (0 == found)
	{
		filename += Reader::defaultPath;
	}

	filename += fname;

	// check if ext missing
	found = fname.find('.gml');
	if (0 == found)
	{
		filename += defaultExt;
	}

	try {
		infile.open(filename);
	}
	catch (FileNotExistException ex) {

		ex.getMsg();
		exit(1);
	}


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
					cout << ex.getMsg();
					exit(1);
				}
				infile >> temp >> temp;
				node.label = temp.substr(1, temp.length() - 2);
				//b.setNode(node.id, node.label);
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
			b.setNode(nodes[i].id, nodes[i].label);
		}

		do {
			 if (0 == temp.compare("edge"))
			{
				infile >> temp >> temp >> temp;
			
				try
				{
					edge.source = stoi(temp);
				}
				catch (DataInvalidFormatException ex)
				{
					cout << ex.getMsg();
					exit(1);
				}
				infile >> temp >> temp;
			
				try
				{
					edge.target = stoi(temp);
				}
				catch (DataInvalidFormatException ex)
				{
					cout << ex.getMsg();
					exit(1);
				}
				infile >> temp >> temp;
			
				try
				{
					edge.weight = stof(temp);
				}
				catch (DataInvalidFormatException ex)
				{
					cout << ex.getMsg();
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

		do {
			if (0 == temp.compare("edge"))
			{
				infile >> temp >> temp >> temp;
				edge.source = stoi(temp);
				infile >> temp >> temp;
				edge.target = stoi(temp);
				infile >> temp >> temp;
				edge.weight = stof(temp);
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
		ex.getMsg();
		exit(1);

	}

}


void GMLHandler::writeFile(BioNet&, string& fname)
{
	return;
}