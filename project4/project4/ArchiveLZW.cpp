#include "ArchiveLZW.h"

bool ArchiveLZW::Compress(string pathFile, string to) {
	ifstream f(pathFile, ios::binary);
	ofstream output(to, ios::binary);
	int j = 0;

	if (!f.is_open()) {
		cout << "No such file";
		return false;
	}
	else
	{
		cout << "Compressing file " << pathFile <<" to file "<< to << " ..." ;
		//createDict();  //---ÑÎÇÄÀÍÈÅ ÔÀÉËÀ ÑËÎÂÀÐß
		map<string, int> dict = createMapFromDict();
		map<string, int>::iterator it = dict.begin();
		string str = "";
		string P = "", PnC;
		unsigned char C;
		
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
			PnC = P +(char) C;
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
			//cout << j++ << endl;
		}
		it= dict.find(P);
		int symCode = it->second;//258
		if (symCode < 256) {
			char nullbyte = 0;
			char code = symCode;
			output.write((char*)&nullbyte, sizeof(nullbyte));
			output.write((char*)&code, sizeof(code));
		}
		else {
			int highByte = symCode >> 8;
			int lowByte = symCode & ((1 << 8) - 1);
			char highB = highByte;
			char lowB = lowByte;
			output.write((char*)&highB, sizeof(highB));
			output.write((char*)&lowB, sizeof(lowB));
		}
		//displayNewDict(dict, it);
		
		cout << "Done."<<endl;
		return true;
	}
}


bool ArchiveLZW::Decompress(string path, string to)
{
	cout << "Decompressing file " << path << " to " << to << " ...";
	string resultSTR = "";
	ifstream output(path, ios::binary);
	ofstream result(to, ios::binary);
	map<string, int> dict = createMapFromDict();
	map<string, int>::iterator it = dict.begin();
	int counter = 255;
	if (!output.is_open()) {
		cout << "No such file";
		return false;
	}
	else
	{
		unsigned char CHAR;
		int highByte, lowByte;
		output.read((char*)&CHAR, sizeof(CHAR));
		highByte = (int)CHAR;
		highByte = highByte << 8;
		output.read((char*)&CHAR, sizeof(CHAR));
		lowByte = (int)CHAR;
		int codeword = highByte + lowByte;
		string sym1;
		int numofb = 1;
		for (; it != dict.end(); it++) {
			if (it->second == codeword) {
				sym1 = it->first;
				break;
			}
		}
		for (int i = 0; i < sym1.length(); i++) {
		result.write((char*)&sym1[i], 1);
		resultSTR += sym1[i];
		}
		string priorCodeword = sym1;
		string codewordStr;
		while (output.read((char*)&CHAR, sizeof(CHAR))) {
			cout << ++numofb << endl;

			highByte = (int)CHAR;
			highByte = highByte << 8;
			output.read((char*)&CHAR, sizeof(CHAR));
			lowByte = (int)CHAR;
			codeword = highByte + lowByte;
			for (it=dict.begin(); it != dict.end(); it++) {
				if (it->second == codeword) {
					codewordStr = it->first;
					break;
				}
				else {
					codewordStr = "";
				}
			}
			if (codewordStr != "") {
				dict[priorCodeword + codewordStr[0]] = ++counter;
				for (int i = 0; i < codewordStr.length(); i++) {
					result.write((char*)&codewordStr[i], 1);
					//cout << ++numofb<<endl;
					resultSTR += codewordStr[i];
				}
			}
			else {
				string PnF = priorCodeword + priorCodeword[0];
				dict[PnF]=++counter;
				for (int i = 0; i < PnF.length(); i++) {
					//cout << ++numofb<<endl;

					result.write((char*)PnF[i], 1);
					resultSTR += PnF[i];
				}
			}
			priorCodeword = codewordStr;
		}
	}
	//displayNewDict(dict, it);
	cout << "Done."<<endl;
	return true;
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
		//dict["\n"] = 10;
		string firstSymbol="";
		for (int i = 0; i < 32; i++)
		{
			firstSymbol = ((char)i);
			dict[firstSymbol] = i;
			firstSymbol = "";
		}
	}
	dictF.close();
	return dict;
}


	

