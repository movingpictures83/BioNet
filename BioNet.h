#ifndef BIONET_H
#define BIONET_H

#include <string>
#include <vector>
#include <iostream>
#include "BioAdj.h"
#include "BioAdjMat.h"
//#include "BioAdjList.h"
using std::string;
using std::pair;
using std::vector;
using std::ostream;

// Code comming from BioNet.cpp
#include "BioNetException.h"
#include <numeric>
#include <algorithm>
#include <limits>
#include <set>
#include <functional>
//#include "BioAdjFactory.h"
#include "BioNetException.h"

using std::to_string;
using std::accumulate;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::set;
using std::exception;
using std::cerr;
using std::endl;


template<typename T>
class BioNet {
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT EINSTEIN
   //
   //
private:
	T minweight;
	T maxweight;
	BioAdj<T>* network;
	bool directed;
	string networkType;

public:
	BioNet();
	BioNet(const T, const T, const bool=false, const string& = BioAdjMat<T>::NetworkType());
	BioNet(const BioNet<T>&);
	BioNet(BioNet<T>&&);
	~BioNet();

	void setRange(const T, const T);
	void setEdge(const int, const int, const T);
	void setNode(const int, const string &n);
	void deleteEdge(const int, const int);
	void deleteEdge(const string &l, const string &r);

	const T shortestPath(const int, const int) const;
	void resize(const int size);
	void clear();
	
	// Accessors
	const T getEdge(const int, const int) const;
	const string getNode(const int) const;
	const T getMinWeight() const { return minweight; }
	const T getMaxWeight() const { return maxweight; }
	const std::string & getNetworkType() const { return networkType; }

	//Operators
	const string & operator[](size_t index) const { return network->getNode(index); };
	const T operator()(size_t lhs, size_t rhs) const { return network->getEdge(lhs, rhs); };
	const T operator()(const string & lhs, const string & rhs) const { return network->getEdge(lhs, rhs); };

	BioNet<T> operator+(const string&)const;
	const BioNet<T>& operator +=(const string&) const;

	const BioNet<T>& operator=(const BioNet& rhs);

	ostream& operator<<(ostream&) const;

   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT TURING
   //
   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // AFTERNOON COHORT KNUTH
   //
   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // AFTERNOON COHORT DIJKSTRA
   //
	void convertToType(const string&);
	const T degree(const int) const;
	//void reserve(size_t);
	const size_t size() const;
	const int numberOfEdges() const;

   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

};


// Moving All templated implementation to the Header so it works as expected

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MORNING COHORT EINSTEIN
//
//

template<typename T>
BioNet<T>::BioNet() : BioNet(-1.0, 1.0) {
	// for now start a default unconnected network with default range
	// The following code only creates a local version variable - Corrected by Dijkstra Team
	// BioNet(-1.0, 1.0);
}

template<typename T>
BioNet<T>::BioNet(const T min, const T max, const bool isDir, const string& type) {

	setRange(min, max);
	directed = isDir;
	networkType = type;
	try {
		network = 0; //BioAdjFactory::create(networkType);
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		network = 0; // BioAdjFactory::create(BioAdjMat::NetworkType());
	}
	network = 0; //BioAdjFactory::create(networkType);
}

template<typename T>
BioNet<T>::BioNet(const BioNet<T>& rhs) {
	setRange(rhs.minweight, rhs.maxweight);
	directed = rhs.directed;
	networkType = rhs.networkType;
	try {
		network = BioAdjFactory::create(networkType);
		*network = *rhs.network;
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		BioAdjFactory::create(BioAdjMat::NetworkType());
		*network = *rhs.network;
	}
}

template<typename T>
BioNet<T>::BioNet(BioNet<T>&& rhs) {
	setRange(rhs.minweight, rhs.maxweight);
	directed = rhs.directed;
	std::swap(networkType, rhs.networkType);
	network = std::move(rhs.network);
	rhs.~BioNet();
}

template<typename T>
BioNet<T>::~BioNet() {
	if (network != nullptr)
		delete network;
}

template<typename T>
void BioNet<T>::setRange(const T min, const T max) {
	if (min > max)
	{
		throw BioNetException("mininum value is larger than maximum value");
	}
	minweight = min;
	maxweight = max;
}

template<typename T>
void BioNet<T>::setEdge(const int i, const int j, const T w) {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network->size())
		throw BioNetException("Node is not in the matrix range");

	if (w < minweight || w > maxweight)
		throw BioNetException("Weight is not in the minWeight and maxWeight");

	network->setEdge(i, j, w);
	if (!directed) {
		network->setEdge(i, j, w);
	}
}

template<typename T>
void BioNet<T>::setNode(const int i, const string& n) {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");

	network->setNode(i, n);
}

