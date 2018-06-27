#pragma once

#include "BioNet.h"
#include "IO.h"
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

class Reader : public IO {
protected:  // Accessible in Reader and classes that inherit from Reader
	
public:
	Reader(string p= IO::getDefaultPath()) : IO(p) {}
	
	//generic for BioNet primitive and reader type
	template <class R, class T>
	static void readFile(BioNet<T>& bn, string& fname, bool useDefault = true)
	{
		fname = (useDefault ?  IO::getDefaultPath() : "") + fname;
		R::doRead(bn, fname);
	}
};