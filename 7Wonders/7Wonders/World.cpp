#include "World.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Display.h"
#include <string>

World::World(unsigned int nh, unsigned int nc) : 
	m_gameOver(false), m_age(0), m_cardDatabaseParser(nh + nc),
	m_deck(), m_discard(), m_scores(nh + nc, std::vector<unsigned int>(TOTAL_SCORE+1)), m_winner(nullptr), m_draw(false)
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
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		delete m_players.at(i);
	}
}


void World::run()
{
	Display display(m_players);
	display.draw();

	while (!m_gameOver)
	{
		if (betweenTurns())
		{
			startAge();
		}
		Player& p = *m_players[0];
		play(p);
		playOthers(p);
		endTurn();
	}

	computeScores();
	displayScores();
}

void World::play(Player& player)
{
	player.prepareTurn();
}

void World::playOthers(Player& player)
{
	for (auto p : m_players)
	{
		if (&player != p)
		{
			play(*p);
		}
	}
}

void World::endTurn()
{
	playTurn();
	draft(m_age);
	if (m_age >= NUMBER_OF_AGES && betweenTurns())
	{
		m_gameOver = true;
	}
}

void World::startAge()
{
	m_age++;
	if (m_age <= NUMBER_OF_AGES)
	{
		m_deck = generateDeck(m_age-1);//FIXME m_age ou m_age-1 ?
		distributeCards();
	}
}

bool World::betweenTurns() const
{
	return m_players[0]->getHand().size() <= 1;
}

bool World::gameOver() const
{
	return m_gameOver;
}



void World::processTurn()
{
	prepareTurn();
	playTurn();
	draft(m_age);
}

CardSet World::generateDeck(int age)
{
	return m_cardDatabaseParser.generateDeck(age);
}

void World::distributeCards()
{
	unsigned int cardsForOnePlayer = m_deck.size() / m_players.size();
	if (m_deck.size() % m_players.size() != 0)
	{
		std::cerr << "Attention : le nombre de cartes (" << m_deck.size() << ") devrait etre divisible par le nombre de joueurs (" << m_players.size() << ")" << std::endl;
	}

	for (unsigned int i = 0; i < m_players.size(); i++)
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
	for (unsigned int i = 0; i<m_players.size() - 1; i++)
	{
		const CardSet& hand = m_players.at(i + 1)->getHand();
		m_players.at(i)->setHand(hand);
	}
	m_players.at(m_players.size() - 1)->setHand(firstHand);
}

void World::prepareTurn()
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players.at(i)->prepareTurn();
	}
}

void World::playTurn()
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players.at(i)->playTurn();
	}
}

void World::computeScores()
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		const Player& player = *(m_players.at(i));
		const CardSet& board = player.getBoard();
		std::cout << "Player " << (i + 1) << std::endl;

		//Blue cards score -----------------------------------------------------
		for (unsigned int j = 0; j < board.size(); j++)
		{
			const Card& card = *board[j];
			if (card.m_color == BLUE)
			{
				m_scores[i][BLUE_CARDS] += card.getPoints();
			}
		}

		//Science score --------------------------------------------------------
		m_scores[i][SCIENCE] = computeScienceScore(board);

		//Total score ----------------------------------------------------------
		m_scores[i][TOTAL_SCORE] = m_scores[i][BLUE_CARDS] + m_scores[i][SCIENCE];
	}
	unsigned int winner = 0;
	for (unsigned int i = 1; i < m_scores.size(); i++)
	{
		if (m_scores[i][TOTAL_SCORE] > m_scores[winner][TOTAL_SCORE])
		{
			winner = i;
		}
	}
	m_winner = m_players[winner];
}

void World::displayScores() const
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		std::cout << "  Blue cards : " << m_scores[i][BLUE_CARDS] << std::endl;
		std::cout << "  Science : " << m_scores[i][SCIENCE] << std::endl;
		std::cout << "Total : " << m_scores[i][TOTAL_SCORE] << std::endl << std::endl;
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

bool World::hasWon(const Player& player) const
{
	return &player == m_winner;
}

bool World::draw() const
{
	return m_draw;
}

unsigned int World::getPlayerId(const Player& player) const
{
	unsigned int res = 0;
	for (unsigned int i = 1; i < m_players.size(); i++)
	{
		if ((m_players[i]) == &player)
		{
			res = i;
			break;
		}
	}
	return 0;
}
