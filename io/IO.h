#pragma once

#include <string>
using std::string;

namespace BioNet {
	///IO class
	/** 
	 * Class for all I/O functionality.
	 * Intended to be the base class for all I/O
	 */
	class IO {
	protected:
		///Global path directory used when the directory is not given by the user
		static string defaultpath;
	public:
		/**
		 * Gets the default path for I/O.
		 * @returns the global default path.
		 */
		static string getDefaultPath() { return defaultpath; }

		/**
		 * Updates the global default path for I/O.
		 * @param p Global default path to set.
		 */
		static void setDefaultPath(string p) { defaultpath = p; }

	};

}