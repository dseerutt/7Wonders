#ifndef __MONTE_CARLO_HPP__
#define __MONTE_CARLO_HPP__

#include "game.hpp"
#include <random>
#include <chrono>
#include <vector>
#include "omp_util.hpp"
#include <iostream>
#include <algorithm>

namespace monte_carlo
{
	template <typename Game>
	class monte_carlo
	{
		Game& game;
		uint32_t batch_size;
		std::chrono::milliseconds milliseconds;
		std::vector<std::mt19937> generators;

	public:
		monte_carlo(Game& game, uint32_t batch_size, uint32_t milliseconds);
		uint16_t select_move();
	};

	template <typename Game>
	uint16_t monte_carlo<Game>::select_move()
	{
		using namespace std;
		uint8_t current_player = game.current_player();
		uint16_t nb_moves = game.number_of_moves();
		vector<int> values(game.number_of_moves(), 0);
		const chrono::steady_clock::time_point start = chrono::steady_clock::now();
		chrono::steady_clock::time_point now;
		vector<shared_ptr<Game>> games(util::omp_util::get_num_threads(), nullptr);
		transform(games.begin(), games.end(), games.begin(), [this](const shared_ptr<Game>& _){ return copy(this->game); });
		do
		{
#pragma omp parallel for	
			for (uint16_t move = 0; move < nb_moves; ++move)
			{
				int thread_num = util::omp_util::get_thread_num();
				mt19937& generator = generators[thread_num];
				shared_ptr<Game> g = games[thread_num];
				for (uint32_t i = 0; i < batch_size; ++i)
				{
					auto state = g->get_state();
					g->play(move);
					g->playout(generator);
					values[move] += g->value(current_player);
					g->set_state(state);
				}
			}
			now = chrono::steady_clock::now();
			//	cout << chrono::duration_cast<chrono::milliseconds>(now - start).count() << endl;
		} while (now < start + milliseconds);

		int best_value_so_far = numeric_limits<int>::min();
		uint16_t best_move_so_far = -1;
		for (uint16_t move = 0; move < nb_moves; ++move)
		{
			cout << "(" << game.move_to_string(move) << ", " << values[move] << ") ";
			if (values[move] > best_value_so_far)
			{
				best_value_so_far = values[move];
				best_move_so_far = move;
			}
		}
		cout << endl;
		return best_move_so_far;
	}

	template <typename Game>
	monte_carlo<Game> make_monte_carlo(Game& game, uint32_t batch_size, uint32_t milliseconds)
	{
		return monte_carlo<Game>(game, batch_size, milliseconds);
	}

	template <typename Game>
	monte_carlo<Game>::monte_carlo(Game& game, uint32_t batch_size, uint32_t milliseconds)
		: game(game), batch_size(batch_size), milliseconds(milliseconds)
	{
		using namespace std;
		int num_threads = util::omp_util::get_num_threads();
		for (int i = 0; i < num_threads; ++i)
		{
			generators.push_back(mt19937(chrono::system_clock::now().time_since_epoch().count()));
		}
	}

}

#endif
