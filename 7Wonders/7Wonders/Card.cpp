#include "Card.h"


Card::Card()
{
}

Card::Card(const std::string& name, CardColor color, int points) : m_name(name), m_color(color), m_points(points)
{
}

Card::~Card()
{
}
