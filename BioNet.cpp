#include "stdafx.h"
#include "BioNet.h"
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <limits>

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
	// for now start a default unconnected network
	for (int i = 0; i < NETWORK_SIZE; i++) {
		names[i] = to_string(i);
		for (int j = 0; j < NETWORK_SIZE; j++) {
			network[i][j] = 0.0f;
		}
	}
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
float BioNet::degree(int index)
{
	return std::accumulate(network[index], network[index] + NETWORK_SIZE, 0.0f);
}

float BioNet::shortestPath(int start, int end)
{
	vector<float> dist(NETWORK_SIZE, std::numeric_limits<float>::max());

	vector<int> prev(NETWORK_SIZE, -1);

	vector<float> queue(NETWORK_SIZE, std::numeric_limits<float>::max());

	std::make_heap(queue.begin(), queue.end());

	while (queue.size())
	{

	}

}



int BioNet::numberOfEdges()
{
	int edges = 0;

	for (int i = 0; i < NETWORK_SIZE; i++)
		for (int j = directed ? 0:i ; j < NETWORK_SIZE; j++)
		{
			if (network[i][j] > -FLT_EPSILON && network[i][j] < FLT_EPSILON)
				edges++;
		}
	return edges;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////



