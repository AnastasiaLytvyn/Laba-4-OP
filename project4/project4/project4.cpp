#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "ArchiveLZW.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	ArchiveLZW zipper;

	//string path = "../project4/compressTXT2.txt";
	//zipper.Compress(path,to);
	//string filePath = "../project4/.lzw";
	//zipper.Decompress(filePath, to);

	string str1 = argv[1];
	string path = "../project4/";
	if (str1 == "--compress") {
		string from = path + argv[3];
		string to = path + argv[2];
		if (!zipper.Compress(from,to)) {
			cout << "Something went wrong." << endl;
		}


	}
	else if (str1 == "--decompress") {
		string from = path + argv[2];
		string to = path + argv[3];
		if (!zipper.Decompress(from, to)) {
			cout << "Something went wrong." << endl;
		}
	}
	else {
		cout << "project4.exe -c/-d [file to compress to/decompressed from] [file to be compressed/decompressed to]";
	}
}
