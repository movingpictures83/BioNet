#include "../BioNet/BioList.h"
#include "../BioNet/BioNet.h"


BioList::BioList(float weight, string index) {
	head = new BioNode(weight, index, NULL);
}

BioList::~BioList() {
	clear();
}

void BioList::clear() {}

bool BioList::doSearch(string name, BioNode* start) {
	if (start == NULL) return false;
	else if (start->getName() == name) return true;
	else return doSearch(name, start->getNext());
}