#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "dictionary.h"
using namespace std;



int main(int argc, char* argv[])
{
	map <string, string> dict;

	ifstream dictF("../project4/dict.txt");
	if (!dictF.is_open()) {
		cout << "No such file";
	}
	else {
		string str;
		while (!dictF.eof()) {
			getline(dictF, str);
			if (str != "") {
			dict[str.substr(0, 1)] = str.substr(4);

			}
		}

		map <string, string>::iterator it = dict.begin();
		for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}
	}

	//createDict();
	//string str1 = argv[1];//compress/decompress/err
	//if (str1 == "--compress") {
	//	string path = "../project4/";
	//	string pathFile = path + argv[2];
	//	ifstream f(pathFile, ios::binary);
	//	if (!f.is_open()) {
	//		cout << "No such file";
	//	}
	//	else {
	//		string str; getline(f, str);
	//		for (int i = 0; i < str.length(); i++) {
	//			cout <<str[i] << ' ';
	//		}
	//	}


	//}
	//else if (str1 == "--decompress") {
	//	cout << "....";

	//}
	//else {
	//	cout << "error";
	//}
}




