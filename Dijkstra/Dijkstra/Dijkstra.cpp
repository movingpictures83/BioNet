// Dijkstra.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
#include <algorithm>
#include "../../BioNet.h"
#include "../../BioNetException.h"

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

int main()
{
	cout << "======UNIT TEST======" << endl;
	UnitTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;

	cout << "======SHORTEST PATH UNIT TEST======" << endl;

	ShortestPathUnitTest() ? cout << "PASSED" << endl :  cout << "FAILED" << endl;
	
	cout << "======Exception UNIT TEST======" << endl;
	ExceptionTest();
	UndirectedTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	return 0;
}

bool ShortestPathUnitTest()
{
	//Test for BioNet shortest path WIP
	BioNet<float> net; // Default min -1 max 1
	net.resize(3);
	net.setNode(0, "A");
	net.setNode(1, "B");
	net.setNode(2, "C");
	net.setEdge(0, 1, -1);
	net.setEdge(1, 2, 1);
	net.setEdge(0, 2, 1);
	return net.shortestPath(0, 2) == 1;
}

bool UndirectedTest()
{
	try
	{
		BioNet<float> net;
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
	BioNet<float> TestBio;
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