// Accessors
template<typename T>
const T BioNet<T>::getEdge(const int i, const int j) const {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network->size())
		throw BioNetException("Node is not in the matrix range");
	return network->getEdge(i, j);
}

template<typename T>
const string BioNet<T>::getNode(const int i) const {
	if (i < 0 || i > network->size())  // corrected from network.size()
		throw BioNetException("Node is not in the matrix range");

	return network->getNode(i);
}

template<typename T>
void BioNet<T>::resize(const int size) {

	if (size <= 0)
		throw BioNetException("resize value is invalid");
	network->resize(size);
}


template<typename T>
void BioNet<T>::clear() {
	//network->clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MORNING COHORT TURING
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AFTERNOON COHORT KNUTH
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AFTERNOON COHORT DIJKSKTRA
//

template<typename T>
void BioNet<T>::convertToType(const string& type)
{
	try {
		auto old = network;
		network = BioAdjFactory::create(type);
		network->resize(old->size());
		for (int i{ 0 }; i < network->size(); i++)
		{
			network->setNode(i, old->getNode(i));
			for (int j{ 0 }; j < network->size(); j++)
				network->setEdge(i, j, old->getEdge(i, j));
		}
		networkType = type;
		delete old;
	}
	catch (exception e)
	{
		cerr << e.what() << "Error converting network to type " + type + ".\n" << endl;
	}

}

template<typename T>
const size_t BioNet<T>::size() const
{
	return network->size();
}


/*
template<typename T>
void BioNet<T>::reserve(size_t size)
{
if (size < 0)
throw BioNetException("Size is negative!");
network->reserve(size);
}*/

template<typename T>
const T BioNet<T>::degree(const int index) const {
	if (index < 0 || index >= network->size())
		throw BioNetException("Index out of bounds!");
	return network->degree(index);
}

template<typename T>
const T BioNet<T>::shortestPath(const int start, const int end) const {

	if (start < 0 || start > network->size())
		throw BioNetException("Start node is not in the matrix range");

	if (end < 0 || end > network->size())
		throw BioNetException("End node is not in the matrix range");

	float negativeEdges = 0.0;

	if (minweight < 0)
		negativeEdges = minweight * -1 + 1;

	vector<float> dist(network->size(), std::numeric_limits<float>::max());

	vector<int> prev(network->size(), -1);

	set<int> vertexSet;

	dist[start] = 0;

	for (int i = 0; i < network->size(); i++)
		vertexSet.insert(i);

	auto distFunct = bind([](vector<float>& d, int x, int y) {return d[x] < d[y]; }, dist, _1, _2);

	while (vertexSet.size())
	{
		auto current = *std::min_element(vertexSet.begin(), vertexSet.end(), distFunct);

		if (current == end)
			break;

		vertexSet.erase(current);

		for (int i = 0; i < network[current].size(); i++)
		{
			if (network->getEdge(current, i))
			{
				auto weight = negativeEdges ? network->getEdge(current, i) + negativeEdges : network->getEdge(current, i);

				auto alt = dist[current] + weight;

				if (alt < dist[i])
				{
					dist[i] = alt;
					prev[i] = current;
				}
			}
		}
	}

	if (dist[end] == std::numeric_limits<float>::max())
		throw BioNetException("No path found from start to end nodes.");

	auto result = dist[end];
	auto current = end;
	if (negativeEdges)
		while (prev[current] != -1)
		{
			current = prev[current];
			result -= negativeEdges;
		}
	return result;
}

template<typename T>
const int BioNet<T>::numberOfEdges() const {
	int x = network->numberOfEdges();
	if (!directed)
		x = x / 2;
	return x;
}

template<typename T>
void BioNet<T>::deleteEdge(const int lval, const int rval) {
	// not implemented
	//network->deleteEdge(lval, rval);
}

template<typename T>
void BioNet<T>::deleteEdge(const string& lstr, const string& rstr) {
	// not implemented
	//network->deleteEdge(lstr, rstr);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
const BioNet<T>& BioNet<T>::operator=(const BioNet<T>& rhs)
{
	BioNet copy(rhs);
	std::swap(copy, *this);
	return *this;
}

template<typename T>
BioNet<T> BioNet<T>::operator+(const string& rhs) const
{
	BioNet retVal(*this);
	retVal.resize(network->size() + 1);
	retVal.setNode(network->size() - 1, rhs);
	return retVal;
}

template<typename T>
const BioNet<T>& BioNet<T>::operator+=(const string& rhs) const
{
	network->resize(network->size() + 1);
	network->setNode(network->size() - 1, rhs);
	return *this;
}

template<typename T>
ostream& BioNet<T>::operator<<(ostream& os) const
{
	os << network;
	return os;
}


#endif



