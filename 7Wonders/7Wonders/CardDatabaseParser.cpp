#include "CardDatabaseParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>

CardDatabaseParser::CardDatabaseParser(int playerNumber, int numberOfAge) :
m_brownCards(numberOfAge, std::vector<BrownCard>()),
m_grayCards(numberOfAge, std::vector<GrayCard>()),
m_blueCards(numberOfAge, std::vector<BlueCard>()),
m_yellowCards(numberOfAge, std::vector<YellowCard>()),
m_redCards(numberOfAge, std::vector<RedCard>()),
m_greenCards(numberOfAge, std::vector<GreenCard>()),
m_violetCards(numberOfAge, std::vector<VioletCard>())
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
		std::string cardName;
		switch (color)
		{
		case BROWN:{
			file >> productionB;
			file >> cardName;
			BrownCard b(name, productionB, cardName);
			b.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_brownCards[age - 1].push_back(b);
			break; }
		case GRAY:{
			file >> productionG;
			file >> cardName;
			GrayCard g(name, productionG, cardName);
			g.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_grayCards[age - 1].push_back(g);
			break; }
		case BLUE:{
			int points;
			file >> points;
			file >> cardName;
			BlueCard c(name, points, cardName);
			c.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_blueCards[age - 1].push_back(c);
			break; }
		case YELLOW:{
			file >> productionG;
			file >> cardName;
			YellowCard y(name, productionG, cardName);
			y.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_yellowCards[age - 1].push_back(y);
			break; }
		case VIOLET:{
			file >> productionG;
			file >> cardName;
			VioletCard v(name, productionG, cardName);
			v.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_violetCards[age - 1].push_back(v);
			break; }
		case RED:{
			unsigned int power;
			file >> power;
			file >> cardName;
			RedCard r(name, power, cardName);
			r.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_redCards[age - 1].push_back(r);
			break; }
		case GREEN:{
			char type;
			file >> type;
			file >> cardName;
			GreenCard gr(name, type, cardName);
			gr.initCost(woodCost, stoneCost, brickCost, mineralCost, papyrusCost, glassCost, textileCost, goldCost);
			m_greenCards[age - 1].push_back(gr);
			break; }
		default:{
			break; }
		}
	}
	std::srand(std::time(0));
	for (int i = 0; i < 10 - (playerNumber + 2); i++)
	{
		int randomIndex = rand() % (m_violetCards.size());
		m_violetCards[2].erase(m_violetCards[2].begin() + randomIndex);
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
	for (unsigned int i = 0; i < m_violetCards[age].size(); i++)
	{
		v.push_back(&m_violetCards[age][i]);
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
	case 'v':
		color = VIOLET;
		break;
	default:
		std::cerr << "Erreur : Couleur non reconnue : " << c << std::endl;
		color = BROWN;
		break;
	}
	return color;
}
