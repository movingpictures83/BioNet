#include "BioNet.h"
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <limits>
#include <set>
#include <functional>

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
	minweight = min;
	maxweight = max;
}

void BioNet::setEdge(int i, int j, float w) {
	network[i][j] = w;
}

void BioNet::setNode(int i, string n) {
	names[i] = n;
}
// Accessors
float BioNet::getEdge(int i, int j) { 
	return network[i][j]; 
}

string BioNet::getNode(int i) {
	return names[i];
}

void BioNet::resize(int size) {
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

	float negativeEdges = 0.0;

	if (minweight < 0)
		negativeEdges = minweight * -1 + 1;

	vector<float> dist(network.size(), std::numeric_limits<float>::max());

	vector<int> prev(network.size(), -1);

	set<int> vertexSet;

	dist[start] = 0;

	for (int i = 0; i < network.size(); i++)
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

	if (dist[end] != std::numeric_limits<float>::max())
	{
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



