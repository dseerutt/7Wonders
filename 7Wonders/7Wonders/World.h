#pragma once
#include <vector>
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "CardSet.h"
#include "CardDatabaseParser.h"
#define NUMBER_OF_AGES 3

enum Scores
{
	WAR,
	GOLD,
	WONDER_LEVEL,
	BLUE_CARDS,
	YELLOW_CARDS,
	GUILDS,
	SCIENCE,
	TOTAL_SCORE
};

class World
{
private:
	CardDatabaseParser m_cardDatabaseParser;

public:
	//Game state
	bool m_gameOver;
	unsigned int m_age;
	//std::vector<HumanPlayer> m_humanPlayers;
	//std::vector<ComputerPlayer> m_computerPlayers;
	CardSet m_deck;
	CardSet m_discard;

	int getMilitaryScore(Player* p);
	std::vector<Player*> m_players;
	std::vector<std::vector<unsigned int> > m_scores;
	const Player* m_winner;
	bool m_draw;

public:
	World(unsigned int nh, unsigned int nc);
	~World();

	void run();
	void play(Player& player);
	void playOthers(Player& player);
	void endTurn();
	void startAge();
	bool betweenTurns() const;
	bool gameOver() const;
	//void processTurn();
	CardSet generateDeck(int age);
	void distributeCards();
	void draft(unsigned int age);
	void prepareTurn();
	void playTurn();
	void computeScores();
	void displayScores() const;
	unsigned int computeScienceScore(const CardSet& board) const;
	bool hasWon(const Player& player) const;
	bool draw() const;
	unsigned int getPlayerId(const Player& player) const;
};

