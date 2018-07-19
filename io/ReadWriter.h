#pragma once
#include "Reader.h"
#include "Writer.h"

namespace BioNet {
	
	///ReadWriter class
	/**
	Subclass of read writer that allows for an object to be use with all of the functionality of both classes.
	*/
	class ReadWriter : public  Reader, public Writer {
	
	public:
		ReadWriter(string p = IO::getDefaultPath()) : Reader(p), Writer(p) {}
	};
}