#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <typeinfo>
#include "Adj.h"
#include "../factory/Register.h"
#include "../exception/Exception.h"
#include "../factory/AdjFactory.h"
#include <numeric>

using std::vector;
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
class AdjMat : public Adj<T>
{
private:
	vector<vector<T>> matrix;
	vector<string> names;
	static Register reg;
public:
	/// Returns the Network's **Type** (Matrix, List, etc.).
	static string NetworkType()
	{
		//static const string network = "BioAdjMat";
		//return network;
	    static const type_info& ti = typeid(AdjMat<T>);
		string keyword = ti.name();
		AdjFactory::getInstance()->mFactoryMap.find(keyword) == AdjFactory::getInstance()->mFactoryMap.end() ? Register(keyword, &AdjMat::make) : reg;
		return keyword;
	}

	/// Uses a Factory to create a new **Network** of the current type
	static GenericAdj* make() { return new AdjMat<T>; }

	/// Creates a new Network
	AdjMat(int size = 5) {
		names.resize(size);
		matrix.resize(size);
		for (auto& n : matrix)
			n.resize(size, 0);
	}
	~AdjMat() {}
	///Sets the edge given two node indexes and numeric weight.
	/**

	*/
	void setEdge(const int, const int, const T); 
	///Sets the edge given two node names and numeric weight.
	void setEdge(const string&, const string&, const T);
	///Gets the weight of the edge given two numeric indexes.
	T getEdge(const int, const int) const;
	///Gets the weight of the edge given two node names
	T getEdge(const string&, const string&) const;
	///Sets the node name given an index
	void setNode(const int, const string&);
	///Gets the node name given an index
	string getNode(const int) const;
	///Returns the size of the matrix
	int size() const;
	///Resizes the matrix
	void resize(const int);
	///Gets the degree of the node given an index
	T degree(const int) const;
	///Gets the total number of edges
	unsigned int numberOfEdges() const;
	///Returns the index of the node given a name
	int findNodeIndex(const string&) const;
	///Deletes the edge given two node names
	void deleteEdge(const string &, const string &);
	///Deletes the edge given the two node indexes
	void deleteEdge(int, int);
	///Deletes node given name
	void deleteNode(const string &);
	///Deletes node given index
	void deleteNode(const int);
	//BioAdjMat<T> operator+ (const string &);
	//const AdjMat<T> & operator+= (const string &);
	//const AdjMat<T> & operator/= (const T &);
	//const AdjMat<T> & operator*= (const T &);
	//bool operator== (const AdjMat<T> &);
	//bool operator!= (const AdjMat<T> &);
	//const string & operator[] (int);
	//T operator() (int, int);
	//friend ostream & operator<< (const ostream &, const AdjMat<T> &);

	// moving operators to BioNet Class, this becomes copy
	///Copies rhs into itself.
	void copy(const Adj<T> * rhs) {
		names.resize(rhs->size());
		for (unsigned i = 0; i < names.size(); i++) {
			names[i] = rhs->getNode(i);
		}
		matrix.resize(rhs->size());
		for (unsigned i = 0; i < rhs->size(); i++) {
			for (unsigned j = 0; j < rhs->size(); j++) {
				matrix[i][j] = (T)rhs->getEdge(i, j);
			}
		}
	}
	///Adds node with no edges given a name
	/**
	@param aNode Node to be added.
	*/
	void addNode (const string& aNode) {
		unsigned sz = size();
		resize( sz + 1);
		setNode( sz, aNode);
	}
	///Checks if rhs is equal 
	bool isEqual (const Adj<T>* rhs) {
		auto _rhs = static_cast<const AdjMat<T> *>(rhs);
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++) {
			if (names[i].compare(_rhs->names[i]))
				return false;
			for (unsigned j = 0; j < size; j++)
				if (!((matrix[i][j] - _rhs->matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - _rhs->matrix[i][j]) < FLT_EPSILON))
					return false;
		}
		return true;
	}
	///Scales up the weights by a given factor
	/**
	@param factor number to scale on.
	*/
	void scaleUp(const T factor) {
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++)
			for (unsigned j = 0; j < size; j++)
				matrix[i][j] *= factor;
	}
	///Scales down the weights by a given factor
	/**
	@param factor number to scale on.
	*/
	void scaleDown(const T factor) {
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++)
			for (unsigned j = 0; j < size; j++)
				matrix[i][j] *= factor;
	}
};


// Moved code from BioAdjMat.cpp to work properly now that it's templated

//template<>
Register AdjMat<int>::reg = Register("BioAdjMatInt", &AdjMat::make);
//template<>
Register AdjMat<float>::reg = Register("BioAdjMatFloat", &AdjMat::make);
//template<>
Register AdjMat<double>::reg = Register("BioAdjMatDouble", &AdjMat::make);

/// Sets the weight of a given **Edge** (by its indexes) in the Network **Matrix**
template <typename T>
void AdjMat<T>::setEdge(const int i, const int j, const T w)
{
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw Exception("setEdge() has wrong range");
	matrix[i][j] = w;
}

