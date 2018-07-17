// Dijkstra.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
#include <algorithm>
#include "..\..\Net.h"

#include "..\..\adj\AdjList.h"
#include "..\..\adj\List.h"
#include "..\..\exception\IncorrectFileFormatException.h"
#include "..\..\exception\FileNotExistException.h"
#include "..\..\exception\DataInvalidFormatException.h"
#include "..\..\exception\Exception.h"
#include "..\..\factory\AdjFactory.h"
#include "..\..\adj\AdjMat.h"
#include "..\..\adj\AdjBasic.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::fixed;
using std::for_each;
using namespace BioNet;
using BioNet::Net;

bool ShortestPathUnitTest();
bool UnitTest();
void ExceptionTest();
bool UndirectedTest();
void UnitTestRegister();
bool BioListTest();
bool BioListOperatorTest();
bool BioAdjListTest();
void BioAdjBasicTest();
bool OperatorTest();
bool OperatorsTest();
Net<int> createTestBioNet_BioAdjListInt(int size);


bool fequal(float a, float b) {
	return fabs(b - a) < FLT_EPSILON;
}

int main()
{
	
	cout << "======BIOLIST TEST======" << endl;
	BioListTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	cout << "======BIOADJLIST TEST======" << endl;

	cout << "======UNIT TEST======" << endl;
	UnitTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	cout << "======Operators Test======" << endl;
	OperatorsTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	cout << "======SHORTEST PATH UNIT TEST======" << endl;

	ShortestPathUnitTest() ? cout << "PASSED" << endl :  cout << "FAILED" << endl;
	//
	cout << "======Exception UNIT TEST======" << endl;
	ExceptionTest();
	cout << "======Undirected UNIT Test======" << endl;
	UndirectedTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	
	cout << "====== Register Test ======" << endl;
	UnitTestRegister();
	
	cout << endl << "======ADJ BASIC TEST START ======" << endl;
	BioAdjBasicTest();
	cout << "======ADJ BASIC TEST END ======" << endl << endl;

	cout << "====== BioList Operator Test ======" << endl;
	
	cout << "======OPERATOR TEST======" << endl;
	OperatorTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;

	cout << "======BIO LIST OPERATOR TEST======" << endl;
	BioListOperatorTest() ? cout << "PASSED" << endl : cout << "FAILED" << endl;
	
	

	return 0;
}

void BioAdjBasicTest()
{
	AdjBasic<float> arr(3);
	arr.setNode(0, "A");
	arr.setNode(1, "B");
	
	arr.setEdge("A", "B", 0.5);
	arr.setEdge("B", "A", -0.5);
	arr.setEdge("A", "A", 1.0);
	arr.setEdge("B", "B", 1.0);
	
	// Add New Node
	arr.setNode(2, "C");

	arr.setEdge("A", "C", 0.7);
	arr.setEdge("B", "C", 0.8);
	arr.setEdge("C", "C", 1.0);

	AdjBasic<float> copyarr(3);
	//arr.copy(arr<T>);
	
	// Testing of GetEdge Function
	float nWeight = 0.0;
	nWeight = arr.getEdge("A", "B");
	if (fequal(nWeight,0.5))
		cout << "1. ADJ BASIC TEST WEIGHT PASSED" << endl;
	else
		cout << "1. ADJ BASIC TEST WEIGHT FAILED" << endl;

	// Testing of Find Node Index
	int index = arr.findNodeIndex("C");
	if(index ==2)
		cout << "2. ADJ BASIC FIND NODE INDEX PASSED" << endl;
	else
		cout << "2. ADJ BASIC FIND NODE INDEX FAILED" << endl;

	// Testing for degree
	float degree = arr.degree(0);  // Get degree for Node -'A'
	if (fequal(degree,1.7))
		cout << "3. ADJ BASIC TEST DEGREE PASSED" << endl;
	else
		cout << "3. ADJ BASIC TEST DEGREE FAILED" << endl;

	
	// Testing for Node Delete
	arr.deleteNode("A");
	if(arr.size() == 2 && arr.numberOfEdges() == 3)
		cout << "4. ADJ BASIC NODE & EDGE DELETE PASSED" << endl;
	else
		cout << "4. ADJ BASIC NODE & EDGE DELETE FAILED" << endl;
}

bool OperatorsTest() {
	return false;
}

bool ShortestPathUnitTest()
{
	//Test for BioNet shortest path WIP
	Net<int> net; // Default min -1 max 1
	net.resize(3);
	net.setNode(0, "A");
	net.setNode(1, "B");
	net.setNode(2, "C");
	net.setEdge(0, 1, -1);
	net.setEdge(1, 2, 1);
	net.setEdge(0, 2, 1);
	return net.shortestPath(0, 1) == -1;
}

