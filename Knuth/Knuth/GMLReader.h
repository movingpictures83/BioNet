#pragma once


#include <string>
#include <fstream>
#include "../../BioNet.h"
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::fixed;
using std::endl;

struct Node {
	int id;
	string label;
};
struct Edge {
	int source;
	int target;
	float weight;
};


class GMLReader
{
private:
	Node node;
	Edge edge;
	ifstream infile;

public:
	GMLReader(string filename);
	~GMLReader();
	void ReadFile(BioNet b, string name);
};

