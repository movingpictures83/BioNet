#pragma once
#include "Reader.h"
#include "Writer.h"

namespace BioNet {
	class ReadWriter : public  Reader, public Writer {

	public:
		ReadWriter(string p = IO::getDefaultPath()) : Reader(p), Writer(p) {}
	};
}