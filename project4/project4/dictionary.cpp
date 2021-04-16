#include "dictionary.h"
void createDict() {
	ofstream fOut("../project4/dict.txt");//‘¿“¿√–¿‘»–”ﬁ «¿ ¿¿¿“
	if (!fOut.is_open()) {
		cout << "err";
	}
	else {
		for (int i = 0; i < 223; i++) {
			fOut << (char)(i+32) <<" ->"<< i << endl;
		}
		
	}
	ifstream dictF("../project4/dict.txt");
	if (!dictF.is_open()) {
		cout << "No such file";
	}
	else {
		string str;
		while (!dictF.eof()) {
			getline(dictF, str);
			cout << str << endl;
		}
	}
}

string toBinary(int num) {
	int res = num;
	string str1="";
	string str2 = "";
	while (res != 1 && res!=0) {
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
	return str2;
}