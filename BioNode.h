#pragma once

#include <string>
using std::string;

template<class T>
class BioNode {
private:
	T weight;
	string name;
	BioNode<T>* next;

public:
	BioNode(const T w, const string &i, BioNode<T>* n) { weight = w; name = i; next = n; }
	string getName() { return name; }
	void setName(const string &n) { name = n; }
	BioNode* getNext() { return next; }
	void setWeight(const float w) { weight = w; }
	T getWeight() { return weight; }
	void setNext(BioNode<T>* n) { next->next = n; }
};
