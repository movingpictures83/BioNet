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
/** 
 * Represents a Network implemented as an Adjacency **Matrix**
 * Overrids most methods from its parent generic class.
*/
template<typename T>
class AdjMat : public Adj<T>
{
private:
	vector<vector<T>> matrix;
	vector<string> names;
	static Register reg;
public:
	/// Returns the Network's **Type** (Matrix, List, etc.)
	/**
	 * Returns the network type keyword.
	 * @return the network type keyword.
	 */
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
	/**
	* Allocates a new Adjacency Matrix in memory and returns it.
	* @return A new memory-allocated Adjacency Matrix.
	*/
	static GenericAdj* make() { return new AdjMat<T>; }

	/// Creates a new Network
	/**
	* Constructor.
	* Initializes an Adjacency Matrix.
	*/
	AdjMat(int size = 5) {
		names.resize(size);
		matrix.resize(size);
		for (auto& n : matrix)
			n.resize(size, 0);
	}

	/**
	* Default destructor.
	* Default destructor to destroy the Adjacency Matrix.
	*/
	~AdjMat() {}

	///Sets the edge given two node indexes and numeric weight.
	/**
	* Sets the edge given two node indexes and numeric weight.
	* @param source The index of source node of the edge.
	* @param target The index of target node of the edge.
	* @param weight The weight of the edge.
	*/
	void setEdge(const int source, const int target, const T weight);

	///Sets the edge given two node names references and numeric weight.
	/**
	* Sets the edge given two node indexes and numeric weight.
	* @param source The label of source node of the edge.
	* @param target The label of target node of the edge.
	* @param weight The weight of the edge.
	*/
	void setEdge(const string& source, const string& target, const T weight);

	///Gets the edge weight given two numeric indexes.
	/**
	* Get the edge weight given two node indexes.
	* @param source The index of source node of the edge.
	* @param target The index of target node of the edge.
	* @return Edge weight.
	*/
	T getEdge(const int source, const int target) const;

	///Gets the weight of the edge given two node names
	/**
	* Get the edge weight given two node labels.
	* @param source The label of source node of the edge.
	* @param target The label target node of the edge.
	* @return Edge weight.
	*/
	T getEdge(const string& source, const string& target) const;

	///Sets the node name given an index
	/**
	* Sets the node name and index.
	* @param index The index of node.
	* @param label The label of node.
	* @return No return value.
	*/
	void setNode(const int index, const string& label);

	///Gets the node name given an index
	/**
	* Gets the node name given an index.
	* @param index The index of node.
	* @return Name of the node.
	*/
	string getNode(const int index) const;

	///Returns the size of the matrix
	/**
	* Returns the size of the matrix.
	* @return Size of the matrix.
	*/
	int size() const;

	///Resizes the matrix
	/**
	* Resizes the matrix given an size.
	* @param size Target size of matrix.
	* @return No return value.
	*/
	void resize(const int size);

	///Gets the degree of the node given an index
	/**
	* Gets the degree of the node given an index.
	* @param index Index of the node.
	* @return Degree of node.
	*/
	T degree(const int index) const;

	///Gets the total number of edges in the matrix
	/**
	* Gets the total number of edges in the matrix.
	* @return Number of edges in matrix.
	*/
	unsigned int numberOfEdges() const;

	///Returns the index of the node given a name
	/**
	* Returns the index of the node given a name.
	* @param name Name of the node.
	* @return Index of node.
	*/
	int findNodeIndex(const string& name) const;

	///Deletes the edge given two node names
	/**
	* Deletes the edge given two node names
	* @param first Name of the first node.
	* @param second Name of the second node.
	* @return No return value.
	*/
	void deleteEdge(const string & first, const string & second);

	///Deletes the edge given the two node indexes
	/**
	* Deletes the edge given two node indeces.
	* @param first Index of the first node.
	* @param second Index of the second node.
	* @return No return value.
	*/
	void deleteEdge(int first, int second);

	///Deletes node given name
	/**
	* Deletes the node given the name.
	* @param name Name of the node.
	* @return No return value.
	*/
	void deleteNode(const string & name);

	///Deletes node given index
	/**
	* Deletes the node given the index.
	* @param index Index of the node.
	* @return No return value.
	*/
	void deleteNode(const int index);

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
	 * Adds node with no edges with the given name.
	 * @param aNode Node to be added.
	 */
	void addNode (const string& aNode) {
		unsigned sz = size();
		resize( sz + 1);
		setNode( sz, aNode);
	}

	///Checks if rhs is equal
	/**
	* Checks if given Adjacency Matrix is equal to this one.
	* @param rhs Adjacency Matrix to compare.
	* @return True if equal, false otherwise.
	*/
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
	 * Scales up the weights by a given factor.
	 * @param factor Number to scale on.
	 * @return No return value.
	 */
	void scaleUp(const T factor) {
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++)
			for (unsigned j = 0; j < size; j++)
				matrix[i][j] *= factor;
	}

	///Scales down the weights by a given factor
	/**
	* Scales down the weights by a given factor.
	* @param factor Number to scale on.
	* @return No return value.
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
/**
* Sets the edge given two node indexes and numeric weight.
* @param i The index of source node of the edge.
* @param j The index of target node of the edge.
* @param w The weight of the edge.
*/
template <typename T>
void AdjMat<T>::setEdge(const int i, const int j, const T w)
{
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw Exception("setEdge() has wrong range");
	matrix[i][j] = w;
}

/// Sets the weight of a given **Edge** (by its neightboring Node-Names) in the Network **Matrix**
/**
* Sets the edge given two node names and numeric weight.
* @param n1 The name of source node of the edge.
* @param n2 The name of target node of the edge.
* @param w The weight of the edge.
*/
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
/**
* Get the edge weight given two node indexes.
* @param i The index of source node of the edge.
* @param j The index of target node of the edge.
* @return Edge weight.
*/
template <typename T>
T AdjMat<T>::getEdge(const int i, const int j) const {
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw Exception("setEdge() has wrong range");

	return matrix[i][j];
}

/// Returns the weight of a given **Edge** (by its neightboring Node-Names) in the Network **Matrix**
/**
* Get the edge weight given two node names.
* @param n1 The name of source node of the edge.
* @param n2 The name of target node of the edge.
* @return Edge weight.
*/
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
/**
* Get the index of the node given its name.
* @param lookup Name of the node to find.
* @return Index of found node.
*/
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
