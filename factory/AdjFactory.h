#pragma once

#include "Adj.h"
#include "Exception.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>

using std::string;
using std::unordered_map;
using std::function;

namespace BioNet {
	namespace AdjFactory {

		///Static map object for factory that maps a function to string
		static unordered_map<string, function<GenericAdj*(void)>>mFactoryMap;

		/**
		Adds the contructing function to mFactoryMap

		@param id - unique string identifier for the function being provided for the map.
		@param func - unique function for constructing desired underlying type.
		*/
		static void RegisterType(const string & id, function<GenericAdj*(void)> func)	{	mFactoryMap[id] = func;	}

		/**
		Factory function utilized to create Adj network objects based on user's input and template type

		@param type - generic/defined keyword provided for search of function map to retrieve the desired constructor.
		*/
		template<typename T>
		static Adj<T>* create(const string& type) {
			auto keyPair = mFactoryMap.find(type);
			if (keyPair != mFactoryMap.end())
				return static_cast<Adj<T> *>(keyPair->second());
			else
				throw Exception("Error Creating network of type " + type + ".\n");
		}
	}
}
