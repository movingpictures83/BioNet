#pragma once

#include "../BioNet/BioNode.h"


#include <string>
using std::string;

class BioList {
private:
	string name;
	BioNode * head;
	bool doSearch(string name, BioNode* start);
public:
	BioList(float weight, string name);
	~BioList();
	bool search(string name) { doSearch(name, head); }
	bool setWeight(string name, float weight);
	BioNode* insertFront(float weight, string name);
	void deleteNode(string name);
	void clear();
	string getName();

};
