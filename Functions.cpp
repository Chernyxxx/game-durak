#include "Functions.h"
#include <iostream>

void ShowCards(vector<Card>& cards)
{

	for (int i = 0; i < cards.size(); i++)
	{
		std::cout << (char)cards[i].m_range.m_space << (char)cards[i].m_range.m_figure
			<< (char)cards[i].m_suit << "  ";
	}
	std::cout << endl;
	for (int i = 0; i < cards.size(); i++)
	{
		if (i < 9)
		{
			cout << " " << i + 1 << "   ";
		}
		else
		{
			cout << i + 1 << "   ";
		}

	}
	cout << endl;
	cout << endl;
}

// func - msg how many cards has computer or main deck 
void Info(vector<Card> compCards, vector<Card> deck)
{
	cout << "У компа " << compCards.size() << " карт. " <<
		"Карт в колоде " << deck.size() << endl << endl;
}

void PlayerAttack(vector <Card>& playerCards, const Card& attackCard, int number,
	vector<Card>& cardsOnTable)
{
	cout << "Вы походили " << (char)attackCard.m_range.m_space << (char)attackCard.m_range.m_figure
		<< (char)attackCard.m_suit << endl << endl;
	vector<Card>::iterator attackCardptr;			// Make it to attack card
	attackCardptr = (playerCards.begin() + (number - 1));// Init it
	playerCards.erase(attackCardptr);				// Erase attack card from players deck
	cardsOnTable.push_back(attackCard);				// Add attack card to the table

}

// func - return it to defence card
vector<Card>::iterator CompChooseDefenceCard(vector<Card>& computerCards,
	const Card& attackCard)
{
	vector<Card>cardsToDefence;
	vector<Card>trumpsToDefence;
	for (int i = 0; i < computerCards.size(); i++)
	{	// First choosing the same suit cards which is enough big to defence
		if (computerCards[i].m_suit == attackCard.m_suit &&
			computerCards[i].m_range.m_order > attackCard.m_range.m_order)
		{
			cardsToDefence.push_back(computerCards[i]);
		}
		// Choosing all trumps 
		if (computerCards[i].m_trump == true)
		{
			trumpsToDefence.push_back(computerCards[i]);
		}
	}
	vector<Card>::iterator defCardptr;
	// If same suit cards were found, comp will use the smallest
	if (cardsToDefence.size() > 0)
	{
		for (int i = 0; i < cardsToDefence.size(); i++)
		{
			int place = 0;  // new place for element 
			for (int j = 0; j < cardsToDefence.size(); j++)
			{
				if (cardsToDefence[i].m_range.m_order > cardsToDefence[j].m_range.m_order)
				{
					place++;
				}
			}
			if (place == 0) // Smallest card
			{
				defCardptr = find(computerCards.begin(), computerCards.end(), cardsToDefence[i]);
			}
		}
	}
	// if attack card is not trump & no the same suit cards & comp has trumps
	// 	   then comp defence with the smallest trump
	else if (attackCard.m_trump == false && cardsToDefence.size() == 0 && trumpsToDefence.size() > 0)
	{
		for (int i = 0; i < trumpsToDefence.size(); i++)
		{
			int place = 0;
			for (int j = 0; j < trumpsToDefence.size(); j++)
			{
				if (trumpsToDefence[i].m_range.m_order > trumpsToDefence[j].m_range.m_order)
				{
					place++;
				}
			}
			if (place == 0) // find out the smallest trump
			{
				defCardptr = find(computerCards.begin(), computerCards.end(), trumpsToDefence[i]);
			}
		}
	}
	// if comp does not have anything, it=end
	else
	{
		defCardptr = computerCards.end();
	}
	return defCardptr;
}

void ComputerDefence(vector <Card>& computerCards, Card& attackCard, Card& defenceCard,
	vector<Card>::iterator defenceCardptr, vector <Card>& cardsOnTable)
{
	if (defenceCardptr == computerCards.end())  // Comp doesnt have anything
	{
		computerCards.push_back(attackCard);  // Comp takes card
		cout << "Компьютер взял карту. Теперь у него "
			<< computerCards.size() << " карт." << endl;
	}
	else // Comp has card to defence
	{
		defenceCard = *defenceCardptr;
		cout << "Компьютер отбился"
			<< (char)defenceCard.m_range.m_space
			<< (char)defenceCard.m_range.m_figure
			<< (char)defenceCard.m_suit << endl;
		computerCards.erase(defenceCardptr); // Delete card from comp deck
		cardsOnTable.push_back(defenceCard);   // Put the card on a table

	}
}

