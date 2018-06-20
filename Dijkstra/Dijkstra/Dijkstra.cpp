﻿// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../../BioNet.h"
#include "../../BioNetException.h"

using std::cout;
using std::endl;
using std::fixed;
bool ShortestPathUnitTest();
bool UnitTest();
void ExceptionTest();

int main()
{
	cout << "======UNIT TEST======" << endl;
	UnitTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;

	cout << "======SHORTEST PATH UNIT TEST======" << endl;

	ShortestPathUnitTest() ? cout << "PASSED" << endl :  cout << "FAILED" << endl;
	
	cout << "======Exception UNIT TEST======" << endl;
	ExceptionTest();
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

void ExceptionTest()
{
	BioNet TestBio;
	TestBio.reserve(NETWORK_SIZE);

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