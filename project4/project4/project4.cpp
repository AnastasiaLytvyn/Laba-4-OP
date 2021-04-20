#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "dictionary.h"
#include "RLEArchive.h"

using namespace std;


map <string, int> createMapFromDict() {
	map <string, int> dict;

	ifstream dictF("../project4/dict.txt");
	if (!dictF.is_open()) {
		cout << "No such file";
	}
	else {
		string str;
		while (!dictF.eof()) {
			getline(dictF, str);
			if (str != "") {
				dict[str.substr(0, 1)] = stoi(str.substr(4));
			}
		}
		dict["\n"] = 10;
		/*for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}*/
	}
	dictF.close();
	return dict;
}



int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	RLEArchiver zipper;
	map <string, int> dict = createMapFromDict();
	map <string, int>::iterator it = dict.begin();
	string str1 = argv[1];
	string path = "../project4/";
	if (str1 == "--compress") {
		string from = path + argv[3];
		string to = path + argv[2];
		if (!zipper.Compress(from,to,dict, it)) {
			cout << "Something went wrong." << endl;
		}
		//____________________________________________________________
		//!~~~~~~~~~~~~~~FILEs EXAMPLES FOR COMPRESSING~~~~~~~~~~~~~~!
		//[‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾]
		//|=========================================================||
		//|															||
		//|                |==================|						||
		//|===============TXT FILE COMPRESSING======================||
		//|                |==================|						||
		//|															||
		//|			compressTXT.txt   compressTXT.rle				||
		//|			compressTXT.rle   compressTXTDECOMPRESSED.txt	||
		//|															||
		//|                |==================|						||
		//|================PDF FILE COMPRESSING=====================||
		//|                |==================|						||
		//|															||
		//|			compressPDF.pdf   compressPDF.rle				||
		//|			compressPDF.rle   compressPDFDECOMPRESSED.pdf	||
		//|															||
		//|                |==================|						||
		//|================BMP FILE COMPRESSING=====================||
		//|                |==================|						||
		//|															||
		//|			compressBMP.bmp   compressBMP.rle				||
		//|			compressBMP.rle   compressBMPDECOMPRESSED.bmp	||
		//|=========================================================||
		//[__________________________________________________________]

	}
	else if (str1 == "--decompress") {
		string from = path + argv[2];
		string to = path + argv[3];
		if (!zipper.Decompress(from, to, dict, it)) {
			cout << "Something went wrong." << endl;
		}

	}
	else {
		cout << "project4.exe -c/-d [file to compress to/decompressed from] [file to be compressed/decompressed to]";
	}
}
