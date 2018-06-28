#pragma once
#include <string>
#include <exception>
#include <iostream>
#include "Adj\GenericAdj.h"
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
		virtual int findNodeIndex(const string&) const = 0;
		virtual void deleteEdge(const string&, const string&) = 0;
		virtual void deleteEdge(int, int) = 0;
		virtual void deleteNode(const string&) = 0;
		virtual void deleteNode(int) = 0;
		virtual void addNode(const string&) = 0;
		virtual void copy(const Adj<T>* rhs) = 0;
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

}