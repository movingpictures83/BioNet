#pragma once


#include <string>
using std::string;
class IO {
protected:
	static string defaultPath;
	//static string defaultExt ;
public:
	IO(string path = "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\") { setDefaultPath(path); }

	//Accessor
	virtual string getDefaultExt() = 0;
	//virtual void setDefaultExt(string e) = 0;
	static string getDefaultPath() { return defaultPath;  }
	static void setDefaultPath(string p) { defaultPath = p; }
	
};