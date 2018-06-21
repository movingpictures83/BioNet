// Turing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "CSVReader.h"
#include <string>

using std::cout;
using std::endl;

int main()
{
	string fileName = "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\mostextreme\\mostextreme.csv";
	CSVReader csvReader(fileName);
	BioNet bioNet(-0.5, 0.5, true);
	csvReader.readFile(bioNet);

	//Verify node names
	if (bioNet.getNode(0).compare("\"A\"") != 0) {
		cout << "Error on node A" << endl;
	}

	if (bioNet.getNode(1).compare("\"B\"") != 0) {
		cout << "Error on node B" << endl;
	}

	if (bioNet.getNode(2).compare("\"C\"") != 0) {
		cout << "Error on node C" << endl;
	}

	if (bioNet.getNode(3).compare("\"D\"") != 0) {
		cout << "Error on node D" << endl;
	}

	if (bioNet.getNode(4).compare("\"E\"") != 0) {
		cout << "Error on node E" << endl;
	}

	//Verify Edge's Weight
	float adjMatrix[5][5] = { 
							{ 0.5,-0.5,-0.5,-0.5,-0.5 },
							{ -0.5,0.5,0.5,0.5,0.5 }, 
							{ -0.5,0.5,0.5,0.5,0.5 }, 
							{ -0.5,0.5,0.5,0.5,0.5 }, 
							{ -0.5,0.5,0.5,0.5,0.5 } 
	};

	for (int row = 0; row < 5; ++row) 
		for (int col = 0; col < 5; ++col) 
			if (!(bioNet.getEdge(row, col) > adjMatrix[row][col] - .001 && bioNet.getEdge(row, col) < adjMatrix[row][col] + .001))
				cout << "Edge at " << row << " ," << col << " is incorrect. Expected: " << bioNet.getEdge(row, col) << " Recieved: "  << adjMatrix[row][col] << endl;
	

    return 0;
}
