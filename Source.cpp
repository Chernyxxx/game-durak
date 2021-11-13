#include <string>
#include <vector>
#include <algorithm> 
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

	cout << "\n\tИгра в подкидого дурака!!!" << endl << endl;

	// Random trump definition
	if (deckOfCards[5].m_suit == Card::Suit::DIAMONDS) { cout << "\tКозырь - БУБИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::CLUBS) { cout << "\tКозырь - КРЕСТИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::HEARTS) { cout << "\tКозырь - ЧЕРВИ" << endl << endl; }
	if (deckOfCards[5].m_suit == Card::Suit::SPADES) { cout << "\tКозырь - ПИКИ" << endl << endl; }
	for (int i = 0; i < deckOfCards.size(); i++)
	{
		if (deckOfCards[i].m_suit == deckOfCards[5].m_suit)
		{
			deckOfCards[i].m_trump = true;
		}
	}

	// First card destribution
	vector<Card> playerCards;
	vector<Card> computerCards;
	vector<Card> cardsOnTable;

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
	bool playerTurn = true;
	bool gameOver = false;
	// MAIN GAME CYCLE
	while (gameOver == false)
	{
		// PLAYER ATTACK CYCLE
		while (playerTurn == true && gameOver == false)
		{
			cout << "\n\tВАШ ХОД\n" << endl << endl;
			int attackCardNumber;
			do   // Wrong number check	 
			{
				cout << "Чтобы походить введите номер карты" << endl << endl;
				cin >> attackCardNumber;
			} while (attackCardNumber > playerCards.size());

			Card attackCard = playerCards.at(attackCardNumber - 1);
			PlayerAttack(playerCards, attackCard, attackCardNumber, cardsOnTable);

			// Comp choose defence card
			auto defenceCardptr = CompChooseDefenceCard(computerCards, attackCard);
			Card defenceCard;
			bool compCover;
			// If no card
			if (defenceCardptr == computerCards.end())
			{
				computerCards.push_back(attackCard);  // It grabs
				cout << "Компьютер взял карту. Теперь у него "
					<< computerCards.size() << " карт." << endl << endl;
				compCover = false;
				playerTurn = true;
			}
			// If it has card to cover, it covers
			else
			{
				defenceCard = *defenceCardptr;
				cout << "Компьютер отбился " << (char)defenceCard.m_range.m_space
					<< (char)defenceCard.m_range.m_figure << (char)defenceCard.m_suit << endl << endl;
				computerCards.erase(defenceCardptr);
				cardsOnTable.push_back(defenceCard);
				compCover = true;
				playerTurn = false;

			}
			bool ableToAdd = false; // Is there cards to add? 
			bool cardOK = false; // Choosed card is good to add?
			ableToAdd = CheckCards(playerCards, cardsOnTable);

			// If comp covered & we have anything to add -> go to adding cycle
			while (compCover == true && ableToAdd == true)
			{
				sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
					{return obj1.m_suit > obj2.m_suit; });
				cout << "Вот ваши карты" << endl << endl;
				ShowCards(playerCards);
				//cout << "Вот карты компа" << endl;
				//ShowCards(computerCards);
				Info(computerCards, deckOfCards);
				cout << "Чтобы подкинуть, введите нoмер карты" << endl << endl;
				cout << "Если бито, нажмите 0" << endl << endl;
				cin >> attackCardNumber;

				// If 0 - nothing to add -> finish players attack
				if (attackCardNumber == 0)
				{
					cout << "Бито!" << endl << endl;
					playerTurn = false;
					ableToAdd = false;
					compCover = true; // Press 0 -> comp sucsessfully coverd
					cardOK = false;
				}

				// Player entered some number
				else if (attackCardNumber > 0 && attackCardNumber <= playerCards.size())
				{
					attackCard = playerCards.at(attackCardNumber - 1);
					// Only same range card is good to be added
					for (int i = 0; i < cardsOnTable.size(); i++)
					{
						if (attackCard.m_range.m_order == cardsOnTable[i].m_range.m_order)
						{
							cardOK = true;
							break;
						}
						else
						{
							cardOK = false;
						}
					}
					if (cardOK == true)
					{
						PlayerAttack(playerCards, attackCard, attackCardNumber, cardsOnTable);
					}
					else
					{
						cout << "Эту карту нельзя подкинуть!" << endl << endl;

					}
					ableToAdd = CheckCards(playerCards, cardsOnTable);
				}

				// If player entered incorrect number
				else
				{
					cout << "Неверный номер карты" << endl << endl;
				}

				// Comp defence
				if (cardOK == true)
				{
					defenceCardptr = CompChooseDefenceCard(computerCards, attackCard);

					// If no card to defence -> comp grabs cards
					if (defenceCardptr == computerCards.end())
					{
						for (int i = 0; i < cardsOnTable.size(); i++)
						{
							computerCards.push_back(cardsOnTable[i]);
						}
						cout << "Компьютер взял. Теперь у него "
							<< computerCards.size() << " карт." << endl << endl;
						compCover = false;
						playerTurn = true;
					}
					// If it has card to defence -> it covers
					else
					{
						defenceCard = *defenceCardptr;
						cout << "Компьютер отбился"
							<< (char)defenceCard.m_range.m_space
							<< (char)defenceCard.m_range.m_figure
							<< (char)defenceCard.m_suit << endl;
						computerCards.erase(defenceCardptr);
						cardsOnTable.push_back(defenceCard);
						compCover = true;
						playerTurn = false;
					}
				}
			}
			// If comp didnt cover & we have anything to add -> go to adding cycle
			while (compCover == false && ableToAdd == true)
			{
				sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
					{return obj1.m_suit > obj2.m_suit; });
				cout << "Вот ваши карты" << endl << endl;
				ShowCards(playerCards);
				//cout << "Вот карты компа" << endl;
				//ShowCards(computerCards);
				Info(computerCards, deckOfCards);
				cout << "Вы можете дать туда же" << endl << endl;
				cout << "Для этого введите номер карты" << endl << endl;
				cout << "Если бито, нажмите 0" << endl << endl;
				cin >> attackCardNumber;
				// If 0 - nothing to add -> next players attack
				if (attackCardNumber == 0)
				{
					cout << "Бито!" << endl << endl;
					playerTurn = true;
					ableToAdd = false;
					cardOK = false;
				}
				// Player entered some number
				else if (attackCardNumber > 0 && attackCardNumber <= playerCards.size())
				{
					attackCard = playerCards.at(attackCardNumber - 1);
					// Only same range card is good to be added
					for (int i = 0; i < cardsOnTable.size(); i++)
					{
						if (attackCard.m_range.m_order == cardsOnTable[i].m_range.m_order)
						{
							cardOK = true;
							break;
						}
						else
						{
							cardOK = false;
						}
					}

					if (cardOK == true)
					{
						attackCard = playerCards.at(attackCardNumber - 1);
						auto attackCardptr = find(playerCards.begin(), playerCards.end(), attackCard);
						computerCards.push_back(attackCard);
						playerCards.erase(attackCardptr);
						cout << "Вы подкинули карту "
							<< (char)attackCard.m_range.m_space
							<< (char)attackCard.m_range.m_figure
							<< (char)attackCard.m_suit << endl << endl;
						cout << "Количество карт у компьютера - " <<
							computerCards.size() << endl << endl;
					}
					else
					{
						cout << "Эту карту нельзя дать туда же! " << endl << endl;
					}
					ableToAdd = CheckCards(playerCards, cardsOnTable);
				}
				// If player entered incorrect number
				else
				{
					cout << "Неверный номер карты" << endl << endl;
				}
			}
			// If nothing to add & 0 not entered
			if (ableToAdd == false && attackCardNumber != 0)
			{
				cout << "Вам больше нечего дать!" << endl << endl;
			}

			// Taking cards from deck 
			cout << "Раздача" << endl << endl;
			TakeFromDeck(deckOfCards, playerCards);
			TakeFromDeck(deckOfCards, computerCards);
			sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
				{return obj1.m_suit > obj2.m_suit; });
			cout << "Вот ваши карты" << endl << endl;
			ShowCards(playerCards);
			//cout << "Вот карты компа" << endl;
			//ShowCards(computerCards);
			Info(computerCards, deckOfCards);
			cardsOnTable.clear();

			// FINISH GAME - PLAYER WIN
			if (playerCards.size() == 0 && deckOfCards.size() == 0 && computerCards.size() != 0)
			{
				cout << "\tВы победили!!! :-)" << endl << endl << "\n\tИгра окончена." << endl;
				gameOver = true;
			}
			// FINISH GAME - DRAW
			if (playerCards.size() == 0 && deckOfCards.size() == 0 && computerCards.size() == 0)
			{
				cout << "\tНичья." << endl << endl << "\n\tИгра окончена." << endl;
				gameOver = true;
			}
		} // END OF CYCLE "PLAYER ATTACK"

			// COMPUTER ATTACK
		while (playerTurn == false && gameOver == false)
		{
			auto attackCardPtr = CompChooseAttackCard(computerCards);
			Card compAttackCard = *attackCardPtr;
			CompAttack(computerCards, compAttackCard, cardsOnTable);
			cout << "\n\tХОД КОМПЬЮТЕРА\n" << endl << endl;
			cout << "Компьютер походил картой "
				<< (char)compAttackCard.m_range.m_space
				<< (char)compAttackCard.m_range.m_figure
				<< (char)compAttackCard.m_suit << endl << endl;

			cout << "Для отбоя введите номер карты" << endl << endl;
			cout << "Чтобы взять, нажмите 0 " << endl << endl;
			int defCardNumber = 1;
			Card playerDefCard;
			bool playerCover = false;  // Assign false to enter cycle player defence

			// Player defence
			while (playerCover == false && defCardNumber != 0)
			{
				cin >> defCardNumber;
				// If 0 -> player grabs cards
				if (defCardNumber == 0)
				{
					playerCards.push_back(compAttackCard);
					cout << "Вы взяли карту!" << endl << endl;
					//cout << "Вот ваши карты " << endl;
					//ShowCards(playerCards);
					playerTurn = false;
					playerCover = false;
				}
				else if (defCardNumber > 0 && defCardNumber <= playerCards.size())
				{
					bool defCardOK = CheckPlayerDefCard(playerCards, defCardNumber, compAttackCard);
					if (defCardOK == false)
					{
						cout << "Этой картой нельзя отбиться! Введтите другой номер!" << endl << endl;
					}
					else
					{
						playerDefCard = playerCards.at(defCardNumber - 1);
						//PlayerDefence(playerCards, playerDefCard, defCardNumber, cardsOnTable); //Doesnt work
						cout << "Вы отбились картой "
							<< (char)playerDefCard.m_range.m_space
							<< (char)playerDefCard.m_range.m_figure
							<< (char)playerDefCard.m_suit << endl << endl;
						vector<Card>::iterator playerDefCardptr =
							find(playerCards.begin(), playerCards.end(), playerDefCard);
						cardsOnTable.push_back(playerDefCard);
						playerCards.erase(playerDefCardptr);
						playerCover = true; // To exit cycle
					}
				}
				else
				{
					cout << "Введён неверый номер!" << endl;
				}
			}
			// Check if comp has card to add
			bool compAbleToAdd = CheckCards(computerCards, cardsOnTable);

			// CYCLE comp add cards
			// Cycle is on during player sucsesfull defence & if comp has card to add
			while (playerCover == true && compAbleToAdd == true)
			{
				auto cardToAddptr = CompChooseAddCard(computerCards, cardsOnTable);
				Card cardToAdd = *cardToAddptr;
				CompAttack(computerCards, cardToAdd, cardsOnTable);
				cout << "Комп подкидывает карту "
					<< (char)cardToAdd.m_range.m_space
					<< (char)cardToAdd.m_range.m_figure
					<< (char)cardToAdd.m_suit << endl << endl;
				sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
					{return obj1.m_suit > obj2.m_suit; });
				cout << "Вот ваши карты" << endl << endl;
				ShowCards(playerCards);
				//cout << "Вот карты компа" << endl;
				//ShowCards(computerCards);
				Info(computerCards, deckOfCards);
				cout << "Для отбоя введите номер карты" << endl << endl;
				cout << "Чтобы взять, нажмите 0 " << endl << endl;

				// Player defence in adding cycle
				bool repeatCycle = true;
				while (repeatCycle == true)
				{
					cin >> defCardNumber;
					// if 0 -> player grabs all cards
					if (defCardNumber == 0)
					{
						copy(cardsOnTable.begin(), cardsOnTable.end(), back_inserter(playerCards));
						cout << "Вы взяли!" << endl;
						repeatCycle = false;
						playerCover = false;
					}
					else if (defCardNumber > 0 && defCardNumber <= playerCards.size())
					{
						bool defCardOK = CheckPlayerDefCard(playerCards, defCardNumber, cardToAdd);
						if (defCardOK == false)
						{
							cout << "Этой картой нельзя отбиться! Введтите другой номер!" << endl;
							repeatCycle = true;
						}
						else
						{
							playerDefCard = playerCards.at(defCardNumber - 1);
							//Doesnt work		//PlayerDefence(playerCards, playerDefCard, defCardNumber, cardsOnTable); 
							cout << "Вы отбились картой "
								<< (char)playerDefCard.m_range.m_space
								<< (char)playerDefCard.m_range.m_figure
								<< (char)playerDefCard.m_suit << endl;
							vector<Card>::iterator playerDefCardptr =
								find(playerCards.begin(), playerCards.end(), playerDefCard);
							cardsOnTable.push_back(playerDefCard);
							playerCards.erase(playerDefCardptr);
							repeatCycle = false;
						}
					}
					else
					{
						cout << "Введён неверый номер!" << endl;
						repeatCycle = true;
					}
				}
				compAbleToAdd = CheckCards(computerCards, cardsOnTable);
			}
			if (compAbleToAdd == false && defCardNumber != 0)
			{
				cout << "Компу нечего подкинуть" << endl << endl;
				playerTurn = true;
			}
			// Comp add gives cards to player if it has anything & player didnt cover
			if (playerCover == false && compAbleToAdd == true)
			{
				auto cardToAddptr = CompChooseAddCard(computerCards, cardsOnTable);
				while (cardToAddptr != computerCards.end())
				{
					Card cardToAdd = *cardToAddptr;
					playerCards.push_back(cardToAdd);
					computerCards.erase(cardToAddptr);
					cout << "Компьютер дал Вам туда же карту "
						<< (char)cardToAdd.m_range.m_space
						<< (char)cardToAdd.m_range.m_figure
						<< (char)cardToAdd.m_suit << endl;
					cardToAddptr = CompChooseAddCard(computerCards, cardsOnTable);
				}
			}
			cardsOnTable.clear();
			cout << "Раздача" << endl << endl;
			TakeFromDeck(deckOfCards, playerCards);
			TakeFromDeck(deckOfCards, computerCards);
			sort(playerCards.begin(), playerCards.end(), [](const Card& obj1, const Card& obj2)
				{return obj1.m_suit > obj2.m_suit; });
			cout << "Вот ваши карты" << endl << endl;
			ShowCards(playerCards);
			//cout << "Вот карты компа" << endl;
			//ShowCards(computerCards);
			Info(computerCards, deckOfCards);

			// FINISH GAME - PLAYER LOST
			if (computerCards.size() == 0 && deckOfCards.size() == 0 && playerCards.size() != 0)
			{
				cout << "\tВы проиграли :-(" << endl << "\n\tИгра окончена." << endl;
				gameOver = true;
			}
			// FINISH GAME - DRAW
			if (computerCards.size() == 0 && deckOfCards.size() == 0 && playerCards.size() == 0)
			{
				cout << "\tНичья." << endl << endl << "\n\tИгра окончена." << endl;
				gameOver = true;
			}
		}	// END OF CYCLE "COMPUTER ATTACK"
	}
	return 0;
}