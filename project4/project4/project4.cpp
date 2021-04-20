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
	
	Archiver zipper;
	//createDict();
	
	//string str1 = argv[1];//compress/decompress/err
	string str1 = "--compress";
	if (str1 == "--compress") {
		string path = "../project4/";
		//string pathFile = path + argv[3];
		map <string, int> dict = createMapFromDict();
		map <string, int>::iterator it = dict.begin();
		
		}
	else if (str1 == "--decompress") {
		cout << "....";

	}
	else {
		cout << "error";
	}	
}


///
char* toBinary(int num) {
	int res = num;
	string str1 = "", str2 = "";
	while (res != 1 && res != 0) {
		if (res % 2 == 0) {
			res = num / 2;
			num = res;
			str1 += "0";
		}
		else {
			res = num / 2;
			num = res;

			str1 += "1";
		}
	}
	str1 += to_string(res);
	for (int i = str1.length(); i >= 0; i--) {
		str2 += str1[i];
	}
	char* binNum = new char[str2.length()];
	for (int i = 0; i < str2.length(); i++)
	{
		binNum[i] = str2[i];
	}
	return binNum;
}

unsigned char GetByte(const char data[])
{
	unsigned char byte = 0;
	const char* end = data + 8;

	for (; *data && (data < end); ++data)
	{
		byte <<= 1;

		byte |= (*data == '1') ? 1 : 0;
	}

	return byte;
}