#ifndef BIONET_H
#define BIONET_H
#include <string>
using std::string;

#define NETWORK_SIZE 5
class BioNet {
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // MORNING COHORT EINSTEIN
   //
   //
private:
	float minweight;
	float maxweight;
	float network[NETWORK_SIZE][NETWORK_SIZE];
	string names[NETWORK_SIZE];

public:
	BioNet();
	BioNet(float, float);
	~BioNet();

	void setRange(float, float);
	void setEdge(int, int, float);
	void setNode(int, string);
	// Accessors
	float getEdge(int, int);
	string getNode(int);
	float getMinWeight() { return minweight; }
	float getMaxWeight() { return maxweight; }
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

	float degree(int);

   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////

};



#endif



