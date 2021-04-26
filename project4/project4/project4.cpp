#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "RLEArchive.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	RLEArchiver zipper;
	//string str1 = argv[1];
	string path = "../project4/";
	string str1 = "--decompress";
	if (str1 == "--compress") {
		//string from = path + argv[3];
		//string to = path + argv[2];
		string from = path + "dop.txt";
		string to = path + "dop.rle";
		if (!zipper.Compress(from,to)) {
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
		//string from = path + argv[2];
		//string to = path + argv[3];
		string to = path + "dop111.txt";
		string from = path + "dop.rle";
		if (!zipper.Decompress(from, to)) {
			cout << "Something went wrong." << endl;
		}

	}
	else {
		cout << "project4.exe -c/-d [file to compress to/decompressed from] [file to be compressed/decompressed to]";
	}
}
