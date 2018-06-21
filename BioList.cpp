#include "../BioNet/BioList.h"
#include "../BioNet/BioNet.h"
#include <iostream>

using std::cout;
using std::endl;

BioList::BioList(float weight, string index) {
	head = new BioNode(weight, index, NULL);
}

BioList::~BioList() {
	clear();
}

void BioList::clear() {
	if (head->getNext == NULL)
	{
		delete head;
		return;
	}
	BioNode* temp = head;
	head = temp->getNext;
	delete temp;
	clear();
}

bool BioList::doSearch(string name, BioNode* start) {
	if (start == NULL) return false;
	else if (start->getName() == name) return true;
	else return doSearch(name, start->getNext());
}

BioNode* BioList::insertFront(float weight, string name) {
	BioNode* newHead = new BioNode(weight, name, head);
	head = newHead;
	return head;
}

void BioList::deleteNode(string name) {
	BioNode* temp = head;
	if (temp->getName() == name)
	{
		BioNode* tempNext = temp->getNext();
		delete temp->getNext();
		temp->getNext = tempNext;

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
		temp->getNext = tempNext;
	}

}