#pragma once

#include "Edge.h"
#include <string>
using std::string;


/// A linked list for BioNet
/**
List impements linked list to represent the edges of a node. It also holds the name of the node.
*/
template<typename T>
class List {
private:
	string name;
	Edge<T> * head;
	bool doSearch(string name, Edge<T>* start) {
		if (start == NULL) return false;
		else if (start->getName() == name) return true;
		else return doSearch(name, start->getNext());
	}
	Edge<T>* recursiveDeleteEdge(Edge<T>* node, const string& name) {
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
	List() : head(nullptr) {}
	List(const T weight, const string& name) {
		this->name = name;
		head = new Edge<T>(weight, name, NULL);	}
	List(const List<T>& copy) {
		for (auto node = copy.head; node != nullptr; node = node->getNext())
			insertFront(node->getWeight(), node->getName());
	}
	List(const string& name)
	{
		this->name = name;
		head = 0;
	}
	~List() {
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
	Edge<T>* insertFront(const T weight, const string& name) {
		Edge<T>* newHead = new Edge<T>(weight, name, head);
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
		Edge<T>* temp = head;
		head = temp->getNext();
		delete temp;
		clear();
	}
	Edge<T>* front() const { return head; }
	List<T> operator*(const T weight) {
		List list(*this);
		for (auto node = list.head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() * weight);
		return list;
	}
	const List<T>& operator*=(const T weight) {
		for (auto node = head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() * weight);
		return *this;
	}
	List<T> operator/(const T weight) {
		List list(*this);
		for (auto node = list.head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() / weight);
		return list;
	}
	const List<T>& operator/=(const T weight) {
		for (auto node = head; node != nullptr; node = node->getNext())
			node->setWeight(node->getWeight() / weight);
		return *this;
	}
};
