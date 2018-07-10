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
	///Subclass of IO used to write in files given a file handler
	class Writer : public IO {

	public:
		Writer(string p = IO::getDefaultPath()){}

		/**
		Takes a populated network and writes it to the given file

		generic for FileHandler  R (e.g. CSVHandler, GMLHandler)
		generic for Net primitive T

		@param bn - a networ which will be written to file
		@param fname - a file name which can be accepted by handler type R
		@param useDefault - specifies whether or not to use the default directory path when reading file if
		not the provided path will be used
		*/
		template <typename R, typename T>
		void writeFile(Net<T>& bn, string& fname, bool useDefault = true)
		{
			fname = (useDefault ? defaultPath : "") + fname;
			R::doWrite(bn, fname);
		};
	};
}