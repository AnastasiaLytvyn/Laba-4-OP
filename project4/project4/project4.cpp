#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "dictionary.h"
using namespace std;

char* toBinary(int num) {
	int res = num;
	string str1 = "";
	string str2 = "";
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
		dict["\n"] = to_string(224);
		
		/*for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}*/
	}

	//createDict();
	map <string, string>::iterator it = dict.begin();
	//string str1 = argv[1];//compress/decompress/err
	string str1 = "--compress";
	if (str1 == "--compress") {
		string path = "../project4/";
		//string pathFile = path + argv[2];
		string pathFile = path + "file.txt";
		ifstream f(pathFile);
		if (!f.is_open()) {
			cout << "No such file";
		}
		else {
			string str=""; 
			string P = "", C, PnC;
			string result;
			int bytesnum = 0;
			int counter = 224;
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


			///////
			ofstream binFile("../project4/binaryfile.txt", ios::binary);
			if (!binFile.is_open())
			{
				cout << "No such file";
			}
			else
			{
				int i = 0;
				while (i<result.length())
				{
					string symbol;
					symbol = result.substr(i, result.find(" "));
					result = result.substr(result.find(" ") + 1);
					int newSymbol = stoi(symbol);
					if (newSymbol != 224 && newSymbol<256)
					{
						newSymbol += 32;
						char symm = newSymbol;
						binFile.write((char*)&symm, sizeof(symm));
					}
					if (newSymbol == 224)
					{
						newSymbol =10;
						char symm = newSymbol;
						binFile.write((char*)&symm, sizeof(symm));
					}
					//считывание новых значений с словаря
					//if (newSymbol >=256)
					//{
					//	newSymbol += 31;
					//	char* data = toBinary(newSymbol);
					//	char output_byte = 0;
					//	for (int k = 0; k< 8; k++)
					//	{
					//		output_byte |= data[k] << (7 - k);
					//	}
					//	binFile.write((char*)&output_byte, sizeof(output_byte));

					//	//char symm = newSymbol;
					//	//const size_t nData = sizeof(data) - 1;
					//	//const char* array = data;
					//	//while (array - data < nData)
					//	//{
					//	//	unsigned char byte = GetByte(array);
					//	//	binFile.write((char*)&byte, sizeof(byte));
					//	//	//fwrite(&byte, 1, 1, binFile);
					//	//	array += 8;
					//	//}
					//}
				}
			}
			binFile.close();
		}
	}
	else if (str1 == "--decompress") {
		cout << "....";

	}
	else {
		cout << "error";
	}
}