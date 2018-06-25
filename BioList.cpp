#include "../BioNet/BioList.h"
#include "../BioNet/BioNet.h"
#include <iostream>

using std::cout;
using std::endl;

BioList::BioList(const float weight, const string& index) {
	head = new BioNode(weight, index, NULL);
}

BioList::~BioList() {
	clear();
}

void BioList::clear() {
	if (head->getNext() == NULL)
	{
		delete head;
		return;
	}
	BioNode* temp = head;
	head = temp->getNext();
	delete temp;
	clear();
}

bool BioList::doSearch(const string name, BioNode* start) {
	if (start == NULL) return false;
	else if (start->getName() == name) return true;
	else return doSearch(name, start->getNext());
}

BioNode* BioList::recursiveDeleteEdge(BioNode * node, const string& name)
{
	if (node == nullptr)
		return nullptr;

	if (node->getName() == name)
	{
		auto temp = node->getNext();
		delete node;
		return temp;
	}

	node->setNext(recursiveDeleteEdge(node->getNext(), name));
	return node;
}

BioNode* BioList::insertFront(const float weight, const string& name) {
	BioNode* newHead = new BioNode(weight, name, head);
	head = newHead;
	return head;
}

void BioList::deleteEdge(const string& name) {

	head = recursiveDeleteEdge(head, name);

}

bool BioList::setWeight(const string& name, const float weight)
{ 
	auto * current = head;
	while (current)
	{
		if (current->getName() == name)
		{
			current->setWeight(weight);
			return true;
		}
		current = current->getNext();
	}
	return false;
}

float BioList::getWeight(const string& name) const 
{
	auto * current = head;
	while (current)
	{
		if (current->getName() == name)
			return current->getWeight();
		current = current->getNext();
	}
	return 0;
}

string BioList::getName() const {
	return name;
}

void BioList::setName(const string& n)
{
	name = n;
}

void BioList::setEdgeName(const string& oldName, const string& newName)
{
	auto* node = head;
	while (node)
	{
		if (node->getName() == oldName)
		{
			node->setName(newName);
			break;
		}
	}
}
