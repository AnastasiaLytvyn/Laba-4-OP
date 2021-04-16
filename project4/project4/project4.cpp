#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "dictionary.h"
using namespace std;



int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
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

		
		/*for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}*/
	}

	//createDict();
	map <string, string>::iterator it = dict.begin();
	string str1 = argv[1];//compress/decompress/err
	if (str1 == "--compress") {
		string path = "../project4/";
		string pathFile = path + argv[2];
		ifstream f(pathFile);
		if (!f.is_open()) {
			cout << "No such file";
		}
		else {
			string str; getline(f, str);
			string P = "", C, PnC;
			string result;
			/*
			* str = abaababccd
				1.	P=
					C=a
					PnC=a (1.)
				2.	P=a
					C=b
					P+c=ab (2. добавить в словарь,)
				3.	P=b
					C=a
					P+C=ba
				///////////
				1. Если PnC есть => nextStep -> P=PnC , C++;
				2.Если PnC нету => добавить в map с value++, и для всех символом кроме последнего выписать  value из map; P=C; C++;
			*/
			int counter = 222;
			int bytesnum = 0;
			for (int i = 0; i < str.length(); i++) {
				C = str.substr(i, 1);
				PnC = P + C;
				if (dict.count(PnC) == 1) {
					P = PnC;
					continue;
				}
				else {
					dict[PnC] = to_string(++counter);
					it = dict.find(P);
					result += it->second;
					result += " ";
					bytesnum++;
					P = C;
				}
			}
			it = dict.find(str.substr(str.length() - 1, 1));
			result += it->second;
			bytesnum++;

			cout << result<<endl<<endl<<bytesnum;
			cout << endl << "NEW DICTIONARY:  " << endl;

			it = dict.begin();
			for (int i = 0; it != dict.end(); it++, i++) {
				cout << it->first << " -> " << it->second << endl;
			}
		}
	}
	else if (str1 == "--decompress") {
		cout << "....";

	}
	else {
		cout << "error";
	}
}