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
	
	template <typename T>
	void readFile(BioNet<T>& bn, string& fname)
	{
		fname = IO::getDefaultPath() + fname;
		doRead<T>(bn, fname);
	}

	virtual void f() { cout << "F OF READER" << endl; }
	//{ cout << "BLANK READFILE FOR NOW" << endl; }
private:
	template <typename T>
	virtual void doRead(BioNet<T> &, const string&) = 0; //Abstract virtual function to read file
};