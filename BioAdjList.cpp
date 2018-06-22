#include "BioAdjList.h"

void BioAdjList::setEdge(int x, int y, float w)
{
	network[x].setWeight(network[y].getName(), w);
}

void BioAdjList::setEdge(string x, string y, float w)
{
	int i = 0;
	while (network[i].getName() != x)
		i++;
	network[i].setWeight(y, w);
}

float BioAdjList::getEdge(int x, int y)
{
	return network[x].getWeight(network[y].getName());
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
