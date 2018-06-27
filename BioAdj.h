#pragma once
#include <string>
using std::string;

class Adj {};

template <typename T=float>
class BioAdj : public Adj {
protected:
	string keyword;
public:
    // BioAdj();
	//~BioAdj();
	virtual void setEdge(const int, const int, const T) = 0;
	virtual void setEdge(const string&, const string&, const T) = 0;
	virtual T getEdge(const int, const int) const = 0;
	virtual T getEdge(const string&, const string&) const = 0;
	virtual void setNode(const int, const string&) = 0;
	virtual string getNode(const int) const = 0;
	virtual int size() const = 0;
	virtual T degree(const int) const = 0;
	virtual int numberOfEdges() const = 0;
	virtual void resize(const int) = 0;

	virtual int findNodeIndex(const string&) const =0;
	virtual void deleteEdge(const string&, const string&) =0;
	virtual void deleteEdge(int, int) = 0;
	virtual void deleteNode(const string&) = 0;
	virtual void deleteNode(int) = 0;

	template<typename U>
	virtual void copy(const BioAdj<U>*) = 0;
	virtual void addNode(const string&) = 0;
	virtual void scaleWeights(const T&) = 0;
	template<typename U>
	virtual void isEqual(const BioAdj<U>*) = 0;

	//static Adj* make();
};

