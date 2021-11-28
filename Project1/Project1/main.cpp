#include <iostream>
#include <windows.h>

#include "OneCard.h"

using namespace std;

int main() {
	GameStart OneCardStart; //GameStart Ŭ������ ���� ��ü GS�� ����. �� �� �ʿ��� ��� �������� �ʱ�ȭ�ȴ�.

	while (1) {
		if (OneCardStart.getDeckSize() <= 7) { //���� ī���� ȿ���� �ߵ��� �� ���� ī���� ������ ���ڸ��� �ʵ��� �̸� deck�� reset
			resetDeck(OneCardStart);
		}
		
		//Player�� ����
		OneCardStart.PlayerTurn(); //������ �����ϰ� ����ڰ� ī�带 �� �� �ֵ��� PlayerTurn() �Լ� ȣ��
		if (OneCardStart.getPlayerSize() == 1) { onlyOne(OneCardStart); } //Player�� ī�带 ���� �� �� �������� one card �Է�
		if (checkWin(OneCardStart)) { break; } //Player�� ���ʰ� ���� �� ���� ����
		if (OneCardStart.tmpShape_7 != "none") { OneCardStart.setOriginal(); } //Computer�� 7�� ���� Player�� �׿� �´� ī�带 �� �� deck�� �ߺ��Ǵ� ī�尡 ������ ������� �ǵ���.
		OneCardStart.ChangeShape_Player(); //Player�� 7�� �´ٸ� ���ϴ� ������� �ٲٴ� �Լ� ȣ��
		if (OneCardStart.PlayerNone != 1) { //Player�� �ƹ��͵� ���� �ʰ� draw �ߴٸ� ���� �Լ� ȣ�� X
			OneCardStart.AttackComputer(); //Player�� ���� ī�带 ���� ��
			if (checkWin(OneCardStart)) { break; } //���� �� Computer�� �Ļ� Ž��
		}
		OneCardStart.ifJoker(); //Player�� ���ʿ��� Joker ī��� �����ߴٸ� �� ī�带 ���� ī��� ����

		system("cls"); //Computer�� ���� ���۵Ǳ� ���� ȭ�� �ʱ�ȭ

		//Computer�� ����
		OneCardStart.showComputer(); //Computer�� �� ������ ���
		OneCardStart.ComputerTurn(); //��ǻ���� ����
		if (OneCardStart.getComputerSize() == 1) { onlyOne(OneCardStart); }
		if (checkWin(OneCardStart)) { break; }
		if (OneCardStart.tmpShape_7 != "none") { OneCardStart.setOriginal(); } //Player�� 7�� ���� Computer�� �׿� �´� ī�带 �� �� deck�� �ߺ��Ǵ� ī�尡 ������ �ʵ��� ������� �����ش�.
		OneCardStart.ChangeShape_Computer(); //Computer�� 7�� ���� �� ��� �ٲ� �Լ� ȣ��
		Sleep(3000); //Computer�� ���� ����Ǹ� ��� ��� ��
		system("cls"); //ȭ�� �ʱ�ȭ
		if (OneCardStart.ComputerNone != 1) {
			OneCardStart.AttackPlayer(); //Computer�� ���������� �� ī�尡 ���� ī���� ���� ���� �Լ�
			if (checkWin(OneCardStart)) { break; } //���� �� Player�� �Ļ� Ž��
		}
		OneCardStart.ifJoker();
	}
}