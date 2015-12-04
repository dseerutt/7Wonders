#pragma once
#include <iostream>

class Card
{
public:
	std::string m_name;
	int m_points;//TODO a mettre pour les cartes bleues seulement

public:
	Card(const std::string& name, int points);
	~Card();
};

