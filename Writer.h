#pragma once

#include "BioNet.h"
#include "IO.h"
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;


class Writer : public IO {
protected:  // Accessible in Reader and classes that inherit from Reader
	//string _filename;

public:
	Writer(/*const string& fname,*/ string e, string p = "") : /*_filename(fname),*/ IO(p) {}
	void writeFile(BioNet& bn, string& fname) 
	{
			fname = defaultPath + fname;
			doWrite(bn, fname);
	}; 
	virtual void f() { cout << "F OF WRITER" << endl; }//{ cout << "BLANK READFILE FOR NOW" << endl; }

private:
	virtual void doWrite(BioNet& bn, const string& fname) = 0; // Abstract virtual functions
};