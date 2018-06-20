#pragma once


#include <string>
#include <fstream>
#include "../../BioNet.h"
#include <vector>
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::fixed;
using std::endl;
using std::vector;

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
	vector<Node> nodes;
	vector<Edge> edges;

public:
	GMLReader(string filename);
	~GMLReader();
	void ReadFile(BioNet b, string name);
};

