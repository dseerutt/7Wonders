#pragma once
#include <vector>
#include "CardSet.h"
#include "Card.h"
#include <array>

using namespace std;

class Player
{
protected:
	CardSet m_hand;
	CardSet m_board;
	CardSet* m_discard;
	int money;
	int military;
	Card* m_cardToPlay;
	std::vector<std::array<int, RESOURCES_COUNT> > m_resources;
public:
	std::vector<std::array<int, RESOURCES_COUNT>> getResources();
	Player* leftNeighbor;
	Player* rightNeighbor;
	Player(CardSet* discard);
	~Player();

	unsigned int getMilitary() const;
	unsigned int getScore() const;
	unsigned int getMoney() const;
	const CardSet& getBoard() const;
	bool canBuy(CardSet c);
	int canBuyWithNeighbor(CardSet c);
	bool canProvide(array<int, RESOURCES_COUNT> resource);
	void setHand(const CardSet& newHand);
	const CardSet& getHand() const;
	void prepareTurn();
	void playTurn();
	void AddResource(array<int, RESOURCES_COUNT> resource);
	void AddResourceWithChoice(array<int, RESOURCES_COUNT> resource);
protected:
	const CardSet getPlayableCards() const;
	virtual void pickCard() = 0;
};

