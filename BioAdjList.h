#pragma once
#include "BioAdj.h"
#include "BioList.h"
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;


class BioAdjList : public BioAdj
{
private:
	vector<BioList> network;
	map<string, int> names;
public:
	BioAdjList(int i = 5){
		network.resize(i);
	}
	~BioAdjList() {}

	void setEdge(const int,const int, float);
	void setEdge(const string, const string, float);
	const float getEdge(const int, const int);
	const float getEdge(const string, const string);
	void setNode(const int, const string);
	const string getNode(const int);
	int size() { return network.size(); }
	float degree(const int);
	int numberOfEdges();
	void resize(const int);
};