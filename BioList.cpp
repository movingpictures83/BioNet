#include "../BioNet/BioList.h"
#include "../BioNet/BioNet.h"


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

