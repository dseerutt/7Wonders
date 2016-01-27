#pragma once

#include "openings.hpp"
#include "mcts_two_players.hpp"

#include "MCTSImplementation.h"

#include <string>
#include <iostream>
#include <map>
#include <iomanip>
#include <set>
#include <fstream>

namespace mcts
{
	class MCTS_test
	{
	public:
		MCTS_test(MCTSImplementation& g);
	private:
		openings openings_;

		void play(MCTSImplementation& g);
		void self_play(MCTSImplementation& g);
		void self_play(MCTSImplementation& g, int n, bool with_openings = false);
		void self_play_learn_openings(MCTSImplementation& g, int n);
		void test_openings(MCTSImplementation& g, int nb_learning, int nb_testing);
		int select_move(MCTSImplementation& game);
	};
}