#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>

#include "OneCard.h"

using namespace std;

int GameStart::getDeckSize() { return Deck.size(); }
int GameStart::getComputerSize() { return Computer.size(); }
int GameStart::getPlayerSize() { return Player.size(); }

//��Ŀ�� �� ���� ���� �� ������ ������ ������ 
void GameStart::ifJoker() {
	if (shown_card.back() == "Joker") {
		while (shown_card.back() == "Joker") {
			shown_card.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

//Player�� ������ �� �⺻���� ������ ����� �Լ�
void GameStart::showPlayer() {
	cout << "���� ī��: " << shown_card.back() << endl;

	cout << "Player: ";
	for (int i = 0; i < Player.size(); i++) { //����ڿ��� �־��� ī�带 ��� ����Ͽ� �����ش�.
		cout << i + 1 << ":" << Player[i] << "\t";
	}

	if (cnt == 0) { cout << Player.size() + 1 << ":draw �� �� ����" << endl; }
	else { cout << Player.size() + 1 << ":�� ����" << endl; }
	cout << endl;

	cout << "�ٴڿ� �ִ� ī���� ��: " << shown_card.size() << endl;
	cout << "deck�� ���� ī���� ����: " << Deck.size() << endl;
	cout << "��밡 ���� ī���� ����: " << Computer.size() << endl << endl;

	cout << "ī�带 �����ϼ���>> ";
}

//Computer�� ������ �� ��ǻ���� ī�尡 �ƴ� ���� ī���� ������ ����Ѵ�.
void GameStart::showComputer() {
	cout << "���� ī��: " << shown_card.back() << endl;
}

//Player�� ������ �� Player�� ���� ī�忡 ���� �Լ�
void GameStart::PlayerTurn() {
	cnt = 0; //ù �ϰ� �� ������ �Ͽ� ���� ������ ���� ����
	PlayerNone = 0;

	int n; //Player�� index�� �� ����

	this->showPlayer();

	while (cnt == 0) {
		cin >> select; //Player�� �� ī�忡 ���� ��ȣ�� �Է¹ޱ�
		n = select - 1; //Player�� �� ī���� index

		//�� ī�尡 ���� ��� �� �� draw �� �� ����
		if (select == Player.size() + 1) {
			cout << Deck.back() << endl;
			Player.push_back(Deck.back());
			Deck.pop_back();

			PlayerNone = 1;

			break;
		}

		//ù �Ͽ��� ������ ���ų� ���� �� ���ڰ� ���� ��� ī�带 �� �� �ִ�.
		if (shown_card.back().substr(0, 2) == Player[n].substr(0, 2) || //������ ���� ���
			shown_card.back().substr(2, 1) == Player[n].substr(2, 1) || //���ڰ� ���� ���
			Player[n] == "Joker") //Joker�� �� ���
		{
			//Player�� ������ ī�带 ���� ī�� ���Ϳ� push�ϰ� Player�� ���Ϳ����� erase�Ѵ�.
			shown_card.push_back(Player[n]);
			Player.erase(Player.begin() + (n));

			//������ ���� K�� J�� ���Ե� ī�带 ���� Player�� ù ������ �ʱ�ȭ
			if (shown_card.back().substr(2, 1) == "K" || shown_card.back().substr(2, 1) == "J") {
				cnt = 0;
			}
			//ī�忡 K�� J�� ���ԵǾ� ���� �ʴٸ� ���� ������ �Ѿ
			else { cnt++; }

			//ȭ�� �ʱ�ȭ
			system("cls");
			this->showPlayer();
		}
		//��Ģ�� ��߳��� ī�带 �� ���
		else { cout << "�� �� ���� ī���Դϴ�." << endl; }
	}

	//�� ��° �Ͽ� ���� �Լ�
	if (cnt != 0) {		
		cin >> select; //����ڰ� �� ī�� �Է� �ޱ�
		
		//�� ī�尡 ������ �� �� draw���� �ʰ� �ٷ� �� ����
		while (select != Player.size() + 1) {
			n = select - 1;

			//�� ��° �Ͽ����� ���� �� ���ڰ� ���� ī�常 �� �� �ִ�.
			if (shown_card.back().substr(2, 1) == Player[n].substr(2, 1) ||
				Player[n] == "Joker") //Joker�� �� ���
			{
				//Joker ī�带 ���� ī�� ���Ϳ� push�ϰ� Player�� ���Ϳ��� erase
				shown_card.push_back(Player[n]);
				Player.erase(Player.begin() + (n));

				//ȭ�� �ʱ�ȭ
				system("cls");
				this->showPlayer();

				//Player�� ���� ���� �Է� �ޱ�
				cin >> select;
			}
			//ī�带 �߸� ���� ��� ���� ������ ����ϰ� �ٽ� �Է¹ޱ�
			else {
				cout << "�� �� ���� ī���Դϴ�." << endl;
				//Player�� ���� ���� �Է� �ޱ�
				cin >> select;
			}
		}
	}
}

//��ǻ���� ���ʿ� ���� �Լ�
void GameStart::ComputerTurn() {
	cnt = 0; //ù ��° �Ͽ��� �� ��° ������ �Ѿ�� ���� ī��Ʈ
	ComputerNone = 0;

	int Joker_index = 1234;

	this->showComputer();

	//ù �Ͽ��� ����, ��� ��� ����
	while (cnt == 0) {
		for (int i = 0; i < Computer.size(); i++) {
			if (shown_card.back().substr(0, 2) == Computer[i].substr(0, 2) || //������ ���� ���
				shown_card.back().substr(2, 1) == Computer[i].substr(2, 1)) //���ڰ� ���� ���
			{
				cout << "Computer�� ����>> " << Computer[i] << endl; //��ǻ�Ͱ� �� ī�尡 �������� ����Ͽ� �����ֱ�

				shown_card.push_back(Computer[i]); //Computer�� �� ī�带 ���� ī�� ���Ϳ� push�ϰ�
				Computer.erase(Computer.begin() + i); //Computer�� ���Ϳ����� ���ֱ�

				cnt++; //ī�带 �� �� ������ ī��Ʈ�ϰ�

				break; //break�ؼ� �� ��° �Ͽ� ���� loop�� ����
			}

			if (Computer[i] == "Joker") {
				Joker_index = i; //Computer ������ ���Ҹ� ��ĵ �� Joker�� �ִٸ� ���� �������� ���ֱ� ���� index ����
			}
		}

		//K�� J�� ���Ե� ī�带 ���� ù ������ ���ư�
		if (shown_card.back().substr(2, 1) == "K" || shown_card.back().substr(2, 1) == "J") {
			cnt = 0;
		}

		//Computer�� ��� ī�带 ��ĵ �� �� ī�尡 ������ �� �� draw�ϰ� ���� ����
		if (cnt == 0) {
			//Computer�� ��Ŀ�� �� ��
			if (Joker_index != 1234) {
				cout << "Computer�� ����>> " << Computer[Joker_index] << endl; //Joker_index�� ���� ����Ǿ� �ִٸ� Joker�� ���ֱ�

				//���� ī�� ���Ϳ� Joker�� push�ϰ� Computer ���Ϳ����� Joker ī�带 erase
				shown_card.push_back(Computer[Joker_index]);
				Computer.erase(Computer.begin() + Joker_index);

				cnt++;
				ComputerNone = 1;
				break;
			}
			//�� ī�尡 ���ٸ� �� �� draw
			else {
				cout << "Computer draw" << endl;
				Computer.push_back(Deck.back());
				Deck.pop_back();

				break;
			}
		}
	}

	//ù ���� ���� �� Joker_index�� 1234�� �ʱ�ȭ�Ͽ� �� �� ������ �缳��
	Joker_index = 1234;

	//�� ��° ���� ��
	if (cnt != 0) {
		for (int i = 0; i < Computer.size(); i++) {
			//Joker�� ���ٸ� ī�� ����
			if (shown_card.back().substr(2, 1) == Computer[i].substr(2, 1)) { //�� ��° �Ϻ��ʹ� ���ڰ� ���� ī�常 �� �� ����
				cout << "Computer�� ����>> " << Computer[i] << endl; //��ǻ�Ͱ� �� ī�尡 �������� �ϳ��� �����ֱ�

				shown_card.push_back(Computer[i]);
				Computer.erase(Computer.begin() + i);
			}
		}

		for (int i = 0; i < Computer.size(); i++) {
			if (Computer[i] == "Joker") {
				cout << "Computer�� ����>> Joker" << endl;

				shown_card.push_back(Computer[i]);
				Computer.erase(Computer.begin() + i);

				break;
			}
		}
	}
}


//���� ī��
void GameStart::AttackComputer() { //Player�� ��ǻ�͸� �����ϴ� �Լ�
	if (shown_card.back().substr(2, 1) == "2") { //���ڰ� 2�� ī��� 2�徿 draw
		for (int i = 0; i < 2; i++) {
			Computer.push_back(Deck.back());
			Deck.pop_back();
		}
	}

	if (shown_card.back().substr(2, 1) == "A") { //A ī��� ��쿡 ���� 3��, 5�徿 draw
		if (shown_card.back().substr(0, 2) == "��") {
			for (int i = 0; i < 5; i++) {
				Computer.push_back(Deck.back());
				Deck.pop_back();
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				Computer.push_back(Deck.back());
				Deck.pop_back();
			}
		}
	}

	if (shown_card.back() == "Joker") { //Joker�� ��� 7�徿 draw
		for (int i = 0; i < 7; i++) {
			Computer.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

void GameStart::AttackPlayer() { //Computer�� Player�� �����ϴ� �Լ�
	//���ڰ� 2�� ī��� 2�徿 draw
	if (shown_card.back().substr(2, 1) == "2") {
		for (int i = 0; i < 2; i++) {
			Player.push_back(Deck.back());
			Deck.pop_back();
		}
	}

	//A ī��� ��쿡 ���� 3��, 5�徿 draw
	if (shown_card.back().substr(2, 1) == "A") {
		if (shown_card.back().substr(0, 2) == "��") {
			for (int i = 0; i < 5; i++) {
				Player.push_back(Deck.back());
				Deck.pop_back();
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				Player.push_back(Deck.back());
				Deck.pop_back();
			}
		}
	}

	//Joker�� ��� 7�徿 draw
	if (shown_card.back() == "Joker") {
		for (int i = 0; i < 7; i++) {
			Player.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

//7�� ���� �� ��� �ٲٱ�
void GameStart::ChangeShape_Player() {
	if (select != Player.size() + 1 && shown_card.back().substr(2, 1) == "7") {
		tmpIndex_7 = shown_card.size() - 1; //deck�� ī�尡 �ߺ����� �ʵ��� �� �Լ��� ����� ���Ŀ� ���� ī��� �������� ���� ���� tmpIndex_7�� tmpShape_7
		tmpShape_7 = shown_card.back();

		int shape; //����ڰ� ���ϴ� ����� �Է� ���� ����

		cout << "1:�� 2:�� 3:�� 4:��" << endl
			<< "���ϴ� ����� �����ϼ���>> ";
		cin >> shape;

		switch (shape) { //switch case���� ���� ��� �ٲٱ�
		case 1:
			shown_card.back() = "��7";
			break;

		case 2:
			shown_card.back() = "��7";
			break;

		case 3:
			shown_card.back() = "��7";
			break;

		case 4:
			shown_card.back() = "��7";
			break;
		}
	}
}

void GameStart::ChangeShape_Computer() { //��ǻ�Ͱ� 7�� ���Ե� ī�带 ���� ���� ���� ��� ����
	if (shown_card.back().substr(2, 1) == "7" && cnt != 0) {
		tmpIndex_7 = shown_card.size() - 1;
		tmpShape_7 = shown_card.back();

		int shape = rand() % 4 + 1; //�������� ��� ���� - ������ Player�� ī�带 �ϳ��� ���Ͽ� ����ġ�� ����ؾ� ��
		
		switch (shape) {
		case 1:
			shown_card.back() = "��7";
			break;

		case 2:
			shown_card.back() = "��7";
			break;

		case 3:
			shown_card.back() = "��7";
			break;

		case 4:
			shown_card.back() = "��7";
			break;
		}
	}
}

void GameStart::setOriginal() { //7�� ���Ե� ī�带 ���� ����� �ٲ� �� deck�� �ߺ��� ī�尡 ������ �ʵ��� ������� �ǵ����� �Լ�
	shown_card[tmpIndex_7] = tmpShape_7;
	tmpShape_7 = "none";
}