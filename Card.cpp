#include "Card.h"

// Overload less 
bool operator<(const Card& obj1, const Card& obj2)
{
	return obj1.m_range.m_order < obj2.m_range.m_order;
}

// Overload equal
bool operator==(const Card& obj1, const Card& obj2)
{
	return (obj1.m_suit == obj2.m_suit
		&& obj1.m_range == obj2.m_range
		&& obj1.m_trump == obj2.m_trump);
}

// Overload out 
std::ostream& operator<<(std::ostream& out, const Card& obj)
{
	out << obj.m_range;
	out << obj.m_suit;
	return out;
}
// Overload equal operator for class Range
bool operator==(const Card::Range& obj1, const Card::Range& obj2)
{
	return (obj1.m_order == obj2.m_order &&
		obj1.m_space == obj2.m_space &&
		obj1.m_figure == obj2.m_figure);
}

//Overload out opetator for class Range 
std::ostream& operator<<(std::ostream& out, const Card::Range& obj)
{
	out << obj.m_space;
	out << obj.m_figure;
	return out;
}
