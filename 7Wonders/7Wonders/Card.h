#pragma once
#include <iostream>

enum CardColor
{
	BLUE,
	BROWN,
	COLOR_COUNT
};

class Card
{
public:
	std::string m_name;
	CardColor m_color;
	int m_points;//TODO a mettre pour les cartes bleues seulement

public:
	Card();
	Card(const std::string& name, CardColor color, int points);
	~Card();
};

