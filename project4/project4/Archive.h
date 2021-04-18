#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;

class Archive
{
public:
	Archive();
	string LZWAlgo(map<string,string>, string, map <string, string>::iterator);
	void displayNewDict(map<string, string> dict, map <string, string>::iterator);
	void Compress(string, string);
	void Decompress();

};