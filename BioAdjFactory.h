#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include "Adj.h"
#include "Exception.h"
//#include "BioAdjMat.h"
//#include "BioAdjList.h"

using std::string;
using std::unordered_map;
using std::function;

namespace BioNet {
	namespace BioAdjFactory {
		static unordered_map<string, function<GenericAdj*(void)>>mFactoryMap;

		static void RegisterType(const string & id, function<GenericAdj*(void)> func)
		{
		//	if(mFactoryMap.find(id) != mFactoryMap.end())
				mFactoryMap[id] = func;
		/*	else
				throw BioNetException("Error Creating network of type " + id + ".\n");*/
		}

		template<typename T>
		static Adj<T>* create(const string& type) {
			auto keyPair = mFactoryMap.find(type);
			if (keyPair != mFactoryMap.end())
				return static_cast<Adj<T> *>(keyPair->second());
			else
				throw BioNetException("Error Creating network of type " + type + ".\n");
		}
	}
}
