#pragma once
#include "Adj.h"
#include "List.h"
#include "../exception/Exception.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "../factory/Register.h"
using std::vector;
using std::string;
using std::map;
using std::find_if;

namespace BioNet {
	/// An Adjacency List for BioNet
	/**
		AdjList impements an adjacency list to represent the Bionet network.
		It consists of a vector of List, each element representing a node in the network with
		its corresponding edges.
	*/
	template <typename T>
	class AdjList : public Adj<T>
	{
	public:
		/// A vector of List<T> containing the network.
		vector<List<T>> network;
		
		/// Registers the network type.
		static Register reg;
	public:
		/// Used for factory Construction
		/**
		@return A new, dynamic instance of AdjList
		*/
	
		static GenericAdj* make() { return new AdjList<T>; }
		/// Specifies the type of the network used to register instances in the factory.
		/**
		@return Type name of the network.
		*/
		static const string& NetworkType()
		{
			static const type_info& ti = typeid(AdjList<T>);
			string keyword = ti.name();
			AdjFactory::mFactoryMap.find(keyword) == AdjFactory::mFactoryMap.end() ? Register(keyword, &AdjList::make) : reg;
			return keyword;
		}
		/// AdjList Copy constructor
		AdjList(const AdjList& copy)
		{
			network = vector<List<T>>(copy.network.size());
			for (size_t i = 0; i < copy.network.size(); i++)
				network[i] = List<T>(copy.network[i]);
		}
		/// AdjList constructor
		/**
		@param Initial size of the network
		*/
		AdjList(int size = 5) {
			network.resize(size);
		}
		~AdjList() {}

		///Sets the edge given two node indexes and numeric weight.
		/**
		* Sets the edge given two node indexes and numeric weight.
		* @param source The index of source node of the edge.
		* @param target The index of target node of the edge.
		* @param weight The weight of the edge.
		*/
		void setEdge(const int source, const int target, const T weight)
		{
			network[source].setWeight(network[target].getName(), weight);
		}

		///Sets the edge given two node names references and numeric weight.
		/**
		* Sets the edge given two node indexes and numeric weight.
		* @param source The label of source node of the edge.
		* @param target The label of target node of the edge.
		* @param weight The weight of the edge.
		*/
		void setEdge(const string& source, const string& target, const T weight)
		{
			for (int i = 0; i < network.size(); i++) {
				if (network[i].getName() == source && network[i].search(target)) {
					network[i].setWeight(target, weight);
					return;
				}
			}
			network[this->findNodeIndex(source)].insertFront(weight, target);
		}

		///Gets the edge weight given two numeric indexes.
		/**
		* Get the edge weight given two node indexes.
		* @param source The index of source node of the edge.
		* @param target The index of target node of the edge.
		* @return Edge weight.
		*/
		T getEdge(const int source, const int target) const
		{
			return network[source].getWeight(network[target].getName());
		}

		///Gets the weight of the edge given two node names
		/**
		* Get the edge weight given two node labels.
		* @param source The label of source node of the edge.
		* @param target The label target node of the edge.
		* @return Edge weight.
		*/
		T getEdge(const string& source, const string& target) const
		{
			for (int i = 0; i < network.size(); i++) {
				if (strcmp(network[i].getName().c_str(), source.c_str()) == 0)
					return network[i].getWeight(target);
			}
			return T();
		}

