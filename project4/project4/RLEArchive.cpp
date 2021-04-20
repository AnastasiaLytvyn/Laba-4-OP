#include "RLEArchive.h"

//проверить для перехода на новую строку
bool RLEArchiver::Compress(string from, string to, map <string, int> dict, map <string, int>::iterator it) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	cout << "Сompressing  " << from << " ... ";
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
			int countS2 = countS & ((1 <<12) - 1);
			char countChar1 = countS1;
			char countChar2 = countS2;
			char twoBytesAlert = 27;
			output.write((char*)&twoBytesAlert, 1);
			output.write((char*)&countChar1, 1);
			output.write((char*)&countChar2, 1);
		}
		output.write((char*)&now, 1);
		now = current;
		//1They => i=0; last=1	
	}
	return true;
}