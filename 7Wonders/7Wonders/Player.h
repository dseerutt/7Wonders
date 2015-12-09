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

	Card* m_cardToPlay;
public:
	Player(CardSet* discard);
	~Player();

	unsigned int getScore() const;
	const CardSet& getBoard() const;

	void setHand(const CardSet& newHand);
	const CardSet& getHand() const;
	void prepareTurn();
	void playTurn();
protected:
	const CardSet getPlayableCards() const;
	virtual void pickCard() = 0;
};

