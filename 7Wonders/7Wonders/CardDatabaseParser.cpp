#include "CardDatabaseParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "World.h"

CardDatabaseParser::CardDatabaseParser(int playerNumber) :
m_brownCards(NUMBER_OF_AGES, std::vector<BrownCard>()),
m_grayCards(NUMBER_OF_AGES, std::vector<GrayCard>()),
m_blueCards(NUMBER_OF_AGES, std::vector<BlueCard>()),
m_yellowCards(NUMBER_OF_AGES, std::vector<YellowCard>()),
m_redCards(NUMBER_OF_AGES, std::vector<RedCard>()),
m_greenCards(NUMBER_OF_AGES, std::vector<GreenCard>())
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
	
	unsigned int debugCounter = 0;
	while (!file.eof())
	{
		debugCounter++;
		if (debugCounter > 300)
		{
			std::cerr << "Erreur : boucle infinie dans la lecture de la base de données." << std::endl;
			exit(-1);
		}
		int age;
		file >> age;

		std::string name;
		file >> name;

		if (file.eof())
		{
			break;
		}

		int cardPlayerNumber;
		file >> cardPlayerNumber;
		if (playerNumber < cardPlayerNumber)
		{
			//we ignore the current card
			std::getline(file, dummy);
			continue;
		}

		char colorChar;
		file >> colorChar;
		CardColor color = getColor(colorChar);

		int goldCost;
		file >> goldCost;
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

		std::string productionB;
		std::string productionG;
		switch (color)
		{
		case BROWN:{
			file >> productionB;
			BrownCard b(name, productionB);
			m_brownCards[age-1].push_back(b);
			b.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			break; }
		case GRAY:{
			file >> productionG;
			GrayCard g(name, productionG);
			m_grayCards[age - 1].push_back(g);
			g.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			break; }
		case BLUE:{
			int points;
			file >> points;
			BlueCard c(name, points);
			c.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_blueCards[age - 1].push_back(c);
			break; }
		case YELLOW:{
			YellowCard y(name);
			y.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_yellowCards[age - 1].push_back(y);
			break; }
		case RED:{
			unsigned int power;
			file >> power;
			RedCard r(name, power);
			r.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_redCards[age - 1].push_back(r);
			break; }
		case GREEN:{
			char type;
			file >> type;
			GreenCard gr(name, type);
			gr.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_greenCards[age - 1].push_back(gr);
			break; }
		default:{
			break; }
		}
	}
	/*
		At this point, the decks m_[color]Cards contains every card of the database that have the required number of players
	*/
}


CardDatabaseParser::~CardDatabaseParser()
{
}

CardSet CardDatabaseParser::generateDeck(int age)
{
	CardSet v;
	for (unsigned int i = 0; i < m_brownCards[age].size(); i++)
	{
		v.push_back(&m_brownCards[age][i]);
	}
	for (unsigned int i = 0; i < m_grayCards[age].size(); i++)
	{
		v.push_back(&m_grayCards[age][i]);
	}
	for (unsigned int i = 0; i < m_blueCards[age].size(); i++)
	{
		v.push_back(&m_blueCards[age][i]);
	}
	for (unsigned int i = 0; i < m_yellowCards[age].size(); i++)
	{
		v.push_back(&m_yellowCards[age][i]);
	}
	for (unsigned int i = 0; i < m_redCards[age].size(); i++)
	{
		v.push_back(&m_redCards[age][i]);
	}
	for (unsigned int i = 0; i < m_greenCards[age].size(); i++)
	{
		v.push_back(&m_greenCards[age][i]);
	}
	v.shuffle();
	return v;
}

CardColor CardDatabaseParser::getColor(char c) const
{
	CardColor color;
	switch (c)
	{
	case 'w':
		color = BROWN;
		break;
	case 'g':
		color = GRAY;
		break;
	case 'b':
		color = BLUE;
		break;
	case 'y':
		color = YELLOW;
		break;
	case 'r':
		color = RED;
		break;
	case 'e':
		color = GREEN;
		break;
	default:
		std::cerr << "Erreur : Couleur non reconnue : " << c << std::endl;
		color = BROWN;
		break;
	}
	return color;
}
