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

BioNode* BioList::insertFront(const float weight, const string& name) {
	BioNode* newHead = new BioNode(weight, name, head);
	head = newHead;
	return head;
}

void BioList::deleteNode(const string& name) {
	BioNode* temp = head;
	if (temp->getName() == name)
	{
		BioNode* tempNext = temp->getNext();
		delete temp->getNext();
		temp->setNext(tempNext);

		return;
	}
	while (temp->getNext()->getNext() != nullptr && temp->getNext()->getName() != name)
	{
		temp = temp->getNext(); 
	}
	if (temp->getNext()->getNext() == nullptr && temp->getNext()->getName() != name)
		cout << "Node " << name << " is not in the list" << endl;
	else
	{
		BioNode* tempNext = temp->getNext();
		delete temp->getNext();
		temp->setNext(tempNext);
	}

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
