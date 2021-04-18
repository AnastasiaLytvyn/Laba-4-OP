#include "dictionary.h"
void createDict() {
	ofstream fOut("../project4/dict.txt");//‘¿“¿√–¿‘»–”ﬁ «¿ ¿¿¿“
	if (!fOut.is_open()) {
		cout << "err";
	}
	else {
		for (int i = 32; i < 256; i++) {
			fOut << (char)(i) <<" ->"<< i << endl;
		}
		
	}
	/*ifstream dictF("../project4/dict.txt");
	if (!dictF.is_open()) {
		cout << "No such file";
	}
	else {
		string str;
		while (!dictF.eof()) {
			getline(dictF, str);
			cout << str << endl;
		}
	}*/
}

