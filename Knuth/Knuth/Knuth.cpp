// Knuth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "../../BioNet.h"
#include "GMLReader.h"
#include "../../BioList.h"
#include "../../BioAdjList.h"

#include<vector>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	char ch;



	GMLReader gm("C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red.gml");
	BioNet bn(-1,1);
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red.gml");

	//First Node Test
	if (strcmp(bn.getNode(0).c_str(), "A") != 0)
		cout << "In 1st node got "<< bn.getNode(0) << "instead of A" << endl;
	//Forth Node Test
	if (strcmp(bn.getNode(3).c_str(), "D") != 0)
		cout << "In 4th node got " << bn.getNode(3) << "instead of D" << endl;
	//Last Node Test
	if (strcmp(bn.getNode(8).c_str(), "I") != 0)
		cout << "In Last node got " << bn.getNode(8) << "instead of I" << endl;

	if (!(fabs(0.9 - bn.getEdge(0, 1)) < FLT_EPSILON))
		cout << "Problem in connection between first & second node. Got "<< bn.getEdge(0, 1)<<"instead of 0.9"<< endl;

	if (!(fabs(0.8 - bn.getEdge(0, 2)) < FLT_EPSILON))
		cout << "Problem in connection between first & third node. Got " << bn.getEdge(0, 2) << "instead of 0.8" << endl;

	if (!(fabs(0.6 - bn.getEdge(3, 4)) < FLT_EPSILON))
		cout << "Problem in connection between 4th & 5th node. Got " << bn.getEdge(3, 4) << "instead of 0.6" << endl;

	if (!(fabs(0.5 - bn.getEdge(3, 5)) < FLT_EPSILON))
		cout << "Problem in connection between 4th & 6th node. Got " << bn.getEdge(3, 5) << "instead of 0.5" << endl;

	if (!(fabs(0.85 - bn.getEdge(7, 8)) < FLT_EPSILON))
		cout << "Problem in connection between 8th & 9th node. Got" << bn.getEdge(7, 8) << "instead of 0.85" << endl;
	
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_test_target.gml");
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_test_source.gml");
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_test_label.gml");
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_ID.gml");
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_boundary_test_weight2.gml");
	gm.ReadFile(bn, "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\three_triads_connect_green_red_boundary_test_weight2.gml");

	///////////// ----------BioList tests ------------//////////////
	BioList bl(0.8, "B");

	bl.deleteNode("C");
	/*if (bl.deleteNode("C")) {
		cout << "this was found and deleted";
	}
	else
	{
		cout << "delete failed";
	}*/
	if (bl.insertFront(0.9, "A")) {
		cout << "this node was inserted";
	}
	else
	{
		cout << "insertFront failed";
	}

	if (bl.search("D")) {
		cout << "this node was located";
	}
	else
	{
		cout << "Search failed..!!";
	}
	bl.clear();
	if (bl.search("A"))
		cout << "clear failed !!";

	if (bl.setWeight("G", 0.5))
	{
		cout << "weight set";
	}
	else {
		cout << "error occured while setting weight";
	}


	///////////// ----------BioList tests end ------------//////////////

	///-----BioAdjList tests---------------------///
	BioList bList(0.6, "A");

	vector<BioList> blvector;
	blvector.push_back(bList);
	blvector.push_back(bl);
	BioAdjList bioAdj(blvector);

	cout<< "First Node" << bioAdj.getNode(1);

	bioAdj.setNode(2, "C");
	cout<< "set 2nd node as " << bioAdj.getNode(2);

	bioAdj.setEdge(1, 2, 0.5);
	cout << "New edge should be 0.5 : " << bioAdj.getEdge(1, 2);

	
	///-----BioAdjList tests end---------------------///
	cin.get(ch);
	return 0;
	
}

