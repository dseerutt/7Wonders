#include "Display.h"
#include <conio.h>
#define DEMO
#define CardHeight 114
#define CardWidth 172
const string Display::miniPath = "Mini/";
const string Display::cardPath = "Cards/";

Display::Display(const std::vector<Player*>& players) : 
m_players(players), m_window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "7 Wonders")
{
}

Display::~Display()
{
}

void Display::setAge(int age0)
{
	m_window.clear();
	drawBackground();
	age = age0;
	switch (age)
	{
	case 1:
		//Age 1
		drawSprite("I.png", sf::Vector2f(0, 0), 46, 61);
		break;
	case 2:
		//Age 2
		drawSprite("II.png", sf::Vector2f(0, 0), 59, 61);
		break;
	case 3:
		//Age 3
		drawSprite("III.png", sf::Vector2f(0, 0), 59, 61);
		break;
	default:
		break;
		m_window.display();
		sf::sleep(sf::milliseconds(1000));
		draw();
	}
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

void Display::init()
{
	drawBackground();
	drawSpriteWithScale("pap.png", sf::Vector2f(90, 100), sf::Vector2f(1, 0.75), 640, 533);
	writeTextBlack("Welcome to 7 Wonders", sf::Vector2f(170, 140), 60);
	writeTextBlack("The Game", sf::Vector2f(300, 230), 60);
	drawSpriteWithScale("begin.png", sf::Vector2f(360, 350), sf::Vector2f(1, 1), 88, 50);
	m_window.display();
	std::cout << "Enter any value to continue" << std::endl;
	getchar();
	
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
	//testMaximumCapacity(*m_players.at(0), *m_players.at(0), *m_players.at(0));


	drawBackground();
	drawHand(*m_players.at(0));
	drawBoards(*m_players.at(0), *m_players.at(1), *m_players.at(2));
	drawStatistics(*m_players.at(0), *m_players.at(1), *m_players.at(2));
	m_window.display();
}

void Display::drawScores(std::vector<std::vector<int> > m_scores)
{
	drawBackground();
	drawSpriteWithScale("pap.png", sf::Vector2f(0, 0), sf::Vector2f(1.25, 1.1), 640, 533);
	int offset = 35;
	drawSprite("Player1.png", sf::Vector2f(offset + 240, 100), 500, 500);
	drawSprite("Player2.png", sf::Vector2f(offset + 390, 100), 133, 55);
	drawSprite("Player3.png", sf::Vector2f(offset + 540, 100), 133, 55);
	writeTextBlack("WAR", sf::Vector2f(offset + 42, 170), 20);
	writeTextBlack("GOLD", sf::Vector2f(offset + 42, 210), 20);
	writeTextBlack("WONDER LEVEL", sf::Vector2f(offset + 42, 250), 20);
	writeTextBlack("BLUE CARDS", sf::Vector2f(offset + 42, 290), 20);
	writeTextBlack("YELLOW CARDS", sf::Vector2f(offset + 42, 330), 20);
	writeTextBlack("GUILDS", sf::Vector2f(offset + 42, 370), 20);
	writeTextBlack("SCIENCE", sf::Vector2f(offset + 42, 410), 20);
	writeTextBlack("TOTAL SCORE", sf::Vector2f(offset + 42, 450), 20);
	int posX = 300;
	for (int i = 0; i < m_scores.size(); i++)
	{
		int posY = 167;
		for (int j = 0; j < m_scores.at(i).size(); j++)
		{
			writeTextBlack(to_string(m_scores.at(i).at(j)), sf::Vector2f(offset + posX, posY), 20);
			posY += 40;
		}
		posX += 150;
	}


	m_window.display();
	std::cout << "Enter any value to exit" << std::endl;
	getchar();
	exit(0);
}

void Display::drawStatistics(const Player& p0, const Player& p1, const Player& p2)
{
	//Player names
	drawSprite("Player1.png", sf::Vector2f(50, 5), 500, 500);
	drawSpriteWithScale("wood.png", sf::Vector2f(202, 15), sf::Vector2f(0.25, 0.25), 123, 118);
	drawSprite("Player2.png", sf::Vector2f(310, 5), 133, 55);
	drawSpriteWithScale("stone.png", sf::Vector2f(472, 15), sf::Vector2f(0.25, 0.25), 123, 118);
	drawSprite("Player3.png", sf::Vector2f(580, 5), 133, 55);
	drawSpriteWithScale("clay.png", sf::Vector2f(720, 15), sf::Vector2f(0.25, 0.25), 123, 118);

	//Jetons
	drawSpriteWithScale("coin.png", sf::Vector2f(35, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p0.getMoney()), sf::Vector2f(42, 90), 20);
	drawSpriteWithScale("coin.png", sf::Vector2f(305, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p1.getMoney()), sf::Vector2f(312, 90), 20);
	drawSpriteWithScale("coin.png", sf::Vector2f(575, 60), sf::Vector2f(0.05, 0.05), 512, 512);
	writeText(to_string(p2.getMoney()), sf::Vector2f(582, 90), 20);
	
	drawSpriteWithScale("pyr.png", sf::Vector2f(85, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p0.getMarvel()->getMarvelLevel()), sf::Vector2f(97, 90), 20);
	drawSpriteWithScale("pyr.png", sf::Vector2f(355, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p1.getMarvel()->getMarvelLevel()), sf::Vector2f(368, 90), 20);
	drawSpriteWithScale("pyr.png", sf::Vector2f(625, 55), sf::Vector2f(0.06, 0.06), 600, 600);
	writeText(to_string(p2.getMarvel()->getMarvelLevel()), sf::Vector2f(638, 90), 20);

	drawSpriteWithScale("sword.png", sf::Vector2f(150, 60), sf::Vector2f(0.03, 0.03), 894, 894);
	writeText(to_string(p0.getMilitaryBonus()), sf::Vector2f(157, 90), 20);
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
	drawOldBoard(board, pos);
}

void Display::testMaximumCapacity(const Player& p0, const Player& p1, const Player& p2)
{
	//Cards display
	//Colonne 1
	int tempWidth = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(20, tempWidth), 108, 30);
		tempWidth += 30;
	}

	//Colonne 2
	int tempWidth2 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(140, tempWidth2), 108, 30);
		tempWidth2 += 30;
	}

	//Colonne 3
	int tempWidth3 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(290, tempWidth3), 108, 30);
		tempWidth3 += 30;
	}

	//Colonne 4
	int tempWidth4 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(410, tempWidth4), 108, 30);
		tempWidth4 += 30;
	}

	//Colonne 5
	int tempWidth5 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(560, tempWidth5), 108, 30);
		tempWidth5 += 30;
	}

	//Colonne 6
	int tempWidth6 = 140;
	for (int i = 0; i < 9; i++)
	{
		drawSprite("Mini/CHANTIER_MINI.png", sf::Vector2f(680, tempWidth6), 108, 30);
		tempWidth6 += 30;
	}

}

