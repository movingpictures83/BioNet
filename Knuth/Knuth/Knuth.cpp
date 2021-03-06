// Knuth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "Net.h"
#include "GMLHandler.h"
#include "List.h"
#include "AdjList.h"
#include "Reader.h"
#include "Writer.h"

#include<vector>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace BioNet;

int main()
{
	char ch;
	cout << "STARTING TESTS FOR BIONET" << "\n";

	string fname = "three_triads_connect_green_red.gml";
	Net<float> bn(-1.0,1.0, false, "BioAdjListFloat");
	Reader::readFile<GMLHandler>(bn, fname);

	//First Node Test
	if (strcmp(bn.getNode(0).c_str(), "A") != 0)
		cout << "In 1st node got "<< bn.getNode(0) << "instead of A" << "\n";
	//Forth Node Test
	if (strcmp(bn.getNode(3).c_str(), "D") != 0)
		cout << "In 4th node got " << bn.getNode(3) << "instead of D" << "\n";
	//Last Node Test
	if (strcmp(bn.getNode(8).c_str(), "I") != 0)
		cout << "In Last node got " << bn.getNode(8) << "instead of I" << "\n";

	if (!(fabs(0.9 - bn.getEdge(0, 1)) < FLT_EPSILON))
		cout << "Problem in connection between first & second node. Got "<< bn.getEdge(0, 1)<<"instead of 0.9"<< "\n";

	if (!(fabs(0.8 - bn.getEdge(0, 2)) < FLT_EPSILON))
		cout << "Problem in connection between first & third node. Got " << bn.getEdge(0, 2) << "instead of 0.8" << "\n";

	if (!(fabs(0.6 - bn.getEdge(3, 4)) < FLT_EPSILON))
		cout << "Problem in connection between 4th & 5th node. Got " << bn.getEdge(3, 4) << "instead of 0.6" << "\n";

	if (!(fabs(0.5 - bn.getEdge(3, 5)) < FLT_EPSILON))
		cout << "Problem in connection between 4th & 6th node. Got " << bn.getEdge(3, 5) << "instead of 0.5" << "\n";

	if (!(fabs(0.85 - bn.getEdge(7, 8)) < FLT_EPSILON))
		cout << "Problem in connection between 8th & 9th node. Got" << bn.getEdge(7, 8) << "instead of 0.85" << "\n";
	
	cout << "READ SUCCESSFUL \n" << endl;
/*	string path;
	path = "three_triads_connect_strong_green_red_test_target.gml"; // tests exception wrong target
	Reader::readFile<GMLHandler>(bn, path);
	path = "three_triads_connect_strong_green_red_test_source.gml"; // tests exception wrong source
	Reader::readFile<GMLHandler>(bn, path);
	path = "three_triads_connect_strong_green_red_test_label.gml";
	Reader::readFile<GMLHandler>(bn, path);
	path = "three_triads_connect_strong_green_red_test_Id.gml";
	Reader::readFile<GMLHandler>(bn, path);
	path = "three_triads_connect_strong_green_red_boundary_test_weight2.gml";
	Reader::readFile<GMLHandler>(bn, path);
	path = "three_triads_connect_strong_green_red_boundary_test_weight1.gml";
	Reader::readFile<GMLHandler>(bn, path);
	*/

	cout << "Writing to write_test_1.gml ..." << endl;
	string path = "write_test_1.gml";
	Writer::writeFile<GMLHandler>(bn, path);
	

	///////////// ----------BioList tests ------------//////////////
	string str = "B";
	List<float> bl(str);

	bl.deleteEdge("C");
	/*if (bl.deleteNode("C")) {
		cout << "this was found and deleted";
	}
	else
	{
		cout << "delete failed";
	}*/
	if (!bl.insertFront(0.9, "A"))
		cout << "insertFront failed" << "\n";

	bl.insertFront(0.4, "D");
	if (!bl.search("D"))
		cout << "Search failed..!!" << "\n";
	
	bl.clear();
	if (bl.search("A"))
		cout << "clear failed !!" << "\n";

	if (!bl.setWeight("G", 0.5))
		cout << "error occured while setting weight";


	///////////// ----------BioList tests end ------------//////////////

	///-----BioAdjList tests---------------------///
	
	bn.setNode(0, "A");
	bn.setNode(1, "B");
	bn.setNode(2, "C");

	bn.setEdge(0, 1, 0.1);
	bn.setEdge(0, 2, 0.2);
	bn.setEdge(1, 2, 0.15);

	cout<< "First Node should be A:" << bn.getNode(0) << "\n";

	cout<< "2nd node should be B: " << bn.getNode(1) << "\n";

	cout << "Edge between B and C should be 0.15: " << bn.getEdge(1, 2) << endl;

	
	///-----BioAdjList tests end---------------------///
	cin.get(ch);
	return 0;
	
}