		///Sets the node name given an index
		/**
		* Sets the node name and index.
		* @param index The index of node.
		* @param label The label of node.
		* @return No return value.
		*/
		void setNode(const int index, const string& label)
		{
			string oldName = (string)network[index].getName();
			network[index].setName(label);
			for (int z = 0; z < network.size(); z++) {
				if (z != index)
					network[z].setEdgeName(oldName, label);
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
			Edge<T>* node = network[x].front();
			float result = 0.0f;
			while (node)
			{
				result += (float) node->getWeight();
				node = node->getNext();
			}
			return result;
		}

		/// gets the number of edges in the network
		/**
			@return the number of edges
		*/
		unsigned int numberOfEdges() const
		{
			unsigned int result = 0;
			for (size_t i = 0; i < network.size(); i++)
			{
				Edge<T>* node = network[i].front();
				for(node; node != nullptr; node = node->getNext())
					result++;
			}
			return result;
		}
		
		/// resizes the AdjList
		/**
			@param newSize the new size of the network
		*/
		void resize(const int newSize)
		{
			unsigned int networkSize = network.size();
			int sizeDifference = newSize - networkSize;

			if (sizeDifference < 0) //Last sizeDifference nodes will be destroyed, so the other nodes that have edges to them must be cleaned.
			{
				sizeDifference *= -1;
				for (size_t i = networkSize - sizeDifference; i < networkSize; i++)
				{
					string name = network[i].getName();
					for (size_t j = 0; j < networkSize - sizeDifference; j++)
						network[j].deleteEdge(name);
				}
			}

			network.resize(newSize);
		}

		/// finds the index of a node
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

		/// deletes an edge in the network
		/**
			@param x the name of the first node
			@param y the name of the second node
		*/
		void deleteEdge(const string & x, const string & y)
		{
			network[findNodeIndex(x)].deleteEdge(y);
		}

		/// deletes an edge in the network
		/**
			@param x the index of the first node
			@param y the index of the second node
		*/
		void deleteEdge(int x, int y)
		{
			network[x].deleteEdge(network[y].getName());
		}

		/// deletes a node in the network
		/**
			@param name the name of the node to delete
		*/
		void deleteNode(const string & name)
		{
			int index = findNodeIndex(name);
			for (size_t i = 0; i < network.size(); i++)
				if (i != index)
					network[i].deleteEdge(name);
			network.erase(network.begin() + index);
		}

		/// deletes a node in the network
		/**
			@param index the index of the node to delete
		*/
		void deleteNode(int index)
		{
			string name = network[index].getName();
			for (size_t i = 0; i < network.size(); i++)
				if (i != index)
					network[i].deleteEdge(name);
			network.erase(network.begin() + index);
		}

		/// creates a copy of the network
		/**
			@param rhs the Adj to copy
		*/
		void copy(const Adj<T>* rhs) override {
			const AdjList<T>* _rhs = static_cast<const AdjList<T>*>(rhs);
			network = vector<List<T>>(_rhs->network.size());
			for (size_t i = 0; i < _rhs->network.size(); i++)
				network[i] = List<T>(_rhs->network[i]);
		}

		/// checks whether two networks are equal
		/**
			@param adj the network to compare
		*/
		bool isEqual(const Adj<T>* adj)
		{
			return true;
		}

		/// adds a node to the network
		/**
			@param name the name of the node to add
		*/
		void addNode(const string& name)
		{
			network.emplace_back(List<T>(name));

		}

		/// scales the network by a factor
		/**
			@param weight the factor to scale by
		*/
		void scaleUp(T weight) {
			for (int i = 0; i < network.size(); i++)
			{
				Edge<T>* node = network[i].front();
				while (node)
				{
					node->setWeight(node->getWeight() * weight);
					node = node->getNext();
				}

			}
		}

		/// scales the network by a factor
		/**
		@param weight the factor to scale by
		*/
		void scaleDown(T weight) {
			for (int i = 0; i < network.size(); i++)
			{
				Edge<T>* node = network[i].front();
				while (node)
				{
					node->setWeight(node->getWeight() / weight);
					node = node->getNext();
				}

			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	//template<>
	BioNet::Register BioNet::AdjList<int>::reg = Register("BioAdjListInt", &AdjList<int>::make);
	//template<>
	BioNet::Register BioNet::AdjList<float>::reg = Register("BioAdjListFloat", &AdjList<float>::make);
	//template<>
	BioNet::Register BioNet::AdjList<double>::reg = Register("BioAdjListDouble", &AdjList<double>::make);
}

