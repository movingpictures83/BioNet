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
	cout << "Rafa was here." << endl;
    cout << "Luis' commit\n";
	cout << "Hello World!" << endl;
	cout << "From Lian MO.";
	cout << "Daniel's code was here...\n";
	
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