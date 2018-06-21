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

float BioAdjList::getEdge(int, int)
{
	return 0.0f;
}

float BioAdjList::getEdge(string, string)
{
	return 0.0f;
}

void BioAdjList::setNode(int, string)
{
}

string BioAdjList::getNode(int)
{
	return string();
}
