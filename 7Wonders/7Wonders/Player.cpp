#include "Player.h"
#include "RedCard.h"


Player::Player(CardSet* discard) : m_discard(discard),money(0), military(0), m_hand(), m_board(), m_cardToPlay(nullptr)
{
	std::array<int, RESOURCES_COUNT> resources = { -1, 0, 0, 0, 0, 0, 0 };
	m_resources.push_back(resources);
}

Player::~Player()
{
}

unsigned int Player::getMoney() const
{
	return money;
}

unsigned int Player::getMilitary() const
{
	return military;
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
	if (m_cardToPlay->m_color == RED)
	{
		military += m_cardToPlay->getPower();
	}

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

void Player::AddResource(array<int, RESOURCES_COUNT> resource)
{
	if (std::get<WOOD>(m_resources.at(0)) == -1)
	{
		m_resources.clear();
		m_resources.push_back(resource);
	}
	else {
		for (int i = 0 ; i < m_resources.size() ; i++)
		{
			for (int j = 0; j < RESOURCES_COUNT; j++)
			{
			m_resources.at(i).at(j) += resource.at(j);
			}
		}
	}
}
void Player::AddResourceWithChoice(array<int, RESOURCES_COUNT> resource)
{
	if (std::get<WOOD>(m_resources.at(0)) == -1)
	{
		m_resources.clear();
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (resource.at(i) > 0)
			{
				std::array<int, RESOURCES_COUNT> temp = { 0, 0, 0, 0, 0, 0, 0, 0};
				temp.at(i) = resource.at(i);
				m_resources.push_back(temp);
			}
		}
	}
	else {
		for (int i = 0; i < RESOURCES_COUNT; i++)
		{
			if (resource.at(i) > 0)
			{

			}
		}
	}
}

std::vector<std::array<int, RESOURCES_COUNT>> Player::getResources() {
	return m_resources;
}

