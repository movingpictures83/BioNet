#pragma once


#include <string>
#include <fstream>
#include "../../BioNet.h"
#include "../../Reader.h"
#include "../../Writer.h"
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


class GMLHandler : public Reader, public Writer
{
private:
	Node node;
	Edge edge;
	ifstream infile;
	vector<Node> nodes;
	vector<Edge> edges;
	void doRead(BioNet&, const string& fname);
	void doWrite(BioNet&, const string& fname);

public:
	GMLHandler(string p = "") : Reader("gml", p), Writer("gml", p) {};
	~GMLHandler();
	string getDefaultExt() { return ".gml"; }
};

