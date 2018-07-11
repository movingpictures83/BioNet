#pragma once
#include <map>
#include <string>
#include <ostream>
#include <typeinfo>
#include "Adj.h"
#include "../factory/Register.h"
#include "../exception/Exception.h"
#include "../factory/AdjFactory.h"
#include <numeric>

using std::map;
using std::string;
using std::ostream;
using std::type_info;
using std::endl;

namespace BioNet {

	/// Network implemented as a Map
	//Overrides most methods from its parent's generic class

	//need to implement all the functions according to a string-float map

	template<typename T>
	class AdjTree : public Adj<T>
	{
	private:
		map<string, map<string, float>> tree;
		static Register reg;
	public:
		/// Returns the Network **Type** (tree, List, etc.) of a Network
		static string NetworkType()
		{
			//static const string network = "BioAdjTree";
			//return network;
			static const type_info& ti = typeid(AdjTree<T>);
			string keyword = ti.name();
			AdjFactory::mFactoryMap.find(keyword) == AdjFactory::mFactoryMap.end() ? Register(keyword, &AdjTree::make) : reg;
			return keyword;
		}

		/// Uses a Factory to create a new **Network** of the current type
		static GenericAdj* make() { return new AdjTree<T>; }

		/// Creates a new Network
		AdjTree(int size = 5) {
			tree.resize(size);
			for (auto& n : tree)
				n.resize(size, 0);
		}
		~AdjTree() {}
		///Sets edge given two node indexes and numeric weight.
		void setEdge(const int, const int, const T);
		///Sets edge given two node names and numeric weight.
		void setEdge(const string&, const string&, const T);
		///Get the weight of the edge given two numeric indexes.
		T getEdge(const int, const int) const;
		///Get the weight of the edge given two node names
		T getEdge(const string&, const string&) const;
		///Set's the node name given an index
		void setNode(const int, const string&);
		///Get the node name given an index
		string getNode(const int) const;
		///Return's the size of the tree
		int size() const;
		///Resize the tree
		void resize(const int);
		///Get the degree of the node given an index
		T degree(const int) const;
		///Gets the total number of edges
		int numberOfEdges() const;
		///Returns the index of the node given a name
		int findNodeIndex(const string&) const;
		///Delete's the edge given two node names
		void deleteEdge(const string &, const string &);
		///Delete's the edge given the two node indexes
		void deleteEdge(int, int);
		///Delete node given name
		void deleteNode(const string &);
		///Delete node given index
		void deleteNode(const int);
		///Copies rhs into itself.
		void copy(const Adj<T> * rhs)
		{
		}
		///Add node with no edges given a name
		void addNode(const string& aNode)
		{
		}
		///Checks if rhs is equal 
		bool isEqual(const Adj<T>* rhs)
		{

		}
		///Scales up the weights by a given factor
		void scaleUp(const T factor)
		{

		}
		///Scales down the weights by a given factor
		void scaleDown(const T factor)
		{

		}

		void setEdge(const int x, const int y, const T w)
		{

		}

		void setEdge(const string& x, const string& y, const T w)
		{
		}

		T getEdge(const int x, const int y) const
		{

		}

		T getEdge(const string& a, const string& b) const
		{

		}

		void setNode(const int i, const string& s)
		{
		}
	};
