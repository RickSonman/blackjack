#pragma once
#include <iostream>
#include <vector>
#include <array>

class Card
{
public:
	enum class CardSuit
	{
		SUIT_CLUB,
		SUIT_DIAMOND,
		SUIT_HEART,
		SUIT_SPADE,
		MAX_SUITS
	};

	enum class CardRank
	{
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		MAX_RANKS
	};

	Card(CardRank rank = CardRank::MAX_RANKS, CardSuit suit = CardSuit::MAX_SUITS);
	~Card();
	void printCard() const;
	int getCardValue() const;

private:
	CardRank m_rank;
	CardSuit m_suit;
};

class Deck
{
public:
	Deck();
	~Deck();
	void printDeck() const;
	void shuffleDeck();
	const Card& dealCard();
	char getPlayerChoice();
	bool playBlackjack(Deck &deck);

private:
	std::array<Card,52> m_deck;
	static void swapCard(Card& a, Card& b);
	static int getRandomNumber(int min, int max);
	int m_deck_index;

};
