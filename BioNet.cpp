#include "BioNet.h"
#include "BioNetException.h"
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <limits>
#include <set>
#include <functional>
#include "BioAdjFactory.h"
#include "BioNetException.h"
#include "BioAdjMat.h"
#include "BioAdjList.h"

using std::to_string;
using std::accumulate;
using std::vector;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::set;
using std::exception;
using std::cerr;
using std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MORNING COHORT EINSTEIN
//
//

template<class T>
BioNet<T>::BioNet() : BioNet(-1.0, 1.0){
	// for now start a default unconnected network with default range
	// The following code only creates a local version variable - Corrected by Dijkstra Team
	// BioNet(-1.0, 1.0);
}

template<class T>
BioNet<T>::BioNet(const T min, const T max, const bool isDir, const string &type) {

	setRange(min, max);
	directed = isDir;
	networkType = type;
	try {
		network = BioAdjFactory::create(networkType);
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		network = BioAdjFactory::create(BioAdjMat::NetworkType());
	}
	network = BioAdjFactory::create(networkType);
}

template<class T>
BioNet<T>::BioNet(const BioNet<T>& rhs){
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

template<class T>
BioNet<T>::BioNet(BioNet<T>&& rhs) {
	setRange(rhs.minweight, rhs.maxweight);
	directed = rhs.directed;
	std::swap(networkType, rhs.networkType);
	network = std::move(rhs.network);
	rhs.~BioNet();
}

template<class T>
BioNet<T>::~BioNet() {
	if(network != nullptr)
		delete network;
}

template<class T>
void BioNet<T>::setRange(const T min, const T max) {
	if (min > max)
	{
		throw BioNetException("mininum value is larger than maximum value");
	}
	minweight = min;
	maxweight = max;
}


template<class T>
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

template<class T>
void BioNet<T>::setNode(const int i, const string &n) {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");
	
	network->setNode(i, n);
}

// Accessors
template<class T>
const T BioNet<T>::getEdge(const int i, const int j) const {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network->size())
		throw BioNetException("Node is not in the matrix range");
	return network->getEdge(i, j);
}

template<class T>
const string BioNet<T>::getNode(const int i) const {
	if (i < 0 || i > network->size())  // corrected from network.size()
		throw BioNetException("Node is not in the matrix range");

	return network->getNode(i);
}

template<class T>
void BioNet<T>::resize(const int size) {

	if (size <= 0)
		throw BioNetException("resize value is invalid");
	network->resize(size);
}


template<class T>
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

template<class T>
void BioNet<T>::convertToType(const string &type)
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

template<class T>
const size_t BioNet<T>::size() const
{
	return network->size();
}


/*
template<class T>
void BioNet<T>::reserve(size_t size)
{
	if (size < 0)
		throw BioNetException("Size is negative!");
	network->reserve(size);
}*/

template<class T>
const T BioNet<T>::degree(const int index) const {  //converting network to vectors - EINSTEIN
	if (index < 0 || index >= network->size())
		throw BioNetException("Index out of bounds!");
	return network->degree(index);
}

template<class T>
const T BioNet<T>::shortestPath(const int start, const int end) const {  //converting network to vectors - EINSTEIN

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
				auto weight = negativeEdges ? network->getEdge(current,i) + negativeEdges : network->getEdge(current,i);

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

template<class T>
const int BioNet<T>::numberOfEdges() const {  //converting network to vectors - EINSTEIN
	int x = network->numberOfEdges();
	if (!directed)
		x = x / 2;
	return x;
}

template<class T>
void BioNet<T>::deleteEdge(const int lval, const int rval) {
	// not implemented
	//network->deleteEdge(lval, rval);
}

template<class T>
void BioNet<T>::deleteEdge(const string &lstr, const string &rstr) {
	// not implemented
	//network->deleteEdge(lstr, rstr);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
const BioNet<T>& BioNet<T>::operator=(const BioNet<T>& rhs)
{
	BioNet copy(rhs);
	std::swap(copy, *this);
	return *this;
}

template<class T>
BioNet<T> BioNet<T>::operator+(const string& rhs) const
{
	BioNet retVal(*this);
	retVal.resize(network->size() + 1);
	retVal.setNode(network->size() - 1, rhs);
	return retVal;
}

template<class T>
const BioNet<T>& BioNet<T>::operator+=(const string& rhs) const
{
	network->resize(network->size() + 1);
	network->setNode(network->size() - 1, rhs);
	return *this;
}

template<class T>
ostream& BioNet<T>::operator<<(ostream& os) const
{
	os << network;
	return os;
}