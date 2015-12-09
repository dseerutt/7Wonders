#include "Display.h"

Display::Display(const std::vector<Player*>& players) : 
m_players(players), m_window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "7 Wonders")
{
}

Display::~Display()
{
}

void Display::run() //FIXME
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
	}
}

void Display::draw()
{
	m_window.clear();
	for (unsigned int i = 0; i < 1/*m_players.size()*/; i++)
	{
		drawPlayer(*m_players.at(i));
	}
	m_window.display();
}

void Display::drawPlayer(const Player& p)
{
	sf::Vector2f pos(WINDOW_SIZE_X / 2 + 100.f, WINDOW_SIZE_Y - 100.f);
	const CardSet& board = p.getBoard();
	drawBoard(board, pos);

}

void Display::drawBoard(const CardSet& board, sf::Vector2f pos)
{
	std::vector<unsigned int> count(COLOR_COUNT);
	for (unsigned int i = 0; i < COLOR_COUNT; i++)
	{
		count[i] = 0;
	}
	for (unsigned int i = 0; i < board.size(); i++)
	{
		const Card& c = *board.at(i);
		CardColor col = c.m_color;
		count.at(col)++;
		drawCard(c, pos + sf::Vector2f(col*20.f, -(count.at(col)*10.f)));
	}

	sf::RectangleShape wonder;
	wonder.setPosition(pos);
	wonder.setSize(sf::Vector2f(130.f, 100.f));
	wonder.setFillColor(sf::Color::White);
	m_window.draw(wonder);
}

void Display::drawCard(const Card& c, sf::Vector2f pos)
{
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(sf::Vector2f(20.f, 50.f));
	switch (c.m_color)
	{
	case BROWN:
		rect.setFillColor(sf::Color::Magenta);
		break;
	case GRAY:
		rect.setFillColor(sf::Color::Cyan);
		break;
	case BLUE:
		rect.setFillColor(sf::Color::Blue);
		break;
	case YELLOW:
		rect.setFillColor(sf::Color::Yellow);
		break;
	case RED:
		rect.setFillColor(sf::Color::Red);
		break;
	case GREEN:
		rect.setFillColor(sf::Color::Green);
		break;
	default:
		rect.setFillColor(sf::Color::White);
		break;
	}

	m_window.draw(rect);
}
