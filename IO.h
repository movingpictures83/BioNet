#pragma once


#include <string>
using std::string;
class IO {
private:
	string defaultPath;
	string defaultExt;
public:
	IO(string e, string p="") : defaultPath(p), defaultExt(e) {}

	//Accessor
	string getDefaultExt() { return defaultExt; }
	void setDefaultExt(string e) { defaultExt = e; }
	string getDefaultPath() { return defaultPath;  }
	void setDefaultPath(string p) { defaultPath = p; }
};