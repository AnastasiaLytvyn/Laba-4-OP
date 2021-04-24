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
	string LZWAlgo(string);
	void displayNewDict(map<string, int> dict, map <string, int>::iterator);
	void Decompress();
}; 
