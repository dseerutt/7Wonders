#pragma once
#include <iostream>

enum CardColor
{
	BROWN,
	GRAY,
	BLUE,
	YELLOW,
	RED,
	GREEN,
	COLOR_COUNT
};

class Card
{
public:
	std::string m_name;
	CardColor m_color;

public:
	Card(const std::string& name, CardColor color);
	~Card();

	virtual unsigned int getPoints() const = 0;
};

