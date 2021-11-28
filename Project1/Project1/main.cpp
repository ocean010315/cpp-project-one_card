#include <iostream>
#include <windows.h>

#include "OneCard.h"

using namespace std;

int main() {
	GameStart OneCardStart; //GameStart 클래스에 대한 객체 GS를 생성. 이 때 필요한 멤버 변수들이 초기화된다.

	while (1) {
		if (OneCardStart.getDeckSize() <= 7) { //공격 카드의 효과가 발동할 때 남은 카드의 개수가 모자르지 않도록 미리 deck을 reset
			resetDeck(OneCardStart);
		}
		
		//Player의 순서
		OneCardStart.PlayerTurn(); //게임이 시작하고 사용자가 카드를 낼 수 있도록 PlayerTurn() 함수 호출
		if (OneCardStart.getPlayerSize() == 1) { onlyOne(OneCardStart); } //Player가 카드를 내고 한 장 남았으면 one card 입력
		if (checkWin(OneCardStart)) { break; } //Player의 차례가 끝난 후 승패 판정
		if (OneCardStart.tmpShape_7 != "none") { OneCardStart.setOriginal(); } //Computer가 7을 내고 Player가 그에 맞는 카드를 낸 후 deck에 중복되는 카드가 없도록 원래대로 되돌림.
		OneCardStart.ChangeShape_Player(); //Player가 7을 냈다면 원하는 모양으로 바꾸는 함수 호출
		if (OneCardStart.PlayerNone != 1) { //Player가 아무것도 내지 않고 draw 했다면 공격 함수 호출 X
			OneCardStart.AttackComputer(); //Player가 공격 카드를 냈을 때
			if (checkWin(OneCardStart)) { break; } //공격 후 Computer의 파산 탐지
		}
		OneCardStart.ifJoker(); //Player의 차례에서 Joker 카드로 공격했다면 새 카드를 기준 카드로 설정

		system("cls"); //Computer의 턴이 시작되기 전에 화면 초기화

		//Computer의 순서
		OneCardStart.showComputer(); //Computer가 볼 정보를 출력
		OneCardStart.ComputerTurn(); //컴퓨터의 차례
		if (OneCardStart.getComputerSize() == 1) { onlyOne(OneCardStart); }
		if (checkWin(OneCardStart)) { break; }
		if (OneCardStart.tmpShape_7 != "none") { OneCardStart.setOriginal(); } //Player가 7을 내고 Computer가 그에 맞는 카드를 낸 후 deck에 중복되는 카드가 생기지 않도록 원래대로 돌려준다.
		OneCardStart.ChangeShape_Computer(); //Computer가 7을 냈을 때 모양 바꿀 함수 호출
		Sleep(3000); //Computer의 턴이 종료되면 잠시 대기 후
		system("cls"); //화면 초기화
		if (OneCardStart.ComputerNone != 1) {
			OneCardStart.AttackPlayer(); //Computer가 마지막으로 낸 카드가 공격 카드일 때에 대한 함수
			if (checkWin(OneCardStart)) { break; } //공격 후 Player의 파산 탐지
		}
		OneCardStart.ifJoker();
	}
}