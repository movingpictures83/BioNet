#pragma once

#include <string>
using std::string;

class BioNode {
private:
	float weight;
	string name;
	BioNode* next;

public:
	BioNode(float f, string i, BioNode* n) { weight = f; name = i; next = n; }
	string getName() { return name; }
	BioNode* getNext() { return next; }
	void setWeight(float f) { weight = f; }
	float getWeight() { return weight; }
	void setNext(BioNode* n) { next->next = n; }
};
