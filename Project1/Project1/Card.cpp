#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "OneCard.h"

using namespace std;

Card::Card() {
	srand((unsigned int)time(NULL)); //deck을 초기화한 후 섞어줄 때를 위한 srand() 함수에 time을 사용하여 seed 설정
	
	//deck 초기화
	for (int i = 0; i < 54; i++) { //deck을 섞지 않은 상태로 54장의 카드를 순서대로 입력
		if (i < 13)	Deck.push_back("♠"); //도형에 대한 문자를 먼저 입력
		else if (i < 26) Deck.push_back("♣");
		else if (i < 39) Deck.push_back("◇");
		else if (i < 52) Deck.push_back("♡");
		else Deck.push_back("Joker");

		if (i == 0 || i == 13 || i == 26 || i == 39) Deck[i] += "A"; //알파벳 입력
		else if (i == 10 || i == 23 || i == 36 || i == 49) Deck[i] += "J";
		else if (i == 11 || i == 24 || i == 37 || i == 50) Deck[i] += "Q";
		else if (i == 12 || i == 25 || i == 38 || i == 51) Deck[i] += "K";
	}

	for (double j = 0; j < 4; j++) { //숫자 입력
		for (double k = 1; k < 10; k++) Deck[13 * j + k] += to_string((int) k + 1);
	}

	//순서대로 초기화한 deck 섞기. rand() 함수를 사용하여 두 장을 뽑고 섞어주는 과정을 100번 반복.
	string tmp;
	for (int i = 0; i < 100; i++) {
		int i1 = rand() % 54;
		int i2 = rand() % 54;
		tmp = Deck[i1];
		Deck[i1] = Deck[i2];
		Deck[i2] = tmp;
	}

	//Player, Computer 초기화
	for (int i = 0; i < 7; i++) {
		Player.push_back(Deck.back()); //deck의 위에서부터 사용자에게 카드를 한 장씩 배부
		Deck.pop_back(); //deck에서 뽑은 카드는 deck에서 삭제. 실제로 카드를 나눠준 것과 같은 효과.

		Computer.push_back(Deck.back()); //deck의 위에서부터 컴퓨터에게 카드를 한 장씩 배부
		Deck.pop_back(); //deck에서 뽑은 카드는 deck에서 삭제. 실제로 카드를 나눠준 것과 같은 효과.
	}

	//바닥에 놓일 카드 shown_card 초기화
	while (1) {
		shown_card.push_back(Deck.back());
		Deck.pop_back(); //deck에서 뽑은 카드는 deck에서 삭제. 실제로 카드를 나눠준 것과 같은 효과.

		if (shown_card.back() != "Joker") { break; } //바닥에 놓인 카드가 Joker일 경우 카드 다시 뽑기. (공격 카드이므로)
	}
}