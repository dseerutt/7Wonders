#include "Display.h"
#define DEMO
#define CardHeight 114
#define CardWidth 172
Display::Display(const std::vector<Player*>& players) : 
m_players(players), m_window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "7 Wonders")
{
}

Display::~Display()
{
}

void Display::setAge(int age0)
{
	age = age0;
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
	/*
	for (unsigned int i = 0; i < 1//m_players.size(); i++)
	{
		drawPlayer(*m_players.at(i));
	}*/
	drawBackground();
	drawPlayerDemo(*m_players.at(0), *m_players.at(0), *m_players.at(0));
	drawHand(*m_players.at(0));
	m_window.display();
}


void Display::drawPlayerDemo(const Player& p0, const Player& p1, const Player& p2)
{
	sf::Vector2f pos(WINDOW_SIZE_X / 2 + 100.f, WINDOW_SIZE_Y - 100.f);
	const CardSet& board = p0.getBoard();
	drawBoard(board, pos);
}


void Display::drawBackground()
{
	sf::Texture texture;
	texture.create(800, 600);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	if (!texture.loadFromFile("Pictures/wallpaper.jpg"))
	{
		m_window.close();
	}
	m_window.draw(sprite);
}

void Display::drawHands()
{
	drawHand(*m_players.at(0));
}

void Display::drawHand(const Player& p)
{
	int tempWidth = 0;
	for (int i = 0; i < p.getHand().size(); i++)
	{
		sf::Texture texture2;
		texture2.create(CardHeight, CardWidth);
		sf::Sprite sprite2;
		sprite2.setPosition(sf::Vector2f(tempWidth, 425));
		sprite2.setTexture(texture2);
		if (!texture2.loadFromFile("Pictures/CHANTIER.png"))
		{
			m_window.close();
		}
		m_window.draw(sprite2);
		tempWidth += CardHeight;
	}
	
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
	wonder.setSize(sf::Vector2f(140.f, 100.f));
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
		rect.setFillColor(sf::Color::Color(102,51,0,255));
		break;
	case GRAY:
		rect.setFillColor(sf::Color::Color(128, 128, 128, 255));
		break;
	case BLUE:
		rect.setFillColor(sf::Color::Color(0, 204, 204, 255));
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
	case VIOLET:
		rect.setFillColor(sf::Color::Color(51, 0, 102, 255));
		break;
	default:
		rect.setFillColor(sf::Color::White);
		break;
	}

	m_window.draw(rect);
}
