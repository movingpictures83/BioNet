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
	BioAdjList(const BioAdjList&);
	void setEdge(const int, const int, const float);
	void setEdge(const string&, const string&, const float);
	float getEdge(const int, const int) const;
	float getEdge(const string&, const string&) const;
	void setNode(const int, const string&);
	string getNode(const int) const;
	int size() const;
	float degree(const int) const;
	int numberOfEdges() const;
	void resize(const int);
	int findNodeIndex(const string&) const;
	void deleteEdge(const string &, const string &);
	void deleteEdge(int, int);
	void deleteNode(const string &);
	void deleteNode(int);
	const BioAdjList& operator+=(const string nodename);
	BioAdjList operator+(const string nodename);
	BioAdjList operator=(const BioAdjList &rhs);
};