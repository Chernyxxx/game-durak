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





// PLAYER ATTACK CYCLE
void PlayerAttackLoop(bool playerTurn, vector<Card>& playerCards, 
	vector<Card>& computerCards,vector<Card>& cardsOnTable, vector<Card>& deckOfCards)
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
} // END OF CYCLE "PLAYER ATTACK"




// COMPUTER ATTACK CYCLE
void CompAttackLoop(bool playerTurn, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& cardsOnTable, vector<Card>& deckOfCards)
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
		// END OF CYCLE "COMPUTER ATTACK"
}


void WIN(bool gameOver, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& deckOfCards)
{
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
}

void LOSE(bool gameOver, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& deckOfCards)
{
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
}

