#ifndef __MCTS_TWO_PLAYERS_HPP__
#define __MCTS_TWO_PLAYERS_HPP__

#include "mcts.hpp"
#include "allocator.hpp"
#include "fast_log.hpp"
#include "omp_util.hpp"
#include "display_node.hpp"
#include <fstream>
#include <vector>
#include "openings.hpp"

namespace mcts
{
	template <typename Game>
	class mcts_two_players : public mcts<Game>
	{
		allocator alloc_;
		const util::fast_log fast_log_;
		const float C_;
		const unsigned int nb_visits_before_expansion_;
		const bool new_version_;

		inline node* select(const std::shared_ptr<Game>& game, std::mt19937& generator, node* parent);
		inline void expand(const std::shared_ptr<Game>& game, node* n);
		void think(const std::shared_ptr<Game>& game);
	public:
		mcts_two_players(Game& game, uint32_t milliseconds, float C, unsigned int nb_visits_before_expansion = 8, bool new_version = true);
		void reset();
		void init_with_openings(const openings& o);
		inline uint16_t select_move();
		void last_move(uint16_t move);
		void last_moves(uint16_t computer, uint16_t other);
	};

	template <typename Game>
	mcts_two_players<Game> make_mcts_two_players(Game& game, uint32_t milliseconds, float C, unsigned int nb_visits_before_expansion = 8, bool new_version = true)
	{
		return mcts_two_players<Game>(game, milliseconds, C, nb_visits_before_expansion, new_version);
	}

	template <typename Game>
	mcts_two_players<Game>::mcts_two_players(Game& game, uint32_t milliseconds, float C, unsigned int nb_visits_before_expansion, bool new_version)
		: mcts<Game>(game, milliseconds), C_(C), nb_visits_before_expansion_(nb_visits_before_expansion), new_version_(new_version)
	{
			this->generators.assign(util::omp_util::get_num_threads(), std::mt19937());
			this->root = alloc_.allocate(1);
		}

	template <typename Game>
	void mcts_two_players<Game>::reset()
	{
		alloc_.clear();
		this->root = alloc_.allocate(1);
	}

	template <typename Game>
	void mcts_two_players<Game>::init_with_openings(const openings& o)
	{
		o.copy_to(this->root, alloc_);
	}

	template <typename Game>
	node* mcts_two_players<Game>::select(const std::shared_ptr<Game>& game, std::mt19937& generator, node* parent)
	{
		using namespace std;
		const unsigned int N = parent->get_statistics().count;
		const float log_of_N = fast_log_.log(N);
		const uint16_t nb_children = parent->get_number_of_children();
		uniform_int_distribution<uint16_t> d(0, nb_children - 1);
		uint16_t k = d(generator);
		double best_value_so_far = numeric_limits<double>::lowest();
		uint16_t best_move_so_far = k;
		node* const children = parent->get_children();
		node* best_child_so_far = children + k;
		unsigned int count;
		float v;
		for (uint16_t i = 0; i < nb_children; ++i)
		{
			node* child = children + k;
			count = child->get_statistics().count;
			v = -child->get_statistics().value + C_ * sqrt(log_of_N / count);
			if (v > best_value_so_far)
			{
				best_value_so_far = v;
				best_child_so_far = child;
				best_move_so_far = k;
			}
			++k;
			if (k == nb_children) k = 0;
		}
		if (best_child_so_far->is_proven())
		{
			if (best_child_so_far->is_lost()) parent->set_won();
			else
			{
				bool all_won = true;
				for (uint16_t i = 0; i < nb_children; ++i)
				{
					node* child = children + i;
					if (!child->is_won())
					{
						all_won = false;
						break;
					}
				}
				if (all_won) parent->set_lost();
			}
		}
		game->play(best_move_so_far);
		return best_child_so_far;
	}

	template <typename Game>
	void mcts_two_players<Game>::expand(const std::shared_ptr<Game>& game, node* n)
	{
		unsigned int count = n->get_statistics().count;
		if (count >= nb_visits_before_expansion_ && !n->test_and_set())
		{
			unsigned int nb_children = game->number_of_moves();
			node* children = alloc_.allocate(nb_children);
			for (unsigned int i = 0; i < nb_children; ++i)
			{
				node* child = children + i;
				child->get_statistics_ref().count = 1;
				child->get_statistics_ref().value = 0;
			}
			n->set_children(children);
			n->set_number_of_children(nb_children);
		}
	}

