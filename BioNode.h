#pragma once

#include <string>
using std::string;

class BioNode {
private:
	float weight;
	string name;
	BioNode* next;

public:
	BioNode(const float f, const string &i, BioNode* n) { weight = f; name = i; next = n; }
	string getName() { return name; }
	void setName(const string &n) { name = n; }
	BioNode* getNext() { return next; }
	void setWeight(const float f) { weight = f; }
	float getWeight() { return weight; }
	void setNext(BioNode* n) { next->next = n; }
};
