#include "BioAdjList.h"
#include "BioNetException.h"

void BioAdjList::setEdge(const int x,const int y, float w)
{
	network[x].setWeight(network[y].getName(), w);
}

void BioAdjList::setEdge(const string x, const  string y, float w)
{
	int i = 0;
	while (network[i].getName() != x)
		i++;
	network[i].setWeight(y, w);
}


const float BioAdjList::getEdge(const int x, const int y)
{
	return network[x].getWeight(network[y].getName());
}

const float BioAdjList::getEdge(const string a , const string b)
{
	for (int i = 0; i < network.size(); i++) {
		if (strcmp(network[i].getName().c_str(), a.c_str()) == 0)
			return network[i].getWeight(b);
	}
	return 0.0f;
}

void BioAdjList::setNode(const int i , const string s)
{
	auto oldName = network[i].getName();
	network[i].setName(s);
	for (int z = 0; z < network.size(); z++) {
		if (z != i)
		 network[z].setEdgeName(oldName, s);
	}
}

const string BioAdjList::getNode(const int i)
{
	return network[i].getName();
}

float BioAdjList::degree(const int i)
{
	if (i < 0 || i >= network.size())
		throw BioNetException("Index out of bounds!");
	
	float degree = 0.0f;
	BioNode* temp = network[i].getHead();
	while (temp != nullptr)
		degree += temp->getWeight();
	return degree;
}
int BioAdjList::numberOfEdges()
{
	int edge = 0;
	for (int i = 0; i < network.size(); i++)
	{
		BioNode* temp = network[i].getHead();
		while (temp != nullptr)
		{
			if (temp->getWeight < -FLT_EPSILON || temp->getWeight > FLT_EPSILON)
				edge++;
		}
	}
	return edge;
}
void BioAdjList::resize(const int size)
{
	if (size <= 0)
		throw BioNetException("resize value is invalid");
	network.resize(size);
}