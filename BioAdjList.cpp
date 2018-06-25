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
	auto oldName = network[i].getName();
	network[i].setName(s);
	for (int z = 0; z < network.size(); z++) {
		if (z != i)
		 network[z].setEdgeName(oldName, s);
	}
}

string BioAdjList::getNode(int i)
{
	return network[i].getName();
}

float BioAdjList::degree(int x)
{
	auto node = network[x].front();
	auto result = 0.0f;
	while (node)
		result += node->getWeight();
	return result;
}

BioAdjList BioAdjList::operator+(const string nodename)
{
	BioAdjList list = *this;
	list += nodename;
	return list;
}

BioAdjList BioAdjList::operator=(const BioAdjList & rhs)
{
	return BioAdjList(rhs);
}

const BioAdjList& BioAdjList::operator+=(const string nodename)
{
	
	return *this;
}
