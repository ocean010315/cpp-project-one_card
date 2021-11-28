#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "onecard.h"

using namespace std;

bool checkWin(GameStart& C) {
	srand((unsigned int)time(NULL));

	if (C.getPlayerSize() >= 14 || C.getComputerSize() >= 14) {
		system("cls");

		if (C.getPlayerSize() >= 14) {
			cout << "Player 파산!" << endl << endl;
			cout << "L    \t\t";	cout << "OOOOO\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "S    \t\t";	cout << "E" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "    S\t\t";	cout << "E    " << endl;
			cout << "LLLLL\t\t";	cout << "OOOOO\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
		}
		if (C.getComputerSize() >= 14) {
			cout << "Computer 파산!" << endl << endl;
			cout << "W     W     W\t\t";	cout << "IIII\t\t";	cout << "N    N" << endl;
			cout << " W   W W   W\t\t";		cout << " II \t\t";	cout << "NN   N" << endl;
			cout << "  W W   W W\t\t";		cout << " II \t\t";	cout << "N N  N" << endl;
			cout << "   W     W\t\t";		cout << " II \t\t";	cout << "N  N N" << endl;
			cout << "\t\t\t";				cout << "IIII\t\t";	cout << "N    N" << endl;
		}

		return true;
	}
	else if (C.getPlayerSize() == 0 || C.getComputerSize() == 0) {
		system("cls");

		if (C.getPlayerSize() == 0) {
			cout << "W     W     W\t\t";	cout << "IIII\t\t";	cout << "N    N" << endl;
			cout << " W   W W   W\t\t";		cout << " II \t\t";	cout << "NN   N" << endl;
			cout << "  W W   W W\t\t";		cout << " II \t\t";	cout << "N N  N" << endl;
			cout << "   W     W\t\t";		cout << " II \t\t";	cout << "N  N N" << endl;
			cout << "\t\t\t";					cout << "IIII\t\t";	cout << "N    N" << endl;
		}
		if (C.getComputerSize() == 0) {
			cout << "L    \t\t";	cout << "OOOOO\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "S    \t\t";	cout << "E" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
			cout << "L    \t\t";	cout << "O   O\t\t";	cout << "    S\t\t";	cout << "E    " << endl;
			cout << "LLLLL\t\t";	cout << "OOOOO\t\t";	cout << "SSSSS\t\t";	cout << "EEEEE" << endl;
		}

		return true;
	}
	else return false;
}
