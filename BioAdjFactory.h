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
using BioAdjFactMap = unordered_map<type_index, function<BioAdj*(void)>>;



namespace BioAdjFactory {

	const static BioAdjFactMap mFactoryMap{
		{ typeid(BioAdjList), []() {return new BioAdjList(); } },
		{ typeid(BioAdjMat), []() {return new BioAdjMat(); } }
	};
	
	BioAdj* create(type_index& t) {
		auto it = mFactoryMap.find(t);
		if (mFactoryMap.find(t) != mFactoryMap.end())
			return mFactoryMap.at(t)();
		else
			return nullptr;
	}
}