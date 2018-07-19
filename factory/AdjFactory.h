#pragma once

#include "Adj.h"
#include "Exception.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <stdexcept>

using std::string;
using std::unordered_map;
using std::invalid_argument;

namespace BioNet {

	/**
	Implements Factory Pattern for GenericAdj 

	Contains a map of strings to funtion pointers for making children of GenericAdj

	Uses a static instance pointer so that the class is a singleton.

	*/
	class  AdjFactory {

	private:
		static bool instanceFlag;
		static AdjFactory *instance;
		AdjFactory() { instanceFlag = false; }

	public:
		unordered_map<string, GenericAdj* (*) ()> mFactoryMap;
		~AdjFactory() { instanceFlag = false; }
		/// Initializes the factory and maintains a single copy of the instance variable.
		/** Ensures that factory/singleton patterns are enforced to have one single instance.

		@return Unique factory instance to be available at runtime.
		*/
		static AdjFactory* getInstance();

		/// Adds the contructing function to mFactoryMap
		/**
		Adds the contructing function to mFactoryMap

		@param id - unique string identifier for the function being provided for the map.
		@param func - unique function for constructing desired underlying type.
		*/
		void RegisterType(const string & id, GenericAdj* (*f) ());

		/// Factory function utilized to create Adj network objects based on user's input and template type
		/**
		Factory function utilized to create Adj network objects based on user's input and template type

		@param type - generic/defined keyword provided for search of function map to retrieve the desired constructor.
		*/
		template<typename T>
		Adj<T>* create(const string & s, const string& nettype) {
			
			if (mFactoryMap.count(s) == 0)
				throw Exception("Error Creating network of type " + s + ".\n");
			else {
				Adj<T>* ret = static_cast<Adj<T> *>(mFactoryMap[s]());
				if (ret->getKeyword() != nettype) {
					throw std::invalid_argument("Input nettype does not match the registered Net type.");
				}
				return ret;
			}
		}
	};
}
