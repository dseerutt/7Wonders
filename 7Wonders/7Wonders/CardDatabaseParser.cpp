#include "CardDatabaseParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

CardDatabaseParser::CardDatabaseParser(int playerNumber) : m_allCards(3, std::vector<Card>())
{
	std::fstream file;
	file.open(DATABASE_PATH);

	if (!file.is_open())
	{
		std::cerr << "Erreur : impossible d'ouvrir la base de données " << DATABASE_PATH << std::endl;
		exit(-1);
	}
	std::string dummy;
	std::getline(file, dummy);
	
	while (!file.eof())
	{
		std::string name;
		file >> name;

		int cardPlayerNumber;
		file >> cardPlayerNumber;
		if (playerNumber < cardPlayerNumber)
		{
			//we ignore the current card
			std::getline(file, dummy);
			continue;
		}

		char color;
		file >> color;

		int woodCost;
		file >> woodCost;
		int stoneCost;
		file >> stoneCost;
		int brickCost;
		file >> brickCost;
		int mineralCost;
		file >> mineralCost;

		int textileCost;
		file >> textileCost;
		int glassCost;
		file >> glassCost;
		int papyrusCost;
		file >> papyrusCost;

		int points;
		file >> points;

		Card card(name, points);
		m_allCards[0].push_back(card);
	}
	/*
		At this point, the deck m-allCard contains every card of the database that have the required number of players
	*/
}


CardDatabaseParser::~CardDatabaseParser()
{
}

std::vector<Card> CardDatabaseParser::generateDeck(int age)
{
	std::vector<Card>& v = m_allCards[age];
	std::random_shuffle(v.begin(), v.end());
	return v;
}