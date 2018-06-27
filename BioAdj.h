#pragma once
#include <string>
#include <exception>
#include <iostream>
using std::string;
using std::exception;
using std::cerr;
using std::endl;

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
	virtual void addNode(const string&) = 0;
	virtual void scaleWeights(const T&) = 0;

	template<typename U>
	void copy(const BioAdj<U>* rhs)
	{
		this->clear()
			this->resize(rhs->size());
		for (int i{ 0 }; i < rhs->size(); i++)
		{
			this->setNode(i, rhs->getNode(i));
			for (int j{ 0 }; i < rhs->size(); j++)
				this->setEdge((T)rhs->getEdge(i, j));
		};
	}
	virtual void copy(const BioAdj<T>* rhs) = 0;



	template<typename U>
	bool isEqual(const BioAdj<U>* rhs)
	{
		if (this->size() != rhs->size())
			return false;
		for (int i{ 0 }; i < this->size(); i++)
		{
			if (target->getNode(i).compare(rhs->getNode(i)))
				return false;
			for (int j{ 0 }; j < this->size(); j++)
			{
				if (target->getEdge(i, j) != (T)source->getEdge(i, j))
					return false
			}
		}
		return true;
	}

	virtual bool isEqual(const BioAdj<T>* == ) = 0;

	const auto& getKeyword() { return keyword; }
	//static Adj* make();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	////ADD TEAM


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	////EQUALS TEAM


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	////SCALE TEAM


	/////////////////////////////////////////////////////////////////////////////////////////////////////
};

/*template<typename T1, typename T2>
bool copy(BioAdj<T1>* target, BioAdj<T2>* source)
{
	try {
		target->clear;
		target->resize(source->size());
		for (int i{ 0 }; i < source->size(); i++)
		{
			target->setNode(i, source->getNode(i));
			for (int j{ 0 }; i < source->size(); j++)
				target->setEdge((T1)source->getEdge(i, j));
		}
	}
	catch (exception e)
	{
		cerr << e.what() << "Failed to copy." << endl;
		return false;
	}
	return true;
}*/
/*template<typename T, typename ... args>
bool func(T&& func, args&&... args)
{
	return func(args);
}
auto ret = func([](auto num) -> auto {return num != 0; }, 1);*/