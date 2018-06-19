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
	BioNet bioNet(-0.5, 0.5);

	//Verify node names
	if (bioNet.getName(0).compare("A") != 0) {
		cout << "Error on node A";
	}

	if (bioNet.getName(1).compare("B") != 0) {
		cout << "Error on node B";
	}

	if (bioNet.getName(2).compare("C") != 0) {
		cout << "Error on node C";
	}

	if (bioNet.getName(3).compare("D") != 0) {
		cout << "Error on node D";
	}

	if (bioNet.getName(4).compare("E") != 0) {
		cout << "Error on node E";
	}

	//Verify Edge's Weight


    return 0;
}
