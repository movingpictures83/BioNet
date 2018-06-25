#pragma once
#include <vector>
#include <string>
#include <ostream>
#include "BioAdj.h"

using std::vector;
using std::string;
using std::ostream;


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
	BioAdjMat operator= (const BioAdjMat &);
	BioAdjMat operator+ (const string &);
	const BioAdjMat & operator+= (const string &);
	const BioAdjMat & operator/= (const float &);
	const BioAdjMat & operator*= (const float &);
	bool operator== (const BioAdjMat &);
	bool operator!= (const BioAdjMat &);
	const string & operator[] (int);
	float operator() (int, int);
	friend ostream & operator<< (const ostream &, const BioAdjMat &);
};