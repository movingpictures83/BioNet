#include "AdjFactory.h"

namespace BioNet {

	bool AdjFactory::instanceFlag = false;
	AdjFactory* AdjFactory::instance = NULL;

	AdjFactory* AdjFactory::getInstance() {
		if (!AdjFactory::instanceFlag) {
			AdjFactory::instance = new AdjFactory();
			AdjFactory::instanceFlag = true;
			return AdjFactory::instance;
		}
		else
			return AdjFactory::instance;
	}

	void AdjFactory::RegisterType(const string & id, GenericAdj* (*f) ()) {
		mFactoryMap[id] = f;
	}
}