// func - Check playercards - is there something to add
bool CheckCards(vector<Card>& cards, vector<Card>& cardsOnTable)
{
	bool a = false;
	for (int i = 0; i < cards.size(); i++)
	{	// We can add only the same range card
		for (int j = 0; j < cardsOnTable.size(); j++)
		{
			if (cards[i].m_range.m_order == cardsOnTable[j].m_range.m_order)
			{
				a = true; // confirmation
				break;
			}
		}
	}
	return a;
}

void TakeFromDeck(vector<Card>& from_where, vector<Card>& where)
{
	// If not enough cards & deck is not empty
	if (where.size() < 6 && from_where.size() > 0)
	{
		int how_many;
		how_many = 6 - where.size(); // calc. how many cards is need to take
		if (from_where.size() < how_many) // but if there are not enough cards in deck
		{
			how_many = from_where.size();
		}
		copy(from_where.begin(), from_where.begin() + how_many, back_inserter(where));
		from_where.erase(from_where.begin(), (from_where.begin() + how_many));
	}
}

vector<Card>::iterator CompChooseAttackCard(vector<Card>& computerCards)
{
	vector<Card>::iterator it;
	it = computerCards.begin();
	return it;
}

void CompAttack(vector<Card>& computerCards, Card compAttackCard,
	vector<Card>& cardsOnTable)
{
	vector<Card>::iterator compAttackCardptr =
		find(computerCards.begin(), computerCards.end(), compAttackCard);
	computerCards.erase(compAttackCardptr);
	cardsOnTable.push_back(compAttackCard);
}

// func - Checks is the card, choosen by player, is enough to defence
bool CheckPlayerDefCard(vector<Card>& playerCards, int defCardNumber, Card attackCard)
{
	Card playerDefCard = playerCards.at(defCardNumber - 1);
	return (playerDefCard.m_suit == attackCard.m_suit &&
		playerDefCard.m_range.m_order >= attackCard.m_range.m_order ||
		playerDefCard.m_trump == true);
}

// func - ???(does not work - does not erase card from players deck)???
void PlayerDefence(vector<Card> playerCards, Card playerDefCard, int number, vector<Card> cardsOnTable)
{
	cout << "Вы отбились картой " << playerDefCard.m_range.m_space
		<< playerDefCard.m_range.m_figure << playerDefCard.m_suit << endl << endl;
	vector<Card>::iterator playerDefCardptr =
		find(playerCards.begin(), playerCards.end(), playerDefCard);
	cardsOnTable.push_back(playerDefCard);
	playerCards.erase(playerDefCardptr);
}

vector<Card>::iterator CompChooseAddCard(vector<Card>& computerCards,
	vector<Card>& cardsOnTable)
{   // First choose cards which is good to add
	vector<Card>cardsToAdd;
	for (int i = 0; i < cardsOnTable.size(); i++)
	{
		for (int j = 0; j < computerCards.size(); j++)
		{
			if (computerCards[j].m_range.m_order == cardsOnTable[i].m_range.m_order)
			{
				cardsToAdd.push_back(computerCards[j]);
			}
		}
	}
	vector<Card>::iterator addCardptr;
	// If comp has cards to add, it choose the smallest
	if (cardsToAdd.size() > 0)
	{
		for (int i = 0; i < cardsToAdd.size(); i++)
		{
			int place = 0;
			for (int j = 0; j < cardsToAdd.size(); j++)
			{
				if (cardsToAdd[i].m_range.m_order > cardsToAdd[j].m_range.m_order)
				{
					place++;
				}
			}
			if (place == 0) // the smallest card
			{
				addCardptr = find(computerCards.begin(), computerCards.end(), cardsToAdd[i]);
			}
		}
	}
	else  // If comp doesnt have cards to add, it=0
	{
		addCardptr = computerCards.end();
	}
	return addCardptr;
	// Doesnt work ???
	/*	if (cardsToDefence.size() > 0)
		{

			auto cardToDefenceptr = min_element(cardsToDefence.begin(),
				cardsToDefence.end());
			return cardToDefenceptr;
		}
		else
		{
			auto cardToDefenceptr = cardsToDefence.end();
			return cardToDefenceptr;
		}*/
}