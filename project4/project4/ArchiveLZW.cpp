#include "ArchiveLZW.h"

string ArchiveLZW::LZWAlgo(string pathFile) {
	ifstream f(pathFile, ios::binary);
	ofstream output("output.lzw", ios::out | ios::binary);
	if (!f.is_open()) {
		cout << "No such file";
		return "";
	}
	else
	{
		//createDict();  //---ÑÎÇÄÀÍÈÅ ÔÀÉËÀ ÑËÎÂÀÐß
		map<string, int> dict = createMapFromDict();
		map<string, int>::iterator it = dict.begin();
		string str = "";
		string P = "", PnC;
		char C;
		string result;
		int bytesnum = 0;
		int counter = 255;
		f.read((char*)&C, 1);
		P += C;
		while (f.read((char*)&C, 1))
		{
			if (C == '\r')
			{
				f.read((char*)&C, 1);
			}
			PnC = P + C;
			if (dict.count(PnC) == 1)
			{
				P = PnC;
				continue;
			}
			else
			{
				dict[PnC] = ++counter;
				it = dict.find(P);
				int bytes = (it->second);
				if (bytes < 256)
				{
					char nullbyte = 0;
					char code = bytes;
					output.write((char*)&nullbyte, sizeof(nullbyte));
					output.write((char*)&code, sizeof(code));
				}
				else
				{
					int highByte = bytes >> 8;
					int lowByte = bytes & ((1 << 8) - 1);
					char highB = highByte;
					char lowB = lowByte;
					output.write((char*)&highB, sizeof(highB));
					output.write((char*)&lowB, sizeof(lowB));
				}
				result += (it->second);
				result += " ";
				bytesnum++;
				P = C;
			}
			/*if (str.substr(str.length() - 1, 1) != "\n")
			{
				it = dict.find(str.substr(str.length() - 1, 1));
				int bytes = (it->second);
				if (bytes < 256)
				{
					char nullbyte = 0;
					char code = bytes;
					output.write((char*)&nullbyte, sizeof(nullbyte));
					output.write((char*)&code, sizeof(code));
				}
				else
				{
					int highByte = bytes >> 8;
					int lowByte = bytes & ((1 << 8) - 1);
					output.write((char*)&highByte, sizeof(highByte));
					output.write((char*)&lowByte, sizeof(lowByte));
				}
				result += it->second;
				bytesnum++;
			}*/
		}
		cout << result;
		cout << endl << endl << bytesnum << endl << endl;
		return result;
	}
}


void ArchiveLZW::Decompress()
{
	ifstream output("output.lzw", ios::binary);
	ofstream final("decompress.txt", ios::binary);

	if (!output.is_open()) {
		cout << "No such file";
		return;
	}
	else
	{
		char now;
		char next;
		while (output.read((char*)&now, 1))
		{
			int symbolnow, symbolnext, bytes;
			symbolnow = now << 8;
			output.read((char*)&next, 1);
			symbolnext = next;
			bytes = symbolnow + symbolnext;
		}
	}
}


void ArchiveLZW::displayNewDict(map<string, int> dict, map <string, int>::iterator it) {
	cout << endl << "NEW DICTIONARY:  " << endl;
	it = dict.begin();
	for (int i = 0; it != dict.end(); it++, i++) {
		cout << it->first << " -> " << it->second << endl;
	}
}

void ArchiveLZW::createDict() {
	ofstream fOut("../project4/dict.txt");
	if (!fOut.is_open()) {
		cout << "err";
	}
	else {
		for (int i = 32; i < 256; i++) {
			fOut << (char)(i) << " ->" << i << endl;
		}
	}
}

map <string, int> ArchiveLZW::createMapFromDict() {
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
	}
	dictF.close();
	return dict;
}