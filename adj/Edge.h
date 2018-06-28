#pragma once

#include <string>
using std::string;

template<typename T>
class Edge {
private:
	T weight;
	string name;
	Edge<T>* next;

public:
	Edge(const T w, const string &i, Edge<T>* n) { weight = w; name = i; next = n; }
	string getName() { return name; }
	void setName(const string &n) { name = n; }
	Edge* getNext() { return next; }
	void setWeight(const float w) { weight = w; }
	T getWeight() { return weight; }
	void setNext(Edge<T>* n) { next->next = n; }
};
