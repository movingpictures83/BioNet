#pragma once

#include "../BioNet/BioNode.h"


#include <string>
using std::string;

class BioList {
private:
	string name;
	BioNode * head;
	bool doSearch(string name, BioNode* start);
	BioNode* recursiveDeleteEdge(BioNode*, const string&);
public:
	BioList() {}
	BioList(const float weight, const string& name);
	BioList(const BioList&);
	~BioList();
	bool search(const string& name) { return doSearch(name, head); }
	bool setWeight(const string& name, const float weight);
	string getName() const;
	void setName(const string&);
	void setEdgeName(const string&, const string&);
	float getWeight(const string& name) const;
	BioNode* insertFront(const float weight, const string& name);
	void deleteEdge(const string& name);
	void clear();
	BioNode* front() const { return head; }
	BioList operator*(const float weight);
	const BioList& operator*=(const float weight);
	BioList operator/(const float weight);
	const BioList& operator/=(const float weight);
};
