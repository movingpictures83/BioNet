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
		//{ ADJ_LST_KEY, []() {return new BioAdjList(); } },
		{ ADJ_MAT_KEY, []() {return new BioAdjMat(); } }
	};
	
	static BioAdj* create(const string& type) {
		if (mFactoryMap.find(type) != mFactoryMap.end())
			return mFactoryMap.at(type)();
		else
			return nullptr;
	}

	static bool swap(const string& type, BioAdj** target)
	{
		auto network = BioAdjFactory::create(type);
		if (!network)
			return false;
		network->resize((*target)->size());
		for (int i{ 0 }; i < network->size(); i++)
		{
			network->setNode(i, (*target)->getNode(i));
			for (int j{ 0 }; j < network->size(); j++)
				network->setEdge(i, j, (*target)->getEdge(i, j));
		}
		std::swap(network, *target);
		delete network;
		return true;
	}
}