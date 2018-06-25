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


namespace BioAdjFactory {
	using BioAdjFactMap = unordered_map<string, function<BioAdj*(void)>>;
	const static BioAdjFactMap mFactoryMap = {
		// Only included temporarily to allow full Build without errors
		//{ "list", []() {return nullptr; } },
		//{ "matrix", []() {return nullptr; } }
		//{ "list", []() {return new BioAdjList(); } },
		{ "matrix", []() {return new BioAdjMat(); } }
	};
	
	BioAdj* create(const string& t) {
		auto it = mFactoryMap.find(t);
		if (mFactoryMap.find(t) != mFactoryMap.end())
			return mFactoryMap.at(t)();
		else
			return nullptr;
	}
}