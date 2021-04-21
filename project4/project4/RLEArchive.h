#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
class RLEArchiver
{
public:
	bool Compress(string, string);
	bool Decompress(string, string);
};