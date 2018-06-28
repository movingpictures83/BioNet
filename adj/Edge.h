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
	///Construct an edge given a weight, name, and a pointer to next edge
	Edge(const T w, const string &i, Edge<T>* n) { weight = w; name = i; next = n; }
	/// Returns the name
	string getName() { return name; }
	/// Updates the name
	void setName(const string &n) { name = n; }
	/// Gets a pointer to the next edge
	Edge* getNext() { return next; }
	///Update the weight
	void setWeight(const T w) { weight = w; }
	///Get the weight of the edge.
	T getWeight() { return weight; }
	///Updates the next pointer.
	void setNext(Edge<T>* n) { next->next = n; }
};
