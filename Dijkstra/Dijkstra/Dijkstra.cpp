// Dijkstra.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
#include <algorithm>
#include "../../BioNet.h"
#include "../../BioList.h"
#include "../../BioNetException.h"
#include "../../BioAdjList.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::fixed;
using std::for_each;

bool ShortestPathUnitTest();
bool UnitTest();
void ExceptionTest();
bool UndirectedTest();
bool BioListTest();
bool BioAdjListTest();

bool fequal(float a, float b) {
	return fabs(b - a) < FLT_EPSILON;
}

int main()
{
	cout << "======BIOLIST TEST======" << endl;
	BioListTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	cout << "======BIOADJLIST TEST======" << endl;
	BioAdjListTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	//cout << "======UNIT TEST======" << endl;
	//UnitTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;

	//cout << "======SHORTEST PATH UNIT TEST======" << endl;

	//ShortestPathUnitTest() ? cout << "PASSED" << endl :  cout << "FAILED" << endl;
	//
	//cout << "======Exception UNIT TEST======" << endl;
	//ExceptionTest();
	//UndirectedTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	return 0;
}

bool ShortestPathUnitTest()
{
	//Test for BioNet shortest path WIP
	BioNet<int> net; // Default min -1 max 1
	net.resize(3);
	net.setNode(0, "A");
	net.setNode(1, "B");
	net.setNode(2, "C");
	net.setEdge(0, 1, -1);
	net.setEdge(1, 2, 1);
	net.setEdge(0, 2, 1);
	return net.shortestPath(0, 2) == 1;
}

bool BioAdjListTest() {
	BioAdjList<float> list;
	if (list.size() != 5) return false;
	list.setNode(0, "A");
	list.setNode(1, "B");
	list.setNode(2, "C");
	list.setNode(3, "D");
	list.setNode(4, "E");
	if (list.degree(0) != 0 && list.degree(1) != 0 && list.degree(2) != 0 && list.degree(3) != 0 && list.degree(4) != 0) return false;
	return true;
}


bool BioListTest() {
	BioList<float> list(0.5f, "Sodium");
	if (list.getName() != "Sodium") return false;
	if (!fequal(list.getWeight("Sodium"),0.5f)) return false;
	list.insertFront(0.2f, "Carbon Dioxide");;
	list.insertFront(0.3f, "Sodium Chloride");
	if (!list.search("Sodium")) return false;
	if (!fequal(list.getWeight("Carbon Dioxide"), 0.2f)) return false;
	list *= 10;
	if (!fequal(list.getWeight("Sodium"), 5)) return false;
	if (!fequal(list.getWeight("Carbon Dioxide"), 2)) return false;
	list /= 10;
	if (!fequal(list.getWeight("Sodium"), 0.5f)) return false;
	if (!fequal(list.getWeight("Carbon Dioxide"), 0.2f)) return false;
	list.setWeight("Sodium", 1.5f);
	if (!fequal(list.getWeight("Sodium"), 1.5f)) return false;
	return true;
}

bool UndirectedTest()
{
	try
	{
		BioNet<int> net;
		net.resize(2);
		net.setNode(0, "A");
		net.setNode(1, "B");
		net.setEdge(1, 0, 1);
		net.setEdge(0, 1, 1);
		return false;
	}
	catch(...)
	{
		return true;
	}
}

bool UnitTest()
{
	BioNet<float> TestBio(-1, 1, true);
	TestBio.resize(5);
	char posNeg = 1;
	//Random Values
	cout << '\t';
	for (int i{ 0 }; i < TestBio.size(); i++)
		cout << i << '\t';
	cout << endl;

	unsigned short nEdges = 0;

	for (int i{ 0 }; i < TestBio.size(); i++)
	{
		cout << i << '\t';
		TestBio.setNode(i, to_string(i));
		for (int j{ 0 }; j < TestBio.size(); j++)
		{
			float amount = (i+j) % 5 == 0 ? 0.0f : (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			TestBio.setEdge( i, j, ((i + j) % 2 == 0 ? -1 : 1) * amount);
			if (amount > FLT_EPSILON || amount < -FLT_EPSILON)
				nEdges++;
			cout.precision(2);
			cout << fixed << TestBio.getEdge(i, j) << '\t';
		}
		cout << endl;
	}
	for (int i{ 0 }; i < TestBio.size(); i++)
	{
		cout << "Element [ " << TestBio.getNode(i) << "]: " << TestBio.degree(i) << endl;
	}
	
	return TestBio.numberOfEdges() == nEdges;
}

void ExceptionTest()
{
	BioNet<int> TestBio;
	TestBio.resize(5);

	try {
		TestBio.getEdge(10, 3);
	}
	catch (BioNetException & e)
	{
		cout << "First Parameter of getEdge() -" << e.what() << endl;
	}

	try {
		TestBio.getEdge(3, 10);
	}
	catch (BioNetException & e)
	{
		cout << "Second Parameter of getEdge() -" << e.what() << endl;
	}

	try {
		TestBio.getNode(10);
	}
	catch (BioNetException & e)
	{
		cout << "Parameter of getNode() -" << e.what() << endl;
	}

}