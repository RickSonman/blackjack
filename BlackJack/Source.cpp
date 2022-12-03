#include <iostream>
#include <array>
#include <ctime> // ��� time()
#include <cstdlib> // ��� rand() � srand()
#include "Card.h"

int main()
{
	srand(static_cast<unsigned int>(time(0))); // ���������� ��������� ���� � �������� ���������� ��������
	rand(); // ������������� Visual Studio: ������ ����� ������� ���������� �����

	Deck deck;

	

	deck.shuffleDeck();

	if (deck.playBlackjack(deck))
		std::cout << "You win!\n";
	else
		std::cout << "You lose!\n";

	return 0;
}