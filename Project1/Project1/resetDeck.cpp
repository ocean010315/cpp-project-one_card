#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "OneCard.h"

using namespace std;

void resetDeck(GameStart& C) {
	srand((unsigned int)time(NULL));

	string memory = C.shown_card.back(); //�� �� ī��� ���� �� �Ʒ� ī��鸸 ����
	C.shown_card.pop_back(); //�� �� ī�� �����س����� ���� ī��鳢�� ���� ���� �����ֱ�

	string tmp;
	for (int i = 0; i < 100; i++) {
		int t1 = rand() % C.shown_card.size();
		int t2 = rand() % C.shown_card.size();

		tmp = C.shown_card[t1];
		C.shown_card[t1] = C.shown_card[t2];
		C.shown_card[t2] = tmp;
	}

	//shown_card ������ ���ҵ��� �� ���������� �ٽ� deck�� push����.
	for (int i = 0; i < C.shown_card.size(); i++) {
		C.Deck.push_back(C.shown_card[i]);
		C.shown_card.pop_back();
	}

	C.shown_card.push_back(memory);
}