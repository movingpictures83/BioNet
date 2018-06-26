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
	
	template <typename R, typename T>
	void writeFile(BioNet<T>& bn, string& fname) 
	{
		R r;
		fname = defaultPath + fname;
		r.doWrite<T>(bn, fname);
	}; 
};