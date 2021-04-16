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
		dict["\n"] = to_string(223);
		
		/*for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}*/
	}

	//createDict();
	map <string, string>::iterator it = dict.begin();
	string str1 = argv[1];//compress/decompress/err
	//string str1 = "--compress";
	if (str1 == "--compress") {
		string path = "../project4/";
		string pathFile = path + argv[2];
		//string pathFile = path + "file.txt";
		ifstream f(pathFile);
		if (!f.is_open()) {
			cout << "No such file";
		}
		else {
			string str=""; 
			string P = "", C, PnC;
			string result;
			int bytesnum = 0;
			int counter = 223;
			while (!f.eof()) {
				getline(f, str);
				str = str + "\n";
				for (int i = 0; i < str.length(); i++) {
					C = str.substr(i, 1);
					PnC = P + C;
					if (dict.count(PnC) == 1) {
						P = PnC;
						continue;//4
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
				if (str.substr(str.length() - 1, 1) != "\n") {
					it = dict.find(str.substr(str.length() - 1, 1));
					result += it->second;
					bytesnum++;
				}
				
				/*if (!f.eof()) {
					result += "^";
				}*/
			}
			
			

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