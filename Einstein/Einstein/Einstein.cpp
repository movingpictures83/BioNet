
// Einstein.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "../../Net.h"

using std::cout;
using std::endl;

int main() {
	cout << "Hello, World!" << endl;
	cout << "Quick Test as a console program" << endl;

	cout << "- Creates a BioNet" << endl;
	//BioNet<float> b = BioNet<float>(-1, 1, false, string("matrix"));
	BioNet::Net<float> b = BioNet::Net<float>();

	cout << "- Resizes it" << endl;
	b.resize(7);
	cout << "- Sets a particular Edge inside it" << endl;
	b.setEdge(3, 2, 3);
	cout << "- Shows all Edges" << endl;
	for (int i = 0; i < b.size(); ++i)
	{
		for (int j = 0; j < b.size(); ++j)
		{
			float min = b.getMinWeight();
			float max = b.getMaxWeight();
			cout << " Show Edge: [" << i << ", " << j << "]: " << b.getEdge(i,j) << endl;

			//Assert::IsTrue(b.getEdge(i, j) >= min);
			//Assert::IsTrue(b.getEdge(i, j) <= max);
		}
	}

	cout << "- All Done" << endl;
    return 0;
}