	template <typename Game>
	void mcts_two_players<Game>::think(const std::shared_ptr<Game>& game)
	{
		using namespace std;
		const chrono::steady_clock::time_point start = chrono::steady_clock::now();
		chrono::steady_clock::time_point now;
		mt19937& generator = mcts<Game>::generators[util::omp_util::get_thread_num()];
		auto state = game->get_state();
		vector<node*> visited(200);
		vector<uint16_t> moves(200);
		unsigned int nb_iter = 0;
		do
		{
			int size = 1;
			node* current = this->root;
			visited[0] = current;
			while (!game->end_of_game() && !current->is_leaf() && !current->is_proven())
			{
				current = select(game, generator, current);
				visited[size++] = current;
			}
			int game_value = 0;
			if (current->is_proven())
			{
				if (current->is_won()) game_value = 1;
				else
				{
					game_value = -1;
				}
			}
			else if (game->end_of_game())
			{
				int v = game->value_for_current_player();
				if (v > 0)
				{
					game_value = 1;
					if (new_version_) current->set_won();
				}
				else if (v < 0)
				{
					game_value = -1;
					if (new_version_)
					{
						current->set_lost();
						if (size > 1) visited[size - 2]->set_won();
					}
				}
			}
			else
			{
				uint8_t player = game->current_player();
				expand(game, current);
				game->playout(generator);
				int v = game->value(player);
				if (v > 0) game_value = 1;
				else if (v < 0) game_value = -1;
			}
			for (int i = size - 1; i >= 0; --i)
			{
				visited[i]->update(game_value);
				game_value = -game_value;
			}
			game->set_state(state);
			++nb_iter;
			if ((nb_iter & 0x3F) == 0) now = chrono::steady_clock::now();
		} while ((nb_iter & 0x3F) != 0 || now < start + this->milliseconds);
	}

	template <typename Game>
	uint16_t mcts_two_players<Game>::select_move()
	{
		using namespace std;
		if (!this->root->is_proven())
		{
#pragma omp parallel
			think(game::copy(this->game));
		}
		// std::ofstream ofs ("graph.gv", ofstream::out);
		//    util::display_node::node_to_dot(ofs, this->root, 1000, 50);
		util::display_node::node_to_ascii(cout, this->root, 1);
		//    std::cout << "finished " << new_version_ << std::endl;
		// string _;
		// getline(cin, _);
		unsigned int best_count_so_far = 0;
		uint16_t nb_children = this->root->get_number_of_children();
		uniform_int_distribution<uint16_t> d(0, nb_children - 1);
		uint16_t k = d(this->generators[0]);
		uint16_t best_move_so_far = k;
		node* children = this->root->get_children();
		unsigned int c;
		for (uint16_t i = 0; i < nb_children; ++i)
		{
			node *child = children + k;
			if (child->is_lost())
			{
				best_move_so_far = k;
				break;
			}
			c = children[k].get_statistics().count;
			if (c > best_count_so_far)
			{
				best_count_so_far = c;
				best_move_so_far = k;
			}
			++k;
			if (k == nb_children) k = 0;
		}
		return best_move_so_far;
	}

	template <typename Game>
	void mcts_two_players<Game>::last_moves(uint16_t computer, uint16_t other)
	{
		if (this->root->is_leaf() || this->root->get_children()[computer].is_leaf())
		{
			alloc_.clear();
			this->root = alloc_.allocate(1);
		}
		else
		{
			this->root = alloc_.move(&this->root->get_children()[computer].get_children()[other]);
		}
	}

	template <typename Game>
	void mcts_two_players<Game>::last_move(uint16_t move)
	{
		if (this->root->is_leaf())
		{
			alloc_.clear();
			this->root = alloc_.allocate(1);
		}
		else
		{
			this->root = alloc_.move(&this->root->get_children()[move]);
		}
	}

}

#endif
