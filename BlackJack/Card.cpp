#include "Card.h"
#include <iostream>
#include <cassert>

Card::Card(CardRank rank, CardSuit suit) : m_rank(rank), m_suit(suit)
{
}

Card::~Card()
{
}

void Card::printCard() const
{
    switch (m_rank)
    {
    case Card::CardRank::RANK_2:		std::cout << '2'; break;
    case Card::CardRank::RANK_3:		std::cout << '3'; break;
    case Card::CardRank::RANK_4:		std::cout << '4'; break;
    case Card::CardRank::RANK_5:		std::cout << '5'; break;
    case Card::CardRank::RANK_6:		std::cout << '6'; break;
    case Card::CardRank::RANK_7:		std::cout << '7'; break;
    case Card::CardRank::RANK_8:		std::cout << '8'; break;
    case Card::CardRank::RANK_9:		std::cout << '9'; break;
    case Card::CardRank::RANK_10:		std::cout << 'T'; break;
    case Card::CardRank::RANK_JACK:	std::cout << 'J'; break;
    case Card::CardRank::RANK_QUEEN:	std::cout << 'Q'; break;
    case Card::CardRank::RANK_KING:	std::cout << 'K'; break;
    case Card::CardRank::RANK_ACE:	std::cout << 'A'; break;
    }

    switch (m_suit)
    {
    case Card::CardSuit::SUIT_CLUB:	std::cout << 'C'; break;
    case Card::CardSuit::SUIT_DIAMOND:std::cout << 'D'; break;
    case Card::CardSuit::SUIT_HEART:	std::cout << 'H'; break;
    case Card::CardSuit::SUIT_SPADE:	std::cout << 'S'; break;
    }
}

int Card::getCardValue() const
{
    switch (m_rank)
    {
    case Card::CardRank::RANK_2:		return 2;
    case Card::CardRank::RANK_3:		return 3;
    case Card::CardRank::RANK_4:		return 4;
    case Card::CardRank::RANK_5:		return 5;
    case Card::CardRank::RANK_6:		return 6;
    case Card::CardRank::RANK_7:		return 7;
    case Card::CardRank::RANK_8:		return 8;
    case Card::CardRank::RANK_9:		return 9;
    case Card::CardRank::RANK_10:		return 10;
    case Card::CardRank::RANK_JACK:	return 10;
    case Card::CardRank::RANK_QUEEN:	return 10;
    case Card::CardRank::RANK_KING:	return 10;
    case Card::CardRank::RANK_ACE:	return 11;
    }

    return 0;
}


Deck::Deck():m_deck_index(0)
{
    int card = 0;
    for (int suit = 0; suit < (int)Card::CardSuit::MAX_SUITS; ++suit)
        for (int rank = 0; rank < (int)Card::CardRank::MAX_RANKS; ++rank)
        {
            /*m_deck[card].suit = static_cast<CardSuit>(suit);
            m_deck[card].rank = static_cast<CardRank>(rank);*/
            m_deck[card] = Card(static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit));
            ++card;
        }
}

Deck::~Deck()
{
}

void Deck::printDeck() const
{
    
    for (const auto& card : m_deck)
    {
        card.printCard();
        std::cout << ' ';
    }

    std::cout << '\n';
}

void Deck::swapCard(Card& a, Card& b)
{
    Card temp = a;
    a = b;
    b = temp;
}

// Генерируем случайное число между min и max (включительно).
// Предполагается, что srand() уже был вызван
int Deck::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    // Равномерно распределяем вычисление значения из нашего диапазона
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Deck::shuffleDeck()
{
    // Перебираем каждую карту в колоде
    for (int index = 0; index < 52; ++index)
    {
        // Выбираем любую случайную карту
        int swapIndex = Deck::getRandomNumber(0, 51);
        // Меняем местами с нашей текущей картой
        Deck::swapCard(m_deck[index], m_deck[swapIndex]);
    }
    m_deck_index = 0;
}

const Card& Deck::dealCard()
{
assert(m_deck_index<52);
return m_deck[m_deck_index++];
}

char Deck::getPlayerChoice()
{
    std::cout << "(h) to hit, or (s) to stand: ";
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'h' && choice != 's');

    return choice;
}

bool Deck::playBlackjack(Deck &deck)
{
    int playerTotal = 0;
    int dealerTotal = 0;

    // Дилер получает одну карту
    dealerTotal += deck.dealCard().getCardValue();
    std::cout << "The dealer is showing: " << dealerTotal << '\n';

    // Игрок получает две карты
    playerTotal += deck.dealCard().getCardValue();
    playerTotal += deck.dealCard().getCardValue();

    while (1)
    {
        std::cout << "You have: " << playerTotal << '\n';
        char choice = getPlayerChoice();
        if (choice == 's')
            break;

        playerTotal += deck.dealCard().getCardValue();

        // Если игрок програл, то
        if (playerTotal > 21)
            return false;
    }

    // Если игрок не проиграл (у него не больше 21 очка), тогда дилер получает карты до тех пор, пока у него в сумме будет не меньше 17 очков
    while (dealerTotal < 17)
    {
        dealerTotal += deck.dealCard().getCardValue();
        std::cout << "The dealer now has: " << dealerTotal << '\n';
    }

    // Если у дилера больше 21, то он проиграл, а игрок выиграл
    if (dealerTotal > 21)
        return true;

    return (playerTotal > dealerTotal);
}
