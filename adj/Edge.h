#pragma once

#include <string>
using std::string;

/// A class to represent the edges between node in a network
/**
A templated class set up to act as connection between nodes with weights
*/
template<typename T>
class Edge {
private:
	/// The weight of an edge
	T weight;
	/// Name of the edge
	string name;
	/// Pointer to the next edge
	Edge<T>* next;

public:
	///Construct an edge given a weight, name, and a pointer to next edge
	/**
	@param w Weight of the edge
	@param i Name of the edge
	@param n Next edge pointer
	*/
	Edge(const T w, const string &i, Edge<T>* n) { weight = w; name = i; next = n; }
	
	/// Returns the name
	/**
	@return Name of the edge
	*/
	string getName() { return name; }

	/// Updates the name
	/**
	@param n New name for the edge
	*/
	void setName(const string &n) { name = n; }

	/// Gets a pointer to the next edge
	/**
	@return Next Edge pointer
	*/
	Edge* getNext() { return next; }

	///Update the weight
	/**
	@param w New weight for the edge
	*/
	void setWeight(const T w) { weight = w; }

	///Get the weight of the edge.
	/**
	@return Weight of the edge
	*/
	T getWeight() { return weight; }

	///Updates the next pointer.
	/**
	@param n Set the next Edge pointer
	*/
	void setNext(Edge<T>* n) { next->next = n; }
};
