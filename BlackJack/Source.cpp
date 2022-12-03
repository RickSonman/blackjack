#include <iostream>
#include <array>
#include <ctime> // для time()
#include <cstdlib> // для rand() и srand()
#include "Card.h"

int main()
{
	srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
	rand(); // пользователям Visual Studio: делаем сброс первого случайного числа

	Deck deck;

	

	deck.shuffleDeck();

	if (deck.playBlackjack(deck))
		std::cout << "You win!\n";
	else
		std::cout << "You lose!\n";

	return 0;
}