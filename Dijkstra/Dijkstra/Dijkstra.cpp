// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../../BioNet.h"
using std::cout;
using std::endl;
using std::fixed;
bool ShortestPathUnitTest();
bool UnitTest();
int main()
{
	cout << "======UNIT TEST======" << endl;
	UnitTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;

	cout << "======SHORTEST PATH UNIT TEST======";
	ShortestPathUnitTest() ? cout << "PASSED" << endl :  cout << "FAILED" << endl;
	
	return 0;
}

bool ShortestPathUnitTest()
{
	//Test for BioNet shortest path WIP
	BioNet net; // Default min -1 max 1
	net.reserve(3);
	net.setNode(0, "A");
	net.setNode(1, "B");
	net.setNode(2, "C");
	net.setEdge(0, 1, -1);
	net.setEdge(1, 2, 1);
	net.setEdge(0, 2, 1);
	return net.shortestPath(0, 2) == 1;
}

bool UnitTest()
{
	BioNet TestBio;
	TestBio.reserve(NETWORK_SIZE);
	char posNeg = 1;
	//Random Values
	cout << " \t0\t1\t2\t3\t4\n";
	for (int i{ 0 }; i < TestBio.size(); i++)
	{
		cout << i << '\t';
		for (int j{ 0 }; j < TestBio.size(); j++)
		{
			TestBio.setEdge( i, j, ((i + j) % 2 == 0 ? -1 : 1) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
			cout.precision(2);
			cout << fixed << TestBio.getEdge(i, j) << '\t';
		}
		cout << endl;
	}
	for (int i{ 0 }; i < TestBio.size(); i++)
	{
		cout << "Element# " << i << ": " << TestBio.degree(i) << endl;
	}
	return true;
}