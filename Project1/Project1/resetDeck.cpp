#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "OneCard.h"

using namespace std;

void resetDeck(GameStart& C) {
	srand((unsigned int)time(NULL));

	string memory = C.shown_card.back(); //맨 위 카드는 저장 후 아래 카드들만 섞기
	C.shown_card.pop_back(); //맨 위 카드 저장해놨으니 남은 카드들끼리 섞기 위해 없애주기

	string tmp;
	for (int i = 0; i < 100; i++) {
		int t1 = rand() % C.shown_card.size();
		int t2 = rand() % C.shown_card.size();

		tmp = C.shown_card[t1];
		C.shown_card[t1] = C.shown_card[t2];
		C.shown_card[t2] = tmp;
	}

	//shown_card 벡터의 원소들을 다 섞어줬으면 다시 deck에 push해줌.
	for (int i = 0; i < C.shown_card.size(); i++) {
		C.Deck.push_back(C.shown_card[i]);
		C.shown_card.pop_back();
	}

	C.shown_card.push_back(memory);
}