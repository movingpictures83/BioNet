
#include "Adj.h"
#include "List.h"
#include "../exception/Exception.h"

#include <string>
#include <map>
#include <algorithm>
#include "../factory/Register.h"
using std::vector;
using std::string;
using std::map;
using std::find_if;

namespace BioNet {
	/// An Adjacency Basic for BioNet
	/**
	AdjBasic impements an adjacency Basic to represent the Bionet network.
	It consists of an array of nodes and an array of edges	*/
	template <typename T>
	struct BasicEdge
	{
		string source;
		string destination;
		T weight;
	};

	template <typename T>
	class AdjBasic : public Adj<T>
	{
	public:
		
		string* arrBNodes;
		BasicEdge* arrBEdges;

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
			static const type_info& ti = typeid(AdjBasic<T>);
			string keyword = ti.name();
			AdjFactory::mFactoryMap.find(keyword) == AdjFactory::mFactoryMap.end() ? Register(keyword, &AdjList::make) : reg;
			return keyword;
		}
		/// AdjList Copy constructor
		AdjBasic(const AdjBasic& copy)
		{
			network = vector<List<T>>(copy.network.size());
			for (size_t i = 0; i < copy.network.size(); i++)
				network[i] = List<T>(copy.network[i]);
		}
		/// AdjList constructor
		/**
		@param Initial size of the network
		*/
		AdjBasic(int i = 5) {
			network.resize(i);
		}
		~AdjBasic() {}

		/// Set the edge between two nodes
		/**
		@param x index of the first node
		@param y index of the second node
		@param w weight of the edge
		*/
		void setEdge(const int x, const int y, const T w)
		{
			return 0;
		}

		/// Set the edge between two nodes
		/**
		@param x name of the first node
		@param y name of the second node
		@param w weight of the edge
		*/
		void setEdge(const string& x, const string& y, const T w)
		{
			arrBEdges->source = x;
			arrBEdges->destination = y;
			arrBEdges->weight = w;
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
			arrBNodes[i] = s;
		}

		/// gets the name of the node
		/**
		@param i index of the node
		@return the name of the node
		*/
		string getNode(const int i) const
		{
			return arrBNodes[i];
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
			
			return result;
		}

		/// get the number of edges in the network
		/**
		@return the number of edges
		*/
		int numberOfEdges() const
		{
			
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
			auto _rhs = static_cast<const AdjBasic<T>*>(rhs);
			network = vector<List<T>>(_rhs->network.size());
			for (size_t i = 0; i < _rhs->network.size(); i++)
				network[i] = List<T>(_rhs->network[i]);
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
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		////ADD TEAM

		/// add a node to the network
		/**
		@param name the name of the node to add
		*/
		void addNode(const string& name)
		{
			network.emplace_back(List<T>(name));

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
			{
				Edge<T>* node = network[i].front();
				while (node)
				{
					node->setWeight(node->getWeight() * weight);
					node = node->getNext();
				}

			}
		}

		/// scale the network by a factor
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

	
}

