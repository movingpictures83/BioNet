#pragma once

#include <vector>
#include <string>
#include "BioAdj.h"

using std::vector;
using std::string;


class BioAdjMat : public BioAdj
{
private:
	vector<vector<float>> matrix;
	vector<string> names;

public:
	BioAdjMat(int size = 5) {
		names.resize(size);
		matrix.resize(size);
		for (auto n : matrix)
			n.resize(size);
	}
	~BioAdjMat() {}

	void setEdge(int, int, float);
	void setEdge(string, string, float);
	float getEdge(int, int);
	float getEdge(string, string);
	void setNode(int, string);
	string getNode(int);
	int size();
	void resize(int);
	float degree(int);
	int findNodeIndex(const string&);
	void deleteEdge(const string &, const string &);
	void deleteEdge(int, int);
	void deleteNode(const string &);
	void deleteNode(int);
};