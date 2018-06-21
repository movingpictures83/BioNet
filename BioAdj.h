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
	virtual float degree(int);
};

