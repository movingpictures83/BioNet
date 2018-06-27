#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <typeinfo>
#include "BioAdj.h"
#include "Register.h"

#include "BioNetException.h"
#include "BioAdjFactory.h"
#include <numeric>

using std::vector;
using std::string;
using std::ostream;
using std::type_info;
using std::endl;


template<typename T>
class BioAdjMat : public BioAdj<T>
{
private:
	vector<vector<T>> matrix;
	vector<string> names;
	static Register reg;
public:
	static const string& NetworkType()
	{
		const type_info& keyword = typeid(BioAdjMat<T>);
		return keyword.name();
	}

	static Adj* make() { return new BioAdjMat<T>; }

	BioAdjMat(int size = 5) {
		names.resize(size);
		matrix.resize(size);
		for (auto& n : matrix)
			n.resize(size);
	}
	~BioAdjMat() {}

	void setEdge(const int, const int, const T);
	void setEdge(const string&, const string&, const T);
	T getEdge(const int, const int) const;
	T getEdge(const string&, const string&) const;
	void setNode(const int, const string&);
	string getNode(const int) const;
	int size() const;
	void resize(const int);
	T degree(const int) const;
	int numberOfEdges() const;
	int findNodeIndex(const string&) const;
	void deleteEdge(const string &, const string &);
	void deleteEdge(int, int);
	void deleteNode(const string &);
	void deleteNode(const int);
	//BioAdjMat<T> operator+ (const string &);
	//const BioAdjMat<T> & operator+= (const string &);
	//const BioAdjMat<T> & operator/= (const T &);
	//const BioAdjMat<T> & operator*= (const T &);
	//bool operator== (const BioAdjMat<T> &);
	//bool operator!= (const BioAdjMat<T> &);
	//const string & operator[] (int);
	//T operator() (int, int);
	//friend ostream & operator<< (const ostream &, const BioAdjMat<T> &);

	// moving operators to BioNet Class, this becomes copy
	void copy(const BioAdj<T> * rhs) {
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

	void addNode (const string& aNode) {
		int sz = size();
		resize( sz + 1);
		setNode( sz, aNode);
	}

	bool isEqual (const BioAdj<T>* rhs) {
		auto _rhs = static_cast<const BioAdjMat<T> *>(rhs);
		for (int i = 0; i < names.size(); i++) {
			if (names[i].compare(_rhs->names[i]))
				return false;
			for (int j = 0; j < names.size(); j++)
				if (!((matrix[i][j] - _rhs->matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - _rhs->matrix[i][j]) < FLT_EPSILON))
					return false;
		}
		return true;
	}

	void scaleUp(const T factor) {
		for (int i = 0; i < names.size(); i++)
			for (int j = 0; j < names.size(); j++)
				matrix[i][j] *= factor;
	}

	void scaleDown(const T factor) {
		for (int i = 0; i < names.size(); i++)
			for (int j = 0; j < names.size(); j++)
				matrix[i][j] *= factor;
	}
};


// Moved code from BioAdjMat.cpp to work properly now that it's templated

//BioAdjFactory::mFactoryMap["matrix"] = []() {new BioAdjMat()};

//template<>
Register BioAdjMat<int>::reg = Register("BioAdjMatInt", &BioAdjMat::make);
//template<>
Register BioAdjMat<float>::reg = Register("BioAdjMatFloat", &BioAdjMat::make);
//template<>
Register BioAdjMat<double>::reg = Register("BioAdjMatDouble", &BioAdjMat::make);

template <typename T>
void BioAdjMat<T>::setEdge(const int i, const int j, const T w)
{
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw BioNetException("setEdge() has wrong range");
	matrix[i][j] = w;
}

template <typename T>
void BioAdjMat<T>::setEdge(const string& n1, const string& n2, const T w)
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (int x = 0; x < names.size(); x++) {
		if (!n1.compare(names[x]))
		{
			i = x;
		}
		if (!n2.compare(names[x]))
		{
			j = x;
		}
	}

	if (i == -1 || j == -1) throw BioNetException("Node not found");

	setEdge(i, j, w);
}

template <typename T>
T BioAdjMat<T>::getEdge(const int i, const int j) const {
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw BioNetException("setEdge() has wrong range");

	return matrix[i][j];
}

template <typename T>
T BioAdjMat<T>::getEdge(const string& n1, const string& n2) const
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (int x = 0; x < names.size(); x++) {
		if (!n1.compare(names[x]))
		{
			i = x;
		}
		if (!n2.compare(names[x]))
		{
			j = x;
		}
	}

	if (i == -1 || j == -1) throw BioNetException("Node not found");

	return getEdge(i, j);
}

template <typename T>
int BioAdjMat<T>::findNodeIndex(const string & lookup) const
{
	int index = 0;
	for (auto node : names)
	{
		if (lookup.compare(node))
			return index;

		index++;
	}
	return -1;
}

template <typename T>
void BioAdjMat<T>::setNode(const int index, const string &name)
{
	if (index < 0 || index >= names.size())
		throw BioNetException("Trying to add name out of range");

	names[index] = name;
}

template <typename T>
string BioAdjMat<T>::getNode(const int index) const
{
	if (index < 0 || index >= names.size())
		throw BioNetException("Trying to add name out of range");

	return names[index];
}

template <typename T>
void BioAdjMat<T>::deleteEdge(const string & istr, const string & jstr)
{
	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}

template <typename T>
void BioAdjMat<T>::deleteEdge(const int i, const int j)
{
	auto size = names.size();
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw BioNetException("Trying to delete invaid edge");
	matrix[i][j] = 0;
}

template <typename T>
void BioAdjMat<T>::deleteNode(const string & nodeName)
{
	auto node = findNodeIndex(nodeName);
	deleteNode(node);
}

template <typename T>
void BioAdjMat<T>::deleteNode(const int nodeIndex)
{
	auto size = matrix.size();
	if (nodeIndex < 0 || nodeIndex >= size)
		throw BioNetException("Trying to delete invaid Node");

	matrix.erase(matrix.begin() + nodeIndex);
	for (auto & node : matrix)
		node.erase(node.begin() + nodeIndex);
}

template <typename T>
void BioAdjMat<T>::resize(const int size) {
	if (size <= 0)
		throw BioNetException("resize value is invalid");
	matrix.resize(size);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(size);
	}
	names.resize(size);
}

template <typename T>
int BioAdjMat<T>::size() const {
	return names.size();
}

template <typename T>
T BioAdjMat<T>::degree(const int index) const {
	if (index < 0 || index >= matrix.size())
		throw BioNetException("Index out of bounds!");
	return std::accumulate(matrix[index].begin(), matrix[index].end(), 0.0f);
}

template <typename T>
int BioAdjMat<T>::numberOfEdges() const {
	int edges = 0;

	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
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

// removing thisoperator overload in favorof having them only in BioNet
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
