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

//조커가 맨 위에 있을 때 공격의 역할이 끝나면 
void GameStart::ifJoker() {
	if (shown_card.back() == "Joker") {
		while (shown_card.back() == "Joker") {
			shown_card.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

//Player의 차례일 때 기본적인 정보를 출력할 함수
void GameStart::showPlayer() {
	cout << "기준 카드: " << shown_card.back() << endl;

	cout << "Player: ";
	for (int i = 0; i < Player.size(); i++) { //사용자에게 주어진 카드를 모두 출력하여 보여준다.
		cout << i + 1 << ":" << Player[i] << "\t";
	}

	if (cnt == 0) { cout << Player.size() + 1 << ":draw 후 턴 종료" << endl; }
	else { cout << Player.size() + 1 << ":턴 종료" << endl; }
	cout << endl;

	cout << "바닥에 있는 카드의 수: " << shown_card.size() << endl;
	cout << "deck에 남은 카드의 개수: " << Deck.size() << endl;
	cout << "상대가 가진 카드의 개수: " << Computer.size() << endl << endl;

	cout << "카드를 선택하세요>> ";
}

//Computer의 차례일 때 컴퓨터의 카드가 아닌 기준 카드의 정보를 출력한다.
void GameStart::showComputer() {
	cout << "기준 카드: " << shown_card.back() << endl;
}

//Player의 차례일 때 Player가 내는 카드에 대한 함수
void GameStart::PlayerTurn() {
	cnt = 0; //첫 턴과 그 이후의 턴에 대한 구분을 위한 변수
	PlayerNone = 0;

	int n; //Player의 index가 될 변수

	this->showPlayer();

	while (cnt == 0) {
		cin >> select; //Player가 낼 카드에 대한 번호를 입력받기
		n = select - 1; //Player가 낼 카드의 index

		//낼 카드가 없는 경우 한 장 draw 후 턴 종료
		if (select == Player.size() + 1) {
			cout << Deck.back() << endl;
			Player.push_back(Deck.back());
			Deck.pop_back();

			PlayerNone = 1;

			break;
		}

		//첫 턴에서 도형이 같거나 숫자 및 문자가 같은 경우 카드를 낼 수 있다.
		if (shown_card.back().substr(0, 2) == Player[n].substr(0, 2) || //도형이 같은 경우
			shown_card.back().substr(2, 1) == Player[n].substr(2, 1) || //숫자가 같은 경우
			Player[n] == "Joker") //Joker를 낼 경우
		{
			//Player가 선택한 카드를 기준 카드 벡터에 push하고 Player의 벡터에서는 erase한다.
			shown_card.push_back(Player[n]);
			Player.erase(Player.begin() + (n));

			//규착에 따라 K나 J가 포함된 카드를 내면 Player의 첫 턴으로 초기화
			if (shown_card.back().substr(2, 1) == "K" || shown_card.back().substr(2, 1) == "J") {
				cnt = 0;
			}
			//카드에 K나 J가 포함되어 있지 않다면 다음 턴으로 넘어감
			else { cnt++; }

			//화면 초기화
			system("cls");
			this->showPlayer();
		}
		//규칙에 어긋나는 카드를 낼 경우
		else { cout << "낼 수 없는 카드입니다." << endl; }
	}

	//두 번째 턴에 대한 함수
	if (cnt != 0) {		
		cin >> select; //사용자가 낼 카드 입력 받기
		
		//낼 카드가 없으면 한 장 draw하지 않고 바로 턴 종료
		while (select != Player.size() + 1) {
			n = select - 1;

			//두 번째 턴에서는 숫자 및 문자가 같은 카드만 낼 수 있다.
			if (shown_card.back().substr(2, 1) == Player[n].substr(2, 1) ||
				Player[n] == "Joker") //Joker를 낼 경우
			{
				//Joker 카드를 기준 카드 벡터에 push하고 Player의 벡터에서 erase
				shown_card.push_back(Player[n]);
				Player.erase(Player.begin() + (n));

				//화면 초기화
				system("cls");
				this->showPlayer();

				//Player의 다음 선택 입력 받기
				cin >> select;
			}
			//카드를 잘못 냈을 경우 에러 문구를 출력하고 다시 입력받기
			else {
				cout << "낼 수 없는 카드입니다." << endl;
				//Player의 다음 선택 입력 받기
				cin >> select;
			}
		}
	}
}

//컴퓨터의 차례에 대한 함수
void GameStart::ComputerTurn() {
	cnt = 0; //첫 번째 턴에서 두 번째 턴으로 넘어가기 위한 카운트
	ComputerNone = 0;

	int Joker_index = 1234;

	this->showComputer();

	//첫 턴에는 숫자, 모양 상관 없음
	while (cnt == 0) {
		for (int i = 0; i < Computer.size(); i++) {
			if (shown_card.back().substr(0, 2) == Computer[i].substr(0, 2) || //도형이 같은 경우
				shown_card.back().substr(2, 1) == Computer[i].substr(2, 1)) //숫자가 같은 경우
			{
				cout << "Computer의 선택>> " << Computer[i] << endl; //컴퓨터가 낸 카드가 무엇인지 출력하여 보여주기

				shown_card.push_back(Computer[i]); //Computer가 낸 카드를 기준 카드 벡터에 push하고
				Computer.erase(Computer.begin() + i); //Computer의 벡터에서는 빼주기

				cnt++; //카드를 한 장 냈으면 카운트하고

				break; //break해서 두 번째 턴에 대한 loop로 가기
			}

			if (Computer[i] == "Joker") {
				Joker_index = i; //Computer 벡터의 원소를 스캔 후 Joker가 있다면 가장 마지막에 내주기 위해 index 저장
			}
		}

		//K나 J가 포함된 카드를 내면 첫 턴으로 돌아감
		if (shown_card.back().substr(2, 1) == "K" || shown_card.back().substr(2, 1) == "J") {
			cnt = 0;
		}

		//Computer의 모든 카드를 스캔 후 낼 카드가 없으면 한 장 draw하고 루프 종료
		if (cnt == 0) {
			//Computer가 조커를 낼 때
			if (Joker_index != 1234) {
				cout << "Computer의 선택>> " << Computer[Joker_index] << endl; //Joker_index에 값이 저장되어 있다면 Joker를 내주기

				//기준 카드 벡터에 Joker를 push하고 Computer 벡터에서는 Joker 카드를 erase
				shown_card.push_back(Computer[Joker_index]);
				Computer.erase(Computer.begin() + Joker_index);

				cnt++;
				ComputerNone = 1;
				break;
			}
			//낼 카드가 없다면 한 장 draw
			else {
				cout << "Computer draw" << endl;
				Computer.push_back(Deck.back());
				Deck.pop_back();

				break;
			}
		}
	}

	//첫 턴이 끝난 후 Joker_index를 1234로 초기화하여 낼 수 없도록 재설정
	Joker_index = 1234;

	//두 번째 턴일 때
	if (cnt != 0) {
		for (int i = 0; i < Computer.size(); i++) {
			//Joker가 없다면 카드 내기
			if (shown_card.back().substr(2, 1) == Computer[i].substr(2, 1)) { //두 번째 턴부터는 숫자가 같은 카드만 낼 수 있음
				cout << "Computer의 선택>> " << Computer[i] << endl; //컴퓨터가 낸 카드가 무엇인지 하나씩 보여주기

				shown_card.push_back(Computer[i]);
				Computer.erase(Computer.begin() + i);
			}
		}

		for (int i = 0; i < Computer.size(); i++) {
			if (Computer[i] == "Joker") {
				cout << "Computer의 선택>> Joker" << endl;

				shown_card.push_back(Computer[i]);
				Computer.erase(Computer.begin() + i);

				break;
			}
		}
	}
}


//공격 카드
void GameStart::AttackComputer() { //Player가 컴퓨터를 공격하는 함수
	if (shown_card.back().substr(2, 1) == "2") { //숫자가 2인 카드는 2장씩 draw
		for (int i = 0; i < 2; i++) {
			Computer.push_back(Deck.back());
			Deck.pop_back();
		}
	}

	if (shown_card.back().substr(2, 1) == "A") { //A 카드는 경우에 따라 3장, 5장씩 draw
		if (shown_card.back().substr(0, 2) == "♠") {
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

	if (shown_card.back() == "Joker") { //Joker인 경우 7장씩 draw
		for (int i = 0; i < 7; i++) {
			Computer.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

void GameStart::AttackPlayer() { //Computer가 Player를 공격하는 함수
	//숫자가 2인 카드는 2장씩 draw
	if (shown_card.back().substr(2, 1) == "2") {
		for (int i = 0; i < 2; i++) {
			Player.push_back(Deck.back());
			Deck.pop_back();
		}
	}

	//A 카드는 경우에 따라 3장, 5장씩 draw
	if (shown_card.back().substr(2, 1) == "A") {
		if (shown_card.back().substr(0, 2) == "♠") {
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

	//Joker인 경우 7장씩 draw
	if (shown_card.back() == "Joker") {
		for (int i = 0; i < 7; i++) {
			Player.push_back(Deck.back());
			Deck.pop_back();
		}
	}
}

//7을 냈을 때 모양 바꾸기
void GameStart::ChangeShape_Player() {
	if (select != Player.size() + 1 && shown_card.back().substr(2, 1) == "7") {
		tmpIndex_7 = shown_card.size() - 1; //deck에 카드가 중복되지 않도록 이 함수가 실행된 이후에 원래 카드로 돌려놓기 위한 변수 tmpIndex_7과 tmpShape_7
		tmpShape_7 = shown_card.back();

		int shape; //사용자가 원하는 모양을 입력 받을 변수

		cout << "1:♠ 2:♣ 3:◇ 4:♡" << endl
			<< "원하는 모양을 선택하세요>> ";
		cin >> shape;

		switch (shape) { //switch case문을 통해 모양 바꾸기
		case 1:
			shown_card.back() = "♠7";
			break;

		case 2:
			shown_card.back() = "♣7";
			break;

		case 3:
			shown_card.back() = "◇7";
			break;

		case 4:
			shown_card.back() = "♡7";
			break;
		}
	}
}

void GameStart::ChangeShape_Computer() { //컴퓨터가 7이 포함된 카드를 냈을 때에 대한 경우 구현
	if (shown_card.back().substr(2, 1) == "7" && cnt != 0) {
		tmpIndex_7 = shown_card.size() - 1;
		tmpShape_7 = shown_card.back();

		int shape = rand() % 4 + 1; //랜덤으로 모양 설정 - 원래는 Player의 카드를 하나씩 비교하여 가중치를 계산해야 함
		
		switch (shape) {
		case 1:
			shown_card.back() = "♠7";
			break;

		case 2:
			shown_card.back() = "♣7";
			break;

		case 3:
			shown_card.back() = "◇7";
			break;

		case 4:
			shown_card.back() = "♡7";
			break;
		}
	}
}

void GameStart::setOriginal() { //7이 포함된 카드를 내고 모양을 바꾼 후 deck에 중복된 카드가 생기지 않도록 원래대로 되돌리는 함수
	shown_card[tmpIndex_7] = tmpShape_7;
	tmpShape_7 = "none";
}