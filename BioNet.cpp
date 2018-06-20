#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <limits>
#include "BioNet.h"
#include "BioNetException.h"

using std::to_string;
using std::accumulate;
using std::make_heap;
using std::vector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MORNING COHORT EINSTEIN
//
//
BioNet::BioNet() : BioNet(-1.0, 1.0){
	// for now start a default unconnected network with default range
	// The following code only creates a local version variable - Corrected by Dijkstra Team
	// BioNet(-1.0, 1.0);
}

BioNet::BioNet(float min, float max, bool dir) {

	setRange(min, max);
	directed = dir;
	// Converting network/names to vectors, no initialization needed
	/*// for now start a default unconnected network
	for (int i = 0; i < NETWORK_SIZE; i++) {
		names[i] = to_string(i);
		for (int j = 0; j < NETWORK_SIZE; j++) {
			network[i][j] = 0.0f;
		}
	}*/
}

BioNet::~BioNet() {
}

void BioNet::setRange(float min, float max) {
	if (min > max)
	{
		throw BioNetException("mininum value is larger than maximum value");
	}
	minweight = min;
	maxweight = max;
}

void BioNet::setEdge(int i, int j, float w) {
	if (i < 0 || i > network.size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network.size())
		throw BioNetException("Node is not in the matrix range");

	if (w < minweight || w > maxweight)
		throw BioNetException("Weight is not in the minWeight and maxWeight");

	network[i][j] = w;
}

void BioNet::setNode(int i, string n) {
	if (i < 0 || i > network.size())
		throw BioNetException("Node is not in the matrix range");

	names[i] = n;
}
// Accessors
float BioNet::getEdge(int i, int j) { 
	if (i < 0 || i > network.size())
		throw BioNetException("Node is not in the matrix range");

	if (j < 0 || j > network.size())
		throw BioNetException("Node is not in the matrix range");

	return network[i][j];
}

string BioNet::getNode(int i) {
	if (i < 0 || i > network.size())
		throw BioNetException("Node is not in the matrix range");

	return names[i];
}

void BioNet::resize(int size) {

	if (size <= 0)
		throw BioNetException("resize value is invalid");
	network.resize(size);
	for (int i = 0; i < network.size(); i++) {
		network[i].resize(size);
	}

	names.resize(size);
}

void BioNet::clear() {
	network.clear();
	names.clear();
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
	return network.size();
}

void BioNet::reserve(size_t size)
{
	names.resize(size);
	network.reserve(size);
	for (int i{ 0 }; i < size; i++)
		network.emplace_back(size);
}

float BioNet::degree(int index) {  //converting network to vectors - EINSTEIN
	return std::accumulate(network[index].begin(), network[index].end(), 0.0f);
}


float BioNet::shortestPath(int start, int end) {  //converting network to vectors - EINSTEIN
	vector<float> dist(network.size(), std::numeric_limits<float>::max());

	vector<int> prev(network.size(), -1);

	vector<float> queue(network.size(), std::numeric_limits<float>::max());

	std::make_heap(queue.begin(), queue.end());

	while (queue.size())
	{

	}
	return 0.0;
}



int BioNet::numberOfEdges() {  //converting network to vectors - EINSTEIN
	int edges = 0;

	for (int i = 0; i < network.size(); i++)
		for (int j = directed ? 0:i ; j < network.size(); j++)
		{
			if (network[i][j] > -FLT_EPSILON && network[i][j] < FLT_EPSILON)
				edges++;
		}
	return edges;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////



