#pragma once

#include "Net.h"
#include "IO.h"
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;
using BioNet::IO;

namespace BioNet {
	///Subclass of IO used to read in files given a file handler
	class Reader : public IO {
	protected:  // Accessible in Reader and classes that inherit from Reader

	public:
		/**
		Takes an empty network and populates it from the given file

		generic for FileHandler  R (e.g. CSVHandler, GMLHandler)
		generic for Net primitive T

		@param bn - an unpoplated networ which il be filled by the function
		@param fname - a file name which can be accepted by handler type R 
		@param useDefault - specifies whether or not to use the default path when reading file if
		not the provided path will be used
		*/
		template <class R, class T>
		static void readFile(Net<T>& bn, const string& fname, bool useDefault = true)
		{
			string fullFname = (useDefault ? IO::getDefaultPath() : "") + fname;
			R::doRead(bn, fullFname);
		}
	};
}