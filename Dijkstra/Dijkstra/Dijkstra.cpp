// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../../BioNet.h"
using std::cout;
using std::endl;
using std::fixed;

bool UnitTest();
int main()
{
	//Test for BioNet shortest path WIP
	BioNet net; // Default min -1 max 1
	net.setNode(0, "A");
	net.setNode(1, "B");
	net.setNode(2, "C");
	net.setEdge(0, 1, -1);
	net.setEdge(1, 2, 1);
	net.setEdge(0, 2, 1);
	//int shortest_path = net.shortestPath(0, 2)
	UnitTest();
	return 0;
}

bool UnitTest()
{
	BioNet TestBio;
	char posNeg = 1;
	//Random Values
	cout << " \t0\t1\t2\t3\t4\n";
	for (int i{ 0 }; i < NETWORK_SIZE; i++)
	{
		cout << i << '\t';
		for (int j{ 0 }; j < NETWORK_SIZE; j++)
		{
			TestBio.setEdge( i, j, ((i + j) % 2 == 0 ? -1 : 1) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
			cout.precision(2);
			cout << fixed << TestBio.getEdge(i, j) << '\t';
		}
		cout << endl;
	}
	for (int i{ 0 }; i < NETWORK_SIZE; i++)
	{
		cout << "Element# " << i << ": " << TestBio.degree(i) << endl;
	}
	return true;
}