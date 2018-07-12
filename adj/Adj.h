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

	/// Generic Network class, agnostic of its underlying implementation
	/** to be used by a Factory to produce the different possible implementations of a Network
	*/
	//class Adj {};

	/// represents a **Network** with a selected implementation type (Matrix, List, etc.)
	/** - most methods will need to be overrided by each particular **Network** implementation
	- named methods (copy, isEqual, etc) are suposed to be used in the parent's class overrided operators
	*/
	template <typename T = float>
	class Adj : public GenericAdj {
	protected:
		string keyword;
	public:
		/// sets an **Edge** given the *indexes* of its neighboring **Nodes**
		virtual void setEdge(const int, const int, const T) = 0;
		/// sets an **Edge** given the *names* of its neighboring **Nodes**
		virtual void setEdge(const string&, const string&, const T) = 0;
		/// returns an **Edge** given the *indexes* of its neighboring **Nodes**
		virtual T getEdge(const int, const int) const = 0;
		/// returns an **Edge** given the *names* of its neighboring **Nodes**
		virtual T getEdge(const string&, const string&) const = 0;
		/// sets the name of a **Node**
		virtual void setNode(const int, const string&) = 0;
		/// returns the name of a **Node**
		virtual string getNode(const int) const = 0;
		/// returns the size of the **Network**
		virtual unsigned int size() const = 0;
		/// returns the sum of all weights of the **Edges** in the **Network**
		virtual T degree(const int) const = 0;
		/// returns the number of **Edges** in the **Network**
		virtual int numberOfEdges() const = 0;
		/// resizes the **Network** to a given size
		virtual void resize(const int) = 0;
		/// returns the internal index of a **Node** with the given name
		virtual int findNodeIndex(const string&) const = 0;
		/// removes an **Edge** given the *names* of its neighboring **Nodes**
		virtual void deleteEdge(const string&, const string&) = 0;
		/// removes an **Edge** given the *indexes* of its neighboring **Nodes**
		virtual void deleteEdge(int, int) = 0;
		/// removes the **Node** with the given *name*
		virtual void deleteNode(const string&) = 0;
		/// removes the **Node** byt its internal *index*
		virtual void deleteNode(int) = 0;
		/// adds a **Node** t the **Network** with the given name
		virtual void addNode(const string&) = 0;
		/// copies from another **Network** when both have the same *templated type*
		/**this should call the expectedly more efficient custom method for the internal implementation of the Network*/
		virtual void copy(const Adj<T>* rhs) = 0;
		/// checks if the current *Network** is the same as another (with the same *templated type*)
		/**this should call the expectedly more efficient custom method for the internal implementation of the Network*/
		virtual bool isEqual(const Adj<T>*) = 0;
		virtual void scaleUp(const T) = 0;
		virtual void scaleDown(const T) = 0;

		/// returns the keyword describing the current **Network** implementation
		const auto& getKeyword() { return keyword; }

		/// Copies from another **Network**
		/** - it will make the current **Network** the same size as the given source
		 - it considers the source could be of a different templated type as the destination
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
		/** - it considers both Networks could be of different templated types
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