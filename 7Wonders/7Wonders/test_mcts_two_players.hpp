#ifndef __TEST_MCTS_TWO_PLAYERS_HPP__
#define __TEST_MCTS_TWO_PLAYERS_HPP__

#include "openings.hpp"
#include "mcts_two_players.hpp"
#include <string>
#include <iostream>
#include <map>
#include <iomanip>
#include <set>
#include <fstream>

namespace mcts
{
	template <typename Game>
	class test_mcts_two_players
	{
		openings openings_;

		void play(Game g);
		void self_play(Game g);
		void self_play(Game g, int n, bool with_openings = false);
		void self_play_learn_openings(Game g, int n);
		void test_openings(Game g, int nb_learning, int nb_testing);
		int select_move(Game& game);
	public:
		test_mcts_two_players(const Game& g);
	};

	template <typename Game>
	test_mcts_two_players<Game>::test_mcts_two_players(const Game& g) : openings_(g)
	{
		//self_play(g, 1000);
		play(g);
		//test_openings(g, 10000, 1000);
	}

	template <typename Game>
	void run_test_mcts_two_players(const Game& g)
	{
		test_mcts_two_players<Game>{g};
	}


	template <typename Game>
	void test_mcts_two_players<Game>::test_openings(Game g, int nb_learning, int nb_testing)
	{
		//    self_play(g, nb_testing);
		self_play_learn_openings(g, nb_learning);
		self_play(g, nb_testing, true);
	}

	template <typename Game>
	int test_mcts_two_players<Game>::select_move(Game& game)
	{
		std::cout << game.player_to_string(game.current_player()) << " move: ";
		std::map<std::string, int> m;
		for (int i = 0; i < game.number_of_moves(); ++i)
		{
			m[game.move_to_string(i)] = i;
		}
		std::string move;
		getline(std::cin, move);
		game.play(m[move]);
		return m[move];
	}

	template <typename Game>
	void test_mcts_two_players<Game>::play(Game g)
	{
		//    ProfilerStart("theturk.prof");
		auto the_turk = make_mcts_two_players(g, 5000, 0.3f, 4);
		std::cout << "play one game" << std::endl;
		std::cout << "who's first? (h)uman/(c)omputer ";
		std::string ans;
		getline(std::cin, ans);
		std::cout << g.to_string() << std::endl;
		int human_last_move = -1, computer_last_move = -1;
		while (!g.end_of_game())
		{
			if ((ans == "h" && g.current_player() == 0) || (ans == "c" && g.current_player() == 1))
			{
				human_last_move = select_move(g);
			}
			else
			{
				if (human_last_move != -1 && computer_last_move != -1)
				{
					the_turk.last_moves(computer_last_move, human_last_move);
				}
				uint16_t move = the_turk.select_move();
				computer_last_move = move;
				std::cout << g.player_to_string(g.current_player()) << " move: " << g.move_to_string(move) << std::endl;
				g.play(move);
			}
			std::cout << g << std::endl;
		}
		if (g.won(0)) std::cout << g.player_to_string(0) << " won";
		else if (g.won(1)) std::cout << g.player_to_string(1) << " won";
		else std::cout << "draw";
		std::cout << std::endl;
		//    ProfilerStop();
	}

	template <typename Game>
	void test_mcts_two_players<Game>::self_play_learn_openings(Game g, int n)
	{
		std::vector<uint16_t> moves(200);
		auto state = g.get_state();
		auto the_turk_1 = make_mcts_two_players(g, 1000, 0.6, 2);
		auto the_turk_2 = make_mcts_two_players(g, 1000, 0.6, 2);
		std::map<std::set<int>, std::pair<std::uint32_t, double>> learning_examples;
		for (int i = 0; i < n; ++i)
		{
			std::cout << i << std::endl;
			std::cout << openings_ << std::endl << std::endl;
			moves.clear();
			g.set_state(state);
			the_turk_1.reset();
			the_turk_1.init_with_openings(openings_);
			the_turk_2.reset();
			the_turk_2.init_with_openings(openings_);
			int the_turk_1_last_move = -1, the_turk_2_last_move = -1;
			int k = 0;
			while (!g.end_of_game())
			{
				if (k == 1) the_turk_2.last_move(the_turk_1_last_move);
				if (k % 2 == 0)
				{
					if (the_turk_2_last_move != -1)
					{
						the_turk_1.last_moves(the_turk_1_last_move, the_turk_2_last_move);
					}
					std::uint16_t move = the_turk_1.select_move();
					moves.push_back(move);
					the_turk_1_last_move = move;
					g.play(move);
				}
				else
				{
					if (the_turk_2_last_move != -1)
					{
						the_turk_2.last_moves(the_turk_2_last_move, the_turk_1_last_move);
					}
					std::uint16_t move = the_turk_2.select_move();
					moves.push_back(move);
					the_turk_2_last_move = move;
					g.play(move);
				}
				++k;
			}
			std::cout << g.to_string() << std::endl;
			int v = g.value(0);
			std::cout << "value for first player " << v << std::endl;
			g.set_state(state);
			openings_.update(g, moves, v);
			g.set_state(state);
			for (std::uint16_t m : moves)
			{
				g.play(m);
				v = -v;
				std::set<int> input_vector = std::move(g.to_input_vector());
				auto it = learning_examples.find(input_vector);
				if (it == learning_examples.end())
				{
					learning_examples[input_vector] = std::make_pair(1, v);
				}
				else
				{
					it->second.second = (it->second.second * it->second.first + v) / (it->second.first + 1);
					it->second.first += 1;
				}
			}
		}
		std::cout << "number of learning examples: " << learning_examples.size() << std::endl;
		std::ofstream output("learning_examples.txt");
		for (const auto& example : learning_examples)
		{
			output << example.second.second;
			for (int index : example.first)
			{
				output << " " << index << ":" << 1;
			}
			output << std::endl;
		}
		output.close();
	}

