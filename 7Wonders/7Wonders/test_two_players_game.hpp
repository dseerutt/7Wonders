#ifndef __TEST_TWO_PLAYERS_GAME_HPP__
#define __TEST_TWO_PLAYERS_GAME_HPP__

#include <random>
#include <iostream>
#include <map>
#include <string>

namespace game
{
template<typename Game>
class test_two_players_game
{
	void playout(Game g);
	void play(Game g);
	public:
	test_two_players_game(Game g);
};

template<typename Game>
test_two_players_game<Game>::test_two_players_game(Game g)
{    
	//    playout(g);
	play(g);
}

template <typename Game>
void run_test_two_players_game(const Game& g)
{
	test_two_players_game<Game>{g};
}

template <typename Game>
void test_two_players_game<Game>::playout(Game g)
{
	std::mt19937 mt;
	std::cout << "playout" << std::endl;
	for (int i = 0; i < 100; ++i) 
	{
		uint8_t player = g.current_player();
		auto state = g.get_state();
		g.playout(mt);
		std::cout << "value: " << g.value(player) << std::endl << g.to_string() << std::endl;
		g.set_state(state);
		std::string wait;
		getline(std::cin, wait);
	}
}

template<typename Game>
void test_two_players_game<Game>::play(Game g)
{
	int player = 0;
	std::cout << "play one game" << std::endl;
	while (!g.end_of_game()) 
	{
		std::cout << g.to_string() << std::endl;
		std::cout << g.player_to_string(player) << " move: ";
		std::map<std::string, int> m;
		for (int i = 0; i < g.number_of_moves(); ++i) 
		{
			m[g.move_to_string(i)] = i;
		}
		std::string move;
		std::cin >> move;
		g.play(m[move]);
		player = 1 - player;
	}
	std::cout << g.to_string() << std::endl;
	if (g.won(0)) std::cout << g.player_to_string(0) << " won";
	else if (g.won(1)) std::cout << g.player_to_string(1) << " won";
	else std::cout << "draw";
	std::cout << std::endl;
}

}
#endif
