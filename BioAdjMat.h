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
	BioAdjMat() {}
	~BioAdjMat() {}

	virtual void setEdge(int, int, float);
	virtual void setEdge(string, string, float);
	virtual float getEdge(int, int);
	virtual float getEdge(string, string);
	virtual void setNode(int, string);
	virtual string getNode(int);
	virtual int size();
	virtual float degree(int);
	virtual int numberOfEdges();
	virtual void resize(int);
};