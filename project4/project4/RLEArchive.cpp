#include "RLEArchive.h"


bool RLEArchiver::Compress(string from, string to) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/') + 1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Compressing " << fromFile << "... ";
	char first, second, third;
	input.read((char*)&first, 1);
	input.read((char*)&second, 1);
	input.read((char*)&third, 1);
	char curF, curS, curT;
	int countS;
	string troubleSym = "";
	while (input.read((char*)&curF, 1))
	{
		if (input.read((char*)&curS, 1))
		{
			if (input.read((char*)&curT, 1))
			{
				countS = 1;
				while (first == curF && second == curS && third == curT) 
				{
					countS++;
					if (input.read((char*)&curF, 1))
					{
						if (input.read((char*)&curS, 1)) 
						{
							if (input.read((char*)&curT, 1))
							{
								continue;
							}
							else 
							{
								troubleSym = "thirdSym";
								break;
							}
						}
						else 
						{
							troubleSym = "secondSym";
							break;
						}
					}
					else 
						break;
				}
				if (countS < 256) 
				{
					char countChar = countS;
					output.write((char*)&countChar, 1);
				}
				else 
				{
					int countS1 = countS >> 8;
					int countS2 = countS & ((1 << 8) - 1);
					char countChar1 = countS1;
					char countChar2 = countS2;
					char twoBytesAlert = 27;
					output.write((char*)&twoBytesAlert, 1);
					output.write((char*)&countChar1, 1);
					output.write((char*)&countChar2, 1);
				}
				output.write((char*)&first, sizeof(first));
				output.write((char*)&second, sizeof(second));
				output.write((char*)&third, sizeof(third));
				first = curF;
				second = curS;
				third = curT;
			}
			else {
				char numOfByte = 1;
				output.write((char*)&numOfByte, sizeof(first));
				output.write((char*)&first, sizeof(first));
				output.write((char*)&second, sizeof(second));
				output.write((char*)&third, sizeof(third));
				troubleSym = "thirdSym";
				break;
			}
		}
		else {
			char numOfByte = 1;
			output.write((char*)&numOfByte, sizeof(first));

			output.write((char*)&first, sizeof(first));
			output.write((char*)&second, sizeof(second));
			output.write((char*)&third, sizeof(third));
			troubleSym = "secondSym";
			break;
		}
	}
	if (troubleSym == "thirdSym") {
		char numOfByte = 1;
		input.seekg(-2, ios::end);
		input.read((char*)&curF, 1);
		input.read((char*)&curS, 1);
		output.write((char*)&numOfByte, sizeof(first));
		output.write((char*)&curF, sizeof(first));
		output.write((char*)&curS, sizeof(second));
	}
	else if (troubleSym == "secondSym") {
		char numOfByte = 1;
		input.seekg(-1, ios::end);
		output.write((char*)&numOfByte, sizeof(first));
		input.read((char*)&curF, 1);
		output.write((char*)&curF, sizeof(first));
	}

	cout << "Done." << endl;
	cout << "Result written to " << toFile << ".";
	input.close(); output.close();
	return true;
}

bool RLEArchiver::Decompress(string from, string to)
{
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/') + 1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Decompressing file " << fromFile << "... ";
	char first, second, third;
	char now;
	while (input.read((char*)&now, 1))
	{
		if (now != 27)
		{
			input.read((char*)&first, 1);
			if (input.read((char*)&second, 1)) {
				if (input.read((char*)&third, 1)) {
					for (int i = 0; i < now; i++) {
						output.write((char*)&first, 1);
						output.write((char*)&second, 1);
						output.write((char*)&third, 1);
					}
				}
				else {
					output.write((char*)&first, 1);
					output.write((char*)&second, 1);
				}
			}
			else
				output.write((char*)&first, 1);
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

			input.read((char*)&first, 1);
			{
				if (input.read((char*)&second, 1))
				{
					if (input.read((char*)&third, 1))
					{
						for (int i = 0; i < countSym; i++) 
						{
							output.write((char*)&first, 1);
							output.write((char*)&second, 1);
							output.write((char*)&third, 1);
						}
					}
					else 
					{
						output.write((char*)&first, 1);
						output.write((char*)&second, 1);
					}
				}
				else 
					output.write((char*)&first, 1);
			}
		}
	}
	cout << "DnumOfByte." << endl;
	cout << "Result written to " << toFile << ".";
	input.close(); output.close();
	return true;
}