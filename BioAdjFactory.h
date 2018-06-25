#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include "BioAdj.h"
#include "BioAdjMat.h"
#include "BioAdjList.h"

using std::string;
using std::unordered_map;
using std::function;
using std::swap;

namespace BioAdjFactory {
	using BioAdjFactMap = unordered_map<string, function<BioAdj*(void)>>;
	const static BioAdjFactMap mFactoryMap = {
		// Only included temporarily to allow full Build without errors
		//{ BioAdjList::NetworkType(), []() {return new BioAdjList(); } },
		{ BioAdjMat::NetworkType(), []() {return new BioAdjMat(); } }
	};
	
	static BioAdj* create(const string& type) {
		if (mFactoryMap.find(type) != mFactoryMap.end())
			return mFactoryMap.at(type)();
		else
			throw BioNetException("Error Creating network of type " + type + ".\n");
	}
}