#pragma once
#include <vector>
#include "Player.h"
#include "CardSet.h"
#include "CardDatabaseParser.h"
#define NUMBER_OF_AGES 3

class World
{
private:
	std::vector<Player*> m_players;
	unsigned int m_playerNumber;
	unsigned int m_numberOfTurns;
	CardDatabaseParser m_cardDatabaseParser;
	CardSet m_deck;
	CardSet m_discard;


public:
	World(unsigned int nh, unsigned int nc);
	~World();

	void run();
	CardSet generateDeck(int age);
	void distributeCards();
	void draft(unsigned int age);
	void prepareTurn();
	void playTurn();
	void displayScores() const;
	unsigned int computeScienceScore(const CardSet& board) const;
};

