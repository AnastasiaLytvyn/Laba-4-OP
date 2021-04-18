#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "dictionary.h"
#include "Archive.h"
using namespace std;

char* toBinary(int num) {
	int res = num;
	string str1 = "",str2 = "";
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
map <string, string> createMapFromDict() {
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
		dict["\n"] = to_string(10);

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
	
	Archive zipper;
	//createDict();
	
	string str1 = argv[1];//compress/decompress/err
	//string str1 = "--compress";
	if (str1 == "--compress") {
		string path = "../project4/";
		string pathFile = path + argv[3];
		map <string, string> dict = createMapFromDict();
		map <string, string>::iterator it = dict.begin();
		string result = zipper.LZWAlgo(dict, pathFile, it);
		//cout << result<<endl<<endl;
		//zipper.displayNewDict(dict, it);

		//string outputFile = argv[2];
		//string pathOutput = path + outputFile;

		//zipper.Compress(result, pathOutput);
		
		}
	else if (str1 == "--decompress") {
		cout << "....";

	}
	else {
		cout << "error";
	}	
}
