#ifndef BIONET_H
#define BIONET_H
#include <string>
#include <vector>
#include <iostream>
#include "BioAdj.h"
#include "BioAdjMat.h"
//#include "BioAdjList.h"
using std::string;
using std::pair;
using std::vector;
using std::ostream;

template<class T>
class BioNet {
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT EINSTEIN
   //
   //
private:
	T minweight;
	T maxweight;
	BioAdj* network;
	bool directed;
	string networkType;

public:
	BioNet();
	BioNet(const T, const T, const bool=false, const string& = BioAdjMat::NetworkType());
	BioNet(const BioNet<T>&);
	BioNet(BioNet<T>&&);
	~BioNet();

	void setRange(const T, const T);
	void setEdge(const int, const int, const T);
	void setNode(const int, const string &n);
	void deleteEdge(const int, const int);
	void deleteEdge(const string &l, const string &r);

	const T shortestPath(const int, const int) const;
	void resize(const int size);
	void clear();
	
	// Accessors
	const T getEdge(const int, const int) const;
	const string getNode(const int) const;
	const T getMinWeight() const { return minweight; }
	const T getMaxWeight() const { return maxweight; }
	const std::string & getNetworkType() const { return networkType; }

	//Operators
	const string & operator[](size_t index) const { return network->getNode(index); };
	const T operator()(size_t lhs, size_t rhs) const { return network->getEdge(lhs, rhs); };
	const T operator()(const string & lhs, const string & rhs) const { return network->getEdge(lhs, rhs); };

	BioNet<T> operator+(const string&)const;
	const BioNet<T>& operator +=(const string&) const;

	const BioNet<T>& operator=(const BioNet& rhs);

	ostream& operator<<(ostream&) const;

   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT TURING
   //
   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // AFTERNOON COHORT KNUTH
   //
   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // AFTERNOON COHORT DIJKSTRA
   //
	void convertToType(const string &);
	const T degree(const int) const;
	//void reserve(size_t);
	const size_t size() const;
	const int numberOfEdges() const;

   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

};



#endif



