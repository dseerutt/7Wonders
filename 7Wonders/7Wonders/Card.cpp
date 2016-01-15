#include "Card.h"


Card::Card(const std::string& name, CardColor color) : m_name(name), m_color(color)
{
}

Card::~Card()
{
}

void Card::initCost(int a, int b, int c, int d, int e, int f, int g, int h)
{
	m_Cost[WOOD] = a;
	m_Cost[STONE] = b;
	m_Cost[BRICK] = c;
	m_Cost[MINERAL] = d;
	m_Cost[PAPYRUS] = e;
	m_Cost[GLASS] = f;
	m_Cost[TEXTILE] = g;
	m_Cost[PRICEGOLD] = h;
}
