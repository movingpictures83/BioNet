#pragma once

#include "Adj.h"
#include "Exception.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>

using std::string;
using std::unordered_map;

namespace BioNet {

	/// AdjFactory implements the Factory Pattern for Adj
	class  AdjFactory {

	private:
		static bool instanceFlag;
		static AdjFactory *instance;
		AdjFactory() { instanceFlag = false; }

	public:
		unordered_map<string, GenericAdj* (*) ()>mFactoryMap;
		~AdjFactory() { instanceFlag = false; }

		/// Initializes the factory and maintains a single copy of the instance variable.
		/** The instance AdjFactory variable, once initialized, will be the only one able to be created (singleton).
		*/
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
		void RegisterType(const string & id, GenericAdj* (*f) ()) { 
			mFactoryMap[id] = f; 
		}

		/**
		Factory function utilized to create Adj network objects based on user's input and template type

		@param type - generic/defined keyword provided for search of function map to retrieve the desired constructor.
		*/
		template<typename T>
		static Adj<T>* create(const string & s) {
			return mFactoryMap[s]();
		}
	};
}
