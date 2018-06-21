#include "BioNet.h"
#include "BioNetException.h"
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <limits>
#include <set>
#include <functional>
#include "BioNet.h"
#include "BioNetException.h"

using std::to_string;
using std::accumulate;
using std::vector;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::set;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MORNING COHORT EINSTEIN
//
//

BioNet::BioNet() : BioNet(-1.0, 1.0){
	// for now start a default unconnected network with default range
	// The following code only creates a local version variable - Corrected by Dijkstra Team
	// BioNet(-1.0, 1.0);
}


BioNet::BioNet(float min, float max, bool dir, bool list) {

	setRange(min, max);
	directed = dir;

	if (list)
		network = new BioAdjList();
	else
		network = new BioAdjMat();
	// Converting network/names to vectors, no initialization needed
}


BioNet::~BioNet() {
	delete network;
}

std::pair<int, int> getPair() { return {1, 1 }; }


void BioNet::setRange(float min, float max) {
	if (min > max)
	{
		throw BioNetException("mininum value is larger than maximum value");
	}
	minweight = min;
	maxweight = max;
}


void BioNet::setEdge(int i, int j, float w) {
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

	
void BioNet::setNode(int i, string n) {
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");
	
	network->setNode(i, n);
}
// Accessors

float BioNet::getEdge(int i, int j) { 
	//Converting to a Network Class
	if (i < 0 || i > network->size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network->size())
		throw BioNetException("Node is not in the matrix range");
	return network->getEdge(i, j);
}


string BioNet::getNode(int i) {
	if (i < 0 || i > network->size())  // corrected from network.size()
		throw BioNetException("Node is not in the matrix range");

	return network->getNode(i)
}


void BioNet::resize(int size) {

	if (size <= 0)
		throw BioNetException("resize value is invalid");
	network->resize(size);
}


void BioNet::clear() {
	network->clear();
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


size_t BioNet::size()
{
	return network->size();
}


/*void BioNet::reserve(size_t size)
{
	if (size < 0)
		throw BioNetException("Size is negative!");
	network->reserve(size);
}*/


float BioNet::degree(int index) {  //converting network to vectors - EINSTEIN
	if (index < 0 || index >= network->size())
		throw BioNetException("Index out of bounds!");
	network->degree(index);
}


float BioNet::shortestPath(int start, int end) {  //converting network to vectors - EINSTEIN

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
			if (network[current][i])
			{
				auto weight = negativeEdges ? network[current][i] + negativeEdges : network[current][i];

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



int BioNet::numberOfEdges() {  //converting network to vectors - EINSTEIN
	return network->numberOfEdges();
}

void BioNet::deleteEdge(int lval, int rval)
{
	network->deleteEdge(lval, rval);
}

void BioNet::deleteEdge(stringl lstr, string rstr)
{
	network->deleteEdge(lstr, rstr);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////



