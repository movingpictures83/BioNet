#include "BioAdjList.h"

void BioAdjList::setEdge(int x, int y, float w)
{
	auto * current = &network[x];
	while (current)
	{
	
	}
	
}

void BioAdjList::setEdge(string, string, float)
{
}

float BioAdjList::getEdge(int a , int b)
{
	return network[a].getWeight(network[b].getName());
}

float BioAdjList::getEdge(string a , string b)
{
	for (int i = 0; i < network.size(); i++) {
		if (strcmp(network[i].getName().c_str(), a.c_str()) == 0)
			return network[i].getWeight(b);
	}
	return 0.0f;
}

void BioAdjList::setNode(int i , string s)
{
	
}

string BioAdjList::getNode(int i)
{
	return network[i].getName();
}
