#ifndef ONECARD_H
#define ONECARD_H

#include <iostream>
#include <vector>

using namespace std;

class Card {
protected:
	vector<string> Deck; //전체 카드를 초기화할 변수
	vector<string> Player; //사용자에게 주어지는 카드를 나타내는 변수
	vector<string> Computer; //컴퓨터에게 주어지는 카드를 나타내는 변수
	vector<string> shown_card; //사용자 및 컴퓨터가 카드를 낼 때 기준이 되는 카드를 나타내는 변수

public:
	Card(); //deck, Player, Computer, shown_card 초기화
};

class GameStart: public Card { //게임이 시작되고 사용자와 컴퓨터가 돌아가며 카드를 내는 상황을 구현할 클래스. Card 클래스를 상속시켜 GameStart 클래스만으로 Card 클래스가 생성되도록 함.
	int cnt;
	int select; //Player의 선택을 입력받을 변수

public:
	int getDeckSize();
	int getPlayerSize();
	int getComputerSize();

	void ifJoker(); //shown_card.back() == "Joker"일 때 deck에서 한 장 꺼내서 shown_card.push_back()해주기

	void showPlayer(); //Player와 shown_card의 종류, Computer가 가진 카드의 개수 보여주기
	void showComputer();

	//K, Q, J, 7 등의 특수 카드는 Turn 함수에 구현
	void PlayerTurn(); //사용자의 순서에 카드를 내는 상황을 구현할 함수
	bool PlayerNone; //Player가 카드를 하나도 내지 않았을 때를 명시해줄 변수

	void ComputerTurn(); //컴퓨터의 순서에 카드를 내는 상황을 구현할 함수
	bool ComputerNone;

	void AttackComputer(); //Player가 Computer에게 공격 카드를 냈을 때
	void AttackPlayer(); //Computer가 Player에게 공격 카드를 냈을 때

	//숫자 7을 냈을 때 모양 바꾸기
	int tmpIndex_7;
	string tmpShape_7 = "none";
	void ChangeShape_Player(); //Player가 7을 냈을 때
	void ChangeShape_Computer(); //Computer가 7을 냈을 때
	void setOriginal(); //모양 바꾼 카드 원래대로 돌려주기

	friend void resetDeck(GameStart& C); //deck에 카드가 없을 때 shown_card 배열에서 섞어서 초기화
	friend void onlyOne(GameStart& C);
	friend bool checkWin(GameStart& C); //이기는 경우를 판정할 함수
};

#endif