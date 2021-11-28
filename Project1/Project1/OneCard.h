#ifndef ONECARD_H
#define ONECARD_H

#include <iostream>
#include <vector>

using namespace std;

class Card {
protected:
	vector<string> Deck; //��ü ī�带 �ʱ�ȭ�� ����
	vector<string> Player; //����ڿ��� �־����� ī�带 ��Ÿ���� ����
	vector<string> Computer; //��ǻ�Ϳ��� �־����� ī�带 ��Ÿ���� ����
	vector<string> shown_card; //����� �� ��ǻ�Ͱ� ī�带 �� �� ������ �Ǵ� ī�带 ��Ÿ���� ����

public:
	Card(); //deck, Player, Computer, shown_card �ʱ�ȭ
};

class GameStart: public Card { //������ ���۵ǰ� ����ڿ� ��ǻ�Ͱ� ���ư��� ī�带 ���� ��Ȳ�� ������ Ŭ����. Card Ŭ������ ��ӽ��� GameStart Ŭ���������� Card Ŭ������ �����ǵ��� ��.
	int cnt;
	int select; //Player�� ������ �Է¹��� ����

public:
	int getDeckSize();
	int getPlayerSize();
	int getComputerSize();

	void ifJoker(); //shown_card.back() == "Joker"�� �� deck���� �� �� ������ shown_card.push_back()���ֱ�

	void showPlayer(); //Player�� shown_card�� ����, Computer�� ���� ī���� ���� �����ֱ�
	void showComputer();

	//K, Q, J, 7 ���� Ư�� ī��� Turn �Լ��� ����
	void PlayerTurn(); //������� ������ ī�带 ���� ��Ȳ�� ������ �Լ�
	bool PlayerNone; //Player�� ī�带 �ϳ��� ���� �ʾ��� ���� ������� ����

	void ComputerTurn(); //��ǻ���� ������ ī�带 ���� ��Ȳ�� ������ �Լ�
	bool ComputerNone;

	void AttackComputer(); //Player�� Computer���� ���� ī�带 ���� ��
	void AttackPlayer(); //Computer�� Player���� ���� ī�带 ���� ��

	//���� 7�� ���� �� ��� �ٲٱ�
	int tmpIndex_7;
	string tmpShape_7 = "none";
	void ChangeShape_Player(); //Player�� 7�� ���� ��
	void ChangeShape_Computer(); //Computer�� 7�� ���� ��
	void setOriginal(); //��� �ٲ� ī�� ������� �����ֱ�

	friend void resetDeck(GameStart& C); //deck�� ī�尡 ���� �� shown_card �迭���� ��� �ʱ�ȭ
	friend void onlyOne(GameStart& C);
	friend bool checkWin(GameStart& C); //�̱�� ��츦 ������ �Լ�
};

#endif