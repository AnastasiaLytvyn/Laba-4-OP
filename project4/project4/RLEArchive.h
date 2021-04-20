#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
class Archiver
{

public:
	bool Compress(string, string, map <string, int>, map <string, int>::iterator);
	bool Decompress(string, string, map <string, int>, map <string, int>::iterator);
};