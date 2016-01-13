#include "Player.h"


Player::Player(CardSet* discard) : m_discard(discard),money(0), m_hand(), m_board(), m_cardToPlay(nullptr)
{
}

Player::~Player()
{
}

unsigned int Player::getMoney() const
{
	return money;
}

unsigned int Player::getScore() const
{
	unsigned int score = 0;
	for (unsigned int i = 0; i < m_board.size(); i++)
	{
		score += m_board.at(i)->getPoints();
	}
	return score;
}

const CardSet& Player::getBoard() const
{
	return m_board;
}

void Player::setHand(const CardSet& newHand)
{
	m_hand.clear();
	for (unsigned int i = 0; i < newHand.size(); i++)
	{
		m_hand.push_back(newHand.at(i));
	}
}

const CardSet& Player::getHand() const
{
	return m_hand;
}

const CardSet Player::getPlayableCards() const
{
	CardSet cards = m_hand;
	return cards;
}


void Player::canBuy(int price)
{
	//TODO
}

void Player::prepareTurn()
{
	if (m_hand.size() <= 1)
	{
		if (m_hand.size() == 0)
		{
			std::cerr << "Attention : un joueur ne possède aucune carte en main au debut du tour." << std::endl;
			throw("Un joueur ne possède aucune carte en main");
			return;
		}
		m_discard->push_back(m_hand.at(0));
	}
	else
	{
		pickCard();
	}
}

void Player::playTurn()
{
	if (m_cardToPlay == 0)
	{
		throw("Pas de carte à jouer sélectionnée");
	}

	if (m_hand.size() <= 1)
	{
		throw("Taille de la main non conforme");
	}
	m_board.push_back(m_cardToPlay);

	CardSet::iterator cardToErase;
	for (auto it = m_hand.begin(); it != m_hand.end(); ++it)
	{
		Card* card = *it;
		if (card == m_cardToPlay)
		{
			cardToErase = it;
			break;
		}
	}
	m_hand.erase(cardToErase);
}
