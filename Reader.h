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
	Reader(/*const string& fname ,*/ string e, string p="") : /*_filename(fname),*/ IO(p) {}
	void readFile(BioNet& bn, string& fname)
	{
		fname = defaultPath + fname;
		doRead(bn, fname);
	};
	virtual void f() { cout << "F OF READER" << endl; }
	//{ cout << "BLANK READFILE FOR NOW" << endl; }
private:
	virtual void doRead(BioNet&, const string&) = 0; //Abstract virtual function to read file
};