void Display::drawBackground()
{
	drawSprite("wallpaper.jpg", 800, 600);
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
		string temp = cardPath + p.getHand().at(i)->m_name + ".png";
		drawCardSprite(temp, sf::Vector2f(tempWidth, 425), 514, 794);
		tempWidth += CardHeight;
	}
	
}

void Display::drawPlayer(const Player& p)
{
	sf::Vector2f pos(WINDOW_SIZE_X / 2 + 100.f, WINDOW_SIZE_Y - 100.f);
	const CardSet& board = p.getBoard();
	drawOldBoard(board, pos);
}

void Display::drawBoards(const Player& p0, const Player& p1, const Player& p2)
{
	drawBoard1(p0.getBoard());
	drawBoard2(p1.getBoard());
	drawBoard3(p2.getBoard());
}

void Display::drawBoard1(const CardSet& board)
{
	int tempWidth = 140;
	if (board.size() > 9)
	{
		//Colonne 1
		for (int i = 0; i < 9; i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(20, tempWidth), 200, 60);
			tempWidth += 46;
		}
		//Colonne 2
		int tempWidth2 = 150;
		for (int i = 9; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(140, tempWidth2), 144, 46);
			tempWidth2 += 46;
		}
	}
	else
	{
		//Colonne 1
		for (int i = 0; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(20, tempWidth), 108, 30);
			tempWidth += 30;
		}
	}
}

void Display::drawBoard2(const CardSet& board)
{
	int tempWidth = 140;
	if (board.size() > 9)
	{
		//Colonne 1
		for (int i = 0; i < 9; i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(290, tempWidth), 108, 30);
			tempWidth += 30;
		}
		//Colonne 2
		int tempWidth2 = 140;
		for (int i = 9; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(410, tempWidth2), 108, 30);
			tempWidth2 += 30;
		}
	}
	else
	{
		//Colonne 1
		for (int i = 0; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(290, tempWidth), 108, 30);
			tempWidth += 30;
		}
	}
}

void Display::drawBoard3(const CardSet& board)
{
	int tempWidth = 140;
	if (board.size() > 9)
	{
		//Colonne 1
		for (int i = 0; i < 9; i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(560, tempWidth), 108, 30);
			tempWidth += 30;
		}
		//Colonne 2
		int tempWidth2 = 140;
		for (int i = 9; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(680, tempWidth2), 108, 30);
			tempWidth2 += 30;
		}
	}
	else
	{
		//Colonne 1
		for (int i = 0; i < board.size(); i++)
		{
			string temp = miniPath + board.at(i)->m_name + "_MINI.png";
			drawMiniCardSprite(temp, sf::Vector2f(560, tempWidth), 108, 30);
			tempWidth += 30;
		}
	}
}

void Display::drawOldBoard(const CardSet& board, sf::Vector2f pos)
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

void Display::drawCardSprite(string path, sf::Vector2f pos, int wherex, int wherey)
{
	sf::Texture texture2;
	texture2.create(wherex, wherey);
	sf::Sprite sprite2;
	sprite2.setPosition(pos);
	sprite2.setTexture(texture2);
	sprite2.setScale(0.23, 0.23);
	if (!texture2.loadFromFile(RelativePath + path))
	{
		m_window.close();
	}
	m_window.draw(sprite2);
}

void Display::drawMiniCardSprite(string path, sf::Vector2f pos, int wherex, int wherey)
{
	sf::Texture texture2;
	texture2.create(wherex, wherey);
	sf::Sprite sprite2;
	sprite2.setPosition(pos);
	sprite2.setTexture(texture2);
	sprite2.setScale(1, 1);
	if (!texture2.loadFromFile(RelativePath + path))
	{
		m_window.close();
	}
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

void Display::writeTextBlack(string text, sf::Vector2f position, int size)
{
	sf::Text atext;
	sf::Font font;
	if (!font.loadFromFile(RelativePath + "parc.ttf"))
	{
		// error
	}
	atext.setFont(font);
	atext.setCharacterSize(size+10);
	atext.setStyle(sf::Text::Bold);
	atext.setColor(sf::Color::Black);
	atext.setPosition(position.x, position.y);
	atext.setString(text);
	m_window.draw(atext);
}