#pragma once
#include "BioAdj.h"
#include "BioList.h"
#include "BioNetException.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Register.h"
using std::vector;
using std::string;
using std::map;
using std::find_if;

template <typename T>
class BioAdjList : public BioAdj<T>
{
public:
	vector<BioList<T>> network;
	static Register reg;
public:
	static Adj* make() 
	{
		return new BioAdjList<T>();
	}

	static const string& NetworkType()
	{
		static const string network = "BioAdjLst";
		return network;
	}

	BioAdjList(const BioAdjList& copy)
	{
		network = vector<BioList<T>>(copy.network.size());
		for (size_t i = 0; i < copy.network.size(); i++)
			network[i] = BioList<T>(copy.network[i]);
	}

	BioAdjList(int i = 5){
		network.resize(i);
	}
	~BioAdjList() {}

	void setEdge(const int x, const int y, const T w)
	{
		network[x].setWeight(network[y].getName(), w);
	}

	void setEdge(const string& x, const string& y, const T w)
	{
		int i = 0;
		while (network[i].getName() != x)
			i++;
		network[i].setWeight(y, w);
	}

	T getEdge(const int x, const int y) const
	{
		return network[x].getWeight(network[y].getName());
	}

	T getEdge(const string& a, const string& b) const
	{
		for (int i = 0; i < network.size(); i++) {
			if (strcmp(network[i].getName().c_str(), a.c_str()) == 0)
				return network[i].getWeight(b);
		}
		return T();
	}
	
	void setNode(const int i, const string& s)
	{
		auto oldName = network[i].getName();
		network[i].setName(s);
		for (int z = 0; z < network.size(); z++) {
			if (z != i)
				network[z].setEdgeName(oldName, s);
		}
	}

	string getNode(const int i) const
	{
		return network[i].getName();
	}

	int size() const
	{
		return network.size();
	}

	T degree(const int x) const
	{
		auto node = network[x].front();
		auto result = 0.0f;
		while (node)
			result += node->getWeight();
		return result;
	}

	int numberOfEdges() const
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

	void resize(const int newSize)
	{
		auto sizeDifference = newSize - network.size();

		if (sizeDifference < 0) //Last sizeDifference nodes will be destroyed, so the other nodes that have edges to them must be cleaned.
		{
			sizeDifference *= -1;
			auto networkSize = network.size();
			for (size_t i = networkSize - sizeDifference; i < networkSize; i++)
			{
				auto name = network[i].getName();
				for (size_t j = 0; j < networkSize - sizeDifference; j++)
					network[j].deleteEdge(name);
			}
		}

		network.resize(newSize);
	}

	int findNodeIndex(const string& name) const
	{
		for (int i = 0; i < network.size(); i++)
			if (network[i].getName() == name)
				return i;
		throw BioNetException("Node not found.");
	}

	void deleteEdge(const string & x, const string & y)
	{
		network[findNodeIndex(x)].deleteEdge(y);
	}

	void deleteEdge(int x, int y)
	{
		network[x].deleteEdge(network[y].getName());
	}

	void deleteNode(const string & name)
	{
		auto index = findNodeIndex(name);
		for (size_t i = 0; i < network.size(); i++)
			if (i != index)
				network[i].deleteEdge(name);
		network.erase(network.begin() + index);
	}

	void deleteNode(int index)
	{
		auto name = network[index].getName();
		for (size_t i = 0; i < network.size(); i++)
			if (i != index)
				network[i].deleteEdge(name);
		network.erase(network.begin() + index);
	}

	const BioAdjList& operator+=(const string nodename)
	{
		network.push_back(BioList<T>(0, nodename));
		return *this;
	}

	BioAdjList operator+(const string nodename)
	{
		BioAdjList list = *this;
		list += nodename;
		return list;
	}

	const BioAdjList& operator-=(const string nodename)
	{
		deleteNode(nodename);
		return *this;
	}

	BioAdjList operator-(const string nodename)
	{
		BioAdjList list = *this;
		list -= nodename;
		return list;
	}

	BioAdjList operator=(const BioAdjList &rhs)
	{
		return BioAdjList(rhs);
	}

	BioAdjList operator*(const T weight)
	{
		BioAdjList list = *this;
		for (int i = 0; i < list.network.size(); i++)
			list.network[i] *= weight;
		return list;
	}

	BioAdjList operator/(const T weight)
	{
		BioAdjList list = *this;
		for (int i = 0; i < list.network.size(); i++)
			list.network[i] /= weight;
		return list;
	}

	const BioAdjList& operator*=(const T weight)
	{
		for (int i = 0; i < network.size(); i++)
			network[i] *= weight;
		return *this;
	}

	const BioAdjList& operator/=(const T weight)
	{
		for (int i = 0; i < network.size(); i++)
			network[i] /= weight;
		return *this;
	}
};

template<>
Register BioAdjList<int>::reg = Register("BioAdjListInt", &BioAdjList<int>::make); 
template<>
Register BioAdjList<float>::reg = Register("BioAdjListFloat", &BioAdjList<float>::make); 
template<>
Register BioAdjList<double>::reg = Register("BioAdjListDouble", &BioAdjList<double>::make);