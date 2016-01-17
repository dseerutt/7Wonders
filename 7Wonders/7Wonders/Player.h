#pragma once
#include <vector>
#include "CardSet.h"
#include "Card.h"
#include "BrownCard.h"
#include <array>

using namespace std;

class Player
{
protected:
	CardSet m_hand;
	CardSet m_board;
	CardSet* m_discard;
	bool comptoir1 = false;
	bool comptoir2 = false;
	bool market = false;
	int money;
	int military;
	Card* m_cardToPlay;
	bool defausse = false;
	std::vector<std::array<int, RESOURCES_COUNT> > m_resources;
public:
	int Player::tradeCountColor(int color);
	std::vector<std::array<int, RESOURCES_COUNT>> getResources();
	bool alreadyPlayed(string s);
	Player* leftNeighbor;
	Player* rightNeighbor;
	Player(CardSet* discard);
	~Player();
	string displayResourceManager(string me);
	string displayResource(string me, std::vector<std::array<int, RESOURCES_COUNT>>);
	static string displayResourceType(int i);

	unsigned int getMilitary() const;
	unsigned int getScore() const;
	unsigned int getMoney() const;
	const CardSet& getBoard() const;
	static int identifyResource(char c);
	bool canBuy(Card* c);
	bool Buy(Card* c);
	void applyEffects(Card* c);
	int canBuyWithNeighbor(Card* c);
	bool canProvide(array<int, RESOURCES_COUNT> resource);
	int countResourcesL(array<int, RESOURCES_COUNT> resource);
	int countResourcesR(array<int, RESOURCES_COUNT> resource);
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

