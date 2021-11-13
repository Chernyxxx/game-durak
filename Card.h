#pragma once
#include <ostream>

class Card
{
public:

	class Range
	{
	public:
		Range()
		{}
		enum Figure
		{
			ZERO = 48,
			SIX = 54,
			SEVEN = 55,
			EIGHT = 56,
			NINE = 57,
			TEN = 48,
			JACK = 194,
			QUEEN = 196,
			KING = 202,
			ACE = 210
		};
		Range(int order, char space, enum Figure figure)
		{
			m_order = order;
			m_space = space;
			m_figure = figure;
		}
		int m_order;
		char m_space;
		Figure m_figure;
	};
	enum Suit
	{
		HEARTS = 3,
		DIAMONDS = 4,
		CLUBS = 5,
		SPADES = 6
	};
	Card() {}

	Card(Range range, enum Suit suit, bool trump)
	{
		m_range = range;
		m_suit = suit;
		m_trump = trump;
	}
	Range m_range;
	Suit m_suit;
	bool m_trump = false;

	// Overloads
	friend std::ostream& operator<<(std::ostream& out, const Card& obj);
	friend bool operator<(const Card& obj1, const Card& obj2);
	friend bool operator==(const Card& obj1, const Card& obj2);
	friend bool operator==(const Card::Range& obj1, const Card::Range& obj2);
	friend std::ostream& operator<<(std::ostream& out, const Range& obj);
	friend bool operator==(const Range& obj1, const Range& obj2);
};

