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

	class AdjFactory {

	private:
		static bool instanceFlag;
		static AdjFactory *instance;
		AdjFactory() { instanceFlag = false; }


	public:
		unordered_map<string, GenericAdj* (*) ()> mFactoryMap;
		~AdjFactory() { instanceFlag = false; }

		static AdjFactory* getInstance() {
			if (!instanceFlag) {
				instance = new AdjFactory();
				instanceFlag = true;
				return instance;
			}
			else
				return instance;
		}

		/**
		Adds the contructing function to mFactoryMap

		@param id - unique string identifier for the function being provided for the map.
		@param func - unique function for constructing desired underlying type.
		*/
		void RegisterType(const string & id, GenericAdj* (*f) ()) { mFactoryMap[id] = f; }

		/**
		Factory function utilized to create Adj network objects based on user's input and template type

		@param type - generic/defined keyword provided for search of function map to retrieve the desired constructor.
		*/
		template<typename T>
		GenericAdj* create(string s) {
			return mFactoryMap[s]();
		}
	};
}
