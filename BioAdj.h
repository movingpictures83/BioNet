#pragma once
#include <string>
using std::string;

class BioAdj
{
protected:
	string keyword;
public:
     BioAdj();
	~BioAdj();
	virtual void setEdge(int, int, float) = 0;
	virtual void setEdge(string, string, float) = 0;
	virtual float getEdge(int, int) = 0;
	virtual float getEdge(string, string) = 0;
	virtual void setNode(int, string) = 0;
	virtual string getNode(int) = 0;
	virtual int size() = 0;
	virtual float degree(int) = 0;
	virtual int numberOfEdges() = 0;
	virtual void resize(int) = 0;

	virtual int findNodeIndex(const string&) =0;
	virtual void deleteEdge(const string &, const string &) =0;
	virtual void deleteEdge(int, int) = 0;
	virtual void deleteNode(const string &) = 0;
	virtual void deleteNode(int) = 0;
};

