#pragma once
#include <vector>
#include <string>
#include <ostream>
#include "BioAdj.h"

using std::vector;
using std::string;
using std::ostream;

template <typename T>
class BioAdjMat : public BioAdj<T>
{
private:
	vector<vector<T>> matrix;
	vector<string> names;

public:
	static const string& NetworkType()
	{
		static const string network = "BioAdjMat";
		return network;
	}

	BioAdjMat(int size = 5) {
		names.resize(size);
		matrix.resize(size);
		for (auto& n : matrix)
			n.resize(size);
	}
	~BioAdjMat() {}

	void setEdge(const int, const int, const T);
	void setEdge(const string&, const string&, const T);
	T getEdge(const int, const int) const;
	T getEdge(const string&, const string&) const;
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
	const BioAdjMat & operator/= (const T &);
	const BioAdjMat & operator*= (const T &);
	bool operator== (const BioAdjMat &);
	bool operator!= (const BioAdjMat &);
	const string & operator[] (int);
	T operator() (int, int);
	friend ostream & operator<< (const ostream &, const BioAdjMat &);
};