#pragma once
#include <vector>
#include "Card.h"

class Player
{
protected:
	std::vector<Card> m_hand;
	std::vector<Card> m_board;

	std::vector<Card>* m_discard;

	Card* m_cardToPlay;
public:
	Player(std::vector<Card>* discard);
	~Player();
	void setHand(const std::vector<Card>& newHand);
	const std::vector<Card>& getHand() const;
	void prepareTurn();
	void playTurn();
protected:
	virtual void pickCard() = 0;
};

