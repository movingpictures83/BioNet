#include "BioAdjList.h"

void BioAdjList::setEdge(const int x, const int y, const float w)
{
	network[x].setWeight(network[y].getName(), w);
}

void BioAdjList::setEdge(const string& x, const string& y, const float w)
{
	int i = 0;
	while (network[i].getName() != x)
		i++;
	network[i].setWeight(y, w);
}


float BioAdjList::getEdge(int x, int y) const
{
	return network[x].getWeight(network[y].getName());
}

float BioAdjList::getEdge(const string& a , const string& b) const
{
	for (int i = 0; i < network.size(); i++) {
		if (strcmp(network[i].getName().c_str(), a.c_str()) == 0)
			return network[i].getWeight(b);
	}
	return 0.0f;
}

void BioAdjList::setNode(const int i , const string& s)
{
	auto oldName = network[i].getName();
	network[i].setName(s);
	for (int z = 0; z < network.size(); z++) {
		if (z != i)
		 network[z].setEdgeName(oldName, s);
	}
}

string BioAdjList::getNode(const int i) const
{
	return network[i].getName();
}

int BioAdjList::size() const
{
	return 0;
}

float BioAdjList::degree(const int x) const
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

BioAdjList::BioAdjList(const BioAdjList& copy) {

}


const BioAdjList& BioAdjList::operator+=(const string nodename)
{
	
	return *this;
}

int BioAdjList::numberOfEdges() const
{
	auto result = 0;
	for (size_t i = 0; i < network.size(); i++)
	{
		auto node = network[i].front();
		while (node)
			result++;
	}
	return result;
}

void BioAdjList::resize(int newSize)
{
	auto sizeDifference = newSize - network.size();

	if(sizeDifference < 0) //Last sizeDifference nodes will be destroyed, so the other nodes that have edges to them must be cleaned.
	{
		sizeDifference *= -1;
		auto networkSize = network.size();
		for (size_t i = networkSize - sizeDifference; i < networkSize; i++)
		{
			auto name = network[i].getName();
			for (size_t j = 0; j < networkSize - sizeDifference; j++)
				network[j].deleteNode(name);
		}
	}

	network.resize(newSize);
}

int BioAdjList::findNodeIndex(const string &) const
{
	return 0;
}

void BioAdjList::deleteEdge(const string &, const string &)
{
}

void BioAdjList::deleteEdge(int, int)
{
}

void BioAdjList::deleteNode(const string &)
{
}

void BioAdjList::deleteNode(int i) {

}
