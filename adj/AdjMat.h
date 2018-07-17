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
	/// Returns the Network **Type** (Matrix, List, etc.) of a Network
	static string NetworkType()
	{
		//static const string network = "BioAdjMat";
		//return network;
	    static const type_info& ti = typeid(AdjMat<T>);
		string keyword = ti.name();
		AdjFactory::mFactoryMap.find(keyword) == AdjFactory::mFactoryMap.end() ? Register(keyword, &AdjMat::make) : reg;
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
	unsigned int size() const;
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
	///Add node with no edges given a name
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
	void scaleUp(const T factor) {
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++)
			for (unsigned j = 0; j < size; j++)
				matrix[i][j] *= factor;
	}
	///Scales down the weights by a given factor
	void scaleDown(const T factor) {
		unsigned size = names.size();
		for (unsigned i = 0; i < size; i++)
			for (unsigned j = 0; j < size; j++)
				matrix[i][j] /= factor;
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
		if (lookup == names[i])
			return index;

		index++;
	}
	return -1;
}

/// Sets the name of a **Node** given its internal index
template <typename T>
void AdjMat<T>::setNode(const int index, const string &name)
{
	if (index < 0 || index >= names.size())
		throw Exception("Trying to add name out of range");

	names[index] = name;
}

/// Returns the nameof a **Node** given its index
template <typename T>
string AdjMat<T>::getNode(const int index) const
{
	if (index < 0 || index >= names.size())
		throw Exception("Trying to add name out of range");

	return names[index];
}

/// Removes an **Edge** from the **Network** given its two neighboring Node-names
template <typename T>
void AdjMat<T>::deleteEdge(const string & istr, const string & jstr)
{
	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}

