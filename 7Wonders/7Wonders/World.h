#pragma once
#include <vector>
#include "CardSet.h"
#include "CardDatabaseParser.h"
#include "Player.h"
#ifndef TESTING
#include "Display.h"
#endif // !TESTING
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
	static CardDatabaseParser m_cardDatabaseParser;

public:
	//Game state
	bool m_gameOver;
	unsigned int m_age;
	CardSet m_deck;
	CardSet m_discard;
#ifndef TESTING
	Display m_display;
	Display& getDisplay();
#endif // !TESTING

	std::vector<Player*> m_players;
	std::vector<std::vector<int> > m_scores;
	const Player* m_winner;
	bool m_draw;

public:
	World(unsigned int nh, unsigned int nc);
	~World();

	void upgradeMarvel(Player* p, int PV);
	int getMilitaryScore(Player* p);
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
	void updateMilitary();
	void computeScores();
	void displayScores() const;
	unsigned int computeScienceScore(const CardSet& board, char guild) const;
	bool hasWon(const Player& player) const;
	bool draw() const;
	unsigned int getPlayerId(const Player& player) const;
};

