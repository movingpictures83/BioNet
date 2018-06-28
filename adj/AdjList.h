#pragma once
#include "Adj.h"
#include "List.h"
#include "Exception.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Register.h"
using std::vector;
using std::string;
using std::map;
using std::find_if;

namespace BioNet {
	/// An Adjacency List for BioNet
	/**
		AdjList impements an adjacency list to represent the Bionet network.
		It consists of a vector of BioList, each element representing a node in the network with
		its corresponding edges.
	*/
	template <typename T>
	class AdjList : public Adj<T>
	{
	public:
		vector<BioList<T>> network;
		static Register reg;
	public:
		/// Used for factory Construction
		/**
		@return A new, dynamic instance of AdjList
		*/
		static GenericAdj* make()
		{
			return new AdjList<T>();
		}
		/// Specifies the type of the network used to register instances in the factory.
		/**
		@return Type name of the network.
		*/
		static const string& NetworkType()
		{
			static const string network = "BioAdjLst";
			return network;
		}
		/// AdjList Copy constructor
		AdjList(const AdjList& copy)
		{
			network = vector<BioList<T>>(copy.network.size());
			for (size_t i = 0; i < copy.network.size(); i++)
				network[i] = BioList<T>(copy.network[i]);
		}
		/// AdjList constructor
		/**
		@param Initial size of the network
		*/
		AdjList(int i = 5) {
			network.resize(i);
		}
		~AdjList() {}

		/// Set the edge between two nodes
		/**
			@param x index of the first node
			@param y index of the second node
			@param w weight of the edge
		*/
		void setEdge(const int x, const int y, const T w)
		{
			network[x].setWeight(network[y].getName(), w);
		}

		/// Set the edge between two nodes
		/**
		@param x name of the first node
		@param y name of the second node
		@param w weight of the edge
		*/
		void setEdge(const string& x, const string& y, const T w)
		{
			int i = 0;
			while (network[i].getName() != x)
				i++;
			network[i].setWeight(y, w);
		}

		/// gets the weight of the edge
		/**
			@param x index of the first node
			@param y index of the second node
			@return the weight of the edge
		*/
		T getEdge(const int x, const int y) const
		{
			return network[x].getWeight(network[y].getName());
		}
		/// gets the weight of the edge
		/**
			@param a name of the first node
			@param b name of the second node
			@return the weight of the edge
		*/
		T getEdge(const string& a, const string& b) const
		{
			for (int i = 0; i < network.size(); i++) {
				if (strcmp(network[i].getName().c_str(), a.c_str()) == 0)
					return network[i].getWeight(b);
			}
			return T();
		}

		/// sets the node in the network
		/** 
			@param i index of the node
			@param s name of the node
		*/
		void setNode(const int i, const string& s)
		{
			auto oldName = network[i].getName();
			network[i].setName(s);
			for (int z = 0; z < network.size(); z++) {
				if (z != i)
					network[z].setEdgeName(oldName, s);
			}
		}

		/// gets the name of the node
		/**
			@param i index of the node
			@return the name of the node
		*/
		string getNode(const int i) const
		{
			return network[i].getName();
		}

		/// the size of the network
		/**
			@return the size of the network
		*/
		int size() const
		{
			return network.size();
		}

		/// the degree of a node
		/**
			@param x the index of the node
			@return the total of the edges
		*/
		T degree(const int x) const
		{
			auto node = network[x].front();
			auto result = 0.0f;
			while (node)
				result += node->getWeight();
			return result;
		}

		/// get the number of edges in the network
		/**
			@return the number of edges
		*/
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
		
		/// resize the AdjList
		/**
			@param newSize the new size of the network
		*/
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

		/// find the index of a node
		/**
			Finds the index of a node or returns a BioNetException if not found.
			@param name the name of the node
			@return the index of the node
		*/
		int findNodeIndex(const string& name) const
		{
			for (int i = 0; i < network.size(); i++)
				if (network[i].getName() == name)
					return i;
			throw Exception("Node not found.");
		}

		/// delete an edge in the network
		/**
			@param x the name of the first node
			@param y the name of the second node
		*/
		void deleteEdge(const string & x, const string & y)
		{
			network[findNodeIndex(x)].deleteEdge(y);
		}

		/// delete an edge in the network
		/**
			@param x the index of the first node
			@param y the index of the second node
		*/
		void deleteEdge(int x, int y)
		{
			network[x].deleteEdge(network[y].getName());
		}

		/// delete a node in the network
		/**
			@param name the name of the node to delete
		*/
		void deleteNode(const string & name)
		{
			auto index = findNodeIndex(name);
			for (size_t i = 0; i < network.size(); i++)
				if (i != index)
					network[i].deleteEdge(name);
			network.erase(network.begin() + index);
		}

		/// delete a node in the network
		/**
			@param index the index of the node to delete
		*/
		void deleteNode(int index)
		{
			auto name = network[index].getName();
			for (size_t i = 0; i < network.size(); i++)
				if (i != index)
					network[i].deleteEdge(name);
			network.erase(network.begin() + index);
		}

		/// create a copy of the network
		/**
			@param rhs the Adj to copy
		*/
		void copy(const Adj<T>* rhs) {
			auto _rhs = static_cast<const AdjList<T>*>(rhs);
			network = vector<BioList<T>>(_rhs->network.size());
			for (size_t i = 0; i < _rhs->network.size(); i++)
				network[i] = BioList<T>(_rhs->network[i]);
		}
		//void addNode(const string& str)
		//{}

		/// scale the weights of the network
		/**
			@param scale the factor to scale the weights
		*/
		void scaleWeights(const T& scale)
		{}

		/// check if two networks are equal
		/**
			@param adj the network to compare
		*/
		bool isEqual(const Adj<T>* adj)
		{
			return true;
		}
		/*const BioAdjList& operator+=(const string nodename)
		{
			network.push_back(BioList<T>(0, nodename));
			return *this;
		}*/

		/*BioAdjList operator+(const string nodename)
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
		}*/

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////ADD TEAM

		/// add a node to the network
		/**
			@param name the name of the node to add
		*/
		void addNode(const string& name)
		{
			network.emplace_back(BioList<T>(name));

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////EQUALS TEAM


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////SCALE TEAM

		/// scale the network by a factor
		/**
			@param weight the factor to scale by
		*/
		void scaleUp(T weight) {
			for (int i = 0; i < network.size(); i++)
				network[i] *= weight;
		}

		/// scale the network by a factor
		/**
		@param weight the factor to scale by
		*/
		void scaleDown(T weight) {
			for (int i = 0; i < network.size(); i++)
				network[i] /= weight;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	template<>
	BioNet::Register BioNet::AdjList<int>::reg = Register("BioAdjListInt", &AdjList<int>::make);
	template<>
	BioNet::Register BioNet::AdjList<float>::reg = Register("BioAdjListFloat", &AdjList<float>::make);
	template<>
	BioNet::Register BioNet::AdjList<double>::reg = Register("BioAdjListDouble", &AdjList<double>::make);
}

