#pragma once


#include <string>
using std::string;

namespace BioNet {
	class FileHandler {
	protected:  
		/**
		File extention most file handlers  over ride
		Accessible in Reader and classes that inherit from Reader
		*/
		string extension;

	public:
		/// Returns default extentionused for a partcular instance of a file handler
		string getDefaultExt()
		{
			return extension;
		}
	};
}
//FileHandler::extension = "default";
