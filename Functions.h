#pragma once
#include <vector>
#include "Card.h"
#include <algorithm>

using namespace std;

void ShowCards(vector<Card>& cards);

// func - msg how many cards has computer or main deck 
void Info(vector<Card> compCards, vector<Card> deck);


void PlayerAttack(vector <Card>& playerCards, const Card& attackCard, int number,
	vector<Card>& cardsOnTable);


// func - return it to defence card
vector<Card>::iterator CompChooseDefenceCard(vector<Card>& computerCards,
	const Card& attackCard);


void ComputerDefence(vector <Card>& computerCards, Card& attackCard, Card& defenceCard,
	vector<Card>::iterator defenceCardptr, vector <Card>& cardsOnTable);


// func - Check playercards - is there something to add
bool CheckCards(vector<Card>& cards, vector<Card>& cardsOnTable);


void TakeFromDeck(vector<Card>& from_where, vector<Card>& where);


vector<Card>::iterator CompChooseAttackCard(vector<Card>& computerCards);

void CompAttack(vector<Card>& computerCards, Card compAttackCard,
	vector<Card>& cardsOnTable);


// func - Checks is the card, choosen by player, is enough to defence
bool CheckPlayerDefCard(vector<Card>& playerCards, int defCardNumber, Card attackCard);


// func - ???(does not work - does not erase card from players deck)???
void PlayerDefence(vector<Card> playerCards, Card playerDefCard,
	int number, vector<Card> cardsOnTable);

vector<Card>::iterator CompChooseAddCard(vector<Card>& computerCards, 
	vector<Card>& cardsOnTable);

void PlayerAttackLoop(bool playerTurn, vector<Card>& playerCards, 
	vector<Card>& computerCards,vector<Card>& cardsOnTable, vector<Card>& deckOfCards);

void CompAttackLoop(bool playerTurn, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& cardsOnTable, vector<Card>& deckOfCards);

void WIN(bool gameOver, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& deckOfCards);

void LOSE(bool gameOver, vector<Card>& playerCards, vector<Card>& computerCards,
	vector<Card>& deckOfCards);




