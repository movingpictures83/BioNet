#include "BioAdjMat.h"
#include "BioNetException.h"
#include "BioAdjFactory.h"
#include <numeric>
#include <ostream>

using std::ostream;
using std::endl;

//BioAdjFactory::mFactoryMap["matrix"] = []() {new BioAdjMat()};

void BioAdjMat::setEdge(const int i, const int j, const float w)
{
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw BioNetException("setEdge() has wrong range");
	matrix[i][j] = w;
}
void BioAdjMat::setEdge(const string &n1, const string &n2, const float w)
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (int x = 0; x < names.size(); x++)
	{
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
float BioAdjMat::getEdge(const int i, const int j) const {
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw BioNetException("setEdge() has wrong range");

	return matrix[i][j];
}
float BioAdjMat::getEdge(const string &n1, const string &n2) const
{
	int i = -1;
	int j = -1;

	// loop through to find indeces
	for (int x = 0; x < names.size(); x++)
	{
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

int BioAdjMat::findNodeIndex(const string & lookup) const
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
void BioAdjMat::setNode(const int index, const string &name)
{
	if (index < 0 || index >= names.size())
		throw BioNetException("Trying to add name out of range");

	names[index] = name;
}

string BioAdjMat::getNode(const int index) const
{
	if (index < 0 || index >= names.size())
		throw BioNetException("Trying to add name out of range");

	return names[index];
}


void BioAdjMat::deleteEdge(const string & istr, const string & jstr)
{

	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}
void BioAdjMat::deleteEdge(const int i, const int j)
{
	auto size = names.size();
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw BioNetException("Trying to delete invaid edge");
	matrix[i][j] = 0;
}

void BioAdjMat::deleteNode(const string & nodeName)
{
	auto node = findNodeIndex(nodeName);
	deleteNode(node);
}
void BioAdjMat::deleteNode(const int nodeIndex)
{
	auto size = matrix.size();
	if (nodeIndex < 0 || nodeIndex >= size )
		throw BioNetException("Trying to delete invaid Node");

	matrix.erase(matrix.begin() + nodeIndex);
	for (auto & node : matrix)
		node.erase(node.begin() + nodeIndex);
}

void BioAdjMat::resize(const int size) {
	if (size <= 0)
		throw BioNetException("resize value is invalid");
	matrix.resize(size);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(size);
	}
	names.resize(size);
}

int BioAdjMat::size() const {
	return names.size();
}

float BioAdjMat::degree(const int index) const{
	if (index < 0 || index >= matrix.size())
		throw BioNetException("Index out of bounds!");
	return std::accumulate(matrix[index].begin(), matrix[index].end(), 0.0f);
}

int BioAdjMat::numberOfEdges() const{  //converting network to vectors - EINSTEIN 
	int edges = 0;
	
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] < -FLT_EPSILON || matrix[i][j] > FLT_EPSILON)
				edges++;
		}
	return edges;
}

BioAdjMat BioAdjMat::operator= (const BioAdjMat & rhs)
{
	names.resize(rhs.size());
	for (int i = 0; i < names.size(); i++)
	{
		names[i] = rhs.getNode(i);
	}
	matrix.resize(rhs.size());
	for (int i = 0; i < rhs.size(); i++)
	{
		for (int j = 0; j < rhs.size(); j++)
		{
			matrix[i][j] = rhs.getEdge(i, j);
		}
	}
	return * this;
}

const BioAdjMat BioAdjMat::operator+ (const string & aNode)
{
	BioAdjMat newAdjMat;
	newAdjMat.resize((*this).size() + 1);
	for (int i = 0; i < (*this).size(); i++)
	{
		newAdjMat.names[i] = names[i];
		for (int j = 0; j < (*this).size(); j++)
		{
			newAdjMat[i, j] = matrix[i][j];
		}
	}
	newAdjMat.names[(*this).size()] = aNode;
	return newAdjMat;
}

const BioAdjMat & BioAdjMat::operator+= (const string & aNode)
{
	(*this).resize((*this).size() + 1);
	(*this).setNode((*this).size(), aNode);
	return *this;
}

const BioAdjMat & BioAdjMat::operator/= (const float & factor)
{
	if (factor > -FLT_EPSILON && factor < FLT_EPSILON)
		throw BioNetException("Can't divide 0");
	for (int i = 0; i < names.size(); i++)
		for (int j = 0; j < names.size(); j++)
			matrix[i][j] /= factor;
	return (*this);
}


const BioAdjMat & BioAdjMat::operator*= (const float & factor)
{
	for (int i = 0; i < names.size(); i++)
		for (int j = 0; j < names.size(); j++)
			matrix[i][j] *= factor;
	return (*this);

}

bool BioAdjMat::operator== (const BioAdjMat & rhs)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i].compare(rhs.names[i]))
			return false;
		for (int j = 0; j < names.size(); j++)
			if (!((matrix[i][j] - rhs.matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - rhs.matrix[i][j]) < FLT_EPSILON))
				return false;
	}
	return true;
}
bool BioAdjMat::operator!= (const BioAdjMat & rhs)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i].compare(rhs.names[i]))
			return true;
		for (int j = 0; j < names.size(); j++)
			if (!((matrix[i][j] - rhs.matrix[i][j]) > -FLT_EPSILON && (matrix[i][j] - rhs.matrix[i][j]) < FLT_EPSILON))
				return true;
	}
	return false;
}

const string & BioAdjMat::operator[] (int i)
{
	if (i < 0 || i > names.size())
		throw BioNetException("Index is out of range");
	return names[i];
}

float BioAdjMat::operator() (int i, int j)
{
	if (i < 0 || i > names.size() || j < 0 || j > names.size())
		throw BioNetException("Index is out of range");
	return matrix[i][j];
}

ostream & operator<<(ostream & o , const BioAdjMat & rhs)
{
	for (int i = 0; i < rhs.size(); i++)
	{
		o << rhs.getNode(i) << " ";
		for (int j = 0; j < rhs.size(); j++)
			o << rhs.getEdge(i, j) << " ";
		o << endl;
	}
	return o;
}

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


