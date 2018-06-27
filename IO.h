#pragma once


#include <string>
using std::string;
class IO {
protected:
	static string defaultPath;
public:
	IO(string path = "C:\\Users\\student\\Desktop\\BioNet\\data\\Basic\\three_triads\\") { setDefaultPath(path); }

	static string getDefaultPath() { return defaultPath;  }
	static void setDefaultPath(string p) { defaultPath = p; }
	
};
