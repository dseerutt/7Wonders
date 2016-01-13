#pragma once
#include <vector>
#include "CardSet.h"
#include "Card.h"

class Player
{
protected:
	CardSet m_hand;
	CardSet m_board;
	CardSet* m_discard;
	int money;
	Card* m_cardToPlay;
public:
	Player(CardSet* discard);
	~Player();

	unsigned int getScore() const;
	unsigned int getMoney() const;
	const CardSet& getBoard() const;
	void canBuy(int price);
	void setHand(const CardSet& newHand);
	const CardSet& getHand() const;
	void prepareTurn();
	void playTurn();
protected:
	const CardSet getPlayableCards() const;
	virtual void pickCard() = 0;
};

