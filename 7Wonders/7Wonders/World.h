#pragma once
#include <vector>
#include "Player.h"
#include "Card.h"
#include "CardDatabaseParser.h"

class World
{
private:
	std::vector<Player*> m_players;
	unsigned int m_playerNumber;
	unsigned int m_numberOfTurns;
	CardDatabaseParser m_cardDatabaseParser;
	std::vector<Card> m_deck;
	std::vector<Card> m_discard;


public:
	World(unsigned int nh, unsigned int nc);
	~World();

	void run();
	std::vector<Card> generateDeck(int age);
	void distributeCards();
	void draft(unsigned int age);
	void prepareTurn();
	void playTurn();
};

