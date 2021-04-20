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
	//createDict();

	//string str1 = argv[1];//compress/decompress/err
	string str1 = "--compress";
	if (str1 == "--compress") {
		string path = "../project4/";
		//string pathFile = path + argv[3];
		map <string, int> dict = createMapFromDict();
		map <string, int>::iterator it = dict.begin();
		if (zipper.Compress("img.bmp", "compimg.rle", dict, it))
			cout << "Done\n";
		if (zipper.Decompress("compimg.rle", "imgres.bmp", dict, it))
			cout << "Decompress Done\n";
		//if (zipper.Compress("new.bmp", "newcomp.rle", dict, it))
		//	cout << "Done\n";
		//if (zipper.Decompress("newcomp.rle", "newresult.bmp", dict, it))
		//	cout << "Decompress Done\n";
		//if (zipper.Compress("text.txt", "textcomp.rle", dict, it))
		//	cout << "Done\n";
		//if (zipper.Decompress("textcomp.rle", "textresult.txt", dict, it))
		//	cout << "Decompress Done\n";
		//if (zipper.Compress("sample.bmp", "samplecomp.rle", dict, it))
		//	cout << "Done\n";
		//if (zipper.Decompress("samplecomp.rle", "sampleresult.bmp", dict, it))
		//	cout << "Decompress Done\n";
		//if (zipper.Compress("math.pdf", "mathcomp.rle", dict, it))
		//	cout << "Done\n";
		//if (zipper.Decompress("mathcomp.rle", "math.pdf", dict, it))
		//	cout << "Decompress Done\n";
	}
	else if (str1 == "--decompress") {
		cout << "....";

	}
	else {
		cout << "error";
	}
}