/// Sets the weight of a given **Edge** (by its neightboring Node-Names) in the Network **Matrix**
template <typename T>
void AdjMat<T>::setEdge(const string& n1, const string& n2, const T w)
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (unsigned x = 0; x < names.size(); x++) {
		if (!n1.compare(names[x]))
		{
			i = x;
		}
		if (!n2.compare(names[x]))
		{
			j = x;
		}
	}

	if (i == -1 || j == -1) throw Exception("Node not found");

	setEdge(i, j, w);
}

/// Returns the weight of a given **Edge** (by its indexes) in the Network **Matrix**
template <typename T>
T AdjMat<T>::getEdge(const int i, const int j) const {
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw Exception("setEdge() has wrong range");

	return matrix[i][j];
}

/// Returns the weight of a given **Edge** (by its neightboring Node-Names) in the Network **Matrix**
template <typename T>
T AdjMat<T>::getEdge(const string& n1, const string& n2) const
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (unsigned x = 0; x < names.size(); x++) {
		if (!n1.compare(names[x]))
		{
			i = x;
		}
		if (!n2.compare(names[x]))
		{
			j = x;
		}
	}

	if (i == -1 || j == -1) throw Exception("Node not found");

	return getEdge(i, j);
}

/// Returns the internal index of a **Node** given its **Name**
template <typename T>
int AdjMat<T>::findNodeIndex(const string & lookup) const
{
	unsigned index = 0;
	for (unsigned i = 0; i < names.size(); i++)
	{
		if (lookup.compare(names[i]))
			return index;

		index++;
	}
	return -1;
}

/// Sets the name of a **Node** given its internal index
/**
	@param index index of the node to set
	@param name name to set that node to
*/
template <typename T>
void AdjMat<T>::setNode(const int index, const string &name)
{
	if (index < 0 || index >= names.size())
		throw Exception("Trying to add name out of range");

	names[index] = name;
}

/// Returns the name of a **Node** given its index
/**
	@param index index of the node to get
*/
template <typename T>
string AdjMat<T>::getNode(const int index) const
{
	if (index < 0 || index >= names.size())
		throw Exception("Trying to add name out of range");

	return names[index];
}

/// Removes an **Edge** from the **Network** given its two neighboring Node-names
/**
	@param istr name of the first index of edge
	@param jstr name of the second index of edge
*/
template <typename T>
void AdjMat<T>::deleteEdge(const string & istr, const string & jstr)
{
	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}

/// Removes an **Edge** from the **Network** given its internal indexes
/**
	- it does this by setting the value of the **Edge** to 0 in the **Matrix** representation
	@param i first index of edge
	@param j second index of edge
*/
template <typename T>
void AdjMat<T>::deleteEdge(const int i, const int j)
{
	unsigned size = names.size();
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw Exception("Trying to delete invaid edge");
	matrix[i][j] = 0;
}

/// Removes a **Node** from the **Network** given its name
/**
	@param nodename the name of the node to delete
*/
template <typename T>
void AdjMat<T>::deleteNode(const string & nodename)
{
	int node = findNodeIndex(nodename);
	deleteNode(node);
}

/// Removes a **Node** from the **Network** given its index
/**
	@param nodeindex the index of the node to delete
*/
template <typename T>
void AdjMat<T>::deleteNode(const int nodeindex)
{
	unsigned size = matrix.size();
	if (nodeindex < 0 || nodeindex >= size)
		throw Exception("Trying to delete invaid Node");

	matrix.erase(matrix.begin() + nodeindex);
	for (auto & node : matrix)
		node.erase(node.begin() + nodeindex);
}

/// Resizes the **Network** to a new given size
/**
	@param size the new size of the network
*/
template <typename T>
void AdjMat<T>::resize(const int size) {
	if (size <= 0)
		throw Exception("resize value is invalid");
	matrix.resize(size);
	for (unsigned i = 0; i < matrix.size(); i++) {
		matrix[i].resize(size);
	}
	names.resize(size);
}

/// Returns the size of the current **Network**
/**
	@return the size of the network
*/
template <typename T>
int AdjMat<T>::size() const {
	return names.size();
}

///Gets the degree of the node given an index
/**	
	@param x the index of the node
	@return the total of the edges
*/
template <typename T>
T AdjMat<T>::degree(const int index) const {
	if (index < 0 || index >= matrix.size())
		throw Exception("Index out of bounds!");
	return std::accumulate(matrix[index].begin(), matrix[index].end(), 0.0f);
}

///Gets the total number of edges
/**
	@return the number of edges
*/
template <typename T>
unsigned int AdjMat<T>::numberOfEdges() const {
	unsigned edges = 0;

	for (unsigned i = 0; i < matrix.size(); i++)
		for (unsigned j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] < -FLT_EPSILON || matrix[i][j] > FLT_EPSILON)
				edges++;
		}
	return edges;
}

}
