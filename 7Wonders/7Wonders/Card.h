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
	RESOURCES_COUNT
};

class Card
{
public:
	std::string m_name;
	CardColor m_color;
	int m_price;
	std::string m_production;

public:
	Card(const std::string& name, CardColor color);
	~Card();
	int m_Cost[RESOURCES_COUNT];
	virtual unsigned int getPoints() const = 0;
	virtual unsigned int getPower() const = 0;
	void initCost(int a, int b, int c, int d, int e, int f, int g, int h);
};

