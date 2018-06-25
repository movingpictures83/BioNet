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

	void setEdge(const int, const int, const float);
	void setEdge(const string&, const string&, const float);
	float getEdge(const int, const int) const;
	float getEdge(const string&, const string&) const;
	void setNode(const int, const string&);
	string getNode(const int) const;
	int size() const;
	void resize(const int);
	float degree(const int) const;
	int numberOfEdges() const;
	int findNodeIndex(const string&) const;
	void deleteEdge(const string &, const string &);
	void deleteEdge(int, int);
	void deleteNode(const string &);
	void deleteNode(const int);
	//int numberOfEdges(bool) ;
};