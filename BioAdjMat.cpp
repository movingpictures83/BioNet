#include "BioAdjMat.h"
#include "BioNetException.h"

int BioAdjMat::findNodeIndex(const string & lookup)
{
	int index = 0;
	for (auto node : names)
	{
		if (node == lookup)
			return index;

		index++;
	}
	return -1;
}
void BioAdjMat::setNode(int index, string name)
{
	if (index >= names.size())
		throw BioNetException("Trying to add name out of range");

	names[index] = name;
}

string BioAdjMat::getNode(int index)
{
	if (index >= names.size())
		throw BioNetException("Trying to add name out of range");

	return names[index];
}


void BioAdjMat::deleteEdge(string istr, string jstr)
{

	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}
void BioAdjMat::deleteEdge(int i, int j)
{
	int size = names.size();
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw BioNetException("Trying to delete invaid edge");
	matrix[i][j] = 0;
}

void BioAdjMat::deleteNode(string)
{

}
void BioAdjMat::deleteNode(int)
{

}