bool BioAdjListTest() {
	AdjList<int> list;
	if (list.size() != 5) return false;
	list.setNode(0, "A");
	list.setNode(1, "B");
	list.setNode(2, "C");
	list.setNode(3, "D");
	list.setNode(4, "E");
	if (list.degree(0) != 0 && list.degree(1) != 0 && list.degree(2) != 0 && list.degree(3) != 0 && list.degree(4) != 0) return false;
	list.setEdge("A", "B", 1);
	list.setEdge("B", "C", 2);
	list.setEdge("C", "D", 3);
	list.setEdge("D", "E", 4);
	auto x = list.getEdge("A", "B");
	list.scaleUp(10);
	x = list.getEdge("A", "B");
	if (list.getEdge("A", "B") != 10 && list.getEdge("B", "C") != 20
		&& list.getEdge("C", "D") != 30
		&& list.getEdge("D", "E") != 40) return false;
	list.scaleDown(10);
	if (list.getEdge("A", "B") != 1 && list.getEdge("B", "C") != 2
		&& list.getEdge("C", "D") != 3
		&& list.getEdge("D", "E") != 4) return false;
	list.setEdge("A", "B", 25);
	if (list.getEdge("A", "B") != 25) return false;
	if (list.findNodeIndex("E") != 4) return false;
	if (list.numberOfEdges() != 4) return false;
	return true;
}


bool BioListTest() {
	List<float> list("Sodium");
	if (list.getName() != "Sodium") return false;
	list.insertFront(0.2f, "Carbon Dioxide");;
	list.insertFront(0.3f, "Sodium Chloride");
	if (!list.search("Sodium Chloride")) return false;
	if (!fequal(list.getWeight("Carbon Dioxide"), 0.2f)) return false;
	list.setWeight("Sodium Chloride", 1.5f);
	if (!fequal(list.getWeight("Sodium Chloride"), 1.5f)) return false;
	return true;
}

bool BioListOperatorTest() {

	Net<float> aNet;
	aNet.resize(3);
	aNet.setRange(10.0f, 10.0f);
	aNet.setNode(0, "Sodium");
	aNet.setNode(1, "Carbon Dioxide");
	aNet.setNode(2, "Sodium Chloride");

	aNet.setEdge(0, 1, 0.5f);
	aNet.setEdge(1, 2, 1.0f);
	aNet.setEdge(0, 2, 1.5f);


	aNet *= 2.0f;

	if (aNet.getEdge(0, 1) != 1 || aNet.getEdge(1, 2) != 2 || aNet.getEdge(0, 2) != 3)
		return false;
	return true;
}

bool UndirectedTest()
{
	try
	{
		Net<int> net;
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
	Net<float> TestBio(-1, 1, true);
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

			float amount = (i + j) % 5 == 0 ? 0.0f : (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			float amount1 = TestBio.getEdge(j, i);
			if ( amount1 != 0)
			{
				amount = amount1;
				int test = 0;
				test = 1;
			}
			
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
	Net<int> TestBio;
	TestBio.resize(5);
	
	try {
		TestBio.getEdge(10, 3);
	}
	catch (Exception & e)
	{
		cout << "First Parameter of getEdge() -" << e.what() << endl;
	}

	try {
		TestBio.getEdge(3, 10);
	}
	catch (Exception & e)
	{
		cout << "Second Parameter of getEdge() -" << e.what() << endl;
	}

	try {
		TestBio.getNode(10);
	}
	catch (Exception & e)
	{
		cout << "Parameter of getNode() -" << e.what() << endl;
	}
	
}

void UnitTestRegister()
{
	try {
		Adj<int> * e = AdjFactory::create<int>(AdjMat<int>::NetworkType());
		e->resize(10);
		auto const val = e->getEdge(0, 0);
		if (typeid(decltype(val)) == typeid(int))
			cout << "Correct Type" << endl;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}

}

bool OperatorTest()
{
	bool success = true;
	Net<int> bn = createTestBioNet_BioAdjListInt(5);

	// Operator ()
	if (bn(2, 3) != 6) success = false;

	// Operator ()
	if (bn("Node3", "Node4") != 12) success = false;

	// Operator +=
	bn += "First";
	if (bn[26] != "First") success = false; //26?

	// Operator +


	return success;
}

Net<int> createTestBioNet_BioAdjListInt(int size)
{
	Net<int> bn = Net<int>(0, size*size, true, "BioAdjListInt");

	for (int i = 0; i < size; ++i)
	{
		bn.setNode(i, "Node" + std::to_string(i));
	}
	for (int i = 1; i < size; ++i)
	{
		for (int j = 1; j < size; ++j)
		{
			if (i != j)
			{
				bn.setEdge(i, j, i*j);
			}
		}
	}

	return bn;
}