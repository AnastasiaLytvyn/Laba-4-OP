#include "RLEArchive.h"

bool RLEArchiver::Compress(string from, string to) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/')+1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Ñompressing " << fromFile << "... ";
	char now;
	input.read((char*)&now, 1);
	int countS;
	char current;
	while (input.read((char*)&current, 1)) {
		countS = 1;
		while (now == current) {
			countS++;
			if (input.read((char*)&current, 1)) {
				continue;
			}
			else {
				break;
			}
		}
		if (countS < 256) {
			char countChar = countS;
			output.write((char*)&countChar, 1);
		}
		else {
			int countS1 = countS >> 8;
			int countS2 = countS & ((1 << 8) - 1);
			char countChar1 = countS1;
			char countChar2 = countS2;
			char twoBytesAlert = 27;
			output.write((char*)&twoBytesAlert, 1);
			output.write((char*)&countChar1, 1);
			output.write((char*)&countChar2, 1);
		}
		output.write((char*)&now, sizeof(now));
		now = current;
	}

	if (from.substr(from.rfind('.')) == ".bmp") {
		char sym1 = 1;
		output.write((char*)&sym1, sizeof(sym1));
		output.write((char*)&now, sizeof(now));
	}
	cout << "Done." << endl;
	cout << "Result written to " << toFile << ".";
	input.close(); output.close();
	return true;
}


bool RLEArchiver::Decompress(string from, string to) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/')+1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Decompressing file " << fromFile<< "... ";
	char now;
	char symbol;
	while (input.read((char*)&now, 1))
	{
		if (now != 27)
		{
			input.read((char*)&symbol, 1);
			for (int i = 0; i < now; i++)
			{
				output.write((char*)&symbol, 1);
			}
		}
		else
		{
			char highByte, lowByte;
			input.read((char*)&highByte, 1);
			int highB, lowB;
			highB = (highByte) << 8;
			input.read((char*)&lowByte, 1);
			lowB = lowByte;
			int countSym;
			countSym = highB + lowB;
			input.read((char*)&symbol, 1);
			for (int i = 0; i < countSym; i++)
			{
				output.write((char*)&symbol, 1);
			}
		}
	}
	cout << "Done." << endl;
	cout << "Result written to " << toFile << ".";
	input.close(); output.close();
	return true;
}

