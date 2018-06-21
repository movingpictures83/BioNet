#pragma once
#include <string>
using std::string;

class BioAdj
{
protected:
	string keyword;
public:
     BioAdj();
	 BioAdj(BioAdj &&bioAdg);
	~BioAdj();
	virtual void setEdge(int, int, float);
	virtual void setEdge(string, string, float);
	virtual void getEdge(int, int);
	virtual void getEdge(string, string);
	virtual void setNode(int, string);
	virtual void getNode(int);
};

