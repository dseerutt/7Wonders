#include "World.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Display.h"
#include <string>

World::World(unsigned int nh, unsigned int nc) : 
	m_playerNumber(nh+nc), m_numberOfTurns(0), m_cardDatabaseParser(nh+nc), m_deck(), m_discard()
{
	for (unsigned int i = 0; i < nh; i++)
	{
		m_players.push_back(new HumanPlayer(&m_discard));
	}
	for (unsigned int i = 0; i < nc; i++)
	{
		m_players.push_back(new ComputerPlayer(&m_discard));
	}
}

World::~World()
{
	for (unsigned int i = 0; i < m_playerNumber; i++)
	{
		delete(m_players.at(i));
	}
}


void World::run()
{
	Display display(m_players);
	display.draw();

	for (unsigned int age = 0; age < NUMBER_OF_AGES; age++)
	{
		m_deck = generateDeck(age);
		
		distributeCards();
		for (unsigned t = 0; t < m_numberOfTurns; t++)
		{
			prepareTurn();
			playTurn();
			draft(age);

			display.draw();
		}
	}
}

std::vector<Card> World::generateDeck(int age)
{
	return m_cardDatabaseParser.generateDeck(age);
}

void World::distributeCards()
{
	unsigned int cardsForOnePlayer = m_deck.size() / m_playerNumber;
	if (m_deck.size() % m_playerNumber != 0)
	{
		std::cerr << "Attention : le nombre de cartes (" << m_deck.size() << ") devrait etre divisible par le nombre de joueurs (" << m_playerNumber << ")" << std::endl;
	}
	m_numberOfTurns = cardsForOnePlayer;

	for (unsigned int i = 0; i < m_playerNumber; i++)
	{
		std::vector<Card> hand;
		for (unsigned int j = 0; j<cardsForOnePlayer; j++)
		{
			hand.push_back(m_deck.at(i*cardsForOnePlayer + j));
		}
		m_players.at(i)->setHand(hand);
	}
}

void World::draft(unsigned int age)
{
	const std::vector<Card>& FirstHand = m_players.at(0)->getHand();
	for (unsigned int i = 0; i<m_playerNumber-1; i++)
	{
		const std::vector<Card>& hand = m_players.at(i+1)->getHand();
		m_players.at(i)->setHand(hand);
	}
	m_players.at(m_playerNumber - 1)->setHand(FirstHand);
}

void World::prepareTurn()
{
	for (unsigned int i = 0; i < m_playerNumber; i++)
	{
		m_players.at(i)->prepareTurn();
	}
}

void World::playTurn()
{
	for (unsigned int i = 0; i < m_playerNumber; i++)
	{
		m_players.at(i)->playTurn();
	}
}

