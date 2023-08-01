#include <fstream>
#include"optimize.h"

void OutputQt(){
    ofstream file("Qt.txt");
	for (int i = 0; i < Qt.size(); i++) {
		file << Qt[i].first << '\t' << Qt[i].second << '\t' << Qt[i].third << '\t' << Qt[i].fourth << '\t' << endl;
	}
	file.close();
}
void OutputNewQt(){
    ofstream file("NewQt.txt");
	for (int i = 0; i < NewQt.size(); i++) {
		file << NewQt[i].first << '\t' << NewQt[i].second << '\t' << NewQt[i].third << '\t' << NewQt[i].fourth << '\t' << endl;
	}
	file.close();
}