/// Removes an **Edge** from the **Network** given its internal indexes
/**- it does this by setting the value of the **Edge** to 0 in the **Matrix** representation
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
template <typename T>
void AdjMat<T>::deleteNode(const string & nodeName)
{
	int node = findNodeIndex(nodeName);
	deleteNode(node);
}

/// Removes a **Node** from the **Network** given its index
template <typename T>
void AdjMat<T>::deleteNode(const int nodeIndex)
{
	unsigned size = matrix.size();
	if (nodeIndex < 0 || nodeIndex >= size)
		throw Exception("Trying to delete invaid Node");

	matrix.erase(matrix.begin() + nodeIndex);
	for (auto & node : matrix)
		node.erase(node.begin() + nodeIndex);
}

/// Re-sizes the **Network** to a new given size
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
template <typename T>
unsigned int AdjMat<T>::size() const {
	return names.size();
}


template <typename T>
T AdjMat<T>::degree(const int index) const {
	if (index < 0 || index >= matrix.size())
		throw Exception("Index out of bounds!");
	return std::accumulate(matrix[index].begin(), matrix[index].end(), 0.0f);
}

template <typename T>
int AdjMat<T>::numberOfEdges() const {
	unsigned edges = 0;

	for (unsigned i = 0; i < matrix.size(); i++)
		for (unsigned j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] < -FLT_EPSILON || matrix[i][j] > FLT_EPSILON)
				edges++;
		}
	return edges;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////ADD TEAM


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////EQUALS TEAM


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////SCALE TEAM




/////////////////////////////////////////////////////////////////////////////////////////////////////

// removing this operator overload in favor of having them only in BioNet
//template <typename T>
//BioAdjMat<T> BioAdjMat<T>::addNode (const string& aNode)
//{
//	BioAdjMat<T> newAdjMat;
//	newAdjMat.resize((*this).size() + 1);
//	for (int i = 0; i < (*this).size(); i++)
//	{
//		newAdjMat.names[i] = names[i];
//		for (int j = 0; j < (*this).size(); j++)
//		{
//			newAdjMat.matrix[i][j] = matrix[i][j];
//		}
//	}
//	newAdjMat.names[(*this).size()] = aNode;
//	return newAdjMat;
//}

//template <typename T>
//const BioAdjMat<T> & BioAdjMat<T>::operator/= (const T & factor)
//{
//	if (factor > -FLT_EPSILON && factor < FLT_EPSILON)
//		throw BioNetException("Can't divide 0");
//	for (int i = 0; i < names.size(); i++)
//		for (int j = 0; j < names.size(); j++)
//			matrix[i][j] /= factor;
//	return (*this);
//}
//
//template <typename T>
//const BioAdjMat<T> & BioAdjMat<T>::operator*= (const T & factor)
//{
//	for (int i = 0; i < names.size(); i++)
//		for (int j = 0; j < names.size(); j++)
//			matrix[i][j] *= factor;
//	return (*this);
//
//}
//
//template <typename T>
//bool BioAdjMat<T>::operator== (const BioAdjMat<T>& rhs)
//{
//	for (int i = 0; i < names.size(); i++)
//	{
//		if (names[i].compare(rhs.names[i]))
//			return false;
//		for (int j = 0; j < names.size(); j++)
//			if (!((matrix[i][j] - rhs.matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - rhs.matrix[i][j]) < FLT_EPSILON))
//				return false;
//	}
//	return true;
//}
//
//template <typename T>
//bool BioAdjMat<T>::operator!= (const BioAdjMat<T>& rhs)
//{
//	for (int i = 0; i < names.size(); i++)
//	{
//		if (names[i].compare(rhs.names[i]))
//			return true;
//		for (int j = 0; j < names.size(); j++)
//			if (!((matrix[i][j] - rhs.matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - rhs.matrix[i][j]) < FLT_EPSILON))
//				return true;
//	}
//	return false;
//}

//template <typename T>
//const string & BioAdjMat<T>::operator[] (int i)
//{
//	if (i < 0 || i > names.size())
//		throw BioNetException("Index is out of range");
//	return names[i];
//}
//
//template <typename T>
//T BioAdjMat<T>::operator() (int i, int j)
//{
//	if (i < 0 || i > names.size() || j < 0 || j > names.size())
//		throw BioNetException("Index is out of range");
//	return matrix[i][j];
//}
//
//template <typename T>
//ostream & operator<<(ostream & o, const BioAdjMat<T> & rhs)
//{
//	for (int i = 0; i < rhs.size(); i++)
//	{
//		o << rhs.getNode(i) << " ";
//		for (int j = 0; j < rhs.size(); j++)
//			o << rhs.getEdge(i, j) << " ";
//		o << endl;
//	}
//	return o;
//}


/* OLD CODE FROM BIONET, FOR BioAdjMat.  DO NOT DELETE
*
*
*
*-BioNet::BioNet(float min, float max, bool dir) {
// for now start a default unconnected network
-	for (int i = 0; i < NETWORK_SIZE; i++) {
-		names[i] = to_string(i);
-		for (int j = 0; j < NETWORK_SIZE; j++) {
-			network[i][j] = 0.0f;
-		}
-	}
}
*
void BioNet::setEdge(int i, int j, float w) {
-	network->setEdge(i, j, w);
-
-	if (i < 0 || i > network.size())
-	if (j < 0 || j > network.size())
-	network[i][j] = w;
-		if (network[j][i] == 0)
-			network[j][i] = w;
-		if (network[j][i] != w)
-			throw BioNetException("Both directions do not have the same weight");
-	}

void BioNet::setNode(int i, string n) {
-	network->setNode(i, n);
-
-	if (i < 0 || i > network.size())
names[i] = n;
}

float BioNet::getEdge(int i, int j) {
-
-	if (i < 0 || i > network.size())
throw BioNetException("Node is not in the matrix range");
-	if (j < 0 || j > network.size())
throw BioNetException("Node is not in the matrix range");
-	return network[i][j];
}

string BioNet::getNode(int i) {
-	if (i < 0 || i > names.size())  // corrected from network.size()
throw BioNetException("Node is not in the matrix range");
-	return names[i];
}


void BioNet::resize(int size) {
if (size <= 0)
throw BioNetException("resize value is invalid");
-	network.resize(size);
-	for (int i = 0; i < network.size(); i++) {
-		network[i].resize(size);
-	}
-
-
-	names.resize(size);
}

void BioNet::clear() {
-	// network.clear();  // Converting to a Network Class
-	names.clear();
}

size_t BioNet::size()
{
-	return network.size();
}


-void BioNet::reserve(size_t size)
if (size < 0)
throw BioNetException("Size is negative!");
-	names.resize(size);
-	network.reserve(size);
-	for (int i{ 0 }; i < size; i++)
-		network.emplace_back(size);
-}

float BioNet::degree(int index) {  //converting network to vectors - EINSTEIN
-	if (index < 0 || index >= network.size())
throw BioNetException("Index out of bounds!");
-	return std::accumulate(network[index].begin(), network[index].end(), 0.0f);
}

float BioNet::shortestPath(int start, int end) {  //converting network to vectors - EINSTEIN
-	if (start < 0 || start > network.size())
throw BioNetException("Start node is not in the matrix range");
-	if (end < 0 || end > network.size())
throw BioNetException("End node is not in the matrix range");

float negativeEdges = 0.0;
if (minweight < 0)
negativeEdges = minweight * -1 + 1;
-	vector<float> dist(network.size(), std::numeric_limits<float>::max());
-	vector<int> prev(network.size(), -1);
set<int> vertexSet;
dist[start] = 0;
-	for (int i = 0; i < network.size(); i++)
vertexSet.insert(i);
auto distFunct = bind([](vector<float>& d, int x, int y) {return d[x] < d[y]; }, dist, _1, _2);
}

int BioNet::numberOfEdges() {  //converting network to vectors - EINSTEIN
-	int edges = 0;
-
-	for (int i = 0; i < network.size(); i++)
-		for (int j = directed ? 0:i ; j < network.size(); j++)
-		{
-			if (network[i][j] < -FLT_EPSILON || network[i][j] > FLT_EPSILON)
-				edges++;
-		}
-	return edges;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
*
*
*
*
*
*
*
*/

}
