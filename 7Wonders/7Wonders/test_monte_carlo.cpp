#include "monte_carlo.hpp"
#include "test_monte_carlo.hpp"
#include <iostream>
#include <map>

#include "MCTSImplementation.h"

using namespace std;
using namespace game;

namespace monte_carlo
{
	test_monte_carlo::test_monte_carlo()
	{    
		play();
	}

	template <typename Game>
	void test_monte_carlo::select_move(Game& game)
	{
		cout << game.player_to_string(game.current_player()) << " move: ";
		map<string, int> m;
		for (int i = 0; i < game.number_of_moves(); ++i) 
		{
			m[game.move_to_string(i)] = i;
		}
		string move;
		cin >> move;
		game.play(m[move]);
	}

	void test_monte_carlo::play()
	{
		/*MCTSImplementation c4;
		auto mc = make_monte_carlo(c4, 80000, 2000);
		cout << "play one game" << endl;
		cout << "who's first? (h)uman/(c)omputer ";
		string ans;
		cin >> ans;
		cout << c4 << endl;
		while (!c4.end_of_game()) 
		{       
			if ((ans == "h" && c4.current_player() == 0) || (ans == "c" && c4.current_player() == 1))
			{
				select_move(c4);
			}
			else
			{
				uint16_t move = mc.select_move();
				cout << c4.player_to_string(c4.current_player()) << " move: " << c4.move_to_string(move) << endl;
				c4.play(move);
			}
			cout << c4 << endl;
		}
		if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
		else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
		else cout << "draw";
		cout << endl;*/
	}
}
