#pragma once

#include "../BioNet/BioNode.h"


#include <string>
using std::string;

template<typename T>
class BioList {
private:
	string name;
	BioEdge<T> * head;
	bool doSearch(string name, BioEdge<T>* start) {
		if (start == NULL) return false;
		else if (start->getName() == name) return true;
		else return doSearch(name, start->getNext());
	}
	BioEdge<T>* recursiveDeleteEdge(BioEdge<T>* node, const string& name) {
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
public:
	BioList() {}
	BioList(const T weight, const string& name) {
		this->name = name;
		head = new BioEdge<T>(weight, name, NULL);	}
	BioList(const BioList<T>& copy) {
		for (auto node = copy.head; node != nullptr; node = node->getNext())
			insertFront(node->getWeight(), node->getName());
	}
	~BioList() {
		clear();
	}
	bool search(const string& name) { return doSearch(name, head); }
	bool setWeight(const string& name, const T weight) {
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
	string getName() const { return name; }
	void setName(const string& s) { name = s; }
	void setEdgeName(const string& oldName, const string& newName) {
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
	T getWeight(const string& name) const {
		auto * current = head;
		while (current)
		{
			if (current->getName() == name)
				return current->getWeight();
			current = current->getNext();
		}
		return 0;
	}
	BioEdge<T>* insertFront(const T weight, const string& name) {
		BioEdge<T>* newHead = new BioEdge<T>(weight, name, head);
		head = newHead;
		return head;
	}
	void deleteEdge(const string& name) {
		head = recursiveDeleteEdge(head, name);
	}
	void clear() {
		if (head->getNext() == NULL)
		{
			delete head;
			return;
		}
		BioEdge<T>* temp = head;
		head = temp->getNext();
		delete temp;
		clear();
	}
	BioEdge<T>* front() const { return head; }
	BioList<T> operator*(const T weight) {
		BioList list(*this);
		for (auto node = list.head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() * weight);
		return list;
	}
	const BioList<T>& operator*=(const T weight) {
		for (auto node = head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() * weight);
		return *this;
	}
	BioList<T> operator/(const T weight) {
		BioList list(*this);
		for (auto node = list.head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() / weight);
		return list;
	}
	const BioList<T>& operator/=(const T weight) {
		for (auto node = head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() / weight);
		return *this;
	}
};
