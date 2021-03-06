#include "World.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>

CardDatabaseParser World::m_cardDatabaseParser(3, NUMBER_OF_AGES);

World::World(unsigned int nh, unsigned int nc) : 
	m_gameOver(false), m_age(0), m_deck(), m_discard(), 
	m_scores(nh + nc, std::vector<int>(TOTAL_SCORE + 1)), m_winner(nullptr), m_draw(false)
#ifndef TESTING
	, m_display(m_players)
#endif // !TESTING
{
	int index = 0;
	for (unsigned int i = 0; i < nh; i++)
	{
		m_players.push_back(new HumanPlayer(&m_discard,index));
		index++;
	}
	for (unsigned int i = 0; i < nc; i++)
	{
		m_players.push_back(new ComputerPlayer(&m_discard,index));
		index++;
	}
	//Choix des voisins
	vector<int> unused;
	vector<int> order;
	for (int i = 0; i < nh + nc; i++)
	{
		unused.push_back(i);
	}

	std::srand(std::time(0));
	do
	{
		int randomIndex = rand() % (unused.size());
		order.push_back(unused.at(randomIndex));
		unused.erase(unused.begin() + randomIndex);
	} while (!unused.empty());
	//Bornes
	m_players[order.at(m_players.size() - 1)]->leftNeighbor = m_players[order.at(0)];
	m_players[order.at(0)]->rightNeighbor = m_players[order.at(m_players.size() - 1)];

	//Corps
	for (int i = 0; i < m_players.size() - 1; i++)
	{
		m_players[order.at(i)]->leftNeighbor = m_players[order.at(i + 1)];
		m_players[order.at(i + 1)]->rightNeighbor = m_players[order.at(i)];
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
#ifndef TESTING
	Display display(m_players);
	display.init();
#endif // !TESTING
	
			//display.test(m_deck);
	while (!m_gameOver)
	{
		if (betweenTurns())
		{
			updateMilitary();
			startAge();

#ifndef TESTING
			display.setAge(m_age);
#endif // !TESTING

		}

#ifndef TESTING
		display.draw();
#endif // !TESTING

		Player& p = *m_players[0];
		play(p);
		playOthers(p);
		endTurn();
	}

	computeScores();
	displayScores();
#ifndef TESTING
	display.drawScores(m_scores);
#endif // !TESTING
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

void World::updateMilitary()
{
	for (int i = 0; i < m_players.size(); i++)
	{
		m_scores[i][WAR] += getMilitaryScore(m_players.at(i));
	}
}

int World::getMilitaryScore(Player* p)
{
	int factor;
	if (m_age == 3)
	{
		factor = 5;
	}
		else 
		if (m_age == 2)
	{
		factor = 3;
	}
		else
		{
			factor = 1;
		}
	int leftScore = p->leftNeighbor->getMilitary();
	int rightScore = p->rightNeighbor->getMilitary();
	int myscore = p->getMilitary();
	int resul = 0;
	if (leftScore > myscore)
	{
		resul--;
		p->militaryMalus++;
	}
		else
		if (leftScore < myscore)
		{
		resul += factor;
		p->militaryBonus += factor;
		}

	if (rightScore > myscore)
	{
		resul--;
		p->militaryMalus++;
	}
	else
		if (rightScore < myscore)
		{
		resul += factor;
		}

	return resul;
}

void World::endTurn()
{
	playTurn();
	draft(m_age);
	if (m_age >= NUMBER_OF_AGES && betweenTurns())
	{
		computeScores();
		m_gameOver = true;
	}
}

void World::startAge()
{
	m_age++;
	m_deck = generateDeck(m_age-1);
	distributeCards();

#ifndef TESTING
	m_display.setAge(m_age);
#endif // !TESTING
}

bool World::betweenTurns() const
{
	return m_players[0]->getHand().size() <= 0;
}

bool World::gameOver() const
{
	return m_gameOver;
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
		throw "Le nombre de cartes n'est pas divisible par le nombre de joueurs";
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
	if (age % 2 == 1)
	{
		const CardSet firstHand = m_players.at(0)->getHand();
		for (unsigned int i = 0; i < m_players.size() - 1; i++)
		{
			const CardSet& hand = m_players.at(i + 1)->getHand();
			m_players.at(i)->setHand(hand);
		}
		m_players.at(m_players.size() - 1)->setHand(firstHand);
	}
	else
	{
		const CardSet lastHand = m_players.at(m_players.size()-1)->getHand();
		for (unsigned int i = m_players.size() - 1 ; i > 0; i--)
		{
			const CardSet& hand = m_players.at(i - 1)->getHand();
			m_players.at(i)->setHand(hand);
		}
		m_players.at(0)->setHand(lastHand);
	}
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


void World::upgradeMarvel(Player* p, int PV)
{
	int index = 0;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players.at(i) == p)
		{
			index = i;
		}
	}
	m_scores[index][WONDER_LEVEL] += PV;
}

void World::computeScores()
{
	updateMilitary();
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		const Player& player = *(m_players.at(i));
		const CardSet& board = player.getBoard();
		//std::cout << "Player " << (i + 1) << std::endl;

		//Blue cards score -----------------------------------------------------
		for (unsigned int j = 0; j < board.size(); j++)
		{
			m_players.at(i)->applyEndingEffects(board.at(j));
			const Card& card = *board[j];
			if (card.m_color == BLUE)
			{
				m_scores[i][BLUE_CARDS] += card.getPoints();
			}
		}

		//Coins score --------------------------------------------------------
		m_scores[i][GOLD] = ((int)m_players[i]->getMoney() / 3);

		//War score --------------------------------------------------------
		//m_scores[i][WAR] += getMilitaryScore(m_players.at(i));


		//MarvelPV score --------------------------------------------------------
		m_scores[i][WONDER_LEVEL] = m_players[i]->getMarvel()->getMarvelScore();

		//Yellow Card Score --------------------------------------------------------
		m_scores[i][YELLOW_CARDS] = m_players[i]->getGeneratedScore();

		//Guild score --------------------------------------------------------
		m_scores[i][GUILDS] = m_players[i]->getGuildScore();
	}

	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		const Player& player = *(m_players.at(i));
		const CardSet& board = player.getBoard();
		//Science score --------------------------------------------------------
		m_scores[i][SCIENCE] = computeScienceScore(board, m_players.at(i)->getScienceGuild());

		//Total score ----------------------------------------------------------
		int resul = 0;
		for (int j = 0; j < TOTAL_SCORE; j++)
		{
			resul += m_scores[i][j];
		}
		m_scores[i][TOTAL_SCORE] = resul;
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
		std::cout << "  Yellow cards : " << m_scores[i][YELLOW_CARDS] << std::endl;
		std::cout << "  War : " << m_scores[i][WAR] << std::endl;
		std::cout << "  Science : " << m_scores[i][SCIENCE] << std::endl;
		std::cout << "  WonderScore : " << m_scores[i][WONDER_LEVEL] << std::endl;
		std::cout << "  Guilds : " << m_scores[i][GUILDS] << std::endl;
		std::cout << "  Gold Score : " << m_scores[i][GOLD] << std::endl;
		std::cout << "Total : " << m_scores[i][TOTAL_SCORE] << std::endl << std::endl;
	}
	for (auto e : m_discard)
	{
		//std::cout << e->m_name << std::endl;
	}
}

unsigned int World::computeScienceScore(const CardSet& board, char guild) const
{
	unsigned int compass = 0, gear = 0, tablet = 0;
	switch (guild)
	{
	case 'n':
			break;
	case 'c':
		compass++;
		break;
	case 'g':
		gear++;
			break;
	case 't':
		tablet++;
			break;
		default:
			break;
	}
	for (unsigned int i = 0; i < board.size(); i++)
	{
		const GreenCard& card = (GreenCard&) (*board[i]);
		if (card.m_color == GREEN)
		{
			//std::cout << card.m_name << "()()" << std::endl;
			if (card.getType() == 'c')
				compass++;
			if (card.getType() == 'g')
				gear++;
			if (card.getType() == 't')
				tablet++;
		}
	}
	//std::cout << "c:" << compass << " g:" << gear << " t:" << tablet << std::endl;
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
	return res;
}

#ifndef TESTING
Display& World::getDisplay()
{
	return m_display;
}
#endif // !TESTING
