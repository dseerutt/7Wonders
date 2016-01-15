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

enum Resources
{
	WOOD,
	STONE,
	BRICK,
	MINERAL,
	PAPYRUS,
	GLASS,
	TEXTILE,
	PRICEGOLD,
	RESOURCES_COUNT
};

class Card
{
public:
	std::string m_name;
	CardColor m_color;

public:
	Card(const std::string& name, CardColor color);
	~Card();
	int m_Cost[RESOURCES_COUNT];
	virtual unsigned int getPoints() const = 0;
	virtual unsigned int getPower() const = 0;
};

