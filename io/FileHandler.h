#pragma once


#include <string>
using std::string;

namespace BioNet {
	/**
	* Specific functionality for handling files.
	* To use in conjuction with a Reader or Writer class.
	*/
	class FileHandler {
	protected:  
		// File extention most file handlers override.
		string extension;

	public:
		/**
		* Default file extention.
		* @return default extension for this FileHandler
		*/
		string getDefaultExt()
		{
			return extension;
		}
	};
}
//FileHandler::extension = "default";
