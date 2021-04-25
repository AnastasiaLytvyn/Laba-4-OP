#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;

class ArchiveLZW
{
private:
	void createDict();
	map <string, int> createMapFromDict();
public:
	bool Compress(string,string);
	void displayNewDict(map<string, int> dict, map <string, int>::iterator);
	bool Decompress(string, string);
	//string findInMap(map <string, int>, map <string, int>::iterator, int );
}; 
