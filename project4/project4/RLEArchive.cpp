#include "RLEArchive.h"

bool RLEArchiver::Compress(string from, string to) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	string fromFile = from.substr(from.rfind('/')+1);
	string toFile = to.substr(from.rfind('/') + 1);
	cout << "Сompressing " << fromFile << "... ";
	char first,second,third;
	input.read((char*)&first, 1);
	input.read((char*)&second, 1);
	input.read((char*)&third, 1);
	char first1, second1, third1;
	int countS;
	string where1 = "";
	while (input.read((char*)&first1, 1)) {
		if (input.read((char*)&second1, 1)) {
			if (input.read((char*)&third1, 1)) {
				countS = 1;
				while (first == first1 && second == second1 && third == third1) {
					countS++;
					if (input.read((char*)&first1, 1)) {
						if (input.read((char*)&second1, 1)) {
							if (input.read((char*)&third1, 1)) {
								continue;
							}
							else {
								where1 = "third";
								break;
							}
						}
						else {
							where1 = "second";
							break;
						}
					}
					else {
						where1 = "first";
						break;
					}
				}
				if (countS < 256) {
					char countChar = countS;
					output.write((char*)&countChar, 1);
				}
				else if(countS<65535){
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
				first = first1;
				second = second1;
				third = third1;
			}
			else {
				char one = 1;
				output.write((char*)&one, sizeof(first));
				output.write((char*)&first, sizeof(first));
				output.write((char*)&second, sizeof(second));
				output.write((char*)&third, sizeof(third));
				where1 = "third";
				break;
			}
		}
		else {
			char one = 1;
			output.write((char*)&one, sizeof(first));

			output.write((char*)&first, sizeof(first));
			output.write((char*)&second, sizeof(second));
			output.write((char*)&third, sizeof(third));
			where1 = "second";
			break;
		}
	}
	if (where1 == "third") {
		char one = 1;
		input.seekg(-2, ios::end);
		input.read((char*)&first1, 1);
		input.read((char*)&second1, 1);
		output.write((char*)&one, sizeof(first));
		output.write((char*)&first1, sizeof(first));
		output.write((char*)&second1, sizeof(second));
	}	
	else if (where1 == "second") {
		char one = 1;
		input.seekg(-1, ios::end);
		output.write((char*)&one, sizeof(first));
		input.read((char*)&first1, 1);
		output.write((char*)&first1, sizeof(first));
	}
	else if(where1 == "first")
		
	
	/*if (from.substr(from.rfind('.')) == ".bmp") {
		char sym1 = 1;
		output.write((char*)&sym1, sizeof(sym1));
		output.write((char*)&now, sizeof(now));
	}*/
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
	char first, second, third;
	char numBytes;
	while (input.read((char*)&numBytes, 1))
	{
		if (numBytes != 27) // 27 - два байта, либо 27 повторов
		{
			if (input.read((char*)&first, 1)) {
				if (input.read((char*)&second, 1)) {
					if (input.read((char*)&third, 1)) {
						for (int i = 0; i < numBytes; i++) {
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
				else {
					output.write((char*)&first, 1);
				}
			}
			else {
				break;
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
			
			if (input.read((char*)&first, 1)) {
				if (input.read((char*)&second, 1)) {
					if (input.read((char*)&third, 1)) {
						for (int i = 0; i < countSym; i++) {
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
				else {
					output.write((char*)&first, 1);
				}
			}
			else {
				break;
			}
		}
	}
	cout << "Done." << endl;
	cout << "Result written to " << toFile << ".";
	input.close(); output.close();
	return true;
}

