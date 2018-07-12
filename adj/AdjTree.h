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

	/// Network implemented as an Adjacency **Matrix**
	/** represents a Network implemented as an Adjacency **Matrix**
	- overrides most methods from its parent's generic class
	*/
	template<typename T>
	class AdjTree : public Adj<T>
	{
	private:
		map<string, map<string, float>> Tree;
		static Register reg;
	public:
		/// Returns the Network **Type** (Matrix, List, etc.) of a Network
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
			names.resize(size);
			matrix.resize(size);
			for (auto& n : matrix)
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
		///Return's the size of the matrix
		int size() const;
		///Resize the matrix
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
		//BioAdjTree<T> operator+ (const string &);
		//const AdjTree<T> & operator+= (const string &);
		//const AdjTree<T> & operator/= (const T &);
		//const AdjTree<T> & operator*= (const T &);
		//bool operator== (const AdjTree<T> &);
		//bool operator!= (const AdjTree<T> &);
		//const string & operator[] (int);
		//T operator() (int, int);
		//friend ostream & operator<< (const ostream &, const AdjTree<T> &);

		// moving operators to BioNet Class, this becomes copy
		///Copies rhs into itself.
		void copy(const Adj<T> * rhs) {
			names.resize(rhs->size());
			for (int i = 0; i < names.size(); i++) {
				names[i] = rhs->getNode(i);
			}
			matrix.resize(rhs->size());
			for (int i = 0; i < rhs->size(); i++) {
				for (int j = 0; j < rhs->size(); j++) {
					matrix[i][j] = (T)rhs->getEdge(i, j);
				}
			}
		}
		///Add node with no edges given a name
		void addNode(const string& aNode) {
			int sz = size();
			resize(sz + 1);
			setNode(sz, aNode);
		}
		///Checks if rhs is equal 
		bool isEqual(const Adj<T>* rhs) {
			auto _rhs = static_cast<const AdjTree<T> *>(rhs);
			for (int i = 0; i < names.size(); i++) {
				if (names[i].compare(_rhs->names[i]))
					return false;
				for (int j = 0; j < names.size(); j++)
					if (!((matrix[i][j] - _rhs->matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - _rhs->matrix[i][j]) < FLT_EPSILON))
						return false;
			}
			return true;
		}
		///Scales up the weights by a given factor
		void scaleUp(const T factor) {
			for (int i = 0; i < names.size(); i++)
				for (int j = 0; j < names.size(); j++)
					matrix[i][j] *= factor;
		}
		///Scales down the weights by a given factor
		void scaleDown(const T factor) {
			for (int i = 0; i < names.size(); i++)
				for (int j = 0; j < names.size(); j++)
					matrix[i][j] *= factor;
		}
	};
