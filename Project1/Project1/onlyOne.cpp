#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "onecard.h"

using namespace std;

void onlyOne(GameStart& C) {
	srand((unsigned int)time(NULL));

	clock_t start, end;

	int timeComputer = rand() % 4000 + 1000;
	string onecard;

	cout << timeComputer << "ms �ȿ� onecard �Է�! >> ";

	start = clock();
	cin >> onecard;
	end = clock();

	int timePlayer = end - start;

	if (timeComputer > timePlayer) {
		cout << "Player�� �� �������ϴ�" << endl;
		C.Computer.push_back(C.Deck.back());
		C.Deck.pop_back();
		Sleep(3000);
	}
	else {
		cout << "Computer�� �� �������ϴ�" << endl;
		C.Player.push_back(C.Deck.back());
		C.Deck.pop_back();
		Sleep(3000);
	}
}