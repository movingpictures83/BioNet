#pragma once

#include <string>
using std::string;

template<typename T>
class BioEdge {
private:
	T weight;
	string name;
	BioEdge<T>* next;

public:
	BioEdge(const T w, const string &i, BioEdge<T>* n) { weight = w; name = i; next = n; }
	string getName() { return name; }
	void setName(const string &n) { name = n; }
	BioEdge* getNext() { return next; }
	void setWeight(const float w) { weight = w; }
	T getWeight() { return weight; }
	void setNext(BioEdge<T>* n) { next->next = n; }
};
