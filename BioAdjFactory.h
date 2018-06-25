#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include "BioAdj.h"
#include "BioAdjList.h"
#include "BioAdjMat.h"

using std::string;
using std::unordered_map;
using std::function;
using std::type_index;
using BioAdjFactMap = unordered_map<string, function<BioAdj*(void)>>;



namespace BioAdjFactory {

	static BioAdjFactMap mFactoryMap;
	
	/*{
		{ "list", []() {return new BioAdjList(); } },
		{ "matrix", []() {return new BioAdjMat(); } }
	};*/
	
	static BioAdj* create(string& t) {
		auto it = mFactoryMap.find(t);
		if (mFactoryMap.find(t) != mFactoryMap.end())
			return mFactoryMap.at(t)();
		else
			return nullptr;
	}
}