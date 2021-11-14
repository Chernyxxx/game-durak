#include <string>
#include <vector>
//#include <algorithm> 
#include <ctime> 
#include <iostream>
#include "Card.h"
#include "Functions.h"



using namespace std;

int main()
{

	setlocale(LC_ALL, "ru");

	//Making card nominals - objects of class Range
	Card::Range six(0, ' ', Card::Range::Figure::SIX);
	Card::Range seven(1, ' ', Card::Range::Figure::SEVEN);
	Card::Range eight(2, ' ', Card::Range::Figure::EIGHT);
	Card::Range nine(3, ' ', Card::Range::Figure::NINE);
	Card::Range ten(4, '1', Card::Range::Figure::ZERO);
	Card::Range jack(5, ' ', Card::Range::Figure::JACK);
	Card::Range queen(6, ' ', Card::Range::Figure::QUEEN);
	Card::Range king(7, ' ', Card::Range::Figure::KING);
	Card::Range ace(8, ' ', Card::Range::Figure::ACE);

	// Make 36 cards
	Card six_diamomds(six, Card::Suit::DIAMONDS, false);
	Card seven_diamomds(seven, Card::Suit::DIAMONDS, false);
	Card eight_diamomds(eight, Card::Suit::DIAMONDS, false);
	Card nine_diamomds(nine, Card::Suit::DIAMONDS, false);
	Card ten_diamomds(ten, Card::Suit::DIAMONDS, false);
	Card jack_diamomds(jack, Card::Suit::DIAMONDS, false);
	Card queen_diamomds(queen, Card::Suit::DIAMONDS, false);
	Card king_diamomds(king, Card::Suit::DIAMONDS, false);
	Card ace_diamomds(ace, Card::Suit::DIAMONDS, false);

	Card six_clubs(six, Card::Suit::CLUBS, false);
	Card seven_clubs(seven, Card::Suit::CLUBS, false);
	Card eight_clubs(eight, Card::Suit::CLUBS, false);
	Card nine_clubs(nine, Card::Suit::CLUBS, false);
	Card ten_clubs(ten, Card::Suit::CLUBS, false);
	Card jack_clubs(jack, Card::Suit::CLUBS, false);
	Card queen_clubs(queen, Card::Suit::CLUBS, false);
	Card king_clubs(king, Card::Suit::CLUBS, false);
	Card ace_clubs(ace, Card::Suit::CLUBS, false);

	Card six_hearts(six, Card::Suit::HEARTS, false);
	Card seven_hearts(seven, Card::Suit::HEARTS, false);
	Card eight_hearts(eight, Card::Suit::HEARTS, false);
	Card nine_hearts(nine, Card::Suit::HEARTS, false);
	Card ten_hearts(ten, Card::Suit::HEARTS, false);
	Card jack_hearts(jack, Card::Suit::HEARTS, false);
	Card queen_hearts(queen, Card::Suit::HEARTS, false);
	Card king_hearts(king, Card::Suit::HEARTS, false);
	Card ace_hearts(ace, Card::Suit::HEARTS, false);

	Card six_spades(six, Card::Suit::SPADES, false);
	Card seven_spades(seven, Card::Suit::SPADES, false);
	Card eight_spades(eight, Card::Suit::SPADES, false);
	Card nine_spades(nine, Card::Suit::SPADES, false);
	Card ten_spades(ten, Card::Suit::SPADES, false);
	Card jack_spades(jack, Card::Suit::SPADES, false);
	Card queen_spades(queen, Card::Suit::SPADES, false);
	Card king_spades(king, Card::Suit::SPADES, false);
	Card ace_spades(ace, Card::Suit::SPADES, false);
	
	// Make a deck
	vector<Card> deckOfCards{ six_clubs,six_diamomds,six_hearts,six_spades, seven_clubs,seven_diamomds,
	seven_hearts,seven_spades, eight_clubs,eight_diamomds,eight_hearts,eight_spades,
	nine_clubs,nine_diamomds,nine_hearts,nine_spades, ten_clubs,ten_diamomds,ten_hearts,ten_spades,
	jack_clubs,jack_diamomds,jack_hearts,jack_spades, queen_clubs,queen_diamomds,queen_hearts,
	queen_spades, king_clubs,king_diamomds,king_hearts,king_spades, ace_clubs,ace_diamomds,
	ace_hearts,ace_spades };

	// Mix a deck
	srand(time(NULL));
	random_shuffle(deckOfCards.begin(), deckOfCards.end());

	cout << "\nИгра в подкидого дурака!!!" << endl << endl; 

	// Random trump definition
	if (deckOfCards[5].m_suit == Card::Suit::DIAMONDS) { cout << "Козырь - БУБИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::CLUBS) { cout << "Козырь - КРЕСТИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::HEARTS) { cout << "Козырь - ЧЕРВИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::SPADES) { cout << "Козырь - ПИКИ" << endl << endl; }
	for (int i = 0; i < deckOfCards.size(); i++)
	{
		if (deckOfCards[i].m_suit == deckOfCards[5].m_suit)
		{
			deckOfCards[i].m_trump = true;
		}
	}

	// Decks init
	vector<Card> playerCards;
	vector<Card> computerCards;
	vector<Card> cardsOnTable;
	
	// First card destribution
	// to player
	copy(deckOfCards.begin(), (deckOfCards.begin() + 6), back_inserter(playerCards));
	deckOfCards.erase(deckOfCards.begin(), (deckOfCards.begin() + 6));

	// sort by suit
	sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
		{return obj1.m_suit > obj2.m_suit; });

	// to comp
	copy((deckOfCards.begin()), (deckOfCards.begin() + 6), back_inserter(computerCards));
	deckOfCards.erase(deckOfCards.begin(), (deckOfCards.begin() + 6));

	//								START	
	cout << "Вот ваши карты" << endl << endl;
	ShowCards(playerCards);
	//cout << "Вот карты компа" << endl;
	//ShowCards(computerCards);
	
	bool gameOver = false;
	bool playerTurn = true;


	// MAIN GAME CYCLE


	while (gameOver == false)
	{
		
		while (playerTurn == true && gameOver == false)
		{
			PlayerAttackLoop(playerTurn, playerCards, computerCards, 
				cardsOnTable, deckOfCards);
		}

		WIN(gameOver, playerCards, computerCards, deckOfCards);

		while (playerTurn == false && gameOver == false)
		{
			CompAttackLoop(playerTurn, playerCards, computerCards, 
				cardsOnTable, deckOfCards);
		}
		LOSE(gameOver, playerCards, computerCards, deckOfCards);

	}
	return 0;
}