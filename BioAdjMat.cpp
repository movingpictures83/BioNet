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


void BioAdjMat::deleteEdge(const string & istr, const string & jstr)
{

	int i = findNodeIndex(istr);
	int j = findNodeIndex(jstr);
	deleteEdge(i, j);
}
void BioAdjMat::deleteEdge(int i, int j)
{
	auto size = names.size();
	if (i < 0 || j < 0 || i >= size || j >= size)
		throw BioNetException("Trying to delete invaid edge");
	matrix[i][j] = 0;
}

void BioAdjMat::deleteNode(const string & nodeName)
{
	auto node = findNodeIndex(nodeName);
	deleteNode(node);
}
void BioAdjMat::deleteNode(int nodeIndex)
{
	auto size = names.size();
	if (nodeIndex < 0 || nodeIndex >= size )
		throw BioNetException("Trying to delete invaid Node");

	matrix.erase(matrix.begin() + nodeIndex);
	for (auto & node : matrix)
		node.erase(node.begin() + nodeIndex);
}