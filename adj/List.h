#pragma once

#include "Edge.h"
#include <string>
using std::string;

namespace BioNet
{
	/// A linked list for BioNet
	/**
	List impements linked list to represent the edges of a node.
	*/
	template<typename T>
	class List {
	private:
		/// Name of the List
		string name;
		/// The starting Edge in the list
		Edge<T> * head;
		/// Recursive helper function to search over the linked list for a specific destination edge.
		/**
		@return Returns true if the search was successful
		@param name Name of the List
		@param start The first Edge in the List
		*/
		bool doSearch(string name, Edge<T>* start) {
			if (start == NULL) return false;
			else if (start->getName() == name) return true;
			else return doSearch(name, start->getNext());
		}

		/// Recursive helper function to delete a node from the linked list.
		/**
		@return Edge<T>* The delete Edge's next
		@param node The Edge to delete
		@param name The name of the Node
		*/
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

		/// Recursive helper function to delete the linked list.
		/**
		@param node The starting node of the List
		*/
		void recursiveClear(Edge<T>* node)
		{
			if (node)
			{
				recursiveClear(node->getNext());
				delete node;
			}
		}
	public:
		/// Default constructor, initializes linked list to null.
		/**
		*/
		List() : head(nullptr) {}

		/// Copy constructor
		/**
		@param copy List to copy
		*/
		List(const List<T>& copy) {
			this->name = copy.name;
			this->head = nullptr;

			for (auto node = copy.head; node != nullptr; node = node->getNext())
				insertFront(node->getWeight(), node->getName());
		}
		/// Main Constructor
		/**
		@param name Name of the node
		*/
		List(const string& name)
		{
			this->name = name;
			head = 0;
		}
		/// Destructor
		/**
		Destroys all edge instances and releases all resources allocated by List.
		*/
		~List() {
			clear();
		}
		/// Recursively search for a node on the linked list.
		/**
		@return Returns if the search was successful or not
		@param name Name of the destination node of the edge.
		*/
		bool search(const string& name) { return doSearch(name, head); }
		/// Sets the weight of an edge
		/**
		@return Returns true if the setWeight was successful
		@param name Name of the destination node of the edge.
		@param weight New weight of the edge.
		*/
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
		/// Get accessor method for the name of the node.
		/**
		@return Name of the node.
		*/
		string getName() const { return name; }

		/// Set accessor method for the name of the node.
		/**
		@param s New name for the node.
		*/
		void setName(const string& s) { name = s; }

		/// Set accessor method for the name of the destination node of an edge.
		/**
		@param oldName Old name for the destination node on an edge.
		@param newName New name for the destination node on an edge.
		*/
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

		/// Get accessor method for the weight of an edge.
		/**
		@param name Name of the destination node of the edge.
		@return Weight of the edge.
		*/
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

		///Add a new edge to the node.
		/**
		The edge is inserted at the front of the linked list.
		@param weight Weight of the new node.
		@param name Name of the destination node.
		@return A pointer to the new edge.
		*/
		Edge<T>* insertFront(const T weight, const string& name) {
			Edge<T>* newHead = new Edge<T>(weight, name, head);
			head = newHead;
			return head;
		}

		/// Recursively deletes an edge from the node.
		/**
		@param name Name of the destiantion node of the edge to be deleted.
		*/
		void deleteEdge(const string& name) {
			head = recursiveDeleteEdge(head, name);
		}

		/// An iterative delete edge function
		/**
		@param name Name of the edge to delete
		*/
		void deleteEdgeIter(const string& name)
		{
			Edge<T> temp;
			while (head != NULL)
			{
				temp = head;
				head = head->next;
				delete temp;
			}
		}

		/// Recursively releases all edges of the node.
		/**
		All edges instances are destroyed.
		*/
		void clear()
		{
			recursiveClear(head);
		}

		/// Get accessor method for the head of the linked list of edges.
		/**
		@return The first Edge on the linked list.
		*/
		Edge<T>* front() const { return head; }
	};
}