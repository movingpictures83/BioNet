#pragma once
#include <string>
using std::string;

#define ADJ_MAT_KEY "BioAdjMat"
#define ADJ_LST_KEY "BioAdjList"

class BioAdj
{
protected:
	string keyword;
public:
    // BioAdj();
	//~BioAdj();
	virtual void setEdge(const int, const int, const float) = 0;
	virtual void setEdge(const string&, const string&, const float) = 0;
	virtual float getEdge(const int, const int) const = 0;
	virtual float getEdge(const string&, const string&) const = 0;
	virtual void setNode(const int, const string&) = 0;
	virtual string getNode(const int) const = 0;
	virtual int size() const = 0;
	virtual float degree(const int) const = 0;
	virtual int numberOfEdges() const = 0;
	virtual void resize(const int) = 0;

	virtual int findNodeIndex(const string&) const =0;
	virtual void deleteEdge(const string &, const string &) =0;
	virtual void deleteEdge(int, int) = 0;
	virtual void deleteNode(const string &) = 0;
	virtual void deleteNode(int) = 0;
};

