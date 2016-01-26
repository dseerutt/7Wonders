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

void Display::run() //FIXMEPLEASE
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
	/*
	drawPlayerDemo(*m_players.at(0), *m_players.at(0), *m_players.at(0));
	*/
	drawBackground();
	testMaximumCapacity(*m_players.at(0), *m_players.at(0), *m_players.at(0));
	drawHand(*m_players.at(0));
	drawStatistics(*m_players.at(0), *m_players.at(0), *m_players.at(0));
	m_window.display();
}

void Display::drawStatistics(const Player& p0, const Player& p1, const Player& p2)
{
	//Player names
	drawSprite("Player1.png", sf::Vector2f(70, 5), 500, 500);
	drawSprite("Player2.png", sf::Vector2f(330, 5), 133, 55);
	drawSprite("Player3.png", sf::Vector2f(600, 5), 133, 55);

	//Jetons

	drawSpriteWithScale("coin.png", sf::Vector2f(35, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p0.getMoney()), sf::Vector2f(42, 90), 20);
	drawSpriteWithScale("coin.png", sf::Vector2f(305, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p1.getMoney()), sf::Vector2f(312, 90), 20);
	drawSpriteWithScale("coin.png", sf::Vector2f(575, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p2.getMoney()), sf::Vector2f(582, 90), 20);
	
	drawSpriteWithScale("pyr.png", sf::Vector2f(85, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p0.getMarvel()->getMarvelLevel()), sf::Vector2f(97, 90), 20);
	drawSpriteWithScale("pyr.png", sf::Vector2f(350, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p0.getMarvel()->getMarvelLevel()), sf::Vector2f(363, 90), 20);
	drawSpriteWithScale("pyr.png", sf::Vector2f(620, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p0.getMarvel()->getMarvelLevel()), sf::Vector2f(633, 90), 20);

	drawSpriteWithScale("sword.png", sf::Vector2f(157, 60), sf::Vector2f(0.03, 0.03), 894, 894);
	writeText(to_string(p0.getMilitaryBonus()), sf::Vector2f(164, 90), 20);
	drawSpriteWithScale("sword.png", sf::Vector2f(420, 60), sf::Vector2f(0.03, 0.03), 894, 894);
	writeText(to_string(p1.getMilitaryBonus()), sf::Vector2f(427, 90), 20);
	drawSpriteWithScale("sword.png", sf::Vector2f(697, 60), sf::Vector2f(0.03, 0.03), 894, 894);
	writeText(to_string(p2.getMilitaryBonus()), sf::Vector2f(704, 90), 20);

	drawSpriteWithScale("shield.png", sf::Vector2f(205, 60), sf::Vector2f(0.30, 0.30), 84, 84);
	writeText(to_string(p0.getMilitaryMalus()), sf::Vector2f(212, 90), 20);
	drawSpriteWithScale("shield.png", sf::Vector2f(475, 60), sf::Vector2f(0.30, 0.30), 84, 84);
	writeText(to_string(p1.getMilitaryMalus()), sf::Vector2f(482, 90), 20);
	drawSpriteWithScale("shield.png", sf::Vector2f(745, 60), sf::Vector2f(0.30, 0.30), 84, 84);
	writeText(to_string(p2.getMilitaryMalus()), sf::Vector2f(752, 90), 20);
	
	switch (age)
	{
	case 1:
		//Age 1
		drawSprite("1.png", sf::Vector2f(0, 0), 46, 61);
		drawSprite("1.png", sf::Vector2f(760, 0), 46, 61);
		break;
	case 2:
		//Age 2
		drawSprite("2.png", sf::Vector2f(0, 0), 59, 61);
		drawSprite("2.png", sf::Vector2f(750, 0), 59, 61);
		break;
	case 3:
		//Age 3
		drawSprite("3.png", sf::Vector2f(0, 0), 59, 61);
		drawSprite("3.png", sf::Vector2f(735, 0), 59, 61);
		break;
	default:
		break;
	}

}

void Display::drawPlayerDemo(const Player& p0, const Player& p1, const Player& p2)
{
	sf::Vector2f pos(WINDOW_SIZE_X / 2 + 100.f, WINDOW_SIZE_Y - 100.f);
	const CardSet& board = p0.getBoard();
	drawBoard(board, pos);
}

void Display::testMaximumCapacity(const Player& p0, const Player& p1, const Player& p2)
{


	//Cards display
	//Colonne 1
	int tempWidth = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(20, tempWidth), 108, 30);
		tempWidth += 30;
	}

	//Colonne 2
	int tempWidth2 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(140, tempWidth2), 108, 30);
		tempWidth2 += 30;
	}

	//Colonne 3
	int tempWidth3 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(290, tempWidth3), 108, 30);
		tempWidth3 += 30;
	}

	//Colonne 4
	int tempWidth4 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(410, tempWidth4), 108, 30);
		tempWidth4 += 30;
	}

	//Colonne 5
	int tempWidth5 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(560, tempWidth5), 108, 30);
		tempWidth5 += 30;
	}

	//Colonne 6
	int tempWidth6 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("CHANTIER_MINI.png", sf::Vector2f(680, tempWidth6), 108, 30);
		tempWidth6 += 30;
	}

}

void Display::drawBackground()
{
	drawSprite("wallpaper.jpg", 800, 600);

	drawSprite("CHANTIER_MINI.png",sf::Vector2f(108, 30), 108, 30);
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
		drawSprite("CHANTIER.png", sf::Vector2f(tempWidth, 425), CardHeight, CardWidth);
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


void Display::drawSprite(string path, sf::Vector2f pos, int wherex, int wherey)
{
	sf::Texture texture2;
	texture2.create(wherex, wherey);
	sf::Sprite sprite2;
	sprite2.setPosition(pos);
	sprite2.setTexture(texture2);
	if (!texture2.loadFromFile(RelativePath + path))
	{
		m_window.close();
	}
	m_window.draw(sprite2);
}

void Display::drawSpriteWithScale(string path, sf::Vector2f pos, sf::Vector2f scale, int wherex, int wherey)
{
	sf::Texture texture2;
	texture2.create(wherex, wherey);
	sf::Sprite sprite2;
	sprite2.setPosition(pos);
	sprite2.setTexture(texture2);
	if (!texture2.loadFromFile(RelativePath + path))
	{
		m_window.close();
	}
	sprite2.scale(scale);
	m_window.draw(sprite2);
}

void Display::drawSprite(string path, int wherex, int wherey)
{
	sf::Texture texture2;
	texture2.create(wherex, wherey);
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	if (!texture2.loadFromFile(RelativePath + path))
	{
		m_window.close();
	}
	m_window.draw(sprite2);
}

void Display::writeText(string text, sf::Vector2f position, int size)
{
	sf::Text atext;
	sf::Font font;
	if (!font.loadFromFile(RelativePath + "arial.ttf"))
	{
		// error
	}
	atext.setFont(font);
	atext.setCharacterSize(size);
	atext.setStyle(sf::Text::Bold);
	atext.setColor(sf::Color::White);
	atext.setPosition(position.x, position.y);
	atext.setString(text);
	m_window.draw(atext);
}