#include "test_game.h"
#include "MCTSImplementation.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace game
{
	test_game::test_game()
	{
		//playout();
		play();
	}

	void test_game::playout()
	{
		/*mt19937 mt;
		MCTSImplementation c4;
		cout << "playout" << endl;
		for (int i = 0; i < 100; ++i)
		{
			uint8_t player = c4.current_player();
			auto state = c4.get_state();
			c4.playout(mt);
			cout << "value: " << c4.value(player) << endl << c4 << endl;
			c4.set_state(state);
			string wait;
			getline(cin, wait);
		}*/
	}

	void test_game::play()
	{
		/*MCTSImplementation c4;
		int player = 0;
		cout << "play one game" << endl;
		while (!c4.end_of_game())
		{
			cout << c4 << endl;
			cout << c4.player_to_string(player) << " move: ";
			map<string, int> m;
			for (int i = 0; i < c4.number_of_moves(); ++i)
			{
				m[c4.move_to_string(i)] = i;
			}
			string move;
			cin >> move;
			c4.play(m[move]);
			player = 1 - player;
		}
		cout << c4 << endl;
		if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
		else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
		else cout << "draw";
		cout << endl;*/

		MCTSImplementation g;
		int player = 0;
		std::cout << "play one game" << std::endl;
		while (!g.end_of_game())
		{
			std::cout << g.to_string_before() << std::endl;
			std::cout << g.player_to_string(player) << " move: ";
			std::map<std::string, int> m;
			for (int i = 0; i < g.number_of_moves(); ++i)
			{
				m[g.move_to_string(i)] = i;
			}
			std::string move;
			std::cin >> move;
			g.play(m[move]);

			std::cout << g.to_string_after() << std::endl;
			g.display();
			player = 1 - player;
		}
		g.displayResults();
		if (g.won(0)) std::cout << g.player_to_string(0) << " won";
		else if (g.won(1)) std::cout << g.player_to_string(1) << " won";
		else std::cout << "draw";
		std::cout << std::endl;
	}
}
