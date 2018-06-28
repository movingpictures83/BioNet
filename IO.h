#pragma once


#include <string>
using std::string;

namespace BioNet {
	/**
		Parent class for reader and writer classes allows for shared paths between classes
	*/
	class IO {
	protected:
		///Global path directory used when the directory is not given by the user
		static string defaultPath;
	public:
		IO(string path = "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\") { setDefaultPath(path); }

		/**
			@returns the gobal default path used by all subclasses
		*/
		static string getDefaultPath() { return defaultPath; }

		/**
			updates the global default path for all IO subclasses

			@params p - updated global default path
		*/
		static void setDefaultPath(string p) { defaultPath = p; }

	};

}