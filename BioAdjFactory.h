#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include "BioAdj.h"
#include "BioAdjMat.h"
#include "BioNetException.h"
//#include "BioAdjList.h"

using std::string;
using std::unordered_map;
using std::function;

namespace BioAdjFactory {
	static unordered_map<string, function<Adj*(void)>>mFactoryMap;

	static void RegisterType(const string & id, function<Adj*(void)> func)
	{
		if(mFactoryMap.find(id) != mFactoryMap.end())
			mFactoryMap[id] = func;
		else
			throw BioNetException("Error Creating network of type " + id + ".\n");
	}

	template<typename T>
	static BioAdj<T>* create(const string& type) {
		auto keyPair = mFactoryMap.find(type);
		if (keyPair != mFactoryMap.end())
			return static_cast<BioAdj<T> *>(keyPair->second());
		else
			throw BioNetException("Error Creating network of type " + type + ".\n");
	}
};