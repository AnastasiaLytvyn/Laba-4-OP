#include "RLEArchive.h"

bool RLEArchiver::Compress(string from, string to, map <string, int> dict, map <string, int>::iterator it) {
	ifstream input(from, ios::binary);
	ofstream output(to, ios::binary);
	cout << "Ñompressing  " << from << " ... ";
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
		char countChar = countS;
		output.write((char*)&countChar, 1);
		output.write((char*)&now, 1);
		now = current;
		//1They => i=0; last=1	
	}
	return true;
}