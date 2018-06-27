#pragma once


#include <string>
#include <fstream>
#include "../../BioNet.h"
#include "../../Reader.h"
#include "../../Writer.h"
#include "../../File.h"
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
	double weight;
};


class GMLHandler : public FileHandler
{
private:
	ifstream infile;
	vector<Node> nodes;
	vector<Edge> edges;

public:
	GMLHandler() { extension = "gml"; }
	template <typename T>
	static void doRead(BioNet<T>&, const string& fname);
	template <typename T>
	static void doWrite(BioNet<T>&, const string& fname);
//	GMLHandler(string p = "") : Reader(p), Writer(p) {};
//	~GMLHandler();
//	string getDefaultExt() { return ".gml"; }
};

