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
	//string _filename;

public:
	Reader(/*const string& fname ,*/ string e, string p= IO::getDefaultPath()) : /*_filename(fname),*/ IO(p) {}
	
	//generic for BioNet primitive and reader type
	template <class R, class T>
	static void readFile(BioNet<T>& bn, string& fname)
	{
		R r;
		fname = IO::getDefaultPath() + fname;
		r.doRead<T>(bn, fname);
	}

	virtual void f() { cout << "F OF READER" << endl; }
	//{ cout << "BLANK READFILE FOR NOW" << endl; }
};