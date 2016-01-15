#include "Card.h"


Card::Card(const std::string& name, CardColor color) : m_name(name), m_color(color)
{
	for (int i = 0; i < RESOURCES_COUNT; i++)
	{
		m_Cost[i] = 0;
	}
}

Card::~Card()
{
}
