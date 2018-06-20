#include "stdafx.h"
#include "GMLReader.h"
#include <algorithm>

GMLReader::GMLReader(string filename) {
	nodes.reserve(20);
	infile.open(filename, ios::in);

}

GMLReader::~GMLReader() {};

void GMLReader::ReadFile(BioNet& b, string name) {
	string temp;
	do {
		infile >> temp;
		if (0 == temp.compare("node"))
		{
			infile >> temp >> temp >> temp;
			// temp has ID value now
			node.id = stoi(temp);
			infile >> temp >> temp;
			node.label = temp;
			//b.setNode(node.id, node.label);
			nodes.push_back(node);
		}
		else  if (0 == temp.compare("edge"))
		{
			break;
		}
		else continue;
	} while (!infile.eof());

	b.resize(nodes.size());

	for (int i = 0; i < nodes.size(); i++)
	{
		b.setNode(nodes[i].id, nodes[i].label);
	}

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
