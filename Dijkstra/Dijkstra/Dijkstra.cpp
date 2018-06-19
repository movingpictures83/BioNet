// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../../BioNet.h"
using std::cout;
using std::endl;

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
	return 0;
}