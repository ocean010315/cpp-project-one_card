#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "OneCard.h"

using namespace std;

Card::Card() {
	srand((unsigned int)time(NULL)); //deck�� �ʱ�ȭ�� �� ������ ���� ���� srand() �Լ��� time�� ����Ͽ� seed ����
	
	//deck �ʱ�ȭ
	for (int i = 0; i < 54; i++) { //deck�� ���� ���� ���·� 54���� ī�带 ������� �Է�
		if (i < 13)	Deck.push_back("��"); //������ ���� ���ڸ� ���� �Է�
		else if (i < 26) Deck.push_back("��");
		else if (i < 39) Deck.push_back("��");
		else if (i < 52) Deck.push_back("��");
		else Deck.push_back("Joker");

		if (i == 0 || i == 13 || i == 26 || i == 39) Deck[i] += "A"; //���ĺ� �Է�
		else if (i == 10 || i == 23 || i == 36 || i == 49) Deck[i] += "J";
		else if (i == 11 || i == 24 || i == 37 || i == 50) Deck[i] += "Q";
		else if (i == 12 || i == 25 || i == 38 || i == 51) Deck[i] += "K";
	}

	for (double j = 0; j < 4; j++) { //���� �Է�
		for (double k = 1; k < 10; k++) Deck[13 * j + k] += to_string((int) k + 1);
	}

	//������� �ʱ�ȭ�� deck ����. rand() �Լ��� ����Ͽ� �� ���� �̰� �����ִ� ������ 100�� �ݺ�.
	string tmp;
	for (int i = 0; i < 100; i++) {
		int i1 = rand() % 54;
		int i2 = rand() % 54;
		tmp = Deck[i1];
		Deck[i1] = Deck[i2];
		Deck[i2] = tmp;
	}

	//Player, Computer �ʱ�ȭ
	for (int i = 0; i < 7; i++) {
		Player.push_back(Deck.back()); //deck�� ���������� ����ڿ��� ī�带 �� �徿 ���
		Deck.pop_back(); //deck���� ���� ī��� deck���� ����. ������ ī�带 ������ �Ͱ� ���� ȿ��.

		Computer.push_back(Deck.back()); //deck�� ���������� ��ǻ�Ϳ��� ī�带 �� �徿 ���
		Deck.pop_back(); //deck���� ���� ī��� deck���� ����. ������ ī�带 ������ �Ͱ� ���� ȿ��.
	}

	//�ٴڿ� ���� ī�� shown_card �ʱ�ȭ
	while (1) {
		shown_card.push_back(Deck.back());
		Deck.pop_back(); //deck���� ���� ī��� deck���� ����. ������ ī�带 ������ �Ͱ� ���� ȿ��.

		if (shown_card.back() != "Joker") { break; } //�ٴڿ� ���� ī�尡 Joker�� ��� ī�� �ٽ� �̱�. (���� ī���̹Ƿ�)
	}
}