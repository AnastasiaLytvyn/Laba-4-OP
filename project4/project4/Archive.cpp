#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "Archive.h"
using namespace std;

Archive::Archive() {

}
string Archive::LZWAlgo(map<string, string> dict, string pathFile, map <string, string>::iterator it) {
	
	ifstream f(pathFile, ios::binary);
	if (!f.is_open()) {
		cout << "No such file";
		return "";
	}
	else {


		string str = "";
		string P = "", PnC;
		char C;
		string result;
		int bytesnum = 0;
		int counter = 255;
		while (!f.eof()) {
			getline(f, str);

			for (int i = 0; i < str.length(); i++) {
				C = f.get();
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
			if (str.substr(str.length() - 1, 1) != "\n") {
				it = dict.find(str.substr(str.length() - 1, 1));
				result += it->second;
				bytesnum++;
			}
		}
		cout <<endl << endl << bytesnum<<endl<<endl;
		return result;
	}
	
}
void Archive::displayNewDict(map<string, string> dict, map <string, string>::iterator it) {
	cout << endl << "NEW DICTIONARY:  " << endl;
		it = dict.begin();
		for (int i = 0; it != dict.end(); it++, i++) {
			cout << it->first << " -> " << it->second << endl;
		}
}
void Archive::Compress(string result, string path) {

ofstream output(path, ios::binary);
if (!output.is_open())
{
	cout << "No such file";
}
else
{
	string symbol;
	int IntSymbol;
	while (0<result.length())
	{
		symbol = result.substr(0, result.find(" "));
		result = result.substr(result.find(" ") + 1);
		IntSymbol = stoi(symbol);
		
			char symm = (char)IntSymbol;
			output.write((char*)&symm, sizeof(symm));
		
		
		//считывание новых значений с словаря
		//if (IntSymbol >=256)
		//{
		//	char* data = toBinary(IntSymbol);
		//	char output_byte = 0;
		//	for (int k = 0; k< 8; k++)
		//	{
		//		output_byte |= data[k] << (7 - k);
		//	}
		//	output.write((char*)&output_byte, sizeof(output_byte));

		//	//char symm = IntSymbol;
		//	//const size_t nData = sizeof(data) - 1;
		//	//const char* array = data;
		//	//while (array - data < nData)
		//	//{
		//	//	unsigned char byte = GetByte(array);
		//	//	output.write((char*)&byte, sizeof(byte));
		//	//	//fwrite(&byte, 1, 1, output);
		//	//	array += 8;
		//	//}
		//}
	}
}
	output.close();
	ifstream input(path, ios::binary);
	string str; getline(input, str);
	getline(input, str);
	cout << "LINE:-> " << str[2] << " -> "<<str[3]<<" -> "<<str[4];
}