	template <typename Game>
	void test_mcts_two_players<Game>::self_play(Game g, int n, bool with_openings)
	{
		auto state = g.get_state();
		auto the_turk_v1 = make_mcts_two_players(g, 1000, 0.6, 2);
		auto the_turk_v2 = make_mcts_two_players(g, 1000, 0.6, 2);
		int nb_win_v1 = 0, nb_win_v2 = 0, nb_draw = 0;
		for (int i = 0; i < n; ++i)
		{
			std::cout << i << std::endl;
			g.set_state(state);
			the_turk_v1.reset();
			the_turk_v2.reset();
			if (with_openings) the_turk_v2.init_with_openings(openings_);
			int the_turk_v1_last_move = -1, the_turk_v2_last_move = -1;
			int k = 0;
			while (!g.end_of_game())
			{
				if (with_openings && k == 1 && i % 2 == 0) the_turk_v2.last_move(the_turk_v1_last_move);
				++k;
				//	    cout << c4 << endl;
				if ((i % 2 == 0 && g.current_player() == 0) || (i % 2 == 1 && g.current_player() == 1))
				{
					if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
					{
						the_turk_v1.last_moves(the_turk_v1_last_move, the_turk_v2_last_move);
					}
					std::uint16_t move = the_turk_v1.select_move();
					the_turk_v1_last_move = move;
					g.play(move);
				}
				else
				{
					if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
					{
						the_turk_v2.last_moves(the_turk_v2_last_move, the_turk_v1_last_move);
					}
					std::uint16_t move = the_turk_v2.select_move();
					the_turk_v2_last_move = move;
					play(move);
				}
			}
			if (g.won(0))
			{
				if (i % 2 == 0)
				{
					/*cout << "v1 won" << endl;*/ ++nb_win_v1;
				}
				else
				{
					/*cout << "v2 won" << endl;*/ ++nb_win_v2;
				}
			}
			else if (g.won(1))
			{
				if (i % 2 == 0)
				{
					/*cout << "v2 won" << endl;*/ ++nb_win_v2;
				}
				else
				{
					/*cout << "v1 won" << endl;*/ ++nb_win_v1;
				}
			}
			else
			{
				/*cout << "draw" << endl;*/ ++nb_draw;
			}
			std::cout << std::setw(10) << "v1 nb wins: " << nb_win_v1 << " v2 nb wins: " << nb_win_v2 << " nb draws: " << nb_draw << std::endl;
		}
	}

	template <typename Game>
	void test_mcts_two_players<Game>::self_play(Game g)
	{
		auto the_turk_v1 = make_mcts_two_players(g, 1000, 1.2, 2);
		auto the_turk_v2 = make_mcts_two_players(g, 1000, 1.2, 2);
		std::cout << "play one game" << std::endl;
		std::cout << "who's first? the_turk_(v1)/the_turk_(v2) ";
		std::string ans;
		getline(std::cin, ans);
		std::cout << g << std::endl;
		int the_turk_v1_last_move = -1, the_turk_v2_last_move = -1;
		while (!g.end_of_game())
		{
			if ((ans == "v1" && g.current_player() == 0) || (ans == "v2" && g.current_player() == 1))
			{
				if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
				{
					the_turk_v1.last_moves(the_turk_v1_last_move, the_turk_v2_last_move);
				}
				std::uint16_t move = the_turk_v1.select_move();
				the_turk_v1_last_move = move;
				std::cout << g.player_to_string(g.current_player()) << " move: " << g.move_to_string(move) << std::endl;
				g.play(move);
			}
			else
			{
				if (the_turk_v1_last_move != -1 && the_turk_v2_last_move != -1)
				{
					the_turk_v2.last_moves(the_turk_v2_last_move, the_turk_v1_last_move);
				}
				std::uint16_t move = the_turk_v2.select_move();
				the_turk_v2_last_move = move;
				std::cout << g.player_to_string(g.current_player()) << " move: " << g.move_to_string(move) << std::endl;
				g.play(move);
			}
			std::cout << g << std::endl;
		}
		if (g.won(0)) std::cout << g.player_to_string(0) << " won";
		else if (g.won(1)) std::cout << g.player_to_string(1) << " won";
		else std::cout << "draw";
		std::cout << std::endl;
	}

}

#endif
