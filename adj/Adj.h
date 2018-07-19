#pragma once
#include <string>
#include <exception>
#include <iostream>
#include "GenericAdj.h"
using std::string;
using std::exception;
using std::cerr;
using std::endl;

namespace BioNet {

	/**
	* Return the name of the tyepe T used by derived class Adj<T>
	* i.e Adj<int> gets "int".
	*/
	template <typename T>
	struct Keyword {
		static const string value;
	};

	const string Keyword<int>::value = "int";
	const string Keyword<float>::value = "float";
	const string Keyword<double>::value = "double";

	/// represents a **Network** with a selected implementation type (Matrix, List, etc.)
	/** - most methods will need to be overrided by each particular **Network** implementation
	- named methods (copy, isEqual, etc) are suposed to be used in the parent's class overrided operators
	*/
	template <typename T = float>
	class Adj : public GenericAdj {
	protected:
		const string keyword = Keyword<T>::value;
	public:
		/// sets an **Edge** given the *indexes* of its neighboring **Nodes**
		/**
		* sets an Edge given the indexes of its neighboring Nodes
		* first - Index of the origin node
		* second - Index of the destination node
		* third - weight value
		*/
		virtual void setEdge(const int, const int, const T) = 0;
		/// sets an **Edge** given the *names* of its neighboring **Nodes**
		/**
		* sets an Edge given the names of its neighboring Nodes
		*  first - Name of the origin node
		*  second - Name of the destination node
		*  third - weight value
		*/
		virtual void setEdge(const string&, const string&, const T) = 0;
		/// returns an **Edge** given the *indexes* of its neighboring **Nodes**
		/**
		* return an Edge given the indexes of its neighboring Nodes
		*  first - Index of the origin node
		*  second - Index of the destination node
		*  third - weight value
		*/
		virtual T getEdge(const int, const int) const = 0;
		/// returns an **Edge** given the *names* of its neighboring **Nodes**
		/**
		* return an Edge given the names of its neighboring Nodes
		*  first - Name of the origin node
		*  second - Name of the destination node
		*  third - weight value
		*/
		virtual T getEdge(const string&, const string&) const = 0;
		/// sets the name of a **Node**
		/**
		* sets the name of a **Node**
		*  first- Index of the node
		*  second- Name of the node
		*/
		virtual void setNode(const int, const string&) = 0;
		/// returns the name of a **Node**
		/**
		* returns the name of a **Node**
		* first - Index of the node
		*/
		virtual string getNode(const int) const = 0;
		/// returns the size of the **Network**
		/**
		* returns the size of the **Network**
		*/
		virtual int size() const = 0;
		/// returns the sum of all weights of the **Edges** in the **Network**
		/**
		* returns the sum of all weights of the **Edges** in the **Network**
		* first - Index of the node
		*/
		virtual T degree(const int) const = 0;
		/// returns the number of **Edges** in the **Network**
		/**
		* returns the number of **Edges** in the **Network**
		*/
		virtual unsigned int numberOfEdges() const = 0;
		/// resizes the **Network** to a given size
		/**
		* resizes the **Network** to a given size
		* first - New size
		*/
		virtual void resize(const int) = 0;
		/// returns the internal index of a **Node** with the given name
		/**
		* returns the internal index of a **Node** with the given name
		*/
		virtual int findNodeIndex(const string&) const = 0;
		/// removes an **Edge** given the *names* of its neighboring **Nodes**
		/**
		* removes an **Edge** given the *names* of its neighboring **Nodes**
		* first - node neighbor 1
		* second - node neighbor 2
		*/
		virtual void deleteEdge(const string&, const string&) = 0;
		/// removes an **Edge** given the *indexes* of its neighboring **Nodes**
		/**
		* removes an **Edge** given the *indexes* of its neighboring **Nodes**
		* first - index neighbor 1
		* second - index neighbor 2
		*/
		virtual void deleteEdge(int, int) = 0;
		/// removes the **Node** with the given *name*
		/**
		* removes the **Node** with the given *name*
		* param - Node name
		*/
		virtual void deleteNode(const string&) = 0;
		/// removes the **Node** byt its internal *index*
		/**
		* removes the **Node** byt its internal *index*
		* param - internal *index*
		*/
		virtual void deleteNode(int) = 0;
		/// adds a **Node** t the **Network** with the given name
		/**
		* adds a **Node** t the **Network** with the given name
		* param - Node name
		*/
		virtual void addNode(const string&) = 0;
		/// copies from another **Network** when both have the same *templated type*
		/**this should call the expectedly more efficient custom method for the internal implementation of the Network*/
		virtual void copy(const Adj<T>* rhs) = 0;
		/// checks if the current *Network** is the same as another (with the same *templated type*)
		/**this should call the expectedly more efficient custom method for the internal implementation of the Network*/
		virtual bool isEqual(const Adj<T>*) = 0;
		/**
		* Scale all edges weight multiplying by a given factor
		* first - factor
		*/
		virtual void scaleUp(const T) = 0;
		/**
		* Scale all edges weight dividing by a given factor
		* first - factor
		*/
		virtual void scaleDown(const T) = 0;
		/// returns the keyword describing the current **Network** implementation
		/**
		* returns the keyword describing the current **Network** implementation
		*/
		const string getKeyword() const override { return keyword; }

		/// Copies from another **Network**
		/** 
		* it will make the current **Network** the same size as the given source
		* it considers the source could be of a different templated type as the destination
		*/
		template<typename U>
		void copy(const Adj<U>* rhs)
		{
			this->clear();
			this->resize(rhs->size());
			for (int i{ 0 }; i < rhs->size(); i++)
			{
				this->setNode(i, rhs->getNode(i));
				for (int j{ 0 }; i < rhs->size(); j++)
					this->setEdge((T)rhs->getEdge(i, j));
			};
		}

		/// Checks if the current Network is equal to another
		/**
		* it considers both Networks could be of different templated types
		*/
		template<typename U>
		bool isEqual(const Adj<U>* rhs)
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
						return false;
				}
			}
			return true;
		}
	};
}