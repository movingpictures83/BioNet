#pragma once


#include <string>
using std::string;
class IO {
protected:
	string defaultPath;
	static string defaultExt;
public:
	IO(string e, string p = "") : defaultPath(p) { setDefaultExt(e); };

	//Accessor
	string getDefaultExt() { return defaultExt; }
	static void setDefaultExt(string e) { defaultExt = e; }
	string getDefaultPath() { return defaultPath;  }
	void setDefaultPath(string p) { defaultPath = p; }
};