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
	virtual void setEdge(int, int, float);
	virtual void setEdge(string, string, float);
	virtual float getEdge(int, int);
	virtual float getEdge(string, string);
	virtual void setNode(int, string);
	virtual string getNode(int);
	virtual int size();
};

