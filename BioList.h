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
	BioList(const float weight, const string& name);
	~BioList();
	bool search(const string& name) { doSearch(name, head); }
	bool setWeight(const string& name, const float weight);
	string getName() const;
	void setName(const string&);
	void setEdgeName(const string&, const string&);
	float getWeight(const string& name) const;
	BioNode* insertFront(const float weight, const string& name);
	void deleteNode(const string& name);
	void clear();
	BioNode* front() const { return head; } ;
};
