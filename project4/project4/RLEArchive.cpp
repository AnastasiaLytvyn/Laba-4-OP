#include "RLEArchive.h"

bool RLEArchiver::Compress(string from, string to) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/')+1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Ñompressing " << fromFile << "... ";


	char first, second, third;
	input.read((char*)&first, 1);
	input.read((char*)&second, 1);
	input.read((char*)&third, 1);
	int countS;
	char currentF, currS,currT;

	string emptySym = "";
	while (input.read((char*)&currentF, 1))
	{
		if (input.read((char*)&currS, 1))
		{
			if (input.read((char*)&currT, 1))
			{
				countS = 1;
				while (first == currentF && second == currS && third == currT) {
					countS++;
					if (input.read((char*)&currentF, 1)) {
						if (input.read((char*)&currS, 1)) {
							if (input.read((char*)&currT, 1)) {
								continue;
							}
							else {
								emptySym = "noT";
								break;
							}
						}
						else {
							emptySym = "noS";
							break;
						}
					}
					else {
						//emptySym = "first";
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
				first == currentF;
				second == currS;
				third == currT;

				output.write((char*)&first, sizeof(first));
				output.write((char*)&second, sizeof(second));
				output.write((char*)&third, sizeof(third));
			}
			else {
				char one = 1;
				output.write((char*)&one, sizeof(first));
				output.write((char*)&first, sizeof(first));
				output.write((char*)&second, sizeof(second));
				output.write((char*)&third, sizeof(third));
				emptySym = "noT";
				break;
			}
		}
		else {
			char one = 1;
			output.write((char*)&one, sizeof(first));

			output.write((char*)&first, sizeof(first));
			output.write((char*)&second, sizeof(second));
			output.write((char*)&third, sizeof(third));
			emptySym = "noS";
			break;
		}
	}
	if (emptySym == "noT")
	{
		char one = 1;
		input.seekg(-2, ios::end);
		input.read((char*)&first, 1);
		input.read((char*)&second, 1);
		output.write((char*)&one, sizeof(first));
		output.write((char*)&first, sizeof(first));
		output.write((char*)&second, sizeof(second));
		emptySym = "";
	}
	else
	{
		char one = 1;
		input.seekg(-1, ios::end);
		output.write((char*)&one, sizeof(first));
		input.read((char*)&first, 1);
		output.write((char*)&first, sizeof(first));
		emptySym = "";
	}



	//if (from.substr(from.rfind('.')) == ".bmp") {
	//	char sym1 = 1;
	//	output.write((char*)&sym1, sizeof(sym1));
	//	output.write((char*)&now, sizeof(now));
	//}
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

