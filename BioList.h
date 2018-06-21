#pragma once

#include "../BioNet/BioNode.h"


#include <string>
using std::string;

class BioList {
private:
	BioNode * head;
	bool doSearch(string name, BioNode* start);
public:
	BioList(float weight, string name);
	~BioList();
	bool search(string name) { doSearch(name, head); }
	void clear();


};
