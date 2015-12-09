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

	displayScores();
}

CardSet World::generateDeck(int age)
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
		CardSet hand;
		for (unsigned int j = 0; j<cardsForOnePlayer; j++)
		{
			hand.push_back(m_deck.at(i*cardsForOnePlayer + j));
		}
		m_players.at(i)->setHand(hand);
	}
}

void World::draft(unsigned int age)
{
	const CardSet firstHand = m_players.at(0)->getHand();
	for (unsigned int i = 0; i<m_playerNumber-1; i++)
	{
		const CardSet& hand = m_players.at(i + 1)->getHand();
		m_players.at(i)->setHand(hand);
	}
	m_players.at(m_playerNumber - 1)->setHand(firstHand);
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

void World::displayScores() const
{
	for (unsigned int i = 0; i < m_playerNumber; i++)
	{
		unsigned int warScore = 0, goldScore = 0, wonderLevelsScore = 0, scoreBlue = 0,
			scoreYellow = 0, guildsScore = 0, scienceScore = 0, totalScore = 0;
		const Player& player = *(m_players.at(i));
		const CardSet& board = player.getBoard();
		std::cout << "Player " << (i + 1) << std::endl;

		//Blue cards score -----------------------------------------------------
		for (unsigned int j = 0; j < board.size(); j++)
		{
			const Card& card = *board[j];
			if (card.m_color == BLUE)
			{
				scoreBlue += card.getPoints();
			}
		}
		std::cout << "  Blue cards : " << scoreBlue << std::endl;

		//Science score -----------------------------------------------------
		scienceScore = computeScienceScore(board);
		std::cout << "  Science : " << scienceScore << std::endl;

		//Total score
		totalScore = warScore + goldScore + wonderLevelsScore + scoreBlue + scoreYellow + guildsScore + scienceScore;
		std::cout << "Total : " << totalScore << std::endl << std::endl;

	}
	for (auto e : m_discard)
	{
		std::cout << e->m_name << std::endl;
	}
}

unsigned int World::computeScienceScore(const CardSet& board) const
{
	unsigned int compass = 0, gear = 0, tablet = 0;
	for (unsigned int i = 0; i < board.size(); i++)
	{
		const GreenCard& card = (GreenCard&) (*board[i]);
		if (card.m_color == GREEN)
		{
			std::cout << card.m_name << "()()" << std::endl;
			if (card.getType() == 'c')
				compass++;
			if (card.getType() == 'g')
				gear++;
			if (card.getType() == 't')
				tablet++;
		}
	}
	std::cout << "c:" << compass << " g:" << gear << " t:" << tablet << std::endl;
	unsigned int res = compass*compass + gear*gear + tablet*tablet + 7*std::min(compass, std::min(gear, tablet));
	return res;
}