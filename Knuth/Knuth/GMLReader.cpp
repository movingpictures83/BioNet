#include "stdafx.h"
#include "GMLReader.h"

GMLReader::GMLReader(string filename) {
	infile.open(filename, ios::in);


}

GMLReader::~GMLReader() {};

void GMLReader::ReadFile(BioNet b, string name) {
	string temp;
	do {
		infile >> temp;
		//	temp >> temp >> temp;
		if (0 == temp.compare("node"))
		{
			infile >> temp >> temp >> temp;
			// temp has ID value now
			node.id = stoi(temp);
			infile >> temp >> temp;
			node.label = temp;
			b.setNode(node.id, node.label);
		}
		else if (0 == temp.compare("edge"))
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
			continue;
		}
	} while (temp.length() > 0);
}
