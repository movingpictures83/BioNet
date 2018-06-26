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


#define NETWORK_SIZE 5  //converting network/names to vectors - EINSTEIN
class BioNet {
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT EINSTEIN
   //
   //
private:
	float minweight;
	float maxweight;
	BioAdj* network;
	bool directed;
	string networkType;

public:
	BioNet();
	BioNet(const float, const float, const bool=false, const string& = BioAdjMat::NetworkType());
	BioNet(const BioNet&);
	BioNet(BioNet&&);
	~BioNet();

	void setRange(const float, const float);
	void setEdge(const int, const int, const float);
	void setNode(const int, const string &n);
	void deleteEdge(const int, const int);
	void deleteEdge(const string &l, const string &r);

	const float shortestPath(const int, const int) const;
	void resize(const int size);
	void clear();
	// Accessors
	const float getEdge(const int, const int) const;
	const string getNode(const int) const;
	const float getMinWeight() const { return minweight; }
	const float getMaxWeight() const { return maxweight; }
	const std::string & getNetworkType() const { return networkType; }

	//Operators
	const string & operator[](size_t index) const { return network->getNode(index); };
	const float operator()(size_t lhs, size_t rhs) const { return network->getEdge(lhs, rhs); };
	const float operator()(const string & lhs, const string & rhs) const { return network->getEdge(lhs, rhs); };

	BioNet operator+(const string&)const;
	const BioNet& operator +=(const string&) const;

	const BioNet& operator=(const BioNet& rhs);

	ostream & operator<<(ostream &) const;

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
	const float degree(const int) const;
	//void reserve(size_t);
	const size_t size() const;
	const int numberOfEdges() const;

   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

};